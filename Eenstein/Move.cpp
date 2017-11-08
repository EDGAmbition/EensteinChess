#include"StdAfx.h"
#include"Eenstein.h"
#include"Move.h"
//#include"Evaluation.h"
//#include"state.h"
#include<stdlib.h>
#include<time.h>
#include<math.h>


#ifdef _DEBUG
#undef THIS_FILE
static BYTE THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMove::CMove(){
//	p_CBoardState = new CBoardState;
//	p_CEvaluation = new CEvaluation;
}

CMove::~CMove(){
	delete p_CBoardState;
	delete p_CEvaluation;
}

int CMove::GetRandomNum(){
	srand((unsigned) time(NULL));
	return rand()%6 +1;
}

int CMove::IsExist(int Num,int nExist[] ){
	//if(nExist[Num]) 
		return 1;
	//else
		return 0;
}



ChessPos CMove::GetPos(int board[6][6],int nChessID){
	int i,k;
	int c=0,r=0;
	for(i=1;i<=5;i++){
		for(k=1;k<=5;k++){
			if(nChessID==board[i][k]){
				c=i;
				r=k;
				break;
			}
		}
		if(c) break;
	}
	ChessPos nChessPos;
	nChessPos.x=c;
	nChessPos.y=r;
	return nChessPos;
}
/*
int CMove::GetAroundChessCount(int board[6][6],ChessPos nChessPos){
	int c,r;
	c=nChessPos.x;
	r=nChessPos.y;
	int cnt=0;
	if(board[c-1][r])   cnt++;
	if(board[c][r-1])   cnt++;
	if(board[c-1][r-1]) cnt++;
	return cnt;
}
*/
double CMove::GenerateMove(int board[6][6],ChessPos nChessPos){
	int nBoard[6][6];
	Copy(board,nBoard); //from ... to ...
	int WhichStep=0;
	double max=-10000;
	for(int i=1;i<=3;i++){ //选出最好一步 
		MakeMove(nBoard,nChessPos,i);
		double temp;
		temp=p_CEvaluation->Evaluate(nBoard);
		if(temp>max){
			max=temp;
			WhichStep=i;
		}
		UnMakeMove(board,nBoard,nChessPos,i); 
	}
	MakeMove(board,nChessPos,WhichStep);
	p_CBoardState->UpdateBoardState(board);
	return max;
}

void CMove::Copy(int b[][6],int nB[][6]){
	for(int i=0;i<6;i++){
		for(int j=0;i<6;j++){
			nB[i][j]=b[i][j];
		}
	}
}

void CMove::MakeMove(int board[][6],ChessPos nChessPos,int i){
	switch(i){
		case'1':{
			t1=t0;
			t0=0;
			break;
		}
		case'2':{
			t2=t0;
			t0=0;
			break;
		}
		case'3':{
			t3=t0;
			t0=0;
			break;
		}
	}
}

void CMove::UnMakeMove(int board[][6],int nBoard[][6],ChessPos nChessPos,int i){
	switch(i){
		case'1':{
			nBoard[nChessPos.x][nChessPos.y]=nBoard[nChessPos.x-1][nChessPos.y];
			nBoard[nChessPos.x-1][nChessPos.y]=t1;
			break;
		}
		case'2':{
			nBoard[nChessPos.x][nChessPos.y]=nBoard[nChessPos.x-1][nChessPos.y-1];
			nBoard[nChessPos.x-1][nChessPos.y]=t2;
			break;
		}
		case'3':{
			nBoard[nChessPos.x][nChessPos.y]=nBoard[nChessPos.x][nChessPos.y-1];
			nBoard[nChessPos.x][nChessPos.y-1]=t3;
			break;
		}
	}
}


void CMove::SearchAGoodMove(int board[][6],int RandNum){
	int copy_board[6][6];
	int flag=0;
	double a,b;
	ChessPos TempChessPos;
	ChessPos TempChessPos1,TempChessPos2;
	flag=IsExist(RandNum , (p_CBoardState->BExist));
	if(flag){
		TempChessPos=GetPos(board,RandNum);
		GenerateMove(board,TempChessPos);
	}
	else{
		int min=1000;
		Copy(board,copy_board);
		for(int i=1;i<=6;i++){ // get min
			if(p_CBoardState->BExist[i]){
				if(abs(i-RandNum)<min){
					min=abs(i-RandNum); 
				}
			}
		}
		int cnt=0;
		for(int i=1;i<=6;i++){
			if(min==abs(i-RandNum)){
				cnt++;
	//			TempChessPos=GetPos(board,i);
				if(cnt==1){
					TempChessPos1=GetPos(board,i);
					a=GenerateMove(board,TempChessPos1);
					Copy(copy_board,board);
				}
				else if(cnt==2){
					TempChessPos2=GetPos(board,i);
					b=GenerateMove(board,TempChessPos2);
					Copy(copy_board,board);
				}
			}
		}
		if(a>b) GenerateMove(board,TempChessPos1);
		else    GenerateMove(board,TempChessPos2);

	}
}