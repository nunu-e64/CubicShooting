#include "DxLib.h"
#include "EnemyBall.h"
#include "Define.h"
#include "math.h"

#define ENEMY_BALL_RADIUS 4

CEnemyBall::CEnemyBall(){
	Alive = FALSE;
		Pos.Set(1,1);
		Radius = 1;
		Size = Radius*2;
		Velocity.Set(1,1);

		Power = 1;

		AppearTime = 1;
		AliveTime = 1;
}


void CEnemyBall::Appear(int _speed, int _power, int _alivetime, int _movetype){
	int ImgEnemyBallList[6];

	Radius = ENEMY_BALL_RADIUS;
	Velocity.Set(_speed, 0);
	Speed = _speed;
	MoveType = _movetype;
	Power = _power;
	AliveTime = _alivetime;
	
	LoadDivGraph( "CS_pic/EnemyBall.png", 6, 6, 1, 7, 7, ImgEnemyBallList) ;
	ImgEnemyBall = ImgEnemyBallList[max(1,min(6,_power))-1];
}

bool CEnemyBall::Appear(CEnemyBall *Model, CEnemy *MomEnemy, Vector _mypos, int _timecount, int _rand){
	Pos = MomEnemy->GetPos();
	Radius = Model->Radius;
	Size = Radius*2;
	Speed = Model->Speed;
	
	MoveType = Model->MoveType;
	Power = Model->Power;
	ImgEnemyBall = Model->ImgEnemyBall;

	AppearTime = _timecount;
	AliveTime = Model->AliveTime;
	
	
		int i; 	
		switch(MoveType){
		case 0:		//1way
			Velocity = MomEnemy->GetDirection(_mypos);
			Velocity.Multiple(Speed);
			break;
		case 1:		//3way
			i = (_timecount/MomEnemy->GetShootTime()) % 3 - 1;
			Velocity.Set(cos(MomEnemy->GetAngle(_mypos) + i*PI/8), -sin(MomEnemy->GetAngle(_mypos) + i*PI/8));
			Velocity.Multiple(Speed);
			break;
		case 2:		//7way
			i = (_timecount/MomEnemy->GetShootTime()) % 7 - 3 ;
			Velocity.Set(cos(MomEnemy->GetAngle(_mypos) + i*PI/8), -sin(MomEnemy->GetAngle(_mypos) + i*PI/8));
			Velocity.Multiple(Speed);
			break;
			
		case 3:		//16way（全方位：自爆型用）
			i = (_timecount/MomEnemy->GetShootTime()) % 16 - 7;
			Velocity.Set(cos(i*PI/8), -sin(i*PI/8));
			Velocity.Multiple(Speed);
			break;

		case 4:		//Allway（全方位：回転射撃用）
			i = (_timecount % 360) - 180;
			Velocity.Set(cos(i*PI/180), -sin(i*PI/180));
			Velocity.Multiple(Speed);
			break;
		}

	Alive = true;
	return true;
}


void CEnemyBall::Move(int _timecount){
	if(Alive){
		Pos.Add(Velocity);
			if(Pos.x>WORLD_WIDTH)Pos.x-=WORLD_WIDTH;
			if(Pos.x<0)Pos.x+=WORLD_WIDTH;
			if(Pos.y>WORLD_HEIGHT)Pos.y-=WORLD_HEIGHT;
			if(Pos.y<0)Pos.y+=WORLD_HEIGHT;

		if(_timecount-AppearTime>=AliveTime){
				Alive=FALSE;
		}
	}
}

void CEnemyBall::Draw(Vector _mypos){
	if(Alive){
		if (WindowCheck(Pos, _mypos)){
			DrawPosition(Pos, _mypos);
			/*if(DrawPos.x<-Radius*2 || DrawPos.x>WINDOW_WIDTH+Radius*2) return;		//WindowCheckを利用
			if(DrawPos.y<-Radius*2 || DrawPos.y>WINDOW_HEIGHT+Radius*2)return;*/

			DrawGraph((int)(DrawPos.x)-Radius, (int)(DrawPos.y)-Radius, ImgEnemyBall, TRUE);
		}
	}
}

void CEnemyBall::DrawPosition(Vector _pos, Vector _mypos){
	if(abs(_pos.x-_mypos.x)<WORLD_WIDTH/2){
		DrawPos.x = _pos.x-_mypos.x + WINDOW_WIDTH/2;
	}else{
		DrawPos.x = -((_pos.x-_mypos.x)/abs(_pos.x-_mypos.x))*(WORLD_WIDTH-abs(_pos.x-_mypos.x)) + WINDOW_WIDTH/2 ;
	}
	if(abs(_pos.y-_mypos.y)<WORLD_HEIGHT/2){
		DrawPos.y = _pos.y-_mypos.y + WINDOW_HEIGHT/2;
	}else{
		DrawPos.y = -((_pos.y-_mypos.y)/abs(_pos.y-_mypos.y))*(WORLD_HEIGHT-abs(_pos.y-_mypos.y)) + WINDOW_HEIGHT/2 ;
	}
}

bool CEnemyBall::WindowCheck(Vector _pos, Vector _mypos){	//画面内にいればTRUE
	if ((_pos.x-_mypos.x < WINDOW_WIDTH/2 && _pos.x-_mypos.x > -WINDOW_WIDTH/2)
	 || (WORLD_WIDTH-_pos.x)+_mypos.x < WINDOW_WIDTH/2 || (WORLD_WIDTH-_mypos.x)+_pos.x < WINDOW_WIDTH/2){
		if ((_pos.y-_mypos.y < WINDOW_HEIGHT/2 && _pos.y-_mypos.y > -WINDOW_HEIGHT/2) 
		 || (WORLD_HEIGHT-_pos.y)+_mypos.y < WINDOW_HEIGHT/2 || (WORLD_HEIGHT-_mypos.y)+_pos.y < WINDOW_HEIGHT/2){
			return true;
		}
	}

	return false;
}

bool CEnemyBall::JudgeMine(CMine *Mine, int _timecount){
	if(!Mine->GetAlive()) return false;
	/*if(DrawPos.x<0 || DrawPos.x>WINDOW_WIDTH) return false;		//WindowCheckを利用
	if(DrawPos.y<0 || DrawPos.y>WINDOW_HEIGHT)return false;
*/
/*	if (!WindowCheck(Pos, Mine->GetPos())) return false;		//当たり判定を円から四角に簡易化したので不要
	Vector DistanceVector;
	DistanceVector.Set(Pos.x-Mine->GetPos().x, Pos.y-Mine->GetPos().y);

	if(DistanceVector.GetLength() <= Mine->GetRadius()+Radius){
		Alive = FALSE;
		
		Mine->SetHp(Mine->GetHp()-Power);
		if(Mine->GetHp() <= 0)Mine->SetAlive(FALSE);

		return TRUE;
	}else{
		return FALSE;
	}
*/
	if ((Pos.x > Mine->GetPos().x - Mine->GetSize()/2) && (Pos.x < Mine->GetPos().x + Mine->GetSize()/2) ){
		if ((Pos.y > Mine->GetPos().y - Mine->GetSize()/2) && (Pos.y < Mine->GetPos().y + Mine->GetSize()/2) ){
			Alive = FALSE;
		
			Mine->SetHp(Mine->GetHp()-Power);
			if(Mine->GetHp() <= 0)Mine->SetAlive(FALSE);
			return true;
		}
	}
	return false;
}


Vector CEnemyBall::GetPos(){
	return Pos;
}

int CEnemyBall::GetPower(){
	return Power;
}

bool CEnemyBall::GetAlive(){
	return Alive;
}
void CEnemyBall::SetAlive(bool _bool){
	Alive = _bool;
}

