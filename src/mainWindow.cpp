#include "mainWindow.h"
#include "process.h"
#include "util.h"

#include <wx/aboutdlg.h>

BEGIN_EVENT_TABLE(mainWindow, wxFrame)
EVT_TIMER(ID_EVERY_TICK_TIMER, mainWindow::OnEveryTick)
EVT_BUTTON(ID_SET_KEYS_BUTTON, mainWindow::OnSetRefreshKeys)
EVT_BUTTON(ID_SET_INTERVAL, mainWindow::OnSetInterval)
EVT_CHECKBOX(ID_AUTO_REFRESH_CHECK_BOX, mainWindow::OnRefreshCheckBox)
EVT_MENU(ID_CHOOSE_CURRENT, mainWindow::OnShowCurrenCheck)
EVT_MENU(ID_CHOOSE_DEAD, mainWindow::OnShowDeadCheck)
EVT_MENU(ID_PAUSE_ON_CLICK, mainWindow::OnPauseOnClick)
EVT_MENU(ID_SELECT_PROCESS, mainWindow::OnChooseProcess)
EVT_MENU(wxID_HELP, mainWindow::OnHelp)
EVT_MENU(wxID_ABOUT, mainWindow::OnAbout)
EVT_CLOSE(mainWindow::OnClose)
END_EVENT_TABLE()

static const wxSize ListInitSize = wxSize(650, 300);

mainWindow::mainWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxSize& size, long style)
    : wxFrame(parent, id, title, wxDefaultPosition, size, style)
{
    if (!wxSystemSettings::GetAppearance().IsDark())
        this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));

    _InfoBar = this->CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);

    wxBoxSizer* GlobalSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* KeySizer = new wxBoxSizer(wxHORIZONTAL);

    KeySizer->Add(new wxStaticText(this, wxID_ANY, wxT("设置刷新快捷键")), 0, wxALL, 5);

    _refresh_key_1 = new wxTextCtrl(this, ID_KEY_1);
    KeySizer->Add(_refresh_key_1, 0, wxALL, 5);

    KeySizer->Add(new wxStaticText(this, wxID_ANY, "+"), 0, wxALL, 5);

    _refresh_key_2 = new wxTextCtrl(this, ID_KEY_2);
    KeySizer->Add(_refresh_key_2, 0, wxALL, 5);

    KeySizer->Add(new wxStaticText(this, wxID_ANY, "+"), 0, wxALL, 5);

    _refresh_key_3 = new wxTextCtrl(this, ID_KEY_3);
    KeySizer->Add(_refresh_key_3, 0, wxALL, 5);

    _SetKeyButton = new wxButton(this, ID_SET_KEYS_BUTTON, wxT("设置"));
    KeySizer->Add(_SetKeyButton, 0, wxALL, 5);

    GlobalSizer->Add(KeySizer, 1, wxEXPAND, 5);

    wxBoxSizer* SetIntervalSizer = new wxBoxSizer(wxHORIZONTAL);

    SetIntervalSizer->Add(new wxStaticText(this, wxID_ANY, wxT("设置刷新间隔(cs)")), 0, wxALL, 5);

    _intervalValue = new wxTextCtrl(this, ID_INTERVAL_VALUE, "10");
    SetIntervalSizer->Add(_intervalValue, 0, wxALL, 5);

    _SetIntervalButton = new wxButton(this, ID_SET_INTERVAL, wxT("设置"));
    SetIntervalSizer->Add(_SetIntervalButton, 0, wxALL, 5);

    _AutoRefreshCheckBox = new wxCheckBox(this, ID_AUTO_REFRESH_CHECK_BOX, wxT("自动刷新"));
    SetIntervalSizer->Add(_AutoRefreshCheckBox, 0, wxALL, 5);

    GlobalSizer->Add(SetIntervalSizer, 1, wxEXPAND, 5);

    wxBoxSizer* NextKeySizer = new wxBoxSizer(wxHORIZONTAL);

    NextKeySizer->Add(new wxStaticText(this, wxID_ANY, "Next Key:"), 0, wxALL, 5);

    _NextKeyText = new wxStaticText(this, ID_NEXT_KEY, "unknown");
    NextKeySizer->Add(_NextKeyText, 0, wxALL, 5);

    NextKeySizer->Add(new wxStaticText(this, wxID_ANY, "Max Size:"), 0, wxALL, 5);

    _MaxSizeText = new wxStaticText(this, ID_MAX_SIZE, "unknown");
    NextKeySizer->Add(_MaxSizeText, 0, wxALL, 5);

    NextKeySizer->Add(new wxStaticText(this, wxID_ANY, "Next Index List:"), 0, wxALL, 5);

    _IndexListText = new wxStaticText(this, ID_INDEX_LIST, "unknown");
    NextKeySizer->Add(_IndexListText, 0, wxALL, 5);

    GlobalSizer->Add(NextKeySizer, 1, wxEXPAND, 5);

    _currentLable = new wxStaticText(this, ID_CURRENT_TEXT, "Current Array List");
    _currentList = new wxListCtrl(this, ID_CURRENT_LIST, wxDefaultPosition, ListInitSize, wxLC_REPORT | wxLC_HRULES | wxLC_VRULES);
    _deadLable = new wxStaticText(this, ID_DEAD_TEXT, "Dead Array List");
    _deadList = new wxListCtrl(this, ID_DEAD_LIST, wxDefaultPosition, ListInitSize, wxLC_REPORT | wxLC_HRULES | wxLC_VRULES);

    GlobalSizer->Add(_currentLable, 0, wxALL | wxEXPAND, 5);
    _currentList->InsertColumn(0, "Index", wxLIST_FORMAT_CENTER, 60);
    _currentList->InsertColumn(1, "ID", wxLIST_FORMAT_CENTER, 65);
    _currentList->InsertColumn(2, "Time", wxLIST_FORMAT_CENTER, 75);
    _currentList->InsertColumn(3, "Rate", wxLIST_FORMAT_CENTER, 75);
    _currentList->InsertColumn(4, "LoopType", wxLIST_FORMAT_CENTER, 265);
    _currentList->InsertColumn(5, "Type", wxLIST_FORMAT_CENTER, 160);
    GlobalSizer->Add(_currentList, 0, wxEXPAND | wxALL, 5);

    GlobalSizer->Add(_deadLable, 0, wxALL | wxEXPAND, 5);
    _deadList->InsertColumn(0, "Index", wxLIST_FORMAT_CENTER, 60);
    _deadList->InsertColumn(1, "ID", wxLIST_FORMAT_CENTER, 65);
    _deadList->InsertColumn(2, "Time", wxLIST_FORMAT_CENTER, 75);
    _deadList->InsertColumn(3, "Rate", wxLIST_FORMAT_CENTER, 75);
    _deadList->InsertColumn(4, "LoopType", wxLIST_FORMAT_CENTER, 265);
    _deadList->InsertColumn(5, "Type", wxLIST_FORMAT_CENTER, 160);
    GlobalSizer->Add(_deadList, 0, wxEXPAND | wxALL, 5);

    this->SetSizer(GlobalSizer);

    this->Layout();

    _MenuBar = new wxMenuBar;
    _ProcessMenu = new wxMenu;

    _chooseGame = new wxMenuItem(_ProcessMenu, ID_SELECT_PROCESS, wxT("手动选择进程"), wxT("手动选择进程"), wxITEM_NORMAL);
    _ProcessMenu->Append(_chooseGame);

    _ProcessMenu->AppendSeparator();

    _menuExit = new wxMenuItem(_ProcessMenu, wxID_EXIT, wxT("退出"), wxT("关闭本程序"), wxITEM_NORMAL);
    _ProcessMenu->Append(_menuExit);

    _MenuBar->Append(_ProcessMenu, wxT("程序"));

    _SettingsMenu = new wxMenu;

    _chooseCurrent = new wxMenuItem(_SettingsMenu, ID_CHOOSE_CURRENT, wxT("显示CurrentArrayList"), wxT("显示/隐藏 CurrentArrayList"), wxITEM_CHECK);
    _SettingsMenu->Append(_chooseCurrent);
    _chooseCurrent->Check(true);

    _SettingsMenu->AppendSeparator();

    _chooseDead = new wxMenuItem(_SettingsMenu, ID_CHOOSE_DEAD, wxT("显示DeadArrayList"), wxT("显示/隐藏DeadArrayList"), wxITEM_CHECK);
    _SettingsMenu->Append(_chooseDead);
    _chooseDead->Check(true);

    _SettingsMenu->AppendSeparator();

    _pauseOnClick = new wxMenuItem(_SettingsMenu, ID_PAUSE_ON_CLICK, wxT("点击列表时暂停/恢复刷新"), wxT("自动刷新模式下，左键点击列表暂停，右键点击列表恢复刷新"), wxITEM_CHECK);
    _SettingsMenu->Append(_pauseOnClick);
    _pauseOnClick->Check(false);

    _MenuBar->Append(_SettingsMenu, wxT("设置"));

    _menuHelp = new wxMenu;
    _MenuBar->Append(_menuHelp, wxT("帮助"));
    _menuHelp->Append(wxID_HELP);

    _menuAbout = new wxMenu;
    _MenuBar->Append(_menuAbout, wxT("关于"));
    _menuAbout->Append(wxID_ABOUT);

    this->SetMenuBar(_MenuBar);

    this->Centre(wxBOTH);

    _SetIntervalButton->Enable(_AutoRefreshCheckBox->IsChecked());

    Bind(wxEVT_MENU, [=, this](wxCommandEvent&) { Close(true); }, _menuExit->GetId());
    _currentList->Bind(wxEVT_LEFT_DOWN, &mainWindow::OnLeftDown, this);
    _currentList->Bind(wxEVT_RIGHT_DOWN, &mainWindow::OnRightDown, this);
    _deadList->Bind(wxEVT_LEFT_DOWN, &mainWindow::OnLeftDown, this);
    _deadList->Bind(wxEVT_RIGHT_DOWN, &mainWindow::OnRightDown, this);

    _key_refresh_timer = std::make_unique<wxTimer>(this, ID_EVERY_TICK_TIMER);
    _key_refresh_timer->Start(10);
    _Init();
}

mainWindow::~mainWindow()
{
    _key_refresh_timer->Stop();
}

void mainWindow::OnSetRefreshKeys(wxCommandEvent& event)
{
    auto key1 = _refresh_key_1->GetValue();
    auto key2 = _refresh_key_2->GetValue();
    auto key3 = _refresh_key_3->GetValue();
    _refreshKeys.clear();
    wxString info = wxT("快捷键 ");
    for (const auto& key : {key1, key2, key3}) {
        if (key.empty())
            continue;

        auto _key = key.Upper();
        if (!VirtualKeyMap.contains(_key)) {
            wxMessageBox(wxString::Format(wxT("未知的按键 %s , 已自动忽略。"), _key), wxT("快捷键绑定"), wxOK | wxICON_WARNING);
            continue;
        }
        _refreshKeys.push_back(VirtualKeyMap.at(_key));
        info += key + " ";
    }
    if (_refreshKeys.empty()) {
        info.clear();
        wxMessageBox(wxT("您尚未输入任何按键，快捷键绑定失败！"), wxT("快捷键绑定"), wxOK | wxICON_ERROR);
        return;
    }

    info += wxT(" 绑定成功。");
    SetStatusText(info);
}

void mainWindow::OnSetInterval(wxCommandEvent& event)
{
    int interval;
    if (_intervalValue->GetValue().ToInt(&interval)) {
        if (interval >= 1) {
            _interval = interval;
            wxMessageBox(wxString::Format(wxT("设置刷新间隔为 %ld cs成功。"), interval), wxT("PvZ Animation Monitor设置刷新间隔"), wxOK | wxICON_INFORMATION);
        } else {
            wxMessageBox(wxString::Format(wxT("设置刷新间隔失败，刷新间隔应为 ≥ 1的整数，当前您填入的值为 %ld cs"), interval), wxT("PvZ Animation Monitor设置刷新间隔"), wxOK | wxICON_ERROR);
        }
    } else
        wxMessageBox(wxT("设置刷新间隔失败"), wxT("PvZ Animation Monitor设置刷新间隔"), wxOK | wxICON_ERROR);
}

void mainWindow::OnShowCurrenCheck(wxCommandEvent& event)
{
    if (_chooseCurrent->IsChecked()) {
        if (!_deadList->IsShown()) {
            GetSizer()->SetItemMinSize(_currentList, 650, 600);
        }
        _currentLable->SetLabel("Current Array List");
        _currentList->Show();
    } else {
        _currentLable->SetLabel(wxT("Current Array List已隐藏"));
        _currentList->Hide();
        if (_deadList->IsShown()) {
            GetSizer()->SetItemMinSize(_deadList, 650, 600);
        }
    }
    if (_deadList->IsShown() && _currentList->IsShown()) {
        GetSizer()->SetItemMinSize(_currentList, ListInitSize);
        GetSizer()->SetItemMinSize(_deadList, ListInitSize);
    }
    this->Layout();
}

void mainWindow::OnShowDeadCheck(wxCommandEvent& event)
{
    if (_chooseDead->IsChecked()) {
        if (!_currentList->IsShown()) {
            GetSizer()->SetItemMinSize(_deadList, 650, 600);
        }
        _deadLable->SetLabel("Dead Array List");
        _deadList->Show();
    } else {
        if (_currentList->IsShown()) {
            GetSizer()->SetItemMinSize(_currentList, 650, 600);
        }
        _deadLable->SetLabel(wxT("Dead Array List已隐藏"));
        _deadList->Hide();
    }
    if (_deadList->IsShown() && _currentList->IsShown()) {
        GetSizer()->SetItemMinSize(_currentList, ListInitSize);
        GetSizer()->SetItemMinSize(_deadList, ListInitSize);
    }
    this->Layout();
}

void mainWindow::OnPauseOnClick(wxCommandEvent& event)
{
    if (!_pauseOnClick->IsChecked() && _isPaused)
        _isPaused = false;
}

void mainWindow::_AutoFindGame()
{
    if (_IsValid())
        return;

    HWND hWnd = ::FindWindow(NULL, L"Plants vs. Zombies");
    if (hWnd == NULL) {
        _InfoBar->SetStatusText(wxT("未找到PvZ进程"));
        return;
    }

    if (IsPvZProcess(hWnd)) {
        _Init(hWnd);
        wxMessageBox(wxT("已找到PvZ进程"), wxT("PvZ Animation Monitor自动寻找进程"), wxOK | wxICON_INFORMATION);
        _InfoBar->SetStatusText(wxT("已找到PvZ进程"));
    }
}

void mainWindow::OnChooseProcess(wxCommandEvent& event)
{
    _key_refresh_timer->Stop();
    auto dlg = std::make_unique<ProcessChoose>(nullptr);
    int result = dlg->ShowModal();
    if (result == wxID_OK) {
        _Init(dlg->GetSelectedHWND());
        wxMessageBox(wxT("已找到PvZ进程"), wxT("PvZ Animation Monitor选择进程"), wxOK | wxICON_INFORMATION);
    }
    dlg->Destroy();
    _key_refresh_timer->Start(10);
}

void mainWindow::OnRefreshCheckBox(wxCommandEvent& event)
{
    _SetIntervalButton->Enable(_AutoRefreshCheckBox->IsChecked());
}

void mainWindow::OnEveryTick(wxTimerEvent& event)
{
    if (!_IsValid()) {
        _AutoFindGame();
        return;
    }
    if (!_isPaused && _AutoRefreshCheckBox->IsChecked()) {
        _count++;
        if (_count >= _interval) {
            _count = 0;
            _PrintList();
            _DisplayStatus();
        }
    }
    if (GetIsKeysDown(_hWnd, _refreshKeys)) {
        _PrintList();
        _DisplayStatus();
    }
}

void mainWindow::OnClose(wxCloseEvent& event)
{
    _key_refresh_timer->Stop();
    event.Skip();
}

void mainWindow::OnLeftDown(wxMouseEvent& event)
{
    if (!_pauseOnClick->IsChecked()) {
        _isPaused = false;
        return;
    }
    wxListCtrl* listCtrl = dynamic_cast<wxListCtrl*>(event.GetEventObject());
    if (listCtrl) {
        auto item = this->HitTest(event.GetPosition());
        if (item == wxHT_WINDOW_INSIDE) {
            _isPaused = true;
        }
    }
}

void mainWindow::OnRightDown(wxMouseEvent& event)
{
    if (!_pauseOnClick->IsChecked()) {
        _isPaused = false;
        return;
    }
    wxListCtrl* listCtrl = dynamic_cast<wxListCtrl*>(event.GetEventObject());
    if (listCtrl) {
        auto item = this->HitTest(event.GetPosition());
        if (item == wxHT_WINDOW_INSIDE) {
            _isPaused = false;
        }
    }
}

bool mainWindow::_IsValid()
{
    if (!IsPvZProcess(_hWnd))
        return false;

    DWORD dwPid = 0;
    ::GetWindowThreadProcessId(_hWnd, &dwPid);
    if (dwPid == -1)
        return false;

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
    return hProcess;
}

void mainWindow::_Init(HWND hWnd)
{
    _hWnd = hWnd;
    hProcess = 0;
    aBuffer = 0;
    aBase = 0, aEffect = 0, aDataArray = 0, aReanimationArray = 0;
    aNextKey = 0, aNextIndex = 0, aMaxIndex = 0;
}

void mainWindow::_DisplayStatus()
{
    if (!_IsValid())
        return;

    ReadProcessMemory(hProcess, (LPVOID)(aDataArray + 0x14), &aNextKey, 4, &aBuffer);
    ReadProcessMemory(hProcess, (LPVOID)(aDataArray + 0x4), &aMaxIndex, 4, &aBuffer);
    ReadProcessMemory(hProcess, (LPVOID)(aDataArray + 0xC), &aNextIndex, 4, &aBuffer);
    _NextKeyText->SetLabel(wxString::Format("0x%04X ", aNextKey));

    std::vector<DWORD> indexList;
    indexList.push_back(aNextIndex);
    while (aNextIndex <= aMaxIndex) {
        _DataArrayGetNextIndex(aNextIndex, aMaxIndex);
        indexList.push_back(aNextIndex);
    }
    _MaxSizeText->SetLabel(wxString::Format("0x%04X ", aMaxIndex));

    wxString str;
    for (size_t i = 0; i < indexList.size(); ++i) {
        str += wxString::Format("0x%04X", indexList[i]);
        if (i < indexList.size() - 1)
            str += ", ";
        else
            str += "... ";
    }
    _IndexListText->SetLabel(str);
}

void mainWindow::_PrintList()
{
    if (!_IsValid())
        return;

    ReadProcessMemory(hProcess, (LPVOID)0x006A9EC0, &aBase, 4, &aBuffer);
    ReadProcessMemory(hProcess, (LPVOID)(aBase + 0x820), &aEffect, 4, &aBuffer);
    ReadProcessMemory(hProcess, (LPVOID)(aEffect + 0x8), &aDataArray, 4, &aBuffer);

    if (aBase == 0 || aEffect == 0 || aDataArray == 0) {
        CloseHandle(hProcess);
        return;
    }
    _currentList->DeleteAllItems();
    _deadList->DeleteAllItems();
    ReadProcessMemory(hProcess, (LPVOID)(aDataArray), &aReanimationArray, 4, &aBuffer);
    DWORD aArrayPtr = aReanimationArray;
    for (int i = 0; i < aMaxIndex; i++, aArrayPtr += 0xA0) {
        ReadProcessMemory(hProcess, (LPVOID)(aArrayPtr + 0x14), &aIsDead[i], 1, &aBuffer);
        if (!aIsDead[i])
            _OutReanimation(i, aArrayPtr, _currentList);
        else
            _OutReanimation(i, aArrayPtr, _deadList);
    }

    CloseHandle(hProcess);
}

void mainWindow::_OutReanimation(int index, DWORD& theAddress, wxListCtrl* list)
{
    if (!list->IsShown())
        return;

    DWORD aID, aLoopType, aType;
    float aTime, aRate;
    ReadProcessMemory(hProcess, (LPVOID)(theAddress + 0x9C), &aID, 4, &aBuffer);
    ReadProcessMemory(hProcess, (LPVOID)(theAddress + 0x0), &aType, 4, &aBuffer);
    ReadProcessMemory(hProcess, (LPVOID)(theAddress + 0x4), &aTime, 4, &aBuffer);
    ReadProcessMemory(hProcess, (LPVOID)(theAddress + 0x8), &aRate, 4, &aBuffer);
    ReadProcessMemory(hProcess, (LPVOID)(theAddress + 0x10), &aLoopType, 4, &aBuffer);

    long itemIndex = list->InsertItem(list->GetItemCount(), wxString::Format("0x%04X", index));
    list->SetItem(itemIndex, 1, wxString::Format("0x%04X", aID >> 16));
    list->SetItem(itemIndex, 2, wxString::Format("%6.3ff", aTime));
    list->SetItem(itemIndex, 3, wxString::Format("%6.3ff", aRate));
    list->SetItem(itemIndex, 4, LoopTimeName.contains(aLoopType) ? LoopTimeName.at(aLoopType) : "UNKNOWN");
    list->SetItem(itemIndex, 5, ReanimationName.contains(aType) ? ReanimationName.at(aType) : "UNKNOWN");
}

bool mainWindow::_DataArrayGetNextIndex(DWORD& theCurrent, DWORD theMax)
{
    if (theCurrent >= theMax) {
        theCurrent = theMax + 1;
        return false;
    }
    ReadProcessMemory(hProcess, (LPVOID)(aReanimationArray + theCurrent * 0xA0 + 0x9C), &theCurrent, 4, &aBuffer);
    if (theCurrent >= theMax) {
        theCurrent = theMax + 1;
        return false;
    }
    return true;
}

void mainWindow::OnHelp(wxCommandEvent& event)
{
    wxMessageBox(
        LR"(为pvz英文原版动画监测写的GUI界面，添加了若干小功能：
1.手动选择进程，用于支持多开pvz，不支持大部分改版及中文版，年度版（即使找到了游戏也不能保证兼容）；

2.选择显示Current和Dead列表，默认二者均显示，可在程序菜单栏上的“设置”中取消勾选；

3.在自动刷新模式下，设置刷新间隔，单位为cs，不建议将设置太小间隔，一是CPU占用可能会过高，二是人眼也难以获取信息。
  参考间隔：恶魂的动画监测刷新间隔为10cs，这也是本程序的默认刷新间隔；

4.快捷键绑定动画内存列表的刷新，支持键盘上的大部分按键以及组合键，不区分大小写，但不能有汉字和特殊字符；
  例如想绑定Ctrl+Shift+Z，即按下Ctrl+Shift+Z时刷新一次列表，三个输入框从左到右依次键入ctrl, shift, z即可；
  注意组合键最多绑定三个，三个输入框不必全填满, 当且仅当pvz窗口为顶层窗口时按下按键才会刷新列表。

5.点击列表时暂停/恢复刷新：自动刷新模式下，当鼠标左键在两个列表内任意位置点击时，暂停刷新；
  当鼠标右键在两个列表内任意位置点击时，恢复刷新；
  按键刷新不受影响。
  该功能可在程序菜单栏上的“设置”中选择是否启用。
)",
        wxT("PvZ Animation Monitor帮助"), wxOK | wxICON_INFORMATION);
}

void mainWindow::OnAbout(wxCommandEvent& event)
{
    wxAboutDialogInfo info;
    info.SetName("PvZ Animation Monitor");
    info.SetVersion("v1.0.4");
    info.SetDescription(LR"(
日期: 2025/07/16 12:50:19
开发工具: Visual Studio 2022, CMake, wxWidgets 3.3.0
鸣谢: Ghastasaucey
所有源代码位于: )");
    info.SetLicence(LR"(
The MIT License (MIT)

Copyright © 2025 TemporalShards

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the “Software”), to deal in the Software without
restriction, including without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
)");
    info.SetWebSite("https://github.com/TemporalShards/PvZ-Animation-Monitor");
    wxAboutBox(info, this);
}