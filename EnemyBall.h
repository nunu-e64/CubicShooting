#pragma once
#include "Define.h"
#include "Mine.h"
#include "Enemy.h"

class CEnemyBall{
public:
	CEnemyBall();

	void Draw(Vector _mypos);
	void Move(int _timecount);
	bool JudgeMine(CMine *Mine, int _timecount);
	
	Vector GetPos();
	int GetPower();

	bool GetAlive();
	void SetAlive(bool _bool);

	void Appear(int _speed, int _power, int _alivetime, int _movetype);
	bool Appear(CEnemyBall *Model, CEnemy *MomEnemy, Vector _mypos, int _timecount, int _rand);


private:
	Vector Pos;
	Vector DrawPos;
	int Size;
	int Radius;

	Vector Velocity;
	int Speed;
	
	int Power;
	int MoveType;
	int ImgEnemyBall;

	int AliveTime;
	int AppearTime;
	bool Alive;

	bool WindowCheck(Vector _pos, Vector _mypos);	//‰æ–Ê“à‚É‚ ‚é‚©‚Ç‚¤‚©

	bool JudgeCircle(int _mex, int _mey, Vector _target, int _targetsize);
	void DrawPosition(Vector _pos, Vector _mypos);
};