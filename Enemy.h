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

	Vector GetDirection(Vector _targetpos);	//targetへの方向ベクトルを計算・取得
	double GetAngle(Vector _targetpos);

private:
	Vector Pos;
	int Radius;		//円としたときの半径（当たり判定用）
	
	Vector Velocity;
	int MaxSpeed;
	double AngleSpeed;	//角速度（使わないこともある）

	int MoveType;	//移動の種類
	int BallType;	//弾の種類
	int Hp;			
	int Elements;	//撃破時の自機のどのステータスがアップするか
	int MomStar;	//母星のインデックス番号

	int ShootTime;	//弾発射間隔
	int AliveTime;	//生存時間
	int AppearTime; //出現時刻
	
	int ImgEnemy[3];	//ボディ：MoveTypeで分類　ヘッド：Ballで分類（発射する弾と同じ色） HPバー：四角
	int PicSizeX, PicSizeY; //ボディの絵のサイズ

	bool Alive;

	Vector DrawPosition(Vector _pos, Vector _mypos);	
};