#ifndef EXAMPLE_H
#define EXAMPLE_H

#include "cv.h"
#include "highgui.h"
#include "CvvImage.h"

class Example {

public:
	Example();
	~Example();

	void Printf(CString Context);
	void Example::ProcessCtrl(int Num);

	void FileOperation(void);

	void TimerTest(void);

	void ThreadTest(void);

	void Example::ProcessTest(void);

	void Example::GetHostAddress(CString &strIPAddr);
	void Example::NetTest(void);

	void Example::WinCMDTest(void);

	void Example::OpencvFillRectangle(IplImage* img,UINT32 Startx,UINT32 Starty,UINT32 Endx,UINT32 Endy);

	void Example::OpencvTest(void);
};
#endif