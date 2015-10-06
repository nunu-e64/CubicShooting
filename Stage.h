#pragma once
#include "Define.h"

class CStage{
public:
	CStage();
	void Init();

	void Draw(Vector _mypos);
	void DrawStarCount();
	void DrawEnemyCount(int _alive_enemynum);
	void DrawCaption(bool _showexplain = false);		//���@��G�G�̏ォ��`��������

	
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
	bool HardMode;			//false��easy���[�h
	Vector NearestStar;		//���@�Ɉ�ԋ߂����̑��Έʒu

	void CheckStageNum();
	double GetAngle(Vector _targetpos);
};