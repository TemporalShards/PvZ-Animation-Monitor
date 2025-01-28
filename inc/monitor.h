/*
 * @Author: TemporalShards
 * @Date: 2025-01-25 22:27:08
 * @Last Modified by: TemporalShards
 * @Description：读取相关动画内存
 */
#pragma once
#ifndef __MONITOR_H__
#define __MONITOR_H__

#include "process.h"
#include <Windows.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>

const char* GetLoopTimeName(DWORD theLoopType);

const char* GetReanimationName(DWORD theReanimationType);

class AnimationArrayList {
private:
    HWND _hWnd;

    HANDLE hProcess;
    SIZE_T aBuffer;
    DWORD aBase, aEffect, aDataArray, aReanimationArray;
    DWORD aNextKey, aNextIndex, aMaxIndex;
    bool aIsDead[1024];

protected:
    void OutReanimation(int index, DWORD& theAddress, wxListCtrl* list);

    bool DataArrayGetNextIndex(DWORD& theCurrent, DWORD theMax);

public:
    bool IsValid();

    void PrintList(wxListCtrl* list1, wxListCtrl* list2);

    void SetProcess(HWND hWnd);

    void DisplayStatus(wxStaticText* NextKeyLable, wxStaticText* MaxIndexLable, wxStaticText* indexListLable);
};

#endif //!__MONITOR_H__