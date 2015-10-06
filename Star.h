#pragma once
#include "Define.h"

class CStar{
public:
	CStar();
	void Draw(Vector _mypos, int _timecount);
	void Move();

	Vector GetPos();
	int GetRadius();

	int GetHp();
	void SetHp(int _hp);

	bool GetAlive();
	void SetAlive(bool _bool);
	bool GetVisible();
	void SetVisible(bool _bool);

	bool EnemyBirthNow(int _timecount, int _index);	
	int EnemyBirthKind[3];	//�ǂ̎�ނ̓G��
	int EnemyBirthTime[3];	//�ǂ̊Ԋu�Ő��Y���邩�i3��ނ܂Łj

	bool Appear(int _posx, int _posy, double _speed, int _rand, int _enemykind0, int _enemytime0, int _enemykind1, int _enemytime1, int _enemykind2, int _enemytime2);
	
	Vector NearestStar(Vector _oldnear);

private:
	Vector Pos;
	Vector DeadCircleDrawPos[8];
	Vector DrawPos;

	int Radius;		//�~�Ƃ����Ƃ��̔��a�i�`��E�����蔻��p�j
	Vector Velocity;
	
	int Hp;			
	int TimeGap;	//�����ƂɎ��Ԃ���𐶂ނ��߂̗���

	int ImgStar;
	int ImgStarGauge[2];

	bool Alive;
	bool Visible;	//�\���̗L���@�Q�[���I�[�o�[�����p
	
	Vector DrawPosition(Vector _pos, Vector _mypos);
};