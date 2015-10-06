#pragma once
#include "Define.h"

class CStage{
public:
	CStage();
	void Init();

	void Draw(Vector _mypos);
	void DrawStarCount();
	void DrawEnemyCount(int _alive_enemynum);
	void DrawCaption(bool _showexplain = false);		//自機や敵絵の上から描く文字類

	
	int GetStageNum();
	void SetStageNum(int _stagenum);
	void SetStageNumMin();
	void ChangeStageNum(bool _add);

	bool SetDifficulity();
	bool GetDifficulity();
	void ChangeDifficulity();

	bool LastStage();

	void SetAliveStarNum(int _num);
	int GetAliveStarNum();

	void SetNearestStar(Vector nearest_star);

private:
	int ImgBack;
	int ImgMark;
	int PicSizeX, PicSizeY;
	int FontMini;

	int AliveStarNum;

	int StageNum;
	bool HardMode;			//falseでeasyモード
	Vector NearestStar;		//自機に一番近い星の相対位置

	void CheckStageNum();
	double GetAngle(Vector _targetpos);
};