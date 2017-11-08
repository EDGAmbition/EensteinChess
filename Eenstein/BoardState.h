

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBoardState{
public:
	CBoardState();
	virtual ~CBoardState();
	void UpdateBoardState(int b[][6]);
	int BNum,RNum;
	int BExist[7],RExist[7];
};


