#include "DxLib.h"
#include "MyBall.h"
#include "Define.h"
#include "math.h"

#define LENGTH 5

CMyBall::CMyBall(){
	Alive = FALSE;
		Pos0.Set(1,1);
		Pos1.Set(1,1);

		Velocity.Set(1,1);

		Power=1;
		AliveTime=1;
		ShootTime=1;

		ImgMyBall=1;
}

void CMyBall::Init(){
	int ImgBoxes[20];
	LoadDivGraph("CS_pic/Boxes.png", 20, 1, 20, 1, 1, ImgBoxes);
	ImgMyBall = ImgBoxes[0];
}

void CMyBall::Move(int _timecount){
	if(Alive){
		Pos0.Add(Velocity);
			if(Pos0.x>WORLD_WIDTH)Pos0.x-=WORLD_WIDTH;
			if(Pos0.x<0)Pos0.x+=WORLD_WIDTH;
			if(Pos0.y>WORLD_HEIGHT)Pos0.y-=WORLD_HEIGHT;
			if(Pos0.y<0)Pos0.y+=WORLD_HEIGHT;
		Pos1.Add(Velocity);
			if(Pos1.x>WORLD_WIDTH)Pos1.x-=WORLD_WIDTH;
			if(Pos1.x<0)Pos1.x+=WORLD_WIDTH;
			if(Pos1.y>WORLD_HEIGHT)Pos1.y-=WORLD_HEIGHT;
			if(Pos1.y<0)Pos1.y+=WORLD_HEIGHT;

		if(_timecount-ShootTime>=AliveTime){
				Alive=FALSE;
		}
	}
}

bool CMyBall::Shoot(CMine *Mine, int _shotnum, int _timecount){
	Vector TimeShift;
		if(_shotnum==0)TimeShift.Set(-(Mine->GetSize()/2) + ((int)(_timecount/4) % Mine->GetSize()), 0);
		if(_shotnum==2)TimeShift.Set(+(Mine->GetSize()/2) - ((int)(_timecount/4) % Mine->GetSize()), 0);
		if(_shotnum==1)TimeShift.Set(0, -(Mine->GetSize()/2) + ((int)(_timecount/4) % Mine->GetSize()));
		if(_shotnum==3)TimeShift.Set(0, +(Mine->GetSize()/2) - ((int)(_timecount/4) % Mine->GetSize()));

	Pos0 = Mine->GetPos();	
	Pos1.Set(Pos0.x + (_shotnum%2)*(_shotnum-2)*LENGTH, Pos0.y + ((1+_shotnum)%2)*(_shotnum-1)*(-1)*LENGTH);
		Pos0.Add(TimeShift);
		Pos1.Add(TimeShift);

	Velocity.Set((_shotnum%2)*(_shotnum-2)*(-1), ((1+_shotnum)%2)*(_shotnum-1));
	Velocity.Multiple(Mine->GetBallSpeed());
	
	Power = Mine->GetBallPower();
	ShootTime = _timecount;
	AliveTime = 30;

	Alive = TRUE;
	return TRUE;
}


void CMyBall::Draw(Vector _mypos){
	if(Alive){
		DrawPos0 = DrawPosition(Pos0, _mypos);
		DrawPos1 = DrawPosition(Pos1, _mypos);
	
		//DrawLine((int)DrawPos0.x, (int)DrawPos0.y, (int)DrawPos1.x, (int)DrawPos1.y, WHITE);
		DrawExtendGraph((int)DrawPos0.x, (int)DrawPos0.y, (int)DrawPos1.x+1, (int)DrawPos1.y+1, ImgMyBall, true);
	}
}

Vector CMyBall::DrawPosition(Vector _pos, Vector _mypos){
	Vector DrawPos;
	if(abs(_pos.x-_mypos.x)<WORLD_WIDTH-abs(_pos.x-_mypos.x)){
		DrawPos.x = _pos.x-_mypos.x + WINDOW_WIDTH/2;
	}else{
		DrawPos.x = -((_pos.x-_mypos.x)/abs(_pos.x-_mypos.x))*(WORLD_WIDTH-abs(_pos.x-_mypos.x)) + WINDOW_WIDTH/2 ;
	}
	if(abs(_pos.y-_mypos.y)<WORLD_HEIGHT-abs(_pos.y-_mypos.y)){
		DrawPos.y = _pos.y-_mypos.y + WINDOW_HEIGHT/2;
	}else{
		DrawPos.y = -((_pos.y-_mypos.y)/abs(_pos.y-_mypos.y))*(WORLD_HEIGHT-abs(_pos.y-_mypos.y)) + WINDOW_HEIGHT/2 ;
	}
	
	return DrawPos;
}

bool CMyBall::JudgeEnemy(CEnemy *Enemy){
	
	if (Enemy->GetPos().x > max(Pos0.x, Pos1.x) + Enemy->GetRadius()) return false;
	if (Enemy->GetPos().x < min(Pos0.x, Pos1.x) - Enemy->GetRadius()) return false;
	if (Enemy->GetPos().y > max(Pos0.y, Pos1.y) + Enemy->GetRadius()) return false;
	if (Enemy->GetPos().y < min(Pos0.y, Pos1.y) - Enemy->GetRadius()) return false;

	int i, j;

	i = (int)Pos0.x; j = (int)Pos0.y;
		if(JudgeCircle(i, j, Enemy->GetPos(), Enemy->GetRadius())){		
			Alive = FALSE;
		
			Enemy->SetHp(Enemy->GetHp()-Power);
			if(Enemy->GetHp() <= 0)Enemy->SetAlive(FALSE);

			return TRUE;
		}

	i = (int)Pos1.x; j = (int)Pos1.y;
		if(JudgeCircle(i, j, Enemy->GetPos(), Enemy->GetRadius())){		
			Alive = FALSE;
		
			Enemy->SetHp(Enemy->GetHp()-Power);
			if(Enemy->GetHp() <= 0)Enemy->SetAlive(FALSE);

			return TRUE;
		}

	return false;


/*
	for(int i = (int)min(Pos0.x, Pos1.x); i <= (int)max(Pos0.x, Pos1.x); i++){
	for(int j = (int)min(Pos0.y, Pos1.y); j <= (int)max(Pos0.y, Pos1.y); j++){
		
		if(JudgeCircle(i, j, Enemy->GetPos(), Enemy->GetRadius())){		
			Alive = FALSE;
		
			Enemy->SetHp(Enemy->GetHp()-Power);
			if(Enemy->GetHp() <= 0)Enemy->SetAlive(FALSE);

			return TRUE;
		}
	}
	}
	return FALSE;
	*/
}


bool CMyBall::JudgeStar(CStar *Star){
/*
	if(DrawPos0.x<0 || DrawPos0.x>WINDOW_WIDTH || DrawPos0.y<0 || DrawPos0.y>WINDOW_HEIGHT){
		if(DrawPos1.x<0 || DrawPos1.x>WINDOW_WIDTH || DrawPos1.y<0 || DrawPos1.y>WINDOW_HEIGHT){
			return false;
		}
	}
*/
	if (Star->GetPos().x > max(Pos0.x, Pos1.x) + Star->GetRadius()) return false;
	if (Star->GetPos().x < min(Pos0.x, Pos1.x) - Star->GetRadius()) return false;
	if (Star->GetPos().y > max(Pos0.y, Pos1.y) + Star->GetRadius()) return false;
	if (Star->GetPos().y < min(Pos0.y, Pos1.y) - Star->GetRadius()) return false;


	for(int i = (int)min(Pos0.x, Pos1.x); i <= (int)max(Pos0.x, Pos1.x); i++){
	for(int j = (int)min(Pos0.y, Pos1.y); j <= (int)max(Pos0.y, Pos1.y); j++){
		
		if(JudgeCircle(i, j, Star->GetPos(), Star->GetRadius())){		
			Alive = FALSE;
		
			Star->SetHp(Star->GetHp()-Power);
			if(Star->GetHp() <= 0)Star->SetAlive(FALSE);

			return TRUE;
		}
	}
	}
	return FALSE;
}
bool CMyBall::JudgeCircle(int _mex, int _mey, Vector _target, int _targetsize){
	if((_target.x-_mex)*(_target.x-_mex)+(_target.y-_mey)*(_target.y-_mey) <= _targetsize*_targetsize){
		return TRUE;
	}else{
		return FALSE;
	}
}



Vector CMyBall::GetPos(int _index){
	if(_index==0){
		return Pos0;
	}else if(_index==1){
		return Pos1;
	}else{
		return Pos0;
	}
}

int CMyBall::GetPower(){
	return Power;
}

bool CMyBall::GetAlive(){
	return Alive;
}
void CMyBall::SetAlive(bool _bool){
	Alive = _bool;
}

