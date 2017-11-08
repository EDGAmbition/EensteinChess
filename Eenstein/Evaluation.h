//class CState;
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include"BoardState.h"

class CEvaluation{
public:
	CEvaluation();
	~CEvaluation();
	double Evaluate(int board[6][6]);
//	CState TempState;
protected:
	double BValue[7]; //单个棋子的价值（灵活性+位置价值-威胁） init=5
	double FlexibilityValue(int board[][6],int x,int y);
	double ThreatValue(int board[][6],int x,int y,double val);
	void Possibility(int num,int flag[],int Exist[]);
};

