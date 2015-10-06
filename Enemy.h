#pragma once
#include "Define.h"

class CEnemy{
public:
	CEnemy();
	void Draw(Vector _mypos);
	void Move(Vector _mypos, Vector _starpos, int _timecount);

	Vector GetPos();
	int GetRadius();
	
	int GetBallType();
	int GetHp();
	void SetHp(int _hp);
	bool GetAlive();
	void SetAlive(bool _bool);
	
	int GetMomStar();
	
	int GetAppearTime();
	int GetShootTime();
	
	void Appear(int _speed, int _hp, int _alivetime, int _movetype, int _balltype, int _imgnum, int _shoottime);
	bool Appear(CEnemy *Model, Vector _pos, int _timecount, int _rand, int _momstar);

	Vector GetDirection(Vector _targetpos);	//target�ւ̕����x�N�g�����v�Z�E�擾
	double GetAngle(Vector _targetpos);

private:
	Vector Pos;
	int Radius;		//�~�Ƃ����Ƃ��̔��a�i�����蔻��p�j
	
	Vector Velocity;
	int MaxSpeed;
	double AngleSpeed;	//�p���x�i�g��Ȃ����Ƃ�����j

	int MoveType;	//�ړ��̎��
	int BallType;	//�e�̎��
	int Hp;			
	int Elements;	//���j���̎��@�̂ǂ̃X�e�[�^�X���A�b�v���邩
	int MomStar;	//�ꐯ�̃C���f�b�N�X�ԍ�

	int ShootTime;	//�e���ˊԊu
	int AliveTime;	//��������
	int AppearTime; //�o������
	
	int ImgEnemy[3];	//�{�f�B�FMoveType�ŕ��ށ@�w�b�h�FBall�ŕ��ށi���˂���e�Ɠ����F�j HP�o�[�F�l�p
	int PicSizeX, PicSizeY; //�{�f�B�̊G�̃T�C�Y

	bool Alive;

	Vector DrawPosition(Vector _pos, Vector _mypos);	
};