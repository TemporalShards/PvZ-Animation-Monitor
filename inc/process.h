/*
 * @Author: TemporalShards
 * @Date: 2024-10-04 21:29:06
 * @Last Modified by: TemporalShards
 * @Description：About finding process
 */
#pragma once
#ifndef __PROCESS_H__
#define __PROCESS_H__

#include <wx/listctrl.h>
#include <wx/dialog.h>
#include <map>
#include <Tlhelp32.h>
#include <Windows.h>

bool IsPvZProcess(HWND hWnd);

class ProcessChoose : public wxDialog {
public:
    struct ProcessInfo {
        DWORD processId;
        wxString processName;
        wxString windowTitle;
        HWND hWnd;
    };

    ProcessChoose(wxWindow* parent);

    ~ProcessChoose();

    static wxString GetWindowTitle(HWND hWnd);

    template <typename T, typename... Args>
    static T ReadMemory(HANDLE hProcess, Args... args)
    {
        std::initializer_list<uintptr_t> lst = {static_cast<uintptr_t>(args)...};
        uintptr_t buff = 0;
        T result = T();
        for (auto it = lst.begin(); it != lst.end(); ++it) {
            if (it != lst.end() - 1)
                ReadProcessMemory(hProcess, (const void*)(buff + *it), &buff, sizeof(buff), nullptr);
            else
                ReadProcessMemory(hProcess, (const void*)(buff + *it), &result, sizeof(result), nullptr);
        }
        return result;
    }

    HWND GetSelectedHWND() { return _targetProcess.hWnd; }

private:
    static BOOL CALLBACK _EnumWindowsProc(HWND hWnd, LPARAM lParam);

    void OnItemSelected(wxCommandEvent& event);

    void _RefreshList();

    std::vector<ProcessInfo> _windowsInfo;
    wxListCtrl* _processList;
    ProcessInfo _targetProcess;
    std::map<int, ProcessInfo> _processMap;
};

#endif //!__PROCESS_H__