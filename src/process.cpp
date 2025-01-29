/*
 * @Author: TemporalShards
 * @Date: 2024-10-04 21:29:21
 * @Last Modified by: TemporalShards
 * @Description：Finding process
 */
#include "process.h"
#include "util.h"

#include <Psapi.h>
#include <Shlwapi.h>
#include <wx/button.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>

bool IsPvZProcess(HWND hWnd)
{
    if (hWnd == NULL)
        return false;

    if (!IsWindowVisible(hWnd))
        return false;

    DWORD pid = 0;
    ::GetWindowThreadProcessId(hWnd, &pid);
    if (pid == -1)
        return false;

    auto handle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    if (handle == NULL)
        return false;

    if (ProcessChoose::ReadMemory<int>(handle, 0x45DC55) == 300 && ProcessChoose::ReadMemory<int>(handle, 0x45E445) == 4000
        && GetWindowTitle(hWnd) == "Plants vs. Zombies") {
        CloseHandle(handle);
        return true;
    }
    CloseHandle(handle);
    return false;
}

BOOL CALLBACK ProcessChoose::_EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
    ProcessChoose* windowEnum = (ProcessChoose*)lParam;

    DWORD processId;
    GetWindowThreadProcessId(hWnd, &processId);

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
    if (hProcess == NULL)
        return TRUE;

    wxString processName = L"";
    TCHAR processPath[MAX_PATH] = L"";
    if (GetProcessImageFileName(hProcess, processPath, MAX_PATH)) {
        processName = PathFindFileName(processPath);
    }
    CloseHandle(hProcess);

    ProcessInfo info;
    info.processId = processId;
    info.processName = processName;
    info.windowTitle = GetWindowTitle(hWnd);
    info.hWnd = hWnd;

    if (!windowEnum->_windowsInfo.empty())
        for (const auto& [id, name, title, hwnd] : windowEnum->_windowsInfo) {
            if (id == processId && name == processName && title == info.windowTitle)
                return TRUE;
        }

    windowEnum->_windowsInfo.push_back(info);

    return TRUE;
}

ProcessChoose::ProcessChoose(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, wxT("选择进程"), wxDefaultPosition, wxSize(600, 400))
    , _processList(new wxListView(this, wxID_ANY, wxDefaultPosition, wxSize(580, 340), wxLC_REPORT | wxLC_HRULES | wxLC_VRULES))
{
    _processList->InsertColumn(0, wxT("进程Id"), wxLIST_FORMAT_CENTER, 80);
    _processList->InsertColumn(1, wxT("进程名"), wxLIST_FORMAT_LEFT, 200);
    _processList->InsertColumn(2, wxT("窗口标题"), wxLIST_FORMAT_LEFT, 300);

    _RefreshList();

    wxButton* refreshButton = new wxButton(this, wxID_REFRESH, wxT("刷新"));
    wxButton* okButton = new wxButton(this, wxID_OK, wxT("确定"));
    wxButton* cancelButton = new wxButton(this, wxID_CANCEL, wxT("取消"));

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(refreshButton);
    buttonSizer->AddSpacer(60);
    buttonSizer->Add(okButton);
    buttonSizer->AddSpacer(60);
    buttonSizer->Add(cancelButton);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(_processList, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 5);

    SetSizer(mainSizer);
    mainSizer->Fit(this);

    okButton->Bind(wxEVT_BUTTON, &ProcessChoose::OnItemSelected, this, okButton->GetId());
    refreshButton->Bind(
        wxEVT_BUTTON, [=, this](wxCommandEvent&) { _RefreshList(); }, refreshButton->GetId());
    cancelButton->Bind(
        wxEVT_BUTTON, [=, this](wxCommandEvent&) { wxDialog::EndModal(wxID_CANCEL); }, cancelButton->GetId());
}

ProcessChoose::~ProcessChoose()
{
    _windowsInfo.clear();
    _processMap.clear();
    _processList->Destroy();
    ProcessChoose::Destroy();
}

void ProcessChoose::OnItemSelected(wxCommandEvent& event)
{
    int _selectedItem = _processList->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (_selectedItem >= 0) {
        _targetProcess = _processMap[_selectedItem];
        if (IsPvZProcess(_targetProcess.hWnd))
            wxDialog::EndModal(wxID_OK);
        else
            wxMessageBox(wxString::Format(wxT("您选择的进程不是有效的pvz进程，请重新选择。\n选中的进程信息:\n进程ID: %ld\n进程名: %s\n窗口标题: %s"), _targetProcess.processId, _targetProcess.processName, _targetProcess.windowTitle), wxT("进程信息"), wxOK | wxICON_INFORMATION);
    } else {
        wxMessageBox(wxT("请先选择一个进程。"), wxT("提示"), wxOK | wxICON_INFORMATION);
    }
}

void ProcessChoose::_RefreshList()
{
    _windowsInfo.clear();
    EnumWindows(_EnumWindowsProc, (LPARAM)this);
    auto processes = _windowsInfo;
    std::ranges::sort(processes, [=](const auto& process1, const auto& process2) {
        if (IsPvZProcess(process1.hWnd)) // pvz窗口优先
            return !IsPvZProcess(process2.hWnd);

        if (IsWindowVisible(process1.hWnd))
            return !IsWindowVisible(process2.hWnd);

        return process1.windowTitle != wxEmptyString && process2.windowTitle == wxEmptyString;
    });
    _processList->DeleteAllItems();
    _processMap.clear();
    int Mapidx = 0;
    for (const auto& process : processes) {
        int index = _processList->InsertItem(_processList->GetItemCount(), wxString::Format(wxT("%d"), process.processId));
        _processList->SetItem(index, 1, process.processName);
        _processList->SetItem(index, 2, process.windowTitle);
        _processMap[Mapidx] = process;
        Mapidx++;
    }
}