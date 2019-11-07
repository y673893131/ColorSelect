
// ColorDlg.h : 头文件
//

#pragma once
#include "afxcolorbutton.h"
#include "afxcmn.h"


// CColorDlg 对话框
class CColorDlg : public CDialogEx
{
// 构造
public:
	CColorDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CColorDlg();
// 对话框数据
	enum { IDD = IDD_COLOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
