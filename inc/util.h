/*
 * @Author: TemporalShards
 * @Date: 2025-01-24 21:38:06
 * @Last Modified by: TemporalShards
 * @Description：
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

inline wxString GetWindowTitle(HWND hWnd)
{
    TCHAR title[256];
    if (GetWindowText(hWnd, title, sizeof(title) / sizeof(TCHAR)) > 0)
        return wxString(title);

    return wxEmptyString;
}

static const std::unordered_map<DWORD, const char*> LoopTimeName = {
    {0, "LOOP"},
    {1, "LOOP_FULL_LAST_FRAME"},
    {2, "PLAY_ONCE"},
    {3, "PLAY_ONCE_AND_HOLD"},
    {4, "PLAY_ONCE_FULL_LAST_FRAME"},
    {5, "PLAY_ONCE_FULL_LAST_FRAME_AND_HOLD"},
};

static const std::unordered_map<DWORD, const char*> ReanimationName = {
    {-1, "NULL"},
    {0, "LOADBAR_SPROUT"},
    {1, "LOADBAR_ZOMBIEHEAD"},
    {2, "SODROLL"},
    {3, "FINAL_WAVE"},
    {4, "PEASHOOTER"},
    {5, "WALLNUT"},
    {6, "LILYPAD"},
    {7, "SUNFLOWER"},
    {8, "LAWNMOWER"},
    {9, "READYSETPLANT"},
    {10, "CHERRYBOMB"},
    {11, "SQUASH"},
    {12, "DOOMSHROOM"},
    {13, "SNOWPEA"},
    {14, "REPEATER"},
    {15, "SUNSHROOM"},
    {16, "TALLNUT"},
    {17, "FUMESHROOM"},
    {18, "PUFFSHROOM"},
    {19, "HYPNOSHROOM"},
    {20, "CHOMPER"},
    {21, "ZOMBIE"},
    {22, "SUN"},
    {23, "POTATOMINE"},
    {24, "SPIKEWEED"},
    {25, "SPIKEROCK"},
    {26, "THREEPEATER"},
    {27, "MARIGOLD"},
    {28, "ICESHROOM"},
    {29, "ZOMBIE_FOOTBALL"},
    {30, "ZOMBIE_NEWSPAPER"},
    {31, "ZOMBIE_ZAMBONI"},
    {32, "SPLASH"},
    {33, "JALAPENO"},
    {34, "JALAPENO_FIRE"},
    {35, "COIN_SILVER"},
    {36, "ZOMBIE_CHARRED"},
    {37, "ZOMBIE_CHARRED_IMP"},
    {38, "ZOMBIE_CHARRED_DIGGER"},
    {39, "ZOMBIE_CHARRED_ZAMBONI"},
    {40, "ZOMBIE_CHARRED_CATAPULT"},
    {41, "ZOMBIE_CHARRED_GARGANTUAR"},
    {42, "SCRAREYSHROOM"},
    {43, "PUMPKIN"},
    {44, "PLANTERN"},
    {45, "TORCHWOOD"},
    {46, "SPLITPEA"},
    {47, "SEASHROOM"},
    {48, "BLOVER"},
    {49, "FLOWER_POT"},
    {50, "CACTUS"},
    {51, "DANCER"},
    {52, "TANGLEKELP"},
    {53, "STARFRUIT"},
    {54, "POLEVAULTER"},
    {55, "BALLOON"},
    {56, "GARGANTUAR"},
    {57, "IMP"},
    {58, "DIGGER"},
    {59, "DIGGER_DIRT"},
    {60, "ZOMBIE_DOLPHINRIDER"},
    {61, "POGO"},
    {62, "BACKUP_DANCER"},
    {63, "BOBSLED"},
    {64, "JACKINTHEBOX"},
    {65, "SNORKEL"},
    {66, "BUNGEE"},
    {67, "CATAPULT"},
    {68, "LADDER"},
    {69, "PUFF"},
    {70, "SLEEPING"},
    {71, "GRAVE_BUSTER"},
    {72, "ZOMBIES_WON"},
    {73, "MAGNETSHROOM"},
    {74, "BOSS"},
    {75, "CABBAGEPULT"},
    {76, "KERNELPULT"},
    {77, "MELONPULT"},
    {78, "COFFEEBEAN"},
    {79, "UMBRELLALEAF"},
    {80, "GATLINGPEA"},
    {81, "CATTAIL"},
    {82, "GLOOMSHROOM"},
    {83, "BOSS_ICEBALL"},
    {84, "BOSS_FIREBALL"},
    {85, "COBCANNON"},
    {86, "GARLIC"},
    {87, "GOLD_MAGNET"},
    {88, "WINTER_MELON"},
    {89, "TWIN_SUNFLOWER"},
    {90, "POOL_CLEANER"},
    {91, "ROOF_CLEANER"},
    {92, "FIRE_PEA"},
    {93, "IMITATER"},
    {94, "YETI"},
    {95, "BOSS_DRIVER"},
    {96, "LAWN_MOWERED_ZOMBIE"},
    {97, "CRAZY_DAVE"},
    {98, "TEXT_FADE_ON"},
    {99, "HAMMER"},
    {100, "SLOT_MACHINE_HANDLE"},
    {101, "CREDITS_FOOTBALL"},
    {102, "CREDITS_JACKBOX"},
    {103, "SELECTOR_SCREEN"},
    {104, "PORTAL_CIRCLE"},
    {105, "PORTAL_SQUARE"},
    {106, "ZENGARDEN_SPROUT"},
    {107, "ZENGARDEN_WATERINGCAN"},
    {108, "ZENGARDEN_FERTILIZER"},
    {109, "ZENGARDEN_BUGSPRAY"},
    {110, "ZENGARDEN_PHONOGRAPH"},
    {111, "DIAMOND"},
    {112, "ZOMBIE_HAND"},
    {113, "STINKY"},
    {114, "RAKE"},
    {115, "RAIN_CIRCLE"},
    {116, "RAIN_SPLASH"},
    {117, "ZOMBIE_SURPRISE"},
    {118, "COIN_GOLD"},
    {119, "TREEOFWISDOM"},
    {120, "TREEOFWISDOM_CLOUDS"},
    {121, "TREEOFWISDOM_TREEFOOD"},
    {122, "CREDITS_MAIN"},
    {123, "CREDITS_MAIN2"},
    {124, "CREDITS_MAIN3"},
    {125, "ZOMBIE_CREDITS_DANCE"},
    {126, "CREDITS_STAGE"},
    {127, "CREDITS_BIGBRAIN"},
    {128, "CREDITS_FLOWER_PETALS"},
    {129, "CREDITS_INFANTRY"},
    {130, "CREDITS_THROAT"},
    {131, "CREDITS_CRAZYDAVE"},
    {132, "CREDITS_BOSSDANCE"},
    {133, "ZOMBIE_CREDITS_SCREEN_DOOR"},
    {134, "ZOMBIE_CREDITS_CONEHEAD"},
    {135, "CREDITS_ZOMBIEARMY1"},
    {136, "CREDITS_ZOMBIEARMY2"},
    {137, "CREDITS_TOMBSTONES"},
    {138, "CREDITS_SOLARPOWER"},
    {139, "CREDITS_ANYHOUR"},
    {140, "CREDITS_WEARETHEUNDEAD"},
    {141, "CREDITS_DISCOLIGHTS"},
    {142, "FLAG"},
};

#endif //!__UTIL_H__