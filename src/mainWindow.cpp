#include "mainWindow.h"
#include "util.h"
#include <wx/aboutdlg.h>

BEGIN_EVENT_TABLE(mainWindow, wxFrame)
EVT_TIMER(ID_AUTO_REFRESH_TIMER, mainWindow::OnTimer)
EVT_TIMER(ID_KEY_REFRESH_TIMER, mainWindow::OnEveryTick)
EVT_CLOSE(mainWindow::OnClose)
END_EVENT_TABLE()

mainWindow::mainWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxFrame(parent, id, title, pos, size, style)
{
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);
    this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));

    _InfoBar = this->CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);

    wxBoxSizer* GlobalSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* KeySizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* SetRefreshKeyText = new wxStaticText(this, wxID_ANY, wxT("设置刷新快捷键"), wxDefaultPosition, wxDefaultSize, 0);
    SetRefreshKeyText->Wrap(-1);
    KeySizer->Add(SetRefreshKeyText, 0, wxALL, 5);

    _refresh_key_1 = new wxTextCtrl(this, ID_KEY_1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    KeySizer->Add(_refresh_key_1, 0, wxALL, 5);

    wxStaticText* and1 = new wxStaticText(this, wxID_ANY, "+", wxDefaultPosition, wxDefaultSize, 0);
    and1->Wrap(-1);
    KeySizer->Add(and1, 0, wxALL, 5);

    _refresh_key_2 = new wxTextCtrl(this, ID_KEY_2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    KeySizer->Add(_refresh_key_2, 0, wxALL, 5);

    wxStaticText* and2 = new wxStaticText(this, wxID_ANY, "+", wxDefaultPosition, wxDefaultSize, 0);
    and2->Wrap(-1);
    KeySizer->Add(and2, 0, wxALL, 5);

    _refresh_key_3 = new wxTextCtrl(this, ID_KEY_3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    KeySizer->Add(_refresh_key_3, 0, wxALL, 5);

    _SetKeyButton = new wxButton(this, ID_SET_KEYS_BUTTON, wxT("设置"), wxDefaultPosition, wxDefaultSize, 0);
    KeySizer->Add(_SetKeyButton, 0, wxALL, 5);

    GlobalSizer->Add(KeySizer, 1, wxEXPAND, 5);

    wxBoxSizer* SetIntervalSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* intervalLabel = new wxStaticText(this, wxID_ANY, wxT("设置刷新间隔(cs)"), wxDefaultPosition, wxDefaultSize, 0);
    intervalLabel->Wrap(-1);
    SetIntervalSizer->Add(intervalLabel, 0, wxALL, 5);

    _intervalValue = new wxTextCtrl(this, ID_INTERVAL_VALUE, "10", wxDefaultPosition, wxDefaultSize, 0);
    SetIntervalSizer->Add(_intervalValue, 0, wxALL, 5);

    _SetIntervalButton = new wxButton(this, ID_SET_INTERVAL, wxT("设置"), wxDefaultPosition, wxDefaultSize, 0);
    SetIntervalSizer->Add(_SetIntervalButton, 0, wxALL, 5);

    _AutoRefreshCheckBox = new wxCheckBox(this, ID_AUTO_REFRESH_CHECK_BOX, wxT("自动刷新"), wxDefaultPosition, wxDefaultSize, 0);
    SetIntervalSizer->Add(_AutoRefreshCheckBox, 0, wxALL, 5);

    GlobalSizer->Add(SetIntervalSizer, 1, wxEXPAND, 5);

    wxBoxSizer* NextKeySizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* NextKeyStaticText = new wxStaticText(this, wxID_ANY, "Next Key:", wxDefaultPosition, wxDefaultSize, 0);
    NextKeyStaticText->Wrap(-1);
    NextKeySizer->Add(NextKeyStaticText, 0, wxALL, 5);

    _NextKeyText = new wxStaticText(this, ID_NEXT_KEY, "unknown", wxDefaultPosition, wxDefaultSize, 0);
    _NextKeyText->Wrap(-1);
    NextKeySizer->Add(_NextKeyText, 0, wxALL, 5);

    wxStaticText* MaxSizeStaticText = new wxStaticText(this, wxID_ANY, "Max Size:", wxDefaultPosition, wxDefaultSize, 0);
    MaxSizeStaticText->Wrap(-1);
    NextKeySizer->Add(MaxSizeStaticText, 0, wxALL, 5);

    _MaxSizeText = new wxStaticText(this, ID_MAX_SIZE, "unknown", wxDefaultPosition, wxDefaultSize, 0);
    _MaxSizeText->Wrap(-1);
    NextKeySizer->Add(_MaxSizeText, 0, wxALL, 5);

    wxStaticText* IndexListStaticText = new wxStaticText(this, wxID_ANY, "Next Index List:", wxDefaultPosition, wxDefaultSize, 0);
    IndexListStaticText->Wrap(-1);
    NextKeySizer->Add(IndexListStaticText, 0, wxALL, 5);

    _IndexListText = new wxStaticText(this, ID_INDEX_LIST, "unknown", wxDefaultPosition, wxDefaultSize, 0);
    _IndexListText->Wrap(-1);
    NextKeySizer->Add(_IndexListText, 0, wxALL, 5);

    GlobalSizer->Add(NextKeySizer, 1, wxEXPAND, 5);

    _currentLable = new wxStaticText(this, ID_CURRENT_TEXT, "Current Array List");
    _currentList = new wxListCtrl(this, ID_CURRENT_LIST, wxDefaultPosition, wxSize(650, 300), wxLC_REPORT | wxLC_HRULES | wxLC_VRULES);
    _deadLable = new wxStaticText(this, ID_DEAD_TEXT, "Dead Array List");
    _deadList = new wxListCtrl(this, ID_DEAD_LIST, wxDefaultPosition, wxSize(650, 300), wxLC_REPORT | wxLC_HRULES | wxLC_VRULES);

    GlobalSizer->Add(_currentLable, 0, wxALL | wxEXPAND, 5);
    _currentList->InsertColumn(0, "Index", wxLIST_FORMAT_CENTER, 60);
    _currentList->InsertColumn(1, "ID", wxLIST_FORMAT_CENTER, 60);
    _currentList->InsertColumn(2, "Time", wxLIST_FORMAT_CENTER, 80);
    _currentList->InsertColumn(3, "Rate", wxLIST_FORMAT_CENTER, 80);
    _currentList->InsertColumn(4, "LoopType", wxLIST_FORMAT_CENTER, 160);
    _currentList->InsertColumn(5, "Type", wxLIST_FORMAT_CENTER, 160);
    GlobalSizer->Add(_currentList, 1, wxEXPAND | wxALL, 5);

    GlobalSizer->Add(_deadLable, 0, wxALL | wxEXPAND, 5);
    _deadList->InsertColumn(0, "Index", wxLIST_FORMAT_CENTER, 60);
    _deadList->InsertColumn(1, "ID", wxLIST_FORMAT_CENTER, 60);
    _deadList->InsertColumn(2, "Time", wxLIST_FORMAT_CENTER, 80);
    _deadList->InsertColumn(3, "Rate", wxLIST_FORMAT_CENTER, 80);
    _deadList->InsertColumn(4, "LoopType", wxLIST_FORMAT_CENTER, 160);
    _deadList->InsertColumn(5, "Type", wxLIST_FORMAT_CENTER, 160);
    GlobalSizer->Add(_deadList, 1, wxEXPAND | wxALL, 5);

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

    _MenuBar->Append(_SettingsMenu, wxT("设置"));

    _menuHelp = new wxMenu;
    _MenuBar->Append(_menuHelp, wxT("帮助"));
    _menuHelp->Append(wxID_HELP);

    _menuAbout = new wxMenu;
    _MenuBar->Append(_menuAbout, wxT("关于"));
    _menuAbout->Append(wxID_ABOUT);

    this->SetMenuBar(_MenuBar);

    this->Centre(wxBOTH);

    _SetKeyButton->Bind(wxEVT_BUTTON, &mainWindow::OnSetRefreshKeys, this, _SetKeyButton->GetId());
    _SetIntervalButton->Bind(wxEVT_BUTTON, &mainWindow::OnSetInterval, this, _SetIntervalButton->GetId());
    _AutoRefreshCheckBox->Bind(wxEVT_CHECKBOX, &mainWindow::OnRefreshCheckBox, this, _AutoRefreshCheckBox->GetId());
    Bind(wxEVT_MENU, &mainWindow::OnShowCurrenCheck, this, _chooseCurrent->GetId());
    Bind(wxEVT_MENU, &mainWindow::OnShowDeadCheck, this, _chooseDead->GetId());
    Bind(wxEVT_MENU, [=, this](wxCommandEvent&) { Close(true); }, _menuExit->GetId());
    Bind(wxEVT_MENU, &mainWindow::OnChooseProcess, this, _chooseGame->GetId());
    Bind(wxEVT_MENU, &mainWindow::OnHelp, this, wxID_HELP);
    Bind(wxEVT_MENU, &mainWindow::OnAbout, this, wxID_ABOUT);
    _currentList->Bind(wxEVT_LEFT_DOWN, &mainWindow::OnLeftDown, this);
    _currentList->Bind(wxEVT_RIGHT_DOWN, &mainWindow::OnRightDown, this);
    _deadList->Bind(wxEVT_LEFT_DOWN, &mainWindow::OnLeftDown, this);
    _deadList->Bind(wxEVT_RIGHT_DOWN, &mainWindow::OnRightDown, this);

    _auto_refresh_timer = std::make_unique<wxTimer>(this, ID_AUTO_REFRESH_TIMER);
    _key_refresh_timer = std::make_unique<wxTimer>(this, ID_KEY_REFRESH_TIMER);
    _auto_refresh_timer->Start(_interval);
    _key_refresh_timer->Start(10);
}

mainWindow::~mainWindow()
{
    _auto_refresh_timer->Stop();
    _key_refresh_timer->Stop();
}

void mainWindow::OnSetRefreshKeys(wxCommandEvent& event)
{
    auto key1 = _refresh_key_1->GetValue();
    auto key2 = _refresh_key_2->GetValue();
    auto key3 = _refresh_key_3->GetValue();
    _refreshKeys.clear();
    wxString info = wxT("SetRefreshKeys: 快捷键 ");
    for (const auto& key : {key1, key2, key3}) {
        if (key.empty())
            continue;

        auto _key = key.Upper();
        if (!VirtualKeyMap.contains(_key)) {
            wxMessageBox(wxString::Format(wxT("未知的按键 %s , 已自动忽略"), _key), wxT("快捷键绑定"), wxOK | wxICON_INFORMATION);
            continue;
        }
        _refreshKeys.push_back(VirtualKeyMap.at(_key));
        info += key + " ";
    }
    if (_refreshKeys.empty()) {
        info.clear();
        wxMessageBox(wxT("快捷键绑定失败"), wxT("快捷键绑定"));
        return;
    }

    info += wxT(" 绑定成功");
    SetStatusText(info);
}

void mainWindow::OnSetInterval(wxCommandEvent& event)
{
    int interval;
    if (_intervalValue->GetValue().ToInt(&interval)) {
        _interval = interval * 10;
        _auto_refresh_timer->Stop();
        _auto_refresh_timer->Start(_interval);
        wxMessageBox(wxString::Format(wxT("设置刷新间隔为 %ld cs成功"), interval), wxT("PvZ Animation Monitor设置刷新间隔"));
    } else
        wxMessageBox(wxT("设置刷新间隔失败"), wxT("PvZ Animation Monitor设置刷新间隔"));
}

void mainWindow::OnTimer(wxTimerEvent& event)
{
    // EveryTick()中每帧都检测了pvz进程，这里不用重复检测
    if (_isPaused)
        return;

    if (!_AutoRefreshCheckBox->IsChecked())
        return;

    _monitor.DisplayStatus(_NextKeyText, _MaxSizeText, _IndexListText);
    if (_chooseCurrent->IsChecked()) {
        _currentList->Show();
        _currentList->DeleteAllItems();
    } else 
        _currentList->Hide();
    
    if (_chooseDead->IsChecked()) {
        _deadList->Show();
        _deadList->DeleteAllItems();
    } else 
        _deadList->Hide();
    
    _monitor.PrintList(_currentList, _deadList);
}

void mainWindow::OnShowCurrenCheck(wxCommandEvent& event)
{
    if (_chooseCurrent->IsChecked()) {
        _currentLable->SetLabel(wxT("Current Array List"));
        _currentList->Show();
    } else {
        _currentLable->SetLabel(wxT("Current Array List已隐藏"));
        _currentList->Hide();
    }
}

void mainWindow::OnShowDeadCheck(wxCommandEvent& event)
{
    if (_chooseDead->IsChecked()) {
        _deadLable->SetLabel(wxT("Dead Array List"));
        _deadList->Show();
    } else {
        _deadLable->SetLabel(wxT("Dead Array List已隐藏"));
        _deadList->Hide();
    }
}

void mainWindow::_AutoFindGame()
{
    auto hWnd = ::FindWindow(L"MainWindow", L"Plants vs. Zombies");
    if (hWnd == NULL) {
        SetStatusText(wxT("未找到PvZ进程"));
        return;
    }

    if (IsPvZProcess(hWnd)) {
        _hWnd = hWnd;
        wxMessageBox(wxT("已找到PvZ进程"), wxT("PvZ Animation Monitor自动寻找进程"));
        SetStatusText(wxT("已找到PvZ进程"));
    }
}

void mainWindow::OnChooseProcess(wxCommandEvent& event)
{
    std::unique_ptr<ProcessChoose> dlg = std::make_unique<ProcessChoose>(nullptr);
    int result = dlg->ShowModal();
    if (result == wxID_OK) {
        _hWnd = dlg->GetSelectedHWND();
        _monitor.SetProcess(_hWnd);
        wxMessageBox(wxT("已找到PvZ进程"), wxT("PvZ Animation Monitor选择进程"));
    }
    dlg->Destroy();
}

void mainWindow::OnRefreshCheckBox(wxCommandEvent& event)
{
    if (_AutoRefreshCheckBox->IsChecked())
        _auto_refresh_timer->Start(_interval);
    else
        _auto_refresh_timer->Stop();
}

void mainWindow::OnEveryTick(wxTimerEvent& event)
{
    /*if (_isPaused)
        return;*/

    if (_SetIntervalButton->IsEnabled() != _AutoRefreshCheckBox->IsChecked())
        _SetIntervalButton->Enable(_AutoRefreshCheckBox->IsChecked());

    if (!IsPvZProcess(_hWnd)) {
        _AutoFindGame();
        return;
    }
    if (!_monitor.IsValid()) {
        _monitor.SetProcess(_hWnd);
        return;
    }
    if (GetIsKeysDown(_hWnd, _refreshKeys)) {
        _monitor.DisplayStatus(_NextKeyText, _MaxSizeText, _IndexListText);
        if (_chooseCurrent->IsChecked()) {
            _currentList->Show();
            _currentList->DeleteAllItems();
        } else 
            _currentList->Hide();
        
        if (_chooseDead->IsChecked()) {
            _deadList->Show();
            _deadList->DeleteAllItems();
        } else 
            _deadList->Hide();
        
        _monitor.PrintList(_currentList, _deadList);
    }
}

void mainWindow::OnClose(wxCloseEvent& event)
{
    _auto_refresh_timer->Stop();
    _key_refresh_timer->Stop();
    event.Skip();
}

void mainWindow::OnLeftDown(wxMouseEvent& event)
{
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
    wxListCtrl* listCtrl = dynamic_cast<wxListCtrl*>(event.GetEventObject());
    if (listCtrl) {
        auto item = this->HitTest(event.GetPosition());
        if (item == wxHT_WINDOW_INSIDE) {
            _isPaused = false;
        }
    }
}

void mainWindow::OnHelp(wxCommandEvent& event)
{
    wxMessageBox(LR"(为pvz英文原版动画监测写的GUI界面，添加了若干小功能：
1.手动选择进程，用于支持多开pvz，不支持大部分改版及中文版，年度版（即使找到了游戏也不能保证兼容）；

2.选择显示Current和Dead列表，默认二者均显示，可在程序菜单栏上的“设置”中取消勾选；

3.在自动刷新模式下，设置刷新间隔，单位为cs，不建议将设置太小间隔，一是CPU占用可能会过高，二是人眼也难以获取信息。
  参考间隔：恶魂的动画监测刷新间隔为10cs，这也是本程序的默认刷新间隔；

4.快捷键绑定动画内存列表的刷新，支持键盘上的大部分按键以及组合键，不区分大小写，但不能有汉字和特殊字符；
  例如想绑定Ctrl+Shift+Z，即按下Ctrl+Shift+Z时刷新一次列表，三个输入框从左到右依次键入ctrl, shift, z即可；
  注意组合键最多绑定三个，三个输入框不必全填满, 当且仅当pvz窗口为顶层窗口时按下按键才会刷新列表。

5.自动刷新模式下，当鼠标左键在两个列表内任意位置点击时，暂停刷新；当鼠标右键在两个列表内任意位置点击时，恢复刷新；
  按键刷新不受影响。
)",
        wxT("PvZ Animation Monitor帮助"));
}

void mainWindow::OnAbout(wxCommandEvent& event)
{
    wxAboutDialogInfo info;
    info.SetName("PvZ Animation Monitor");
    info.SetVersion("v1.0.1");
    info.SetDescription(LR"(
日期: 2025/01/29 17:31:00
工具链: Visual Studio 2022, CMake, wxWidgets 3.2.6
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