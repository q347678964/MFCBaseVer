#include "stdafx.h"
#include "resource.h"

#include "FormatChange.h"
#include "Png.h"
#include "BaseVersionDlg.h"

/*************************************************************************************/
//构造、析构函数
Png::Png(int HDCID){
	g_PNG_HDCID = HDCID;
}

Png::~Png(){

}
/*************************************************************************************/
//主窗体操作
void Png::Init(void)
{
	g_PrintfSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
}
void Png::Exit(void)
{

}

void Png::LogPrintf(CString Context){
	static int FirstInFlag = 1;

	WaitForSingleObject(g_PrintfSemaphore, INFINITE);

	char Data[1000];
	int Len = g_FormatHandle.CStringToChar(Context,Data);

	if(FirstInFlag){
		FirstInFlag = 0;
		CFile LogFile(_T("../Output/Log.txt"),CFile::modeCreate | CFile::modeReadWrite);
		LogFile.Write(Data,Len);
		LogFile.Close();
	}else{
		CFile LogFile(_T("../Output/Log.txt"),CFile::modeReadWrite);
		LogFile.SeekToEnd();
		LogFile.Write(Data,Len);
		LogFile.Close();
	}

	ReleaseSemaphore(g_PrintfSemaphore, 1, NULL);
}

/*	PrintfToFile - 将Log打印到文件当中
*	
*/
void Png::PrintfToFile(CString Context){
	CTime time = CTime::GetCurrentTime();   ///构造CTime对象
	CString m_strTime = time.Format(_T("[%H:%M:%S]"));

	Context = m_strTime + (CString)("[Png]") + Context;
    this->LogPrintf(Context);
}

void Png::Printf(CString Context){
	CTime time = CTime::GetCurrentTime();   ///构造CTime对象
	CString m_strTime = time.Format(_T("[%H:%M:%S]"));

	Context = m_strTime + (CString)("[Png]") + Context;
    CBaseVersionDlg *MainDlg = (CBaseVersionDlg *)AfxGetMainWnd();
	MainDlg->Printf(Context);
}

void Png::TransparentPNG(CImage *png)    
{    
    for(int i = 0; i <png->GetWidth(); i++)
    {    
        for(int j = 0; j <png->GetHeight(); j++)    
        {    
            unsigned char* pucColor = reinterpret_cast<unsigned char*>(png->GetPixelAddress(i , j));    
            pucColor[0] = pucColor[0] * pucColor[3] / 255;    
            pucColor[1] = pucColor[1] * pucColor[3] / 255;    
            pucColor[2] = pucColor[2] * pucColor[3] / 255;    
        }    
    }    
}
//Move该功能暂时无效
void Png::Move(PNG_MOVE_DIR MoveDir, int Step){
	
	CWnd *StaticCwnd = this->IDToCWnd(g_PNG_HDCID);
	CStatic *PictureControl = (CStatic *)StaticCwnd;
	CRect rect;
	PictureControl->GetWindowRect(&rect);
	switch(MoveDir){
		case PNG_MOVE_UP:
			rect.top -= Step;
			rect.bottom -= Step;
			break;
		case PNG_MOVE_DOWN:
			rect.top += Step;
			rect.bottom += Step;
			break;
		case PNG_MOVE_LEFT:
			rect.left -= Step;
			rect.right -= Step;
			break;
		case PNG_MOVE_RIGHT:
			rect.left += Step;
			rect.left += Step;
			break;
	}
	PictureControl->MoveWindow(rect.left,rect.top,rect.Width(),rect.Height(),true);
	
}

void Png::Open(char *FilePath)
{
	CWnd *StaticCwnd = this->IDToCWnd(g_PNG_HDCID);
	//CWnd *StaticCwnd = GetDlgCWnd();
	CImage mImage;  

	memcpy(g_FilePath,FilePath,sizeof(g_FilePath));

    if(mImage.Load(CString(FilePath)) == S_OK)
	{	
				
		if (mImage.GetBPP() == 32) //确认该图像包含Alpha通道
		{
			this->TransparentPNG(&mImage);
		}

		HDC StaticHDC = GetDC(*StaticCwnd);			//获取控件的CDC
		CDC *StaticCDC = CDC::FromHandle(StaticHDC);//HDC->CDC
#if 1
		mImage.Draw(StaticHDC,0,0);//直接绘制到HDC上
		mImage.Destroy();
#else	//CDC没有透明通道，以下操作可能忽略掉透明色.
		CRect StaticRect;
		StaticCwnd->GetWindowRect(&StaticRect);
		int StaticWidth = StaticRect.Width();
		int StaticHeight = StaticRect.Height();

		CBitmap	CBitmap_Image;		//将CImage转换为CBitmap存储格式
		FormatChange FC;
		FC.CImage2CBitmap(mImage,CBitmap_Image);
		StaticCDC->SetBkMode(TRANSPARENT);   

		CDC *MemCDC = new CDC;;		//申请内存图片CDC
		MemCDC->CreateCompatibleDC(StaticCDC);   //CreateCompatibleDC创建一个与显示器设备内容兼容的内存设备内容
		MemCDC->SetBkMode(TRANSPARENT);
		MemCDC->SelectObject(&CBitmap_Image); //用SelectObject将位图选入内存设备内容  
#if 1
		{
		
		}
#endif
#if 0	//拉伸方式绘制
		BITMAP   bitmap;	//BITMAP结构用于存放位图信息
		CBitmap_Image.GetBitmap(&bitmap);	//从图片中获取图片的宽高到bitmap
		StaticCDC->StretchBlt(0,0,bitmap.bmWidth/2,bitmap.bmHeight/2,MemCDC,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY); //将DC内的图片内容拉伸之后PO窗体上,Stretch:拉伸
#else
		StaticCDC->BitBlt(0,0,StaticRect.Width(),StaticRect.Height(),MemCDC,0,0,SRCCOPY);	//将CDC内存的图片PO到窗体上
#endif
		delete MemCDC;
#endif
	}
}
