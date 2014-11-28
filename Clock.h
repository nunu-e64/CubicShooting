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
	int OldTime;	//�O�^�[���̎���
	int TimeCount;	//1/50�b�ŃJ�E���g�A�b�v

	int EscapeStart;	//Escape�������n�߂��J�E���g�i50��������Q�[���I���j


	float fps[50];
	float avg_fps;

	int GameMode;	
		//#define MODE_PLAY 0
		//#define MODE_OPENING 1
		//#define MODE_TITLE 2
		//#define MODE_CHOOSE 3

};