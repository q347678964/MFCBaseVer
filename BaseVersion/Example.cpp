#include "stdafx.h"
#include "resource.h"

#include "FormatChange.h"
#include "Example.h"
#include "BaseVersionDlg.h"

Example::Example(){
	this->Printf((CString)"***********************\r\n");
}

Example::~Example(){

}

void Example::Printf(CString Context){
	Context = (CString)("[Example]") + Context;
    CBaseVersionDlg *MainDlg = (CBaseVersionDlg *)AfxGetMainWnd();
	MainDlg->Printf(Context);
}

DWORD WINAPI ThreadProc(LPVOID pParam)
{
	Example *Ex = (Example *)pParam;
	Ex->Printf((CString)"线程休眠\r\n");
	Sleep(1000);
	Ex->Printf((CString)"线程结束\r\n");
	return 0;
}
void Example::ThreadTest(void){
	this->Printf((CString)"线程测试开始\r\n");
	AfxBeginThread((AFX_THREADPROC)ThreadProc,this,THREAD_PRIORITY_HIGHEST);
	this->Printf((CString)"线程已经创建\r\n");
}
void Example::TimerTest(void){

	this->Printf((CString)"时间测试开始\r\n");

	clock_t TimeStart,TimeEnd;
	unsigned int TimeSpend;
	TimeStart = clock();
	Sleep(100);
	TimeEnd = clock();

	TimeSpend = TimeEnd - TimeStart;

	CString TempCString;
	TempCString.Format(_T("时间间隔:%u毫秒\r\n"),TimeSpend);
	this->Printf(TempCString);

	CTime time = CTime::GetCurrentTime();   ///构造CTime对象
#if 0
	int m_nYear = time.GetYear();      ///年
	int m_nMonth = time.GetMonth();      ///月
	int m_nDay = time.GetDay();      ///日
	int m_nHour = time.GetHour();      ///小时
	int m_nMinute = time.GetMinute();   ///分钟
	int m_nSecond = time.GetSecond();   ///秒
#endif
	CString m_strTime = time.Format("%Y-%m-%d %H:%M:%S");
	m_strTime += (CString)("\r\n");
	this->Printf(m_strTime);
	this->Printf((CString)"时间测试完成\r\n");

}

void Example::FileOperation(void){
	this->Printf((CString)"文件操作测试开始\r\n");

	const char data[] = {"This is a test program"};
	CFile mFile(_T("../Output/Test.txt"),CFile::modeCreate | CFile::modeReadWrite);
	mFile.Write(data,sizeof(data));
	mFile.Close();

	this->Printf((CString)"文件操作测试完成\r\n");

}
