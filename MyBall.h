#pragma once
#include "Define.h"
#include "Mine.h"
#include "Enemy.h"
#include "Star.h"

class CMyBall{
public:
	CMyBall();
	void Init();

	void Draw(Vector _mypos);
	void Move(int _timecount);
	bool JudgeEnemy(CEnemy *Enemy);
	bool JudgeStar(CStar *Star);

	Vector GetPos(int _index);
	int GetPower();

	bool GetAlive();
	void SetAlive(bool _bool);

	bool Shoot(CMine *Mine, int _shotnum, int _timecount);

private:
	Vector Pos0;
	Vector Pos1;
	Vector DrawPos0;
	Vector DrawPos1;

	Vector Velocity;
	
	int Power;
	int AliveTime;
	int ShootTime;
	
	int ImgMyBall;
	bool Alive;

	bool JudgeCircle(int _mex, int _mey, Vector _target, int _targetsize);
	Vector DrawPosition(Vector _pos, Vector _mypos);
};