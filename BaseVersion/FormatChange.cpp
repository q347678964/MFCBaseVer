#include "stdafx.h"
#include "resource.h"

#include "FormatChange.h"


FormatChange::FormatChange(){

}
FormatChange::~FormatChange(){

}
/*
*	CStringToChar-将CString转换为Char*的类型.这里涉及unicode->char
*	@Context	CString
*	@Char		转换之后的存储地址，需要在外部开辟,建议和CString一样大.
*	@Ret		转换之后的大小,
*/

int FormatChange::CStringToChar(CString Context,char *Char){
	int Len =WideCharToMultiByte(CP_ACP,0,Context.GetBuffer(Context.GetLength()),-1,NULL,0,NULL,NULL); //计算长度
	WideCharToMultiByte(CP_ACP,0,Context.GetBuffer(Context.GetLength()),-1,Char,Len,NULL,NULL );	//转换
	return Len;
}
/*
*	CharToCString-将char转换为unicode的CString
*	@Context	Char地址
*	@Ret		CString
*/ 
CString FormatChange::CharToCString(char *Char){
	return CString(Char);
}
/*
*	CStringToInt-将CString转为int
*	@Context	CString
*	@Ret		int
*/ 
int FormatChange::CStringToInt(CString Context){
	int ret;
	swscanf(Context,_T("%d"),&ret); 
	return ret;
}
/*
*	CStringToInt-将int转为CString
*	@int	Num
*	@Ret	CString
*/ 
CString FormatChange::IntToCString(int Num){
	CString TempCString;
	TempCString.Format(_T("%d"),Num);
	return TempCString;
}
void FormatChange::CImage2CBitmap(CImage &Image,CBitmap &Bitmap){
	HBITMAP hbmp =(HBITMAP)Image.operator HBITMAP();		//CImage -> Hbitmap
	this->Hbitmap2CBitmap(hbmp,Bitmap);				//Hbitmap->Cbitmap
}

void FormatChange::Hbitmap2CBitmap(HBITMAP &Hbitmap,CBitmap &Bitmap){		//Hbitmap->Cbitmap
	Bitmap.DeleteObject();
	Bitmap.Attach(Hbitmap);
}

void FormatChange::CBitmap2Hbitmap(CBitmap &Bitmap,HBITMAP &Hbitmap){		//Cbitmap -> Hbitmap
	Hbitmap=(HBITMAP)Bitmap;
}
