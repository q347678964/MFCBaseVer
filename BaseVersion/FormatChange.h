#ifndef FORMAT_CHANGE
#define FORMAT_CHANGE


class FormatChange {

public:
	FormatChange();
	~FormatChange();
	int FormatChange::CStringToChar(CString Context,char *Char);
	CString FormatChange::CharToCString(char *Char);
	int FormatChange::CStringToInt(CString Context);
	CString FormatChange::IntToCString(int Num);
	void CImage2CBitmap(CImage &Image,CBitmap &Bitmap);
	void FormatChange::CBitmap2Hbitmap(CBitmap &Bitmap,HBITMAP &Hbitmap);
	void FormatChange::Hbitmap2CBitmap(HBITMAP &Hbitmap,CBitmap &Bitmap);
};
#endif