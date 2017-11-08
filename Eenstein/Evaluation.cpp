#include"StdAfx.h"
#include"Eenstein.h"
#include"Evaluation.h"
//#include"BoardState.h"
//#include<math.h>
//#include<string.h>

const int PosValue[6][6]=
	{
		{-1000,-1111,-1111,-1111,-1111,-1111},
		{-1111,1000,9,8,7,6},
		{-1111,9,9,7,6,5},
		{-1111,8,7,8,5,4},
		{-1111,7,6,5,7,3},
		{-1111,6,5,4,3,6},
	};
CEvaluation::CEvaluation(){
	for(int i=1;i<7;i++){
		if(i%2)
			BValue[i]=5;
		else
			BValue[i]=6;
	}
}

CEvaluation::~CEvaluation(){
	
}

double CEvaluation::Evaluate(int board[6][6]){
	double BValue[7];
	memset(BValue,5,sizeof(double)*7);
	for(int i=1;i<=5;i++){
		for(int j=1;j<5;j++){
			if(board[i][j]>0){
				BValue[board[i][j]]+=FlexibilityValue(board,i,j);
				BValue[board[i][j]]+=PosValue[i][j];
				double temp=ThreatValue(board,i,j,board[i][j]);
				BValue[board[i][j]]+=temp;
			}
		}
	}
	double sum=0;
	for(int i=1;i<=6;i++){
		sum+=BValue[i];
	}
	return sum;
}



double CEvaluation::FlexibilityValue(int board[][6],int x,int y){
	int cnt=0;
	double fv=0;
	if(board[x-1][y]>0){
		cnt++;
		fv-=3.0;
	}
	if(board[x-1][y-1]>0){
		cnt++;
		fv-=5.0;
	}
	if(board[x][y-1]>0){
		cnt++;
		fv-=3.0;
	}
	if(cnt==3)
		fv-=4.0;
	return fv;
}

double CEvaluation::ThreatValue(int board[][6],int x,int y,double val){
//	class CBoardState;
	CBoardState TempState;
	TempState.UpdateBoardState(board);
	int flag[7];
	memset(flag,0,sizeof(int)*7);
	int dx[3][2]={{-1,0},{-1,-1},{0,-1}};
	for(int j=0;j<3;j++){
		int nChess=board[x+dx[j][0]][y+dx[j][1]];
		if(nChess<0){  //是敌人
			Possibility(abs(nChess),flag,TempState.RExist);
		}
	}
	int cnt=0;
	for(int i=1;i<=6;i++)
		if(flag[i])
			cnt++;
	return val*cnt/6;
}

void CEvaluation::Possibility(int num,int flag[],int Exist[]){
	if(Exist[num])
		flag[num];
	else{
		int min=6;
		for(int i=1;i<=6;i++){
			if(abs(num-i)<min){
				min=abs(num-i);
			}
		}
		for(int i=1;i<=6;i++){
			if(min==abs(num-i))
				flag[i]=1;
		}
	}
	
}



