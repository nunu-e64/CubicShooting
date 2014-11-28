#pragma once
#include "Define.h"

class COpening{
public:
	COpening();
	
	int Main(int _timecount, bool _op);
	void Init();
	void Awake(int _timecount);


private:
	int Scene;
		//0:~ラストジャンプ
		//1:~水平移動
		//2:タイトル登場
		//3:タイトル

	int StartTime;
	int MemoTime;
	int NowTime;

	Vector Pos;		//背景画像の左上の点
	Vector OldPos[3];
	Vector Velocity;
	double DeadLineX;

	int ImgOpBack[5];
	int ImgOpMine[23];
	int ImgOpMyEdge[4];
	int ImgOpDeadLine;
	
	void Move(bool _op);
	void DrawMine();	
	void DrawBack();
	void DrawCaption(bool _op);

	bool PressedRETURN;

	bool Jump;
};

