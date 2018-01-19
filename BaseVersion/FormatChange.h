#ifndef FORMAT_CHANGE
#define FORMAT_CHANGE

/*
#define GetRValue(rgb)      ((BYTE)(rgb))
#define GetGValue(rgb)      ((BYTE)(((WORD)(rgb)) >> 8))
#define GetBValue(rgb)      ((BYTE)((rgb)>>16))
*/
class FormatChange {

public:
	FormatChange();
	~FormatChange();
	int FormatChange::CStringToChar(CString Context,char *Char);
	CString FormatChange::CharToCString(char *Char);
	int FormatChange::WcharToChar(WCHAR *Wchar,char *Char);
	int FormatChange::CStringToInt(CString Context);
	CString FormatChange::IntToCString(int Num);
	void CImage2CBitmap(CImage &Image,CBitmap &Bitmap);
	void FormatChange::CBitmap2Hbitmap(CBitmap &Bitmap,HBITMAP &Hbitmap);
	void FormatChange::Hbitmap2CBitmap(HBITMAP &Hbitmap,CBitmap &Bitmap);
};
#endif