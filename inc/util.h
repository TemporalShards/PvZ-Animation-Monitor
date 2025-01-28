/*
 * @Author: TemporalShards
 * @Date: 2025-01-24 21:38:06
 * @Last Modified by: TemporalShards
 * @Description：按键相关
 */
 #pragma once
#ifndef __UTIL_H__
#define __UTIL_H__

#include "wx/string.h"
#include <Windows.h>
#include <unordered_map>

// 虚拟键码表
static const std::unordered_map<wxString, int> VirtualKeyMap = {
    // Alphanumeric keys
    {"A", 0x41}, {"B", 0x42}, {"C", 0x43}, {"D", 0x44}, {"E", 0x45}, {"F", 0x46}, {"G", 0x47}, {"H", 0x48}, {"I", 0x49},
    {"J", 0x4A}, {"K", 0x4B}, {"L", 0x4C}, {"M", 0x4D}, {"N", 0x4E}, {"O", 0x4F}, {"P", 0x50}, {"Q", 0x51}, {"R", 0x52},
    {"S", 0x53}, {"T", 0x54}, {"U", 0x55}, {"V", 0x56}, {"W", 0x57}, {"X", 0x58}, {"Y", 0x59}, {"Z", 0x5A},
    {"0", 0x30}, {"1", 0x31}, {"2", 0x32}, {"3", 0x33}, {"4", 0x34}, {"5", 0x35}, {"6", 0x36}, {"7", 0x37}, {"8", 0x38}, {"9", 0x39},

    // Function keys
    {"F1", 0x70}, {"F2", 0x71}, {"F3", 0x72}, {"F4", 0x73}, {"F5", 0x74}, {"F6", 0x75}, {"F7", 0x76}, {"F8", 0x77},
    {"F9", 0x78}, {"F10", 0x79}, {"F11", 0x7A}, {"F12", 0x7B}, {"F13", 0x7C}, {"F14", 0x7D}, {"F15", 0x7E}, {"F16", 0x7F},
    {"F17", 0x80}, {"F18", 0x81}, {"F19", 0x82}, {"F20", 0x83}, {"F21", 0x84}, {"F22", 0x85}, {"F23", 0x86}, {"F24", 0x87},

    // Special keys
    {"ESCAPE", 0x1B}, {"TAB", 0x09}, {"BACKSPACE", 0x08}, {"ENTER", 0x0D}, {"SHIFT", 0x10}, {"CTRL", 0x11}, {"ALT", 0x12},
    {"PAUSE", 0x13}, {"CAPSLOCK", 0x14}, {"ESC", 0x1B}, {"SPACE", 0x20}, {"PAGEUP", 0x21}, {"PAGEDOWN", 0x22},
    {"END", 0x23}, {"HOME", 0x24}, {"LEFT", 0x25}, {"UP", 0x26}, {"RIGHT", 0x27}, {"DOWN", 0x28},
    {"PRINTSCREEN", 0x2C}, {"INSERT", 0x2D}, {"DELETE", 0x2E}, {"LWIN", 0x5B}, {"RWIN", 0x5C},
    {"NUMLOCK", 0x90}, {"SCROLLLOCK", 0x91}, {"NUMPAD0", 0x60}, {"NUMPAD1", 0x61}, {"NUMPAD2", 0x62},
    {"NUMPAD3", 0x63}, {"NUMPAD4", 0x64}, {"NUMPAD5", 0x65}, {"NUMPAD6", 0x66}, {"NUMPAD7", 0x67},
    {"NUMPAD8", 0x68}, {"NUMPAD9", 0x69}, {"MULTIPLY", 0x6A}, {"ADD", 0x6B}, {"SUBTRACT", 0x6D},
    {"DECIMAL", 0x6E}, {"DIVIDE", 0x6F}, {"SEMICOLON", 0xBA}, {"EQUALS", 0xBB}, {"COMMA", 0xBC},
    {"MINUS", 0xBD}, {"PERIOD", 0xBE}, {"SLASH", 0xBF}, {"BACKSLASH", 0xDC}, {"LEFTBRACKET", 0xDB},
    {"RIGHTBRACKET", 0xDD}, {"APOSTROPHE", 0xDE}, {"GRAVEACCENT", 0xC0}};

// 指定键均被按下时，返回true。
// 取自：https://github.com/qrmd0/AvZLib/tree/main/qrmd/qmLib#avz-qmlib
inline bool GetIsKeysDown(HWND hWnd, const std::vector<int>& keys, bool isRequirePvZActive = true)
{
    if (isRequirePvZActive && GetForegroundWindow() != hWnd)
        return false;

    if (keys.empty())
        return false;

    for (const auto& each : keys) {
        if ((GetAsyncKeyState(each) & 0x8000) == 0)
            return false;
    }
    return true;
}

#endif //!__UTIL_H__