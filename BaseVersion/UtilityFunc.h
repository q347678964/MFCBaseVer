#ifndef UTILITYFUNC_H
#define UTILITYFUNC_H

#include "cv.h"
#include "highgui.h"
#include "CvvImage.h"

class UtilityFunc {

public:
	UtilityFunc();
	~UtilityFunc();
	HANDLE g_PrintfSemaphore;
	FormatChange g_FormatHandle;

	void UtilityFunc::Init(void);
	void UtilityFunc::Exit(void);

	void UtilityFunc::LogPrintf(CString Context);
	void UtilityFunc::PrintfToFile(CString Context);
	void UtilityFunc::Printf(CString Context);

	CWnd* UtilityFunc::IDToCWnd(int HDCID);
	CWnd* UtilityFunc::GetDlgCWnd(void);
	void UtilityFunc::ShowCwnd(CWnd *StaticCwnd,char *WinName);
};
#endif