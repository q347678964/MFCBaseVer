
// BaseVersionDlg.h : ͷ�ļ�
//

#pragma once


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
	BOOL CBaseVersionDlg::PreTranslateMessage(MSG* pMsg);


public:
	CString g_Path;

	void CBaseVersionDlg::DlgPaintInit(void);
	BOOL CBaseVersionDlg::Printf(CString string);
	afx_msg void OnBnClickedButtonOpenfile();
};
