
// BaseVersionDlg.h : ͷ�ļ�
//

#pragma once

#ifndef BASE_VERSION_DLG_H
#define BASE_BERSION_DLG_H

typedef enum MOVE_DIR
{
	MOVE_RIGHT,
	MOVE_BOTTOM,
}MOVE_DIR;

typedef enum DEST_TYPE
{
	DEST_EDIT = 0,
	DEST_BUTTON,
}DEST_TYPE;
// CBaseVersionDlg �Ի���
class CBaseVersionDlg : public CDialog
{
// ����
public:
	CBaseVersionDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BASEVERSION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	BOOL CBaseVersionDlg::PreTranslateMessage(MSG* pMsg);			//������Ϣ���亯��
	HBRUSH CBaseVersionDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);	//������ɫ���ƺ���
public:
	CString g_Path;

	void CBaseVersionDlg::MoveTo(CWnd **SrcWnd,CWnd **DestWnd,int DestID,DEST_TYPE DestType,MOVE_DIR MoveMethod);
	void CBaseVersionDlg::DlgPaintInit(void);
	BOOL CBaseVersionDlg::Printf(CString string);
	void CBaseVersionDlg::ProcessCtrl(int Num);
	void CBaseVersionDlg::PathEditCtrl(CString EditCString);

	afx_msg void OnBnClickedButtonOpenfile();
	afx_msg void OnBnClickedButtonTest();
};

#endif