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
		//0:~���X�g�W�����v
		//1:~�����ړ�
		//2:�^�C�g���o��
		//3:�^�C�g��

	int StartTime;
	int MemoTime;
	int NowTime;

	Vector Pos;		//�w�i�摜�̍���̓_
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

