#pragma once

#ifndef	LOGIN_DLG_H
#define	LOGIN_DLG_H
// Logindlg 对话框
#include "FormatChange.h"

typedef enum LOGIN_MOVE_DIR
{
	LOGIN_MOVE_RIGHT,
	LOGIN_MOVE_BOTTOM,
}LOGIN_MOVE_DIR;

typedef enum LOGIN_DEST_TYPE
{
	LOGIN_DEST_EDIT = 0,
	LOGIN_DEST_BUTTON,
}LOGIN_DEST_TYPE;

typedef enum LOGIN_USER_
{
	LOGIN_USER_IDLE = 0,
	LOGIN_USER_CUSTOMER,
	LOGIN_USER_ROOT,
}LOGIN_USER;

class Logindlg : public CDialog, public FormatChange
{
	DECLARE_DYNAMIC(Logindlg)

public:
	Logindlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Logindlg();
	LOGIN_USER  CurLoginUser;
// 对话框数据
	enum { IDD = IDD_LOGINDLG };

protected:
	HICON m_hIcon;
	afx_msg void OnPaint();
	void DlgPaintInit(void);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HBRUSH Logindlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);	//重载颜色控制函数
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void MoveTo(CWnd **SrcWnd,CWnd **DestWnd,int DestID,LOGIN_DEST_TYPE DestType,LOGIN_MOVE_DIR MoveMethod);
	void Logindlg::LoadPassword(void);
	void Logindlg::SavePassword(CString Pw);
	CString Logindlg::CreatePawword(void);
	afx_msg void OnBnClickedButtonReg();
	void Logindlg::CustomerLoginNotify(void);
	void Logindlg::RootLoginNotify(void);
	void Logindlg::LoginNotifyThreadStart(LOGIN_USER LoginUser);
};
#endif