#pragma once
#include "Define.h"

class CMine{
public:
	CMine();
	void Awake(bool _hardmode=false);
	void Init();
	void Draw(int _timecount);
	void Move();

	Vector GetPos();
	int GetSize();
	int GetRadius();

	void SetVelocity(Vector _velocity);
	void SetVelocity(double _x, double _y);

	int GetBallLv();
	int GetBallPower();
	int GetBallSpeed();
	int GetShootTime();
	
	int GetHp();
	void SetHp(int _hp);

	bool GetAlive();
	void SetAlive(bool _bool);
	bool GetVisible();
	void SetVisible(bool _bool);

private:
	Vector Pos;
	Vector OldPos[3];
	Vector DeadCircleDrawPos[8];
	
	int Size;		//�����`�Ƃ����Ƃ��̈�Ӂi�`��p�j
	int Radius;		//�~�Ƃ����Ƃ��̔��a�i�����蔻��p�j
	
	Vector Velocity;
	double MaxSpeed;
	double Acceleration;
	double Brake;

	int OldHp;
	int Hp;
	int MaxHp;
	//int MutekiTime;		//��e���̖��G����
	//int MutekiStart;	//��e���̎������L�^

	int Lv[3];
	int Exp[3];
	//bool Visible;	//��e�����G���ԗp

	int ImgMine[23];	//16����,��,�~,��,OldPos*3,��
	int ImgMyEdge[4];
	int ImgMyHp[3];

	bool Alive;		//�����m�F�p
	bool Visible;	//�\���̗L���@�Q�[���I�[�o�[�����p

	Vector DrawPosition(Vector _pos, Vector _mypos);

};