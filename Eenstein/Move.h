

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include"BoardState.h"
#include"Evaluation.h"

class CMove{
public:
	CMove();
	virtual ~CMove();
	static int GetRandomNum(); 
	int IsExist(int Num,int nExist[7]);
//	int Exist[7];
//	int GetAroundChessCount(int board[6][6],ChessPos nChessPos);
	static ChessPos  GetPos(int board[6][6],int Num);
	double GenerateMove(int board[6][6],ChessPos nChessPos);
	void SearchAGoodMove(int board[][6],int RandNum);
	void SetEvaluator(CEvaluation *pEval){p_CEvaluation = pEval;};
	void SetBoardState(CBoardState *pBS){p_CBoardState = pBS;};
protected:
	void MakeMove(int nBoard[][6],ChessPos nChessPos,int i);
	void UnMakeMove(int board[][6],int nBoard[][6],ChessPos nChessPos,int i);
	void Copy(int board[][6],int nBoard[][6]);
	CBoardState *p_CBoardState;
	CEvaluation *p_CEvaluation;
	
};

