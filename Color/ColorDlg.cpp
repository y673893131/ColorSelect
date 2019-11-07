
// ColorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Color.h"
#include "ColorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define HOTKEY_ID WM_USER + 1234
#define HOTKEY_SHOW_ID WM_USER + 1235
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CColorDlg 对话框



CColorDlg::CColorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CColorDlg::IDD, pParent)
	, m_Color_R(0)
	, m_Color_G(0)
	, m_Color_B(0)
	, m_Color_Hex(_T(""))
	, m_delayTime(3)
	, m_prefix(_T("#"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CColorDlg::~CColorDlg()
{
	UnregisterHotKey(GetSafeHwnd(), HOTKEY_ID);
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Color_R);
	DDV_MinMaxInt(pDX, m_Color_R, 0, 255);
	DDX_Text(pDX, IDC_EDIT2, m_Color_G);
	DDV_MinMaxInt(pDX, m_Color_G, 0, 255);
	DDX_Text(pDX, IDC_EDIT3, m_Color_B);
	DDV_MinMaxInt(pDX, m_Color_B, 0, 255);
	DDX_Text(pDX, IDC_EDIT4, m_Color_Hex);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_color_Select);
	DDX_Control(pDX, IDC_HOTKEY1, m_hotkey);
	DDX_Text(pDX, IDC_EDIT5, m_delayTime);
	DDV_MinMaxInt(pDX, m_delayTime, 0, 255);
	DDX_Text(pDX, IDC_EDIT6, m_prefix);
}

BEGIN_MESSAGE_MAP(CColorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CColorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CColorDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDCLEAN, &CColorDlg::OnBnClickedClean)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CColorDlg::OnBnClickedMfccolorbutton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CColorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CColorDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CColorDlg 消息处理程序

BOOL CColorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	//右下角
	CRect rt1;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rt1, 0);
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	CRect wR;
	GetWindowRect(&wR);
	::SetWindowPos(m_hWnd, HWND_TOPMOST, x - wR.Width(), rt1.Height() - wR.Height(), 0, 0, SWP_NOSIZE);
	
	//CenterWindow();
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	::RegisterHotKey(GetSafeHwnd(), HOTKEY_ID, /*MOD_CONTROL*/0, VK_F2);
	::RegisterHotKey(GetSafeHwnd(), HOTKEY_SHOW_ID, MOD_CONTROL, VK_F12);

	EnableToolTips(TRUE);
	
	m_tooltips = new CToolTipCtrl;
	m_tooltips->Create(this);
	m_tooltips->Activate(TRUE);
	m_tooltips->AddTool(this, _T(""));
	m_tooltips->SetMaxTipWidth(200);
	

	m_tooltips->SetDelayTime(TTDT_AUTOPOP, m_delayTime * 1000);
	m_tooltips->SetDelayTime(TTDT_RESHOW, m_delayTime * 1000);
	ShowWindow(SW_HIDE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CColorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CColorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CColorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CColorDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	if (m_Color_Hex.IsEmpty())
		m_Color_Hex.Format(_T("%02X%02X%02X"), m_Color_R, m_Color_G, m_Color_B);
	else
	{
		if (m_Color_Hex.GetLength() != 6) return;
		m_Color_Hex.MakeUpper();
		swscanf_s(m_Color_Hex, _T("%02X%02X%02X"), &m_Color_R, &m_Color_G, &m_Color_B);
	}

	m_color_Select.SetColor(RGB(m_Color_R, m_Color_G, m_Color_B));
	UpdateData(FALSE);
}


void CColorDlg::OnBnClickedCancel()
{
	OnCancel();
}


void CColorDlg::OnBnClickedClean()
{
	m_Color_R = 0;
	m_Color_G = 0;
	m_Color_B = 0;
	m_Color_Hex.Empty();
	UpdateData(FALSE);
}


void CColorDlg::OnBnClickedMfccolorbutton1()
{
	UpdateData(TRUE);
	
	
	COLORREF  color = m_color_Select.GetColor();
	m_Color_R = GetRValue(color);
	m_Color_G = GetGValue(color);
	m_Color_B = GetBValue(color);
	m_Color_Hex.Format(_T("%02X%02X%02X"), m_Color_R, m_Color_G, m_Color_B);
	UpdateData(FALSE);
}


void CColorDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		KillTimer(nIDEvent);
		ShowWindow(SW_HIDE);
		SetTimer(2, 5000, NULL);
	}
	if (nIDEvent == 2)
	{
		KillTimer(nIDEvent);
		CRect wR;
		GetClientRect(&wR);
		::SetWindowPos(m_hWnd, HWND_TOPMOST, wR.Width(), wR.Height(), 0, 0, SWP_NOSIZE);
		ShowWindow(SW_SHOW);
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CColorDlg::toCopyText(const CString& sText)
{
	auto dwLength = sText.GetLength();
	HANDLE hGlobalMemory = GlobalAlloc(GHND, dwLength * 2 + 2); //分配全局内存并获取句柄
	LPBYTE lpGlobalMemory = (LPBYTE)GlobalLock(hGlobalMemory);	// 锁定全局内存
	memcpy(lpGlobalMemory, sText, dwLength * 2);
	lpGlobalMemory[dwLength * 2] = '\0';
	lpGlobalMemory[dwLength * 2 + 1] = '\0';

	GlobalUnlock(hGlobalMemory);						// 锁定内存块解锁
	HWND hWnd = GetSafeHwnd();							// 获取安全窗口句柄

	::OpenClipboard(hWnd);								// 打开剪贴板
	::EmptyClipboard();									// 清空剪贴板
	::SetClipboardData(CF_UNICODETEXT, hGlobalMemory);	// 将内存中的数据放置到剪贴板
	::CloseClipboard();									// 关闭剪贴板
}

BOOL CColorDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_HOTKEY)
	{
		if (pMsg->wParam == HOTKEY_ID)
		{
			MSG pTmpMsg;
			pTmpMsg.hwnd = pMsg->hwnd;
			HDC hDC = ::GetDC(NULL);
			COLORREF color = ::GetPixel(hDC, pMsg->pt.x, pMsg->pt.y);
			
			m_Color_R = GetRValue(color);
			m_Color_G = GetGValue(color);
			m_Color_B = GetBValue(color);
			m_Color_Hex.Format(_T("%02X%02X%02X"), m_Color_R, m_Color_G, m_Color_B);
			m_color_Select.SetColor(RGB(m_Color_R, m_Color_G, m_Color_B));
			UpdateData(FALSE);
			SetFocus();
			GetDlgItem(IDC_EDIT4)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT4))->SetSel(0, -1);
			toCopyText(m_prefix + m_Color_Hex);
			//SetFocus();
			static CString s;
			s.Format(_T("Hex:%02X%02X%02X,RGB(%d,%d,%d)"), m_Color_R, m_Color_G, m_Color_B, m_Color_R, m_Color_G, m_Color_B);
			m_tooltips->Pop();
			m_tooltips->UpdateTipText(s, this, 0);
			pTmpMsg.message = WM_MOUSEMOVE;

			m_tooltips->RelayEvent(&pTmpMsg);
			m_tooltips->Update();
			DeleteDC(hDC);
		}
		if (pMsg->wParam == HOTKEY_SHOW_ID)
			ShowWindow(SW_SHOW);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CColorDlg::OnBnClickedButton1()
{
	ShowWindow(SW_HIDE);
}
UINT ModToHotkey(UINT fsModifiers)
{
	if ((fsModifiers & MOD_SHIFT) && !(fsModifiers & MOD_ALT)) // shift转alt
	{
		fsModifiers &= ~MOD_SHIFT;
		fsModifiers |= HOTKEYF_SHIFT;
	}
	else if (!(fsModifiers & MOD_SHIFT) && (fsModifiers & MOD_ALT)) // alt转shift
	{
		fsModifiers &= ~MOD_ALT;
		fsModifiers |= HOTKEYF_ALT;
	}
	return fsModifiers;
}

UINT HotkeyToMod(UINT fsModifiers)
{
	if ((fsModifiers & HOTKEYF_SHIFT) && !(fsModifiers & HOTKEYF_ALT)) // shift转alt
	{
		fsModifiers &= ~HOTKEYF_SHIFT;
		fsModifiers |= MOD_SHIFT;
	}
	else if (!(fsModifiers & HOTKEYF_SHIFT) && (fsModifiers & HOTKEYF_ALT)) // alt转shift
	{
		fsModifiers &= ~HOTKEYF_ALT;
		fsModifiers |= MOD_ALT;
	}
	return fsModifiers;
}

void CColorDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	WORD hotkey,hotcode;
	m_hotkey.GetHotKey(hotkey, hotcode);
	if (hotkey)
	{
		SendMessage(WM_SETHOTKEY, m_hotkey.GetHotKey());
		UnregisterHotKey(GetSafeHwnd(), HOTKEY_ID);
		::RegisterHotKey(GetSafeHwnd(), HOTKEY_ID, HotkeyToMod(hotcode), /*hotcode*/hotkey);
		CString s;
		s.Format(_T("%s捕捉鼠标颜色(Ctrl+F12呼出)"), m_hotkey.GetHotKeyName());
		SetWindowText(s);
	}

	m_tooltips->SetDelayTime(TTDT_AUTOPOP, m_delayTime * 1000);
	m_tooltips->SetDelayTime(TTDT_RESHOW, m_delayTime * 1000);
}