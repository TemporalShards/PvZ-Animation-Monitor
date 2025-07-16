/*
 * @Author: TemporalShards
 * @Date: 2025-01-24 21:31:22
 * @Last Modified by: TemporalShards
 * @Description：程序窗口相关控件和功能
 */
#pragma once
#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <wx/wx.h>
#include <wx/listctrl.h>

class mainWindow : public wxFrame {
private:
    void OnSetRefreshKeys(wxCommandEvent& event);
    void OnSetInterval(wxCommandEvent& event);
    void OnShowCurrenCheck(wxCommandEvent& event);
    void OnShowDeadCheck(wxCommandEvent& event);
    void OnPauseOnClick(wxCommandEvent& event);
    void OnRefreshCheckBox(wxCommandEvent& event);
    void OnChooseProcess(wxCommandEvent& event);
    void OnEveryTick(wxTimerEvent& event);
    void OnClose(wxCloseEvent& event);
    void OnHelp(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnRightDown(wxMouseEvent& event);

    void _AutoFindGame();
    void _OutReanimation(int index, DWORD& theAddress, wxListCtrl* list);
    bool _DataArrayGetNextIndex(DWORD& theCurrent, DWORD theMax);
    void _PrintList();
    void _DisplayStatus();
    bool _IsValid();
    void _Init(HWND hWnd = NULL);

    wxStatusBar* _InfoBar;
    wxTextCtrl* _refresh_key_1;
    wxTextCtrl* _refresh_key_2;
    wxTextCtrl* _refresh_key_3;
    wxButton* _SetKeyButton;
    wxTextCtrl* _intervalValue;
    wxButton* _SetIntervalButton;
    wxCheckBox* _AutoRefreshCheckBox;
    wxStaticText* _NextKeyText;
    wxStaticText* _MaxSizeText;
    wxStaticText* _IndexListText;
    wxMenuBar* _MenuBar;
    wxMenu* _ProcessMenu;
    wxMenuItem* _chooseGame;
    wxMenuItem* _menuExit;
    wxMenu* _SettingsMenu;
    wxMenu* _menuHelp;
    wxMenu* _menuAbout;
    wxListCtrl* _currentList;
    wxListCtrl* _deadList;
    wxStaticText* _currentLable;
    wxStaticText* _deadLable;
    wxMenuItem* _chooseCurrent;
    wxMenuItem* _chooseDead;
    wxMenuItem* _pauseOnClick;

    std::unique_ptr<wxTimer> _key_refresh_timer;

    std::vector<int> _refreshKeys;
    int _interval = 10;
    bool _isPaused;
    int _count = 0;

    HWND _hWnd;
    HANDLE hProcess;
    SIZE_T aBuffer;
    DWORD aBase, aEffect, aDataArray, aReanimationArray;
    DWORD aNextKey, aNextIndex, aMaxIndex;
    bool aIsDead[1024];

public:
    mainWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxSize& size, long style);

    ~mainWindow();

    DECLARE_EVENT_TABLE()
};

enum {
    ID_EVERY_TICK_TIMER = 0,
    ID_CURRENT_LIST,
    ID_DEAD_LIST,
    ID_SELECT_PROCESS,
    ID_KEY_1,
    ID_KEY_2,
    ID_KEY_3,
    ID_SET_KEYS_BUTTON,
    ID_INTERVAL_VALUE,
    ID_SET_INTERVAL,
    ID_AUTO_REFRESH_CHECK_BOX,
    ID_NEXT_KEY,
    ID_MAX_SIZE,
    ID_INDEX_LIST,
    ID_CURRENT_TEXT,
    ID_DEAD_TEXT,
    ID_CHOOSE_CURRENT,
    ID_CHOOSE_DEAD,
    ID_PAUSE_ON_CLICK,
};

#endif //!__MAINWINDOW_H__