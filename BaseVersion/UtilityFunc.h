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
	void UtilityFunc::CwndToCRect(CWnd *StaticCwnd,CRect *rect);
	void UtilityFunc::CwndToIplImage(CWnd *StaticCwnd,IplImage *DestImage);
	void UtilityFunc::ShowCwnd(CWnd *StaticCwnd,char *WinName);
	void UtilityFunc::XSleep(int nWaitInMsecs);
	//Opencv
	void UtilityFunc::SetIplImagePixel(IplImage *img,int x,int y,unsigned char *Pixel);
	void UtilityFunc::GetIplImagePixel(IplImage *img,int x,int y,unsigned char *Pixel);
	int UtilityFunc::PixelCompared(unsigned char *Pixel1,unsigned char *Pixel2);
	int UtilityFunc::HSVCompared(unsigned char SrcH,unsigned char SrcS,unsigned char SrcV,unsigned char DestH,unsigned char DestS,unsigned char DestV,unsigned char DIFF);
	void UtilityFunc::RGBToHSV(IplImage *SrcImage,IplImage *HImage,IplImage *SImage,IplImage *VImage);
};
#endif