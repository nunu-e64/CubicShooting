#include "DxLib.h"
#include "Define.h"
#include "math.h"
#include "Star.h"

//#define STAR_SPEED 0.25
#define STAR_HP 60	//50
#define STAR_RADIUS 26

CStar::CStar(){
	Alive = FALSE;
	Visible = false;

		ImgStar = 1; 
		Radius = 1;
		Pos.Set(1, 1);
		Velocity.Set(1, 1);
		
		Hp = STAR_HP;

		EnemyBirthKind[0]=1;
		EnemyBirthKind[1]=1;
		EnemyBirthKind[2]=1;
		EnemyBirthTime[0]=1;
		EnemyBirthTime[1]=1;
		EnemyBirthTime[2]=1;
		
	for (int i=0; i<8; i++){
		DeadCircleDrawPos[i].Set(0,0);
	}
}

bool CStar::Appear(int _posx, int _posy, double _speed, int _rand, int _enemykind0, int _enemytime0, int _enemykind1, int _enemytime1, int _enemykind2, int _enemytime2){
	
	ImgStar = LoadGraph("CS_pic/Star.png") ;

	int ImgBoxes[20];
	LoadDivGraph("CS_pic/Boxes.png", 20, 1, 20, 1, 1, ImgBoxes);
	ImgStarGauge[0] = ImgBoxes[5];
	ImgStarGauge[1] = ImgBoxes[6];

	Radius = STAR_RADIUS;
	Pos.Set(_posx + _rand%100 - 50 , _posy+ _rand%112 - 50);
	Velocity.Set(_rand%10-5, _rand%9-5);
	Velocity.Multiple(_speed/Velocity.GetLength());
	max(1,2);
	Hp = STAR_HP;
	TimeGap = _rand%5000;
	
	EnemyBirthKind[0]=_enemykind0;
	EnemyBirthKind[1]=_enemykind1;
	EnemyBirthKind[2]=_enemykind2;
	EnemyBirthTime[0]=_enemytime0;
	EnemyBirthTime[1]=_enemytime1;
	EnemyBirthTime[2]=_enemytime2;
	
	for (int i=0; i<8; i++){
		DeadCircleDrawPos[i].Set(0,0);
	}

	Alive = true;
	Visible = true;
	return true;
}

Vector CStar::NearestStar(Vector _oldnear){
	if (Alive){
		Vector vsMePos;
		vsMePos.Set(DrawPos.x-WINDOW_WIDTH/2, DrawPos.y-WINDOW_HEIGHT/2);
		if (vsMePos.GetLength() < _oldnear.GetLength()){
			return vsMePos;	
		}
	}
	return _oldnear;
}

void CStar::Draw(Vector _mypos, int _timecount){
	if (!Visible)return;

	_timecount += TimeGap;

		DrawPos = DrawPosition(Pos, _mypos);
			if(DrawPos.x<-Radius*2-50 || DrawPos.x>WINDOW_WIDTH+Radius*2+50) return;
			if(DrawPos.y<-Radius*2-50 || DrawPos.y>WINDOW_HEIGHT+Radius*2+50)return;

	if(Alive){
		//Star
		DrawRotaGraph((int)(DrawPos.x), (int)(DrawPos.y), 1, (_timecount%300)*PI/150, ImgStar, true) ;
		
		//Enemy生成タイムゲージ
		for(int i=0; i<3; i++){
			DrawExtendGraph((int)DrawPos.x-12, (int)DrawPos.y-3+8*(i-1), (int)DrawPos.x+12, (int)DrawPos.y+3+8*(i-1), ImgStarGauge[0], true);
			DrawExtendGraph((int)DrawPos.x-11, (int)DrawPos.y-2+8*(i-1), (int)(DrawPos.x-11 + 22 * (1+(_timecount%EnemyBirthTime[i])) / EnemyBirthTime[i]), (int)DrawPos.y+2+8*(i-1), ImgStarGauge[1], true);
		}
	}else{
		//ティウンティウン]
		for (int i=0; i<8; i++){
			if(_timecount/5 % 2 == 0) DrawCircle((int)(DeadCircleDrawPos[i].x+DrawPos.x), (int)(DeadCircleDrawPos[i].y+DrawPos.y), 12, GetColor(255,100,0), false);
		}
	}	
}

void CStar::Move(){
	if(Alive){
		Pos.Add(Velocity);
			if(Pos.x>WORLD_WIDTH)Pos.x-=WORLD_WIDTH;
			if(Pos.x<0)Pos.x+=WORLD_WIDTH;
			if(Pos.y>WORLD_HEIGHT)Pos.y-=WORLD_HEIGHT;
			if(Pos.y<0)Pos.y+=WORLD_HEIGHT;
	}else{
		for (int i=0; i<8; i++){
			DeadCircleDrawPos[i].Add(cos(i * PI / 4) * 2, sin(i * PI / 4) * 2);
		}
		if (DeadCircleDrawPos[0].x >= 200) Visible = false;
	}
}


bool CStar::EnemyBirthNow(int _timecount, int _index){
	if((_timecount + TimeGap) % EnemyBirthTime[_index]==0){
		return true;
	}else{
		return false;
	}
}

Vector CStar::DrawPosition(Vector _pos, Vector _mypos){
	Vector DrawPos;
	if(abs((int)(_pos.x-_mypos.x))<WORLD_WIDTH/2){
		DrawPos.x = _pos.x-_mypos.x + WINDOW_WIDTH/2;
	}else{
		DrawPos.x = -((_pos.x-_mypos.x)/abs((int)(_pos.x-_mypos.x)))*(WORLD_WIDTH-abs((int)(_pos.x-_mypos.x))) + WINDOW_WIDTH/2 ;
	}
	if(abs((int)(_pos.y-_mypos.y))<WORLD_HEIGHT/2){
		DrawPos.y = _pos.y-_mypos.y + WINDOW_HEIGHT/2;
	}else{
		DrawPos.y = -((_pos.y-_mypos.y)/abs((int)(_pos.y-_mypos.y)))*(WORLD_HEIGHT-abs((int)(_pos.y-_mypos.y))) + WINDOW_HEIGHT/2 ;
	}
	
	return DrawPos;
}

Vector CStar::GetPos(){
	return Pos;
}
int CStar::GetRadius(){
	return Radius;
}

void CStar::SetHp(int _hp){
	Hp = _hp;
}
int CStar::GetHp(){
	return Hp;
}

bool CStar::GetAlive(){
	return Alive;
}
void CStar::SetAlive(bool _bool){
	Alive=_bool;
}

bool CStar::GetVisible(){
	return Visible;
}
void CStar::SetVisible(bool _bool){
	Visible=_bool;
}