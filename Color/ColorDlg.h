
// ColorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcolorbutton.h"
#include "afxcmn.h"


// CColorDlg �Ի���
class CColorDlg : public CDialogEx
{
// ����
public:
	CColorDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CColorDlg();
// �Ի�������
	enum { IDD = IDD_COLOR_DIALOG };

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
public:
	int m_Color_R;
	int m_Color_G;
	int m_Color_B;
	CString m_Color_Hex;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedClean();
	afx_msg void OnBnClickedMfccolorbutton1();
	CMFCColorButton m_color_Select;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CHotKeyCtrl m_hotkey;
	CToolTipCtrl* m_tooltips;
private:
	void toCopyText(const CString&);
public:
	int m_delayTime;
	CString m_prefix;
};
