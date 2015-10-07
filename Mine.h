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
	
	int Size;		//正方形としたときの一辺（描画用）
	int Radius;		//円としたときの半径（当たり判定用）
	
	Vector Velocity;
	double MaxSpeed;
	double Acceleration;
	double Brake;

	int OldHp;
	int Hp;
	int MaxHp;
	//int MutekiTime;		//被弾時の無敵時間
	//int MutekiStart;	//被弾時の時刻を記録

	int Lv[3];
	int Exp[3];
	//bool Visible;	//被弾時無敵時間用

	int ImgMine[23];	//16方位,中,×,○,OldPos*3,空白
	int ImgMyEdge[4];
	int ImgMyHp[3];

	bool Alive;		//生存確認用
	bool Visible;	//表示の有無　ゲームオーバー処理用

	Vector DrawPosition(Vector _pos, Vector _mypos);

};