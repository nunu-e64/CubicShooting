#include "DxLib.h"
#include "Define.h"
#include "math.h"
#include "Enemy.h"
#include "Star.h"

#define ENEMY_RADIUS 16

CEnemy::CEnemy(){
	Alive=FALSE;

		Radius = 1;
		Pos.x = 1;
		Pos.y = 1;
	
		MaxSpeed = 1;
		Velocity.Set(1, 1);
		AngleSpeed=1;
	
		MoveType = 1;
		BallType = 1;
		Hp = 1;
		Elements = 1;
		MomStar = 1;

		ShootTime = 1;
		AliveTime = 0;
		AppearTime = 0;
}

void CEnemy::Appear(int _speed, int _hp, int _alivetime, int _movetype, int _balltype, int _imgnum, int _shoottime){
	int ImgEnemyList[20];
	
	Radius = ENEMY_RADIUS;
	MaxSpeed = _speed;

	Hp = _hp;
	MoveType = _movetype;
	BallType = _balltype;
	AliveTime = _alivetime;
	ShootTime = _shoottime;

	LoadDivGraph("CS_pic/EnemyList.png", 20, 2, 10, 32, 32, ImgEnemyList);
	int i = (_movetype + _balltype%9 +1) % 6;	//ある程度画像がバラけるよう適当に調整
	ImgEnemy[0] = ImgEnemyList[2*i];
	ImgEnemy[1] = ImgEnemyList[1+2*(max(1,min(6,_imgnum))-1)];

	int ImgBoxes[20];
	LoadDivGraph("CS_pic/Boxes.png", 20, 1, 20, 1, 1, ImgBoxes);
	ImgEnemy[2] = ImgBoxes[1];
	
	
	//ImgEnemy = LoadGraph("pic/Enemy_1.png");
}

bool CEnemy::Appear(CEnemy *Model, Vector _pos, int _timecount, int _rand, int _momstar){
		
	MoveType = Model->MoveType;
	BallType = Model->BallType;
	Hp = Model->Hp;
	Elements = Model->Elements;
	MomStar = _momstar;

	ShootTime = Model->ShootTime;
	AliveTime = Model->AliveTime;
	AppearTime = _timecount;

	ImgEnemy[0] = Model->ImgEnemy[0];
	ImgEnemy[1] = Model->ImgEnemy[1];
	ImgEnemy[2] = Model->ImgEnemy[2];
	GetGraphSize(ImgEnemy[0], &PicSizeX, &PicSizeY);

	Radius = Model->Radius;
	Pos.x = _pos.x + (_rand % 81) - 40;
	Pos.y = _pos.y + (_rand % 83) - 41;
	
	MaxSpeed = Model->MaxSpeed;
	Velocity.Set(_rand%51-25, _rand%53-26);
	Velocity.Multiple(MaxSpeed / Velocity.GetLength());

		if(MoveType == 4){
			Pos = _pos;
			Velocity.Set(MaxSpeed,0);
			//AngleSpeed = 2*PI / (_rand%480 + 240);
		}


	Alive=TRUE;
	return TRUE;
}


void CEnemy::Move(Vector _mypos, Vector _starpos, int _timecount){
	if(Alive){
		if(_timecount-AppearTime>=AliveTime){
			Alive=FALSE;
		}

		if(MoveType==0){	//ランダム直進
		}

		if(MoveType==1){	//自機追尾
			Vector direction;
				direction = GetDirection(_mypos);
				direction.Multiple(0.2);
			Velocity.Add(direction);
			if(Velocity.GetLength()>MaxSpeed) Velocity.Multiple(MaxSpeed/Velocity.GetLength());
		}
		if(MoveType==2){	//母星追尾
			Vector direction;
				direction = GetDirection(_starpos);
				direction.Multiple(0.1);
			Velocity.Add(direction);
			if(Velocity.GetLength()>MaxSpeed) Velocity.Multiple(MaxSpeed/Velocity.GetLength());
		}
		if(MoveType==3){	//出現速度で回転移動
			Vector acceleration;
			int r = 240;
				acceleration.Set(cos((long double)(_timecount-AppearTime)*MaxSpeed/r),sin((long double)(_timecount-AppearTime)*MaxSpeed/r));
				acceleration.Multiple(-1*r*(MaxSpeed/r)*(MaxSpeed/r));
			Velocity.Add(acceleration);
			if(Velocity.GetLength()>MaxSpeed) Velocity.Multiple(MaxSpeed/Velocity.GetLength());
		}
		if(MoveType==4){	//母星の周りを回転移動
			int spin_begin_time = 100;
	
			if(_timecount-AppearTime==spin_begin_time){
				Velocity.Set(0, 0);
				AngleSpeed = (MaxSpeed/(Pos.x-_starpos.x));		//角速度設定
			}else if(_timecount-AppearTime>spin_begin_time){
				Pos.Set(_starpos.x + MaxSpeed*cos((_timecount-AppearTime-spin_begin_time)*AngleSpeed)/AngleSpeed, _starpos.y + MaxSpeed*sin((_timecount-AppearTime-spin_begin_time)*AngleSpeed)/AngleSpeed);
			}
		}

		Pos.Add(Velocity);
			if(Pos.x>WORLD_WIDTH)Pos.x-=WORLD_WIDTH;
			if(Pos.x<0)Pos.x+=WORLD_WIDTH;
			if(Pos.y>WORLD_HEIGHT)Pos.y-=WORLD_HEIGHT;
			if(Pos.y<0)Pos.y+=WORLD_HEIGHT;
	}

}



void CEnemy::Draw(Vector _mypos){
	if(Alive){	
		Vector DrawPos = DrawPosition(Pos, _mypos);	
			
			if(DrawPos.x<-PicSizeX || DrawPos.x>WINDOW_WIDTH+PicSizeX) return;
			if(DrawPos.y<-PicSizeY || DrawPos.y>WINDOW_HEIGHT+PicSizeY)return;
			
		//敵絵
		DrawRotaGraph((int)(DrawPos.x), (int)(DrawPos.y), 1, -GetAngle(_mypos), ImgEnemy[0], true);
		DrawRotaGraph((int)(DrawPos.x), (int)(DrawPos.y), 1, -GetAngle(_mypos), ImgEnemy[1], true);

		//HPゲージ
		DrawExtendGraph((int)(DrawPos.x-Hp/2), (int)DrawPos.y+PicSizeY/2+5, (int)(DrawPos.x+Hp/2), (int)DrawPos.y+PicSizeY/2+4, ImgEnemy[2], true);
	}
}

Vector CEnemy::GetDirection(Vector _targetpos){

		if(Pos.x-_targetpos.x>WORLD_WIDTH/2){
			_targetpos.x+=WORLD_WIDTH;
		}else if(Pos.x-_targetpos.x<-WORLD_WIDTH/2){
			_targetpos.x-=WORLD_WIDTH;
		}
		if(Pos.y-_targetpos.y>WORLD_HEIGHT/2){
			_targetpos.y+=WORLD_HEIGHT;
		}else if(Pos.y-_targetpos.y<-WORLD_HEIGHT/2){
			_targetpos.y-=WORLD_HEIGHT;
		}
	
	Vector direction;
		direction.Set(_targetpos.x-Pos.x, _targetpos.y-Pos.y);
		direction.Multiple(1/direction.GetLength());
	
	return direction;
}

double CEnemy::GetAngle(Vector _targetpos){
		
		if(Pos.x-_targetpos.x>WORLD_WIDTH/2){
			_targetpos.x+=WORLD_WIDTH;
		}else if(Pos.x-_targetpos.x<-WORLD_WIDTH/2){
			_targetpos.x-=WORLD_WIDTH;
		}
		if(Pos.y-_targetpos.y>WORLD_HEIGHT/2){
			_targetpos.y+=WORLD_HEIGHT;
		}else if(Pos.y-_targetpos.y<-WORLD_HEIGHT/2){
			_targetpos.y-=WORLD_HEIGHT;
		}

	double angle;
		angle = atan(-(_targetpos.y-Pos.y)/(_targetpos.x-Pos.x));
		if(_targetpos.x-Pos.x < 0) angle+=PI ;
		if(angle < 0) angle+=PI*2;

	return angle;
}

Vector CEnemy::DrawPosition(Vector _pos, Vector _mypos){
	Vector DrawPos;
	if(abs((int)(_pos.x-_mypos.x))<WORLD_WIDTH-abs((int)(_pos.x-_mypos.x))){
		DrawPos.x = _pos.x-_mypos.x + WINDOW_WIDTH/2;
	}else{
		DrawPos.x = -((_pos.x-_mypos.x)/abs((int)(_pos.x-_mypos.x)))*(WORLD_WIDTH-abs((int)(_pos.x-_mypos.x))) + WINDOW_WIDTH/2 ;
	}
	if(abs((int)(_pos.y-_mypos.y))<WORLD_HEIGHT-abs((int)(_pos.y-_mypos.y))){
		DrawPos.y = _pos.y-_mypos.y + WINDOW_HEIGHT/2;
	}else{
		DrawPos.y = -((_pos.y-_mypos.y)/abs((int)(_pos.y-_mypos.y)))*(WORLD_HEIGHT-abs((int)(_pos.y-_mypos.y))) + WINDOW_HEIGHT/2 ;
	}
	
	return DrawPos;
}


Vector CEnemy::GetPos(){
	return Pos;
}
int CEnemy::GetRadius(){
	return Radius;
}

int CEnemy::GetBallType(){
	return BallType;
}
void CEnemy::SetHp(int _hp){
	Hp = _hp;
}
int CEnemy::GetHp(){
	return Hp;
}
bool CEnemy::GetAlive(){
	return Alive;
}
void CEnemy::SetAlive(bool _bool){
	Alive=_bool;
}

int CEnemy::GetAppearTime(){
	return AppearTime;
}
int CEnemy::GetShootTime(){
	return ShootTime;
}

int CEnemy::GetMomStar(){
	return MomStar;
}
