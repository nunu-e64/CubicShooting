#include "Clock.h"
#include "DxLib.h"
#include "Define.h"

#define MUSIC_VOLUME 200

CClock::CClock(){
	TimeCount = 0;
	OldTime = 0;
	GameMode = 0;
}

void CClock::Awake(){
	SetNowTime();
}

void CClock::SetNowTime(){
	OldTime = GetNowCount();
	TimeCount = 0;
	EscapeStart = 0;
}

bool CClock::Main(){
	
	while(ProcessMessage()==0){
		if(GetNowCount()-OldTime>=20)break;
	}
	
	clsDx();
	/*
	int i = TimeCount % 50;
		fps[i] = (float)(1000/(GetNowCount()-OldTime));
		avg_fps = 0;
		for (int i=0; i<50; i++){
			avg_fps += fps[i]/50;
		}
	
	printfDx("fps:%f\n",avg_fps);
	*/

	/*
	printfDx("fps   :%f\n",fps[i]);
	printfDx("avg_1s:%f\n",avg_fps);
	printfDx("TimeCount:%d\n",TimeCount);
	*/

	OldTime=GetNowCount();
	TimeCount++;


	//Escapeキー長押しして離すとゲーム終了
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		if(EscapeStart==0){
			EscapeStart = TimeCount;
		}
	}else{
		if(TimeCount - EscapeStart > 30 && EscapeStart > 0){
			SetGameMode(MODE_END);
			return false;
		}else{
			EscapeStart=0;
		}
	}

	return true;
}

int CClock::GetTime(){
	return TimeCount;
}

int CClock::GetGameMode(){
	return GameMode;
}
void CClock::SetGameMode(int _gamemode){
	
	
	if (!(_gamemode==GameMode) && !(GameMode==MODE_END)){
		if(CheckMusic()==1)StopMusic() ;
		switch (_gamemode){
		case MODE_PLAYING:
			if(PlayMusic("CS_music/loop003.mp3",DX_PLAYTYPE_LOOP) == -1){
				printfDx("MusicError");
				WaitKey();
				clsDx();
			}
			break;
		case MODE_CHOICE:
			if(PlayMusic("CS_music/backstreet.mp3",DX_PLAYTYPE_LOOP) == -1){
				printfDx("MusicError");
				WaitKey();
				clsDx();
			}
			break;
		case MODE_TITLE:
		case MODE_OPENING:
			if(PlayMusic("CS_music/battle01.mp3",DX_PLAYTYPE_LOOP) == -1){
				printfDx("MusicError");
				WaitKey();
				clsDx();
			}
			break;
		}
	}

	if (!(GameMode==MODE_END)) GameMode = _gamemode;
	
	if(SetVolumeMusic(MUSIC_VOLUME)==-1){
		printfDx("MusicError");
		WaitKey();
		clsDx();
	} ;	
}