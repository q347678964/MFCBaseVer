#ifndef EXAMPLE_H
#define EXAMPLE_H

#include "UtilityFunc.h"
#include "cv.h"
#include "highgui.h"
#include "CvvImage.h"

#define printf(fmg,...)				this->UtilityFunc::Printf("[Example]"fmg,__VA_ARGS__)
#define printfcstring(cstring)		this->UtilityFunc::PrintfCString(CString("[Example]")+cstring)

#define printffile(fmg,...)			this->UtilityFunc::PrintfFile("[Example]"fmg,__VA_ARGS__)
#define printfcstringfile(cstring)	this->UtilityFunc::PrintfCStringToFile(CString("[Example]")+cstring)

class Example : public UtilityFunc{

public:
	Example();
	~Example();

	FormatChange g_FormatHandle;

	void Example::Init(void);
	void Example::Exit(void);

	void Example::ProcessCtrl(int Num);

	void Example::FileOperation(void);

	void Example::TimerTest(void);

	void Example::ThreadTest(void);

	void Example::ProcessTest(void);

	void Example::GetHostAddress(CString &strIPAddr);
	void Example::NetTest(void);

	void Example::WinCMDTest(void);

	void Example::OpencvFillRectangle(IplImage* img,UINT32 Startx,UINT32 Starty,UINT32 Endx,UINT32 Endy);

	void Example::OpencvTest(void);

	void Example::FormatTest(void);

	void Example::ScanWindowTest(void);

	void Example::PNGTest(void);

	void Example::DlgMsgListen(int MessageID);
};
#endif