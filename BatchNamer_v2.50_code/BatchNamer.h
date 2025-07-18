﻿
// BatchNamer.h: PROJECT_NAME 애플리케이션에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.
#include <afxwinappex.h>
#include <map>

#ifndef MY_MAX_PATH
#define MY_MAX_PATH 32768
#endif

//CDlgInput 및 CDlgPreset에 사용되는 입력창 설정용 구조체
struct InputItem
{
	CString m_strItemName;	//콤보박스에 들어갈 이름
	int m_nSubCommand;		//동작하는 기능 종류  
	CString m_strLabel1;	//첫번째 입력창 상단 라벨
	BOOL m_bIsNumber1;		//첫번째 입력창이 숫자만 받는지 여부
	CString m_strLabel2;	//두번째 입력창 상단 라벨
	BOOL m_bIsNumber2;		//두번째 입력창이 숫자만 받는지 여부
	InputItem()
	{
		m_nSubCommand = 0;
		m_bIsNumber1 = FALSE;
		m_bIsNumber2 = FALSE;
	}
	void Clear() 
	{
		m_strItemName.Empty();
		m_strLabel1.Empty();
		m_strLabel2.Empty();
		m_nSubCommand = 0;
		m_bIsNumber1 = FALSE;
		m_bIsNumber2 = FALSE;
	}
};

typedef CArray<InputItem, InputItem&> InputItemArray;


//프리셋의 단위 작업 항목을 나타내는 구조체
struct PresetTask
{
	int m_nCommand;		//기능 종류 (툴바 버튼과 연결)
	int m_nSubCommand;  //기능 종류 (입력창 콤보박스와 연결)
	CString m_str1;		//첫번째 인자
	CString m_str2;		//두번째 인자
	PresetTask() { m_nCommand = 0; m_nSubCommand = 0; }
	PresetTask(PresetTask& task) 
	{
		m_nCommand = task.m_nCommand; 
		m_nSubCommand = task.m_nSubCommand; 
		m_str1 = task.m_str1;
		m_str2 = task.m_str2;
	}
};

typedef CArray<PresetTask, PresetTask&> PresetTaskArray;

#ifndef APPLY_MOVE
#define APPLY_MOVE 0
#define APPLY_COPY 1
#endif


//프리셋을 나타내는 구조체
struct BatchNamerPreset
{
	CString m_strName; //프리셋 이름
	BOOL m_bAutoApply; //자동 적용 여부
	int m_nApplyType; //적용 방식
	BOOL m_bAutoSort; //사전 정렬 여부
	BOOL m_bSortAscsend; //오름차순 정렬 여부
	int m_nSortColumn; //정렬 대상 컬럼

	PresetTaskArray m_aTask;
	BatchNamerPreset()
	{
		Clear();
	};
	~BatchNamerPreset()
	{
		Clear();
	}
	void Clear()
	{
		m_strName = L"";
		m_bAutoApply = FALSE;
		m_nApplyType = APPLY_MOVE;
		m_bAutoSort = FALSE;
		m_bSortAscsend = TRUE;
		m_nSortColumn = 0; //COL_OLDNAME
		m_aTask.RemoveAll();
	};
};


typedef CArray<BatchNamerPreset, BatchNamerPreset&> PresetArray;

CString ConvertKeyCodeToName(DWORD code);

//단축키를 나타내는 구조체
class HotKey
{
public:
	int nKeyCode;
	BOOL bCtrl;
	BOOL bShift;
	HotKey() { nKeyCode = 0; bCtrl = FALSE; bShift = FALSE;}
	HotKey(int nKeyCode_Val, BOOL bCtrl_Val, BOOL bShift_Val)
	{ 
		nKeyCode = nKeyCode_Val;
		bCtrl = bCtrl_Val;
		bShift = bShift_Val;
	}
	HotKey(HotKey& hk)
	{
		nKeyCode = hk.nKeyCode;
		bCtrl = hk.bCtrl;
		bShift = hk.bShift;
	}
	CString GetKeyString()
	{
		CString strRet;
		if (bCtrl) strRet += "Ctrl＋";
		if (bShift) strRet += "Shift＋";
		if (nKeyCode != 0) strRet += ConvertKeyCodeToName((DWORD)nKeyCode);
		return strRet;
	}
};

typedef std::map<int, HotKey> CHotKeyMap;

// CBatchNamerApp:
// 이 클래스의 구현에 대해서는 BatchNamer.cpp을(를) 참조하세요.
//

class CBatchNamerApp : public CWinAppEx
{
public:
	CBatchNamerApp();
//	ULONG_PTR m_gdiplusToken;
	HICON m_hIcon;
//	BOOL m_bEnglishUI;
	CString m_strUILanguage; //Default, Korean, English
	CString m_strINIPath;
	BOOL m_bShowEverytime;
	BOOL m_bAutoSort;
	BOOL m_bNameAutoFix;
	BOOL m_bUseThread;
	BOOL m_bAutoNumber;
	int m_nLoadType;
	int m_nShowFlag;
	int m_nSortCol;
	BOOL m_bSortAscend;
	CRect m_rcMain;
	CRect m_rcInput;
	COLORREF m_clrText;
	COLORREF m_clrBk;
	CString m_strFontName;
	LONG m_nFontWeight;
	int m_nFontSize;
	BYTE m_bFontItalic;
	BOOL m_bUseDefaultColor;
	BOOL m_bUseDefaultFont;
	int m_nIconType;
	PresetArray m_aPreset;
	CUIntArray m_aColWidth;
	BOOL m_bIncludeExt;
	BOOL m_bShowDoneDialog; // 작업 끝나고 결과 메시지 다이얼로그 표시 여부
	BOOL m_bShowLog; // 로그 상시 표시 여부
	BOOL m_bSortLikeWindows; //윈도우 탐색기와 동일한 방식으로 정렬하는 옵션
	BOOL m_bClearAfterApply; //작업 성공시 자동으로 목록으로 삭제하는 옵션
	int m_nLogHeight; // 로그 창 높이
	void PresetExport();
	void PresetImport();
	void INISave(CString strFile);
	void INILoad(CString strFile);
	CString GetPresetExportString();
	void SetLocale(int nLanguageID);
	void UpdateThreadLocale();
	void ShowMsg(CString strMsg, CString strTitle);
	CHotKeyMap m_mapHotKey;
	void InitHotKey();
// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
// 구현입니다.
	DECLARE_MESSAGE_MAP()
};
inline CBatchNamerApp* APP() { return (CBatchNamerApp*)AfxGetApp(); };

extern CBatchNamerApp theApp;


