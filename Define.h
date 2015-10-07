#pragma once
#include "math.h"
#include "Dxlib.h"

#define PI 3.1415926535897932384626433832795f
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WORLD_WIDTH 3600	//back.pngの横の倍数
#define WORLD_HEIGHT 3600	//back.pngの縦の倍数

#define GAME_TITLE "CubicShooting"
#define VERSION "ver0.30"

#define RED GetColor( 255 , 0 , 0 )
#define GREEN GetColor( 0 , 255 , 0 )
#define BLUE GetColor( 0 , 0 , 255 )
#define YELLOW GetColor( 255 , 255 , 0 )
#define BLACK GetColor( 0 , 0 , 0 )
#define WHITE GetColor( 255 , 255 , 255 )
#define GRAY GetColor( 120 , 120 , 120 )

#define STAR_NUM 10
#define ENEMY_NUM 100
#define MY_BALL_NUM 50
#define ENEMY_BALL_NUM 800

#define MODE_PLAYING 0
#define MODE_OPENING 1
#define MODE_TITLE 2
#define MODE_CHOICE 3
#define MODE_GAMEOVER 4
#define MODE_GAMECLEAR 5
#define MODE_END -1

extern void DrawCenterString(int x, int y, const TCHAR *String, int color);

#define MEMORY_CHECK	//メモリの解放し忘れをチェック。Debugビルドで使用可能。
	#if defined(MEMORY_CHECK) && !defined(MEMORY_CHECK_DISABLE)
		#define _CRTDBG_MAP_ALLOC
		#include <stdlib.h>
		#include <crtdbg.h>
		#define new  ::new( _NORMAL_BLOCK, __FILE__, __LINE__ )  
	#endif


class Vector{
public:
	Vector( double _x , double _y ){
		x = _x;
		y = _y;
	}

	Vector(){
		x = 0;
		y = 0;
	}

	double x;
	double y;

	void Set( double _x , double _y){
		x = _x;
		y = _y;
	}
	void Set(Vector _vec){
		x = _vec.x;
		y = _vec.y;
	}
	
	void Add( double _x , double _y){
		x += _x;
		y += _y;
	}
	void Add(Vector _vec){
		x += _vec.x;
		y += _vec.y;
	}

	void Multiple(double _num){
		x = x*_num;
		y = y*_num;
	}

	double GetLength(){
		return sqrt((x*x)+(y*y));
	}
private:
};


void GameAwake();

bool Opening();
bool Title();
bool Choice();

void Awake();
bool GameLoop();
bool GameOver();
bool GameClear();
