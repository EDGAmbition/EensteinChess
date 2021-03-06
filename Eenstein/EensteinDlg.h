
// EensteinDlg.h: 头文件
//

#pragma once

#include"define.h"
#include"Move.h"
#include"Evaluation.h"
#include"BoardState.h"

typedef struct _ChosenChess {
	int x;
	int y;
	int nChess;
	int flag;
}ChosenChess;

// CEensteinDlg 对话框
class CEensteinDlg : public CDialog
{
// 构造
public:
	CEensteinDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EENSTEIN_DIALOG };
#endif

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
	afx_msg void OnClickedNewgame();
	CString m_PosStr;
	int m_RandNum;
	afx_msg void OnBnClickedGetrandom();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	int m_Board[6][6];
	ChosenChess ChosenPos;
	CMove *p_CMove;
	int nSide;
public:
	// 谁的回合
	CString WhoseRound;
	afx_msg void OnEnChangeEdit3();
};
