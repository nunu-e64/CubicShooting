#pragma once

#define RED GetColor( 255 , 0 , 0 )
#define GREEN GetColor( 0 , 255 , 0 )
#define BLUE GetColor( 0 , 0 , 255 )
#define BLACK GetColor( 0 , 0 , 0 )
#define WHITE GetColor( 255 , 255 , 255 )

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#include "math.h"

class Vector{
public:
	Vector( int _x , int _y ){
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

	void Add(Vector _vec){
		x += _vec.x;
		y += _vec.y;
	}

	double GetNorm(){
		return sqrt((x*x)+(y*y));
	}
private:
};

class CBox{
public:
	CBox();

	int Left;
	int Top;
	int Width;
	int Height;
	int Color;

	void Draw();
private:
	
};

class CCircle{
public:
	CCircle();

	int Left;
	int Top;
	int Radius;
	int Color;

	void Draw();
private:
};

class CommandButton{
public:
	CommandButton();
	CommandButton( int _left , int _right , int _width , int _height );
	int Left;
	int Top;
	int Width;
	int Height;
	int ForeColor;
	int BGColor; //BackGroundColor
	int FontSize;

	char *Caption;

	void (*Func)();

	void Update();
	void Draw();
	void Judge();
	void Click();
private:
};


void Awake();
void GameLoop();

void GameOver();

Vector GetIntersection( int a1 , int b1 , int a2 , int b2 );