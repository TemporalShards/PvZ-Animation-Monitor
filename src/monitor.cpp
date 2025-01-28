#include "monitor.h"
#include <wx/msgdlg.h>

const char* GetLoopTimeName(DWORD theLoopType)
{
    switch (theLoopType) {
    case 0:
        return "LOOP";
    case 1:
        return "LOOP_FULL_LAST_FRAME";
    case 2:
        return "PLAY_ONCE";
    case 3:
        return "PLAY_ONCE_AND_HOLD";
    case 4:
        return "PLAY_ONCE_FULL_LAST_FRAME";
    case 5:
        return "PLAY_ONCE_FULL_LAST_FRAME_AND_HOLD";
    }
    return "UNKNOWN";
}

const char* GetReanimationName(DWORD theReanimationType)
{
    switch (theReanimationType) {
    case 0:
        return "LOADBAR_SPROUT";
    case 1:
        return "LOADBAR_ZOMBIEHEAD";
    case 2:
        return "SODROLL";
    case 3:
        return "FINAL_WAVE";
    case 4:
        return "PEASHOOTER";
    case 5:
        return "WALLNUT";
    case 6:
        return "LILYPAD";
    case 7:
        return "SUNFLOWER";
    case 8:
        return "LAWNMOWER";
    case 9:
        return "READYSETPLANT";
    case 10:
        return "CHERRYBOMB";
    case 11:
        return "SQUASH";
    case 12:
        return "DOOMSHROOM";
    case 13:
        return "SNOWPEA";
    case 14:
        return "REPEATER";
    case 15:
        return "SUNSHROOM";
    case 16:
        return "TALLNUT";
    case 17:
        return "FUMESHROOM";
    case 18:
        return "PUFFSHROOM";
    case 19:
        return "HYPNOSHROOM";
    case 20:
        return "CHOMPER";
    case 21:
        return "ZOMBIE";
    case 22:
        return "SUN";
    case 23:
        return "POTATOMINE";
    case 24:
        return "SPIKEWEED";
    case 25:
        return "SPIKEROCK";
    case 26:
        return "THREEPEATER";
    case 27:
        return "MARIGOLD";
    case 28:
        return "ICESHROOM";
    case 29:
        return "ZOMBIE_FOOTBALL";
    case 30:
        return "ZOMBIE_NEWSPAPER";
    case 31:
        return "ZOMBIE_ZAMBONI";
    case 32:
        return "SPLASH";
    case 33:
        return "JALAPENO";
    case 34:
        return "JALAPENO_FIRE";
    case 35:
        return "COIN_SILVER";
    case 36:
        return "ZOMBIE_CHARRED";
    case 37:
        return "ZOMBIE_CHARRED_IMP";
    case 38:
        return "ZOMBIE_CHARRED_DIGGER";
    case 39:
        return "ZOMBIE_CHARRED_ZAMBONI";
    case 40:
        return "ZOMBIE_CHARRED_CATAPULT";
    case 41:
        return "ZOMBIE_CHARRED_GARGANTUAR";
    case 42:
        return "SCRAREYSHROOM";
    case 43:
        return "PUMPKIN";
    case 44:
        return "PLANTERN";
    case 45:
        return "TORCHWOOD";
    case 46:
        return "SPLITPEA";
    case 47:
        return "SEASHROOM";
    case 48:
        return "BLOVER";
    case 49:
        return "FLOWER_POT";
    case 50:
        return "CACTUS";
    case 51:
        return "DANCER";
    case 52:
        return "TANGLEKELP";
    case 53:
        return "STARFRUIT";
    case 54:
        return "POLEVAULTER";
    case 55:
        return "BALLOON";
    case 56:
        return "GARGANTUAR";
    case 57:
        return "IMP";
    case 58:
        return "DIGGER";
    case 59:
        return "DIGGER_DIRT";
    case 60:
        return "ZOMBIE_DOLPHINRIDER";
    case 61:
        return "POGO";
    case 62:
        return "BACKUP_DANCER";
    case 63:
        return "BOBSLED";
    case 64:
        return "JACKINTHEBOX";
    case 65:
        return "SNORKEL";
    case 66:
        return "BUNGEE";
    case 67:
        return "CATAPULT";
    case 68:
        return "LADDER";
    case 69:
        return "PUFF";
    case 70:
        return "SLEEPING";
    case 71:
        return "GRAVE_BUSTER";
    case 72:
        return "ZOMBIES_WON";
    case 73:
        return "MAGNETSHROOM";
    case 74:
        return "BOSS";
    case 75:
        return "CABBAGEPULT";
    case 76:
        return "KERNELPULT";
    case 77:
        return "MELONPULT";
    case 78:
        return "COFFEEBEAN";
    case 79:
        return "UMBRELLALEAF";
    case 80:
        return "GATLINGPEA";
    case 81:
        return "CATTAIL";
    case 82:
        return "GLOOMSHROOM";
    case 83:
        return "BOSS_ICEBALL";
    case 84:
        return "BOSS_FIREBALL";
    case 85:
        return "COBCANNON";
    case 86:
        return "GARLIC";
    case 87:
        return "GOLD_MAGNET";
    case 88:
        return "WINTER_MELON";
    case 89:
        return "TWIN_SUNFLOWER";
    case 90:
        return "POOL_CLEANER";
    case 91:
        return "ROOF_CLEANER";
    case 92:
        return "FIRE_PEA";
    case 93:
        return "IMITATER";
    case 94:
        return "YETI";
    case 95:
        return "BOSS_DRIVER";
    case 96:
        return "LAWN_MOWERED_ZOMBIE";
    case 97:
        return "CRAZY_DAVE";
    case 98:
        return "TEXT_FADE_ON";
    case 99:
        return "HAMMER";
    case 100:
        return "SLOT_MACHINE_HANDLE";
    case 101:
        return "CREDITS_FOOTBALL";
    case 102:
        return "CREDITS_JACKBOX";
    case 103:
        return "SELECTOR_SCREEN";
    case 104:
        return "PORTAL_CIRCLE";
    case 105:
        return "PORTAL_SQUARE";
    case 106:
        return "ZENGARDEN_SPROUT";
    case 107:
        return "ZENGARDEN_WATERINGCAN";
    case 108:
        return "ZENGARDEN_FERTILIZER";
    case 109:
        return "ZENGARDEN_BUGSPRAY";
    case 110:
        return "ZENGARDEN_PHONOGRAPH";
    case 111:
        return "DIAMOND";
    case 112:
        return "ZOMBIE_HAND";
    case 113:
        return "STINKY";
    case 114:
        return "RAKE";
    case 115:
        return "RAIN_CIRCLE";
    case 116:
        return "RAIN_SPLASH";
    case 117:
        return "ZOMBIE_SURPRISE";
    case 118:
        return "COIN_GOLD";
    case 119:
        return "TREEOFWISDOM";
    case 120:
        return "TREEOFWISDOM_CLOUDS";
    case 121:
        return "TREEOFWISDOM_TREEFOOD";
    case 122:
        return "CREDITS_MAIN";
    case 123:
        return "CREDITS_MAIN2";
    case 124:
        return "CREDITS_MAIN3";
    case 125:
        return "ZOMBIE_CREDITS_DANCE";
    case 126:
        return "CREDITS_STAGE";
    case 127:
        return "CREDITS_BIGBRAIN";
    case 128:
        return "CREDITS_FLOWER_PETALS";
    case 129:
        return "CREDITS_INFANTRY";
    case 130:
        return "CREDITS_THROAT";
    case 131:
        return "CREDITS_CRAZYDAVE";
    case 132:
        return "CREDITS_BOSSDANCE";
    case 133:
        return "ZOMBIE_CREDITS_SCREEN_DOOR";
    case 134:
        return "ZOMBIE_CREDITS_CONEHEAD";
    case 135:
        return "CREDITS_ZOMBIEARMY1";
    case 136:
        return "CREDITS_ZOMBIEARMY2";
    case 137:
        return "CREDITS_TOMBSTONES";
    case 138:
        return "CREDITS_SOLARPOWER";
    case 139:
        return "CREDITS_ANYHOUR";
    case 140:
        return "CREDITS_WEARETHEUNDEAD";
    case 141:
        return "CREDITS_DISCOLIGHTS";
    case 142:
        return "FLAG";
    }
    return "UNKNOWN";
}

void AnimationArrayList::PrintList(wxListCtrl* list1, wxListCtrl* list2)
{
    if (!IsValid())
        return;

    ReadProcessMemory(hProcess, (LPVOID)0x006A9EC0, &aBase, 4, &aBuffer);
    ReadProcessMemory(hProcess, (LPVOID)(aBase + 0x820), &aEffect, 4, &aBuffer);
    ReadProcessMemory(hProcess, (LPVOID)(aEffect + 0x8), &aDataArray, 4, &aBuffer);

    if (aBase == 0 || aEffect == 0 || aDataArray == 0) {
        CloseHandle(hProcess);
        return;
    }
    ReadProcessMemory(hProcess, (LPVOID)(aDataArray), &aReanimationArray, 4, &aBuffer);
    DWORD aArrayPtr = aReanimationArray;
    for (int i = 0; i < aMaxIndex; i++, aArrayPtr += 0xA0) {
        ReadProcessMemory(hProcess, (LPVOID)(aArrayPtr + 0x14), &aIsDead[i], 1, &aBuffer);
        if (!aIsDead[i])
            OutReanimation(i, aArrayPtr, list1);
        else
            OutReanimation(i, aArrayPtr, list2);
    }
}

void AnimationArrayList::OutReanimation(int index, DWORD& theAddress, wxListCtrl* list)
{
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
    list->SetItem(itemIndex, 4, wxString::FromUTF8(GetLoopTimeName(aLoopType)));
    list->SetItem(itemIndex, 5, wxString::FromUTF8(GetReanimationName(aType)));
}

bool AnimationArrayList::DataArrayGetNextIndex(DWORD& theCurrent, DWORD theMax)
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

void AnimationArrayList::DisplayStatus(wxStaticText* NextKeyLable, wxStaticText* MaxIndexLable, wxStaticText* indexListLable)
{
    if (!IsValid()) {
        NextKeyLable->SetLabel("unknown");
        MaxIndexLable->SetLabel("unknown");
        indexListLable->SetLabel("unknown");
        return;
    }

    ReadProcessMemory(hProcess, (LPVOID)(aDataArray + 0x14), &aNextKey, 4, &aBuffer);
    ReadProcessMemory(hProcess, (LPVOID)(aDataArray + 0x4), &aMaxIndex, 4, &aBuffer);
    ReadProcessMemory(hProcess, (LPVOID)(aDataArray + 0xC), &aNextIndex, 4, &aBuffer);
    NextKeyLable->SetLabel(wxString::Format("0x%04X ", aNextKey));

    std::vector<DWORD> indexList;
    indexList.push_back(aNextIndex);
    while (aNextIndex <= aMaxIndex) {
        DataArrayGetNextIndex(aNextIndex, aMaxIndex);
        indexList.push_back(aNextIndex);
    }
    MaxIndexLable->SetLabel(wxString::Format("0x%04X ", aMaxIndex));

    wxString str;
    for (size_t i = 0; i < indexList.size(); ++i) {
        str += wxString::Format("0x%04X", indexList[i]);
        if (i < indexList.size() - 1)
            str += ", ";
        else
            str += "... ";
    }
    indexListLable->SetLabel(str);
}

void AnimationArrayList::SetProcess(HWND hWnd)
{
    _hWnd = hWnd;
}

bool AnimationArrayList::IsValid()
{
    if (!IsPvZProcess(_hWnd))
        return false;

    DWORD dwPid = 0;
    ::GetWindowThreadProcessId(_hWnd, &dwPid);
    if (dwPid == -1) {
        return false;
    }

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
    return hProcess;
}