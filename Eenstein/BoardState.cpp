#include"StdAfx.h"
#include"Eenstein.h"
#include"BoardState.h"
#include<math.h>
#include<string.h>

CBoardState::CBoardState(){
	BNum=6;
	RNum=6;
	for(int i=1;i<=6;i++){
		BExist[i]=1;
		RExist[i]=1;
	}
	BExist[0]=-1;
	RExist[0]=-1;
}

CBoardState::~CBoardState(){
	
}

void CBoardState::UpdateBoardState(int board[][6]){
	for(int i=1;i<=5;i++){
		for(int j=1;j<=5;j++){
			if(board[i][j]>0){
				BNum++;
				BExist[abs(BNum)]=1;
			}
			else if(board[i][j]<0){
				RNum++;
				RExist[abs(RNum)]=1;	
			}
		}
	}
}