
// EensteinDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Eenstein.h"
#include "EensteinDlg.h"
#include "afxdialogex.h"
#include "Move.h"
#include"Evaluation.h"
#include"BoardState.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEensteinDlg 对话框



CEensteinDlg::CEensteinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_EENSTEIN_DIALOG, pParent)
	, m_PosStr(_T(""))
	, m_RandNum(0)
	, WhoseRound(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEensteinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_PosStr);
	DDX_Text(pDX, IDC_EDIT2, m_RandNum);
	DDX_Text(pDX, IDC_EDIT3, WhoseRound);
}

BEGIN_MESSAGE_MAP(CEensteinDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_NewGame, &CEensteinDlg::OnClickedNewgame)
	ON_BN_CLICKED(IDC_GetRandom, &CEensteinDlg::OnBnClickedGetrandom)
	ON_WM_LBUTTONDOWN()
	ON_EN_CHANGE(IDC_EDIT3, &CEensteinDlg::OnEnChangeEdit3)
END_MESSAGE_MAP()


// CEensteinDlg 消息处理程序

BOOL CEensteinDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	memset(m_Board, 0, sizeof(m_Board));
	//m_Board[1][1] = -1;
	ChosenPos.flag = 0;
	WhoseRound = "RED";
//	IsGameOver = 0;
	p_CMove = new CMove;

	CBoardState *mp_CBoardState;
	CEvaluation *mp_CEvaluation;

	mp_CBoardState = new CBoardState;
	mp_CEvaluation = new CEvaluation;

	p_CMove->SetBoardState(mp_CBoardState);
	p_CMove->SetEvaluator(mp_CEvaluation);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CEensteinDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEensteinDlg::OnPaint()
{
/*
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
		CDialog::OnPaint();
	}
*/
	CPaintDC dc(this);
	int i, j;

	//»­ºáÖá£»

	for (i = 0; i < GRID_NUM; i++)
	{
		dc.MoveTo(BOARD_POS_X, BOARD_POS_Y + i*BOARD_WIDTH);
		dc.LineTo(BOARD_POS_X + 5 * BOARD_WIDTH, BOARD_POS_Y + i*BOARD_WIDTH);
	}

	//»­ÊúÖá£»
	for (j = 0; j <GRID_NUM; j++)
	{
		dc.MoveTo(BOARD_POS_X + j*BOARD_WIDTH, BOARD_POS_Y);
		dc.LineTo(BOARD_POS_X + j*BOARD_WIDTH, BOARD_POS_Y + 5 * BOARD_WIDTH);
	}

	//»­Æå×Ó£º

	for (i = 1; i <= 5; i++)
	{
		for (j = 1; j <= 5; j++)
		{
			if (m_Board[i][j]>0)
			{ // blue
				char a[2];
				a[0] = '0' + m_Board[i][j];
				a[1] = '\0';
				CString str(a);
				CPen pen(PS_SOLID, 1, RGB(255, 255, 255));
				CBrush brush(RGB(0, 0, 255));

				dc.SelectObject(&brush);//½«pen·Åµ½dcÉÏ
				dc.Rectangle(BOARD_POS_X + (j - 1)*BOARD_WIDTH, BOARD_POS_Y + (i - 1)*BOARD_WIDTH,
					BOARD_POS_X + j*BOARD_WIDTH, BOARD_POS_Y + i*BOARD_WIDTH);

				//	dc.SelectObject(&pen);
				dc.TextOut(BOARD_POS_X + (j - 1)*BOARD_WIDTH + BOARD_WIDTH / 2 - 3, BOARD_POS_Y + (i - 1)*BOARD_WIDTH + BOARD_WIDTH / 2 - 3, str);

			}
			else if (m_Board[i][j]<0)
			{
				char a[2];
				a[0] = '0' + abs(m_Board[i][j]);
				a[1] = '\0';
				CString str(a) ;
				CPen pen(PS_SOLID, 1, RGB(255, 255, 255));
				CBrush brush(RGB(255, 0, 0));
				dc.SelectObject(&brush);//½«pen·Åµ½dcÉÏ
				dc.Rectangle(BOARD_POS_X + (j - 1)*BOARD_WIDTH, BOARD_POS_Y + (i - 1)*BOARD_WIDTH,
					BOARD_POS_X + j*BOARD_WIDTH, BOARD_POS_Y + i*BOARD_WIDTH);
				dc.SelectObject(&pen);
				dc.TextOut(BOARD_POS_X + (j - 1)*BOARD_WIDTH + BOARD_WIDTH / 2 - 3, BOARD_POS_Y + (i - 1)*BOARD_WIDTH + BOARD_WIDTH / 2 - 3, str);
			}

		}
	}

	if (ChosenPos.flag) {
		CPaintDC dc2(this);
		CPen pen(PS_SOLID, 1, RGB(255, 255, 255));
		dc2.SelectObject(&pen);
		//dc2.SelectObject()
		dc2.Arc(BOARD_POS_X + (ChosenPos.x - 1)*BOARD_WIDTH, BOARD_POS_Y + (ChosenPos.y - 1)*BOARD_WIDTH,
			BOARD_POS_X + (ChosenPos.x)*BOARD_WIDTH, BOARD_POS_Y + (ChosenPos.y)*BOARD_WIDTH,
			BOARD_POS_X + (ChosenPos.x - 1)*BOARD_WIDTH + BOARD_WIDTH / 2, BOARD_POS_Y + (ChosenPos.y - 1)*BOARD_WIDTH,
			BOARD_POS_X + (ChosenPos.x - 1)*BOARD_WIDTH + BOARD_WIDTH / 2, BOARD_POS_Y + (ChosenPos.y - 1)*BOARD_WIDTH);
	}

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CEensteinDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CEensteinDlg::OnClickedNewgame()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	memset(m_Board, 0, sizeof(m_Board));
	m_Board[1][1] = '0' - m_PosStr[0];
	m_Board[1][2] = '0' - m_PosStr[1];
	m_Board[1][3] = '0' - m_PosStr[2];
	m_Board[2][1] = '0' - m_PosStr[3];
	m_Board[2][2] = '0' - m_PosStr[4];
	m_Board[3][1] = '0' - m_PosStr[5];

	m_Board[3][5] = 2;
	m_Board[4][4] = 4;
	m_Board[4][5] = 5;
	m_Board[5][3] = 6;
	m_Board[5][4] = 1;
	m_Board[5][5] = 3;
	nSide = RED;

	InvalidateRect(NULL, TRUE);
	UpdateWindow();
}


void CEensteinDlg::OnBnClickedGetrandom()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RandNum = CMove::GetRandomNum();
	if (nSide == BLUE) {

		p_CMove->SearchAGoodMove(m_Board, m_RandNum);
		UpdateData(FALSE);
		InvalidateRect(NULL, TRUE);
		nSide = RED;
		if (nSide == RED)
			WhoseRound = "RED";
		else
			WhoseRound = "BLUE";
	}
	//	ChosenPos.x
	UpdateData(FALSE);
}


void CEensteinDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nSide == RED) {
		// TODO: Add your message handler code here and/or call default
		//memset(m_Board,-1,sizeof(m_Board));
		CDC *pDC;
		pDC = GetDC();
		CRect rect(BOARD_POS_X - 5, BOARD_POS_Y - 5, BOARD_POS_X + 5 * BOARD_WIDTH + 5, BOARD_POS_Y + 5 * BOARD_WIDTH + 5);
		int j = (point.x - BOARD_POS_X) / BOARD_WIDTH + 1;
		int i = (point.y - BOARD_POS_Y) / BOARD_WIDTH + 1;

		if (i >= 1 && i <= 5 && j >= 1 && j <= 5 && m_Board[i][j]<0 && !ChosenPos.flag) { //user command RED side
			ChosenPos.x = i;
			ChosenPos.y = j;
			ChosenPos.flag = 1;
			ChosenPos.nChess = m_Board[i][j];
		}

		else if (i >= 1 && i <= 5 && j >= 1 && j <= 5 &&
			(i == ChosenPos.x || i == ChosenPos.x + 1) &&
			(j == ChosenPos.y || j == ChosenPos.y + 1) &&
			ChosenPos.flag) {
			if (i == ChosenPos.x && j == ChosenPos.y) {
				ChosenPos.flag = 0;
			}
			else {
				m_Board[i][j] = ChosenPos.nChess;
				m_Board[ChosenPos.x][ChosenPos.y] = 0;
				ChosenPos.flag = 0;
				nSide = BLUE;
			}
		}
		if (nSide == RED)
			WhoseRound = "RED";
		else
			WhoseRound = "BLUE";
		UpdateData(FALSE);
		InvalidateRect(NULL, TRUE);
		UpdateWindow();
		//SetCapture();
		CDialog::OnLButtonDown(nFlags, point);
	}
}


void CEensteinDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (nSide == RED)
		WhoseRound = "RED";
	else
		WhoseRound = "BLUE";
	UpdateData(FALSE);
}
