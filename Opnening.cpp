#include "DxLib.h"
#include "Define.h"
#include "math.h"
#include "Opening.h"

#define MY_SIZE 24
#define SPEED_X 6
#define GRAVITY 1
#define JUMPSPEED 20
#define DEADLINE_SPEED 6.8
#define DEADLINE_COLOR GetColor(192, 0, 0)

	////////////////////////////CubicJouneyより//////////////////////
	//Public Const MyMaxSpeed As Long = 12
	//Public MySpeedX As Single, MySpeedY As Single
	//Public Const MyKasoku As Single = 4
	//Public MyBrake As Single
	//Public Const Gravity As Single = 8          'ここらへん全て100ﾐﾘ秒あたり
	//Public Const FirstJumpSpeed As Single = 35  'ジャンプの初速度
	/////////////////////////////////////////////////////////////////


COpening::COpening(){
	Scene = 0;
	StartTime = 0;
	NowTime = 0;
	DeadLineX = 0;
}

void COpening::Init(){

	int small_ImgOpBack = LoadGraph( "CS_pic/ImgOpBack1.png" );
	ImgOpBack[1] = LoadGraph( "CS_pic/ImgOpBack2.png" );
	ImgOpBack[2] = LoadGraph( "CS_pic/back_play_1.png" );
	ImgOpBack[3] = LoadGraph( "CS_pic/ImgOpBack_back.png" );
	LoadDivGraph( "CS_pic/Me_play.png", 23, 23, 1, 22, 22, ImgOpMine) ;
	LoadDivGraph( "CS_pic/MyEdge.png", 4, 4, 1, 24, 24, ImgOpMyEdge) ;
	
	int ImgBoxes[20];
	LoadDivGraph("CS_pic/Boxes.png", 20, 1, 20, 1, 1, ImgBoxes);
	ImgOpBack[4] = ImgBoxes[7];
	ImgOpDeadLine = ImgBoxes[8];

	//背景画像拡大処理
	int PicSizeX, PicSizeY;
		GetGraphSize(small_ImgOpBack, &PicSizeX, &PicSizeY);
		ImgOpBack[0] = MakeScreen(PicSizeX*6, PicSizeY*6, true);
		SetDrawScreen( ImgOpBack[0] ); //描画先変更
		DrawExtendGraph(0, 0, PicSizeX*6, PicSizeY*6, small_ImgOpBack, true);
		SetDrawScreen( DX_SCREEN_BACK ); //描画先を画面裏に
	Pos.Set(0, 1362);
	Velocity.Set(SPEED_X, 0.0);
	Jump = false;

	DeadLineX = -430;
	PressedRETURN = false;
	Scene = 0;
}

void COpening::Awake(int _timecount){
	StartTime = _timecount;
	PressedRETURN = true;
}


int COpening::Main(int _timecount, bool _op){
	NowTime = _timecount-StartTime;

	if (Scene==2 && NowTime-MemoTime==100){		//MemoTimeはタイトル文字のスクロール終了時のTimeCount
		Scene = 3;
	}
	
	Move(_op);

	DrawBack();
	DrawMine();
	DrawCaption(_op);

	
	////音楽ON/OFF
	//if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0 ){
	//	int MouseX , MouseY;
	//	GetMousePoint( &MouseX , &MouseY ) ;
	//	if (MouseX>WINDOW_WIDTH-30 && MouseY>WINDOW_HEIGHT-30){
	//		printfDx("Down\n");
	//	}
	//}

	if (!(CheckHitKey(KEY_INPUT_RETURN)||(!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_1)==0))||CheckHitKey(KEY_INPUT_SPACE))) PressedRETURN = false;

	if(Scene < 3 && NowTime>30 && CheckHitKeyAll()){
		Scene = 3;
		StartTime = -750;
		Velocity.Set(SPEED_X, 0.0);
		Pos.Set(0.0, -800);	
		PressedRETURN = true;
		return -1;
	}else if(Scene == 3 && (CheckHitKey(KEY_INPUT_RETURN)||(!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_1)==0))||CheckHitKey(KEY_INPUT_SPACE)) && !PressedRETURN){
		return -2;
	}else if (Scene==3) {
		return -1;
	}else{
		return 1;
	}
}

void COpening::Move(bool _op){
	
	for(int i=2;i>0;i--){
		OldPos[i] = OldPos[i-1];
	}
	OldPos[0] = Pos;

	if(!_op){
		Pos.Add(Velocity);
		return;
	}else{
		if (Scene==1){
			Velocity.y = min(Velocity.y+(double)GRAVITY/6, 0);
			if(NowTime>650){Scene=2; MemoTime = NowTime;}
		}

		switch(NowTime){
		case 47: 
		case 47+36+2:
		case 47+36+2+34+20:
		case 47+36+2+34+20+34+10:
		case 47+36+2+34+20+34+10+37+15:
		case 47+36+2+34+20+34+10+37+15+32+15:
		case 47+36+2+34+20+34+10+37+15+32+15+32+14:
		case 47+36+2+34+20+34+10+37+15+32+15+32+14+27+3:
		case 47+36+2+34+20+34+10+37+15+32+15+32+14+27+3+32+8:
		case 47+36+2+34+20+34+10+37+15+32+15+32+14+27+3+32+8+34+9:
			if(!Jump)Velocity.y= -1*JUMPSPEED;
			Jump = true;
			break;
		case 47+36 :
		case 47+36+2+34 :
		case 47+36+2+34+20+34:
		case 47+36+2+34+20+34+10+37:
		case 47+36+2+34+20+34+10+37+15+32:
		case 47+36+2+34+20+34+10+37+15+32+15+32:
		case 47+36+2+34+20+34+10+37+15+32+15+32+14+27:
		case 47+36+2+34+20+34+10+37+15+32+15+32+14+27+3+32:
		case 47+36+2+34+20+34+10+37+15+32+15+32+14+27+3+32+8+34:
		case 47+36+2+34+20+34+10+37+15+32+15+32+14+27+3+32+8+34+9+33:
			Velocity.y = 0;
			Jump = false;
			break;
		case 47+36+2+34+20+34+10+37+15+32+15+32+14+27+3+32+8+34+9+33+4:
			if(!Jump)Velocity.y= -1*(JUMPSPEED);
			Jump = true;
			Scene=1;
			break;
		}
		if(Scene<2){
			DeadLineX +=DEADLINE_SPEED;
	
			if(Jump&&Scene==0) Velocity.y = min(Velocity.y+GRAVITY, JUMPSPEED);
			if(Velocity.y==JUMPSPEED){
				Jump=false;
				Velocity.y = 0;
			}
		}

		Pos.Add(Velocity);
	}
}

void COpening::DrawCaption(bool _op){
	
	if (_op){	
		if(!((NowTime/10) % 3 ==0)) {
			DrawString(WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT-100, "Press Key to Skip", GRAY); 
		}
		if(Scene==2){
			SetFontSize(GetFontSize()+5);
			DrawString(WINDOW_WIDTH - (WINDOW_WIDTH/2 + 100) * (NowTime-MemoTime)/100 , 100, "Cubic Shooting", WHITE);
			SetFontSize(GetFontSize()-5);
		}
	}else{
		if(Scene==3){
			if(!((NowTime/15) % 3 ==0)) DrawString(WINDOW_WIDTH/2 - 50, WINDOW_HEIGHT-100, "Press ENTER", GetColor(200,200,200)); 
			
			SetFontSize(GetFontSize()+5);
			DrawString( WINDOW_WIDTH/2 - 100, 100, "Cubic Shooting", WHITE);
			SetFontSize(GetFontSize()-8);
			DrawFormatString( WINDOW_WIDTH/2 +73, 107, GetColor(200,200,200), " %s", VERSION);
			SetFontSize(GetFontSize()+3);
		}
	}
}
void COpening::DrawMine(){
	
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
	
	
		for(int i=2;i>=0;i--){
			Vector DrawPos;
			DrawPos.Set( OldPos[i].x - Pos.x + WINDOW_WIDTH/2, OldPos[i].y - Pos.y + WINDOW_HEIGHT/2);
			DrawExtendGraph((int)DrawPos.x - MY_SIZE/2, (int)DrawPos.y - MY_SIZE/2  , (int)DrawPos.x+MY_SIZE/2, (int)DrawPos.y+MY_SIZE/2, ImgOpMine[19+i], true);
		}
	
		//枠（破線）
		DrawGraph(WINDOW_WIDTH/2 - 12, WINDOW_HEIGHT/2 - 12, ImgOpMyEdge[(NowTime/3)%4], true);
	
		//中身（矢印）
		DrawGraph(WINDOW_WIDTH/2 - 11, WINDOW_HEIGHT/2 - 11, ImgOpMine[MyPicNum], false);
	
}

void COpening::DrawBack(){
	
	int PicSizeX, PicSizeY;
	Vector DrawPos;

	if (Scene>0) {	
		//Stage.cppから丸コピ　宇宙背景
		GetGraphSize(ImgOpBack[2], &PicSizeX, &PicSizeY);
			DrawPos.x = (int)(WORLD_WIDTH+Pos.x) % PicSizeX;		//WORLD_WIDTHを足しているのは画面左端での処理のため
			DrawPos.y = (int)(WORLD_HEIGHT+Pos.y) % PicSizeY;
		
			DrawRectGraph(0, 0, (int)DrawPos.x, (int)DrawPos.y, PicSizeX-(int)DrawPos.x, PicSizeY-(int)DrawPos.y, ImgOpBack[2], FALSE, FALSE);

			for(int i = 0; i <= (WINDOW_WIDTH % PicSizeX) + 1; i++){
				DrawRectGraph(PicSizeX-(int)DrawPos.x+i*PicSizeX, 0, 0, (int)DrawPos.y, PicSizeX, PicSizeY-(int)DrawPos.y, ImgOpBack[2], FALSE, FALSE);
			}
			for(int j = 0; j <= (WINDOW_HEIGHT % PicSizeY) + 1; j++){
				DrawRectGraph(0, PicSizeY-(int)DrawPos.y+j*PicSizeY, (int)DrawPos.x, 0, PicSizeX-(int)DrawPos.x, PicSizeY, ImgOpBack[2], FALSE, FALSE);
			}

			DrawPos.x = PicSizeX - DrawPos.x;
			DrawPos.y = PicSizeY - DrawPos.y;
			for(int i = 0; i <= (WINDOW_WIDTH % PicSizeX) + 1; i++){
				for(int j = 0; j <= (WINDOW_HEIGHT % PicSizeY) + 1; j++){
					DrawGraph((int)DrawPos.x+(i*PicSizeX), (int)DrawPos.y+(j*PicSizeY),ImgOpBack[2],true);	
				}
			}
	}
	
	//地上の背景絵
	if(Scene==0 || Scene==1){
		
			if(NowTime<523)DrawRectGraph(0, 0, (int)Pos.x/3, (int)Pos.y/3 - WINDOW_HEIGHT/2 + 50+130, WINDOW_WIDTH, WINDOW_HEIGHT, ImgOpBack[3], false, false);
			DrawExtendGraph(0, -1*(int)Pos.y, WINDOW_WIDTH, 200-(int)Pos.y, ImgOpBack[4],true);
			DrawRectGraph(0, 0, (int)Pos.x, (int)Pos.y, WINDOW_WIDTH, WINDOW_HEIGHT, ImgOpBack[0], true, false);
	}

	if(Scene==1){
		//グラデーション
		GetGraphSize(ImgOpBack[1], &PicSizeX, &PicSizeY);
		int j = WINDOW_WIDTH/PicSizeX;

		for (int i=0; i < j; i++){
			DrawRectGraph(i*PicSizeX, 0, 0, PicSizeY+(int)Pos.y, PicSizeX, -1*(int)Pos.y, ImgOpBack[1], false, false);
		}
	}
	

	//DeadLine
	if (Scene==0 || Scene==1){
		DrawPos.Set(DeadLineX - Pos.x + WINDOW_WIDTH/2, -Pos.y + 90*6);
		DrawExtendGraph((int)DrawPos.x, (int)DrawPos.y, (int)DrawPos.x+10, -(int)Pos.y+1362+WINDOW_HEIGHT/2+10, ImgOpDeadLine, true);
	}
}