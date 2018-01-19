#ifndef PNG_H
#define PNG_H

#include "UtilityFunc.h"
#include "cv.h"
#include "highgui.h"
#include "CvvImage.h"

typedef enum PNG_MOVE_DIR{
	PNG_MOVE_UP = 0,
	PNG_MOVE_DOWN,
	PNG_MOVE_LEFT,
	PNG_MOVE_RIGHT,
}PNG_MOVE_DIR;

class Png : public UtilityFunc{

public:
	Png::Png(int HDCID);
	Png::~Png();
	HANDLE g_PrintfSemaphore;
	FormatChange g_FormatHandle;

	void Png::Init(void);
	void Png::Exit(void);

	void Png::LogPrintf(CString Context);
	void Png::PrintfToFile(CString Context);
	void Png::Printf(CString Context);
	void Png::TransparentPNG(CImage *png);
	void Png::TransparentPNGToZero(CImage *png);
	void Png::Open(char *FilePath);
	void Png::ShowCwnd(CWnd *StaticCwnd,char *WinName);
	void Png::Move(PNG_MOVE_DIR MoveDir, int Step);
private:
	int g_PNG_HDCID;
	char g_FilePath[100];
};
#endif