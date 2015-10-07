#pragma once
#include "Define.h"
#include "Dxlib.h"

class CRanking{
public:
	CRanking();
	void SetScore(int _stagenum, bool hardmode = false);

	void Init();

private:
	int HighScore[30][3];		//0...Easy, 1...Hard, 2...未使用
	bool YetResister[30][3];

	int FileHandle;
};