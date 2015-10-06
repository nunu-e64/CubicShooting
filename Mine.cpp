#pragma once
#include "DxLib.h"
#include "Mine.h"
#include "Define.h"
#include "math.h"

#define MAXHP 240	//200
#define MAXSPEED 7
#define ACCELE 0.8
#define BRAKE 0.25
#define SHOOTTIME 6 //6 //5

#define BALLPOWER 1
#define BALLSPEED 10
#define BALLLEVEL 0

#define KEY_CROSS 1/sqrt(2.0)

//#define BALLPOWER 1
//#define BALLSPEED 10
//#define BALLLEVEL 0


CMine::CMine(){
	Size = 24;
	Radius = Size/2;

	MaxSpeed = MAXSPEED;
	Acceleration = ACCELE;
	Brake = BRAKE;

	MaxHp = MAXHP;
	//MutekiTime = 60;
	//MutekiStart = 0;
	
	Lv[0]=0;
	Lv[1]=0;
	Lv[2]=0;
	Exp[0]=0;
	Exp[1]=0;
	Exp[2]=0;

	Alive = false;
	Visible = false;
}

void CMine::Awake(bool _hardmode){
	
	Pos.Set(0, WORLD_HEIGHT/2);
		for(int i=0;i<3;i++){
			OldPos[i]=Pos;
		}

	Velocity.Set(0,0);
	
	if(_hardmode) MaxHp = MAXHP/2; else MaxHp = MAXHP;

	Hp = MaxHp;
	OldHp = Hp;
	Alive = true;
	Visible = true;

	for (int i=0; i<8; i++){
		DeadCircleDrawPos[i].Set(0,0);
	}
}

void CMine::Init(){	
	LoadDivGraph( "CS_pic/Me_play.png", 23, 23, 1, 22, 22, ImgMine) ;
	LoadDivGraph( "CS_pic/MyEdge.png", 4, 4, 1, 24, 24, ImgMyEdge) ;
	
	int ImgBoxes[20];
	LoadDivGraph("CS_pic/Boxes.png", 20, 1, 20, 1, 1, ImgBoxes);
	ImgMyHp[0] = ImgBoxes[2];
	ImgMyHp[1] = ImgBoxes[3];
	ImgMyHp[2] = ImgBoxes[4];
}

void CMine::Move(){
	double KeyPress = 1;
	
	if (!Alive){
		for (int i=0; i<8; i++){
			DeadCircleDrawPos[i].Add(cos(i * PI / 4) * 2, sin(i * PI / 4) * 2);
		}
		if (DeadCircleDrawPos[0].x >= 300) Visible = false;
	}

	for(int i=2;i>0;i--){
		OldPos[i] = OldPos[i-1];
	}
	OldPos[0] = Pos;

	if(Alive){
		//上かつ左のような押し方をしていないかチェック
		if ((!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_LEFT)==0)) && (!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_RIGHT)==0))){
		}else if ((!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_LEFT)==0)) || (!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_RIGHT)==0))){
			if ((!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_UP)==0)) && (!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_DOWN)==0))){
			}else if ((!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_UP)==0)) || (!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_DOWN)==0))){
				KeyPress = KEY_CROSS;
			}
		}

		//左右移動
		if ((!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_LEFT)==0)) && (!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_RIGHT)==0))){
		}else if ((!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_LEFT)==0))){
			Velocity.x -= Acceleration*KeyPress;
		}else if ((!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_RIGHT)==0))){
			Velocity.x += Acceleration*KeyPress;
		}

		//上下移動
		if ((!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_DOWN)==0)) && (!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_UP)==0))){
		}else if ((!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_DOWN)==0))){
			Velocity.y += Acceleration*KeyPress;
		}else if ((!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_UP)==0))){
			Velocity.y -= Acceleration*KeyPress;
		}

		bool FlagVelocity = false;
			//ブレーキ処理（ブレーキで正負変わったときは速さ0にする	）
			if(Velocity.y>0)FlagVelocity=true; else FlagVelocity=false;
			if (!Velocity.y==0) Velocity.y -= Brake*Velocity.y/Velocity.GetLength();
			if((Velocity.y<0 && FlagVelocity)||(Velocity.y>0 && !FlagVelocity))Velocity.y = 0;
	
			if(Velocity.x>0)FlagVelocity=true; else FlagVelocity=false;
   			if (!Velocity.x==0) Velocity.x -= Brake*Velocity.x/Velocity.GetLength();
			if((Velocity.x<0 && FlagVelocity)||(Velocity.x>0 && !FlagVelocity))Velocity.x = 0;

   
		if(Velocity.GetLength()>MaxSpeed) Velocity.Set(MaxSpeed*Velocity.x/Velocity.GetLength(), MaxSpeed*Velocity.y/Velocity.GetLength());

		//速度が決まったので位置に反映
		Pos.Add(Velocity);
			if(Pos.x>WORLD_WIDTH)Pos.x-=WORLD_WIDTH;
			if(Pos.x<0)Pos.x+=WORLD_WIDTH;
			if(Pos.y>WORLD_HEIGHT)Pos.y-=WORLD_HEIGHT;
			if(Pos.y<0)Pos.y+=WORLD_HEIGHT;
	
	}
}

void CMine::Draw(int _timecount){
	
	if (!Visible)return;


	int MyPicNum;
	int MyAngle;
	
	MyAngle = (int)(1000*atan(-Velocity.y/Velocity.x)/PI);		// atan･･･-Pi/2～PI/2
		if(MyAngle<=(int)(-1000*5/12)){
			MyPicNum = 12;
		}else if(MyAngle<=(int)(-1000*7/24)){
			MyPicNum = 13;
		}else if(MyAngle<=(int)(-1000*5/24)){
			MyPicNum = 14;
		}else if(MyAngle<=(int)(-1000*1/12)){
			MyPicNum = 15;
		}else if(MyAngle<=(int)(1000*1/12)){
			MyPicNum = 0;
		}else if(MyAngle<=(int)(1000*5/24)){
			MyPicNum = 1;
		}else if(MyAngle<=(int)(1000*7/24)){
			MyPicNum = 2;
		}else if(MyAngle<=(int)(1000*5/12)){
			MyPicNum = 3;
		}else{
			MyPicNum = 4;
		}

		if (Velocity.x < 0) MyPicNum = (MyPicNum + 8) % 16; 
		if (Velocity.GetLength() == 0)MyPicNum = 16;
	
	if(Alive){
		//OldPos
		Vector DrawPos;		
			for(int i=2;i>=0;i--){
				DrawPos = DrawPosition(OldPos[i], Pos);
				DrawExtendGraph((int)DrawPos.x-Size/2, (int)DrawPos.y-Size/2, (int)DrawPos.x+Size/2, (int)DrawPos.y+Size/2, ImgMine[19+i], true);
			}
	
		//枠（破線）
		DrawGraph(WINDOW_WIDTH/2 - 12, WINDOW_HEIGHT/2 - 12, ImgMyEdge[(_timecount/3)%4], true);
	
		//中身（矢印）
		DrawGraph(WINDOW_WIDTH/2 - 11, WINDOW_HEIGHT/2 - 11, ImgMine[MyPicNum], false);
		if(!(OldHp == Hp)&&_timecount/8%2)DrawGraph(WINDOW_WIDTH/2 - 11, WINDOW_HEIGHT/2 - 11, ImgMine[17], false);
	}

	//ティウンティウン
	if(!Alive){
		for (int i=0; i<8; i++){
			if(_timecount/5 % 2 == 0){
				DrawGraph((int)DeadCircleDrawPos[i].x-11+WINDOW_WIDTH/2, (int)DeadCircleDrawPos[i].y-11+WINDOW_HEIGHT/2, ImgMine[18], true);
			}
		}
	}
	

	//HPバー
	if(!(Hp==-1)){	//titleなどではHp-1
		Vector BaseBox;	
			BaseBox.Set(35, WINDOW_HEIGHT-40);

		DrawString((int)BaseBox.x-30, (int)BaseBox.y, "HP:", GetColor( 150 , 150 , 150 ));

		int HpColor = (( !(OldHp == Hp) ) ? RED : GetColor(250, 250*Hp/MaxHp ,10)) ;
		OldHp = Hp;
			DrawExtendGraph((int)BaseBox.x+2, (int)BaseBox.y+2, (int)BaseBox.x+100+2, (int)BaseBox.y+15+2, ImgMyHp[0], true);
			DrawExtendGraph((int)BaseBox.x-1, (int)BaseBox.y-1, (int)BaseBox.x+100+1, (int)BaseBox.y+15+1, ImgMyHp[1], true);
			DrawExtendGraph((int)BaseBox.x, (int)BaseBox.y, (int)BaseBox.x+100, (int)BaseBox.y+15, ImgMyHp[2], true);
			if(Hp>0)DrawBox((int)BaseBox.x, (int)BaseBox.y, (int)BaseBox.x+100*Hp/MaxHp, (int)BaseBox.y+15, HpColor, true);
	}		

}

Vector CMine::DrawPosition(Vector _pos, Vector _mypos){
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

void CMine::SetVelocity(Vector _velocity){
	Velocity.Set(_velocity);
}

int CMine::GetBallLv(){
	return BALLLEVEL;
}
int CMine::GetBallPower(){
	return BALLPOWER;
}
int CMine::GetBallSpeed(){
	return BALLSPEED;
}
int CMine::GetShootTime(){
	return SHOOTTIME;
}


Vector CMine::GetPos(){
	return Pos;
}
int CMine::GetSize(){
	return Size;
}
int CMine::GetRadius(){
	return Radius;
}

void CMine::SetHp(int _hp){
	Hp = _hp;
}
int CMine::GetHp(){
	return Hp;
}
bool CMine::GetAlive(){
	return Alive;
}
void CMine::SetAlive(bool _bool){
	Alive=_bool;
}

bool CMine::GetVisible(){
	return Visible;
}
void CMine::SetVisible(bool _bool){
	Visible=_bool;
}