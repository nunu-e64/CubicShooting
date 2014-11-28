#pragma once


class CClock{
public:
	CClock();
	void Awake();
	bool Main();

	void SetNowTime();
	int GetTime();
	
	void SetGameMode(int _gamemode);
	int GetGameMode();

private:
	int OldTime;	//前タームの時刻
	int TimeCount;	//1/50秒でカウントアップ

	int EscapeStart;	//Escapeを押し始めたカウント（50超えたらゲーム終了）


	float fps[50];
	float avg_fps;

	int GameMode;	
		//#define MODE_PLAY 0
		//#define MODE_OPENING 1
		//#define MODE_TITLE 2
		//#define MODE_CHOOSE 3

};