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

#include "monitor.h"

class mainWindow : public wxFrame {
private:
    void OnSetRefreshKeys(wxCommandEvent& event);
    void OnSetInterval(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
    void OnShowCurrenCheck(wxCommandEvent& event);
    void OnShowDeadCheck(wxCommandEvent& event);
    void OnRefreshCheckBox(wxCommandEvent& event);
    void OnChooseProcess(wxCommandEvent& event);
    void OnEveryTick(wxTimerEvent& event);
    void OnClose(wxCloseEvent& event);

    void OnHelp(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    void _AutoFindGame();

protected:
    wxStatusBar* _InfoBar;
    wxTextCtrl* _refresh_key_1;
    wxTextCtrl* _refresh_key_2;
    wxTextCtrl* _refresh_key_3;
    wxTextCtrl* _intervalValue;
    wxButton* _SetIntervalButton;
    wxCheckBox* _AutoRefreshCheckBox;
    wxStaticText* _NextKeyText;
    wxStaticText* _MaxSizeText;
    wxStaticText* _IndexListText;
    wxMenuBar* MenuBar;
    wxMenu* _ProcessMenu;
    wxMenu* _SettingsMenu;
    wxMenu* _menuHelp;
    wxMenu* _menuAbout;
    wxListCtrl* _currentList;
    wxListCtrl* _deadList;
    wxStaticText* _currentLable;
    wxStaticText* _deadLable;
    wxMenuItem* _chooseCurrent;
    wxMenuItem* _chooseDead;

    // 隔一段时间检测，用于自动刷新
    std::unique_ptr<wxTimer> _auto_refresh_timer;

    // 每帧检测，用于按键刷新
    std::unique_ptr<wxTimer> _key_refresh_timer;

    std::vector<int> _RefreshKeys;
    int _interval = 100;
    AnimationArrayList _monitor;
    HWND _hWnd;

public:
    mainWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style);

    ~mainWindow();

    DECLARE_EVENT_TABLE()
};

enum {
    ID_KEY_REFRESH_TIMER = 0,
    ID_AUTO_REFRESH_TIMER = 1,
    ID_CURRENT_LIST = 2,
    ID_DEAD_LIST = 3,
    ID_SELECT_PROCESS = 4,
    ID_KEY_1 = 5,
    ID_KEY_2 = 6,
    ID_KEY_3 = 7,
    ID_SET_KEYS_BUTTON = 8,
    ID_INTERVAL_VALUE = 9,
    ID_SET_INTERVAL = 10,
    ID_AUTO_REFRESH_CHECK_BOX = 11,
    ID_NEXT_KEY = 12,
    ID_MAX_SIZE = 13,
    ID_INDEX_LIST = 14,
    ID_CURRENT_TEXT = 15,
    ID_DEAD_TEXT = 16,
    ID_CHOOSE_CURRENT = 17,
    ID_CHOOSE_DEAD = 18,
};

#endif //!__MAINWINDOW_H__