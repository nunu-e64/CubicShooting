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
	int EnemyBirthKind[3];	//どの種類の敵を
	int EnemyBirthTime[3];	//どの間隔で生産するか（3種類まで）

	bool Appear(int _posx, int _posy, double _speed, int _rand, int _enemykind0, int _enemytime0, int _enemykind1, int _enemytime1, int _enemykind2, int _enemytime2);
	
	Vector NearestStar(Vector _oldnear);

private:
	Vector Pos;
	Vector DeadCircleDrawPos[8];
	Vector DrawPos;

	int Radius;		//円としたときの半径（描画・当たり判定用）
	Vector Velocity;
	
	int Hp;			
	int TimeGap;	//星ごとに時間ずれを生むための乱数

	int ImgStar;
	int ImgStarGauge[2];

	bool Alive;
	bool Visible;	//表示の有無　ゲームオーバー処理用
	
	Vector DrawPosition(Vector _pos, Vector _mypos);
};