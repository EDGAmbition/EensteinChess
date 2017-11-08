#ifndef define_h_
#define define_h_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define BOARD_POS_X   60
#define BOARD_POS_Y   30

#define BOARD_WIDTH   60

#define GRID_NUM 6
#define GRID_COUNT 225


#define RED  0
#define BLUE 1
//Blue  1 ~  6
//Red  -1 ~ -6
#define B1 1
#define B2 2
#define B3 3
#define B4 4
#define B5 5
#define B6 6

#define R1 -1
#define R2 -2
#define R3 -3
#define R4 -4
#define R5 -5
#define R6 -6

#define None 0
#define t0 board[nChessPos.x][nChessPos.y]
#define t1 board[nChessPos.x-1][nChessPos.y]
#define t2 board[nChessPos.x-1][nChessPos.y-1]
#define t3 board[nChessPos.x][nChessPos.y-1]

typedef struct _ChessPosition{
	int x;
	int y;
}ChessPos;

typedef struct _ChessMove{
	int ChessID;
	ChessPos From;
	ChessPos To;
//	int score;
}ChessMove;

//int board[6][6];

#endif