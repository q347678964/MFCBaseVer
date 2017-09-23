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
	Ex->Printf((CString)"�߳�����\r\n");
	Sleep(1000);
	Ex->Printf((CString)"�߳̽���\r\n");
	return 0;
}
void Example::ThreadTest(void){
	this->Printf((CString)"�̲߳��Կ�ʼ\r\n");
	AfxBeginThread((AFX_THREADPROC)ThreadProc,this,THREAD_PRIORITY_HIGHEST);
	this->Printf((CString)"�߳��Ѿ�����\r\n");
}
void Example::TimerTest(void){

	this->Printf((CString)"ʱ����Կ�ʼ\r\n");

	clock_t TimeStart,TimeEnd;
	unsigned int TimeSpend;
	TimeStart = clock();
	Sleep(100);
	TimeEnd = clock();

	TimeSpend = TimeEnd - TimeStart;

	CString TempCString;
	TempCString.Format(_T("ʱ����:%u����\r\n"),TimeSpend);
	this->Printf(TempCString);

	CTime time = CTime::GetCurrentTime();   ///����CTime����
#if 0
	int m_nYear = time.GetYear();      ///��
	int m_nMonth = time.GetMonth();      ///��
	int m_nDay = time.GetDay();      ///��
	int m_nHour = time.GetHour();      ///Сʱ
	int m_nMinute = time.GetMinute();   ///����
	int m_nSecond = time.GetSecond();   ///��
#endif
	CString m_strTime = time.Format("%Y-%m-%d %H:%M:%S");
	m_strTime += (CString)("\r\n");
	this->Printf(m_strTime);
	this->Printf((CString)"ʱ��������\r\n");

}

void Example::FileOperation(void){
	this->Printf((CString)"�ļ��������Կ�ʼ\r\n");

	const char data[] = {"This is a test program"};
	CFile mFile(_T("../Output/Test.txt"),CFile::modeCreate | CFile::modeReadWrite);
	mFile.Write(data,sizeof(data));
	mFile.Close();

	this->Printf((CString)"�ļ������������\r\n");

}
