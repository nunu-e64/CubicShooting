#include "DxLib.h"
#include "Stage.h"

#define STAGE_MAX 9
#define STAGE_MIN 0

CStage::CStage(){
	StageNum=STAGE_MIN;
	ImgBack=1;
	NearestStar.Set(0,0);
	HardMode = false;
	AliveStarNum=0;
}

void CStage::Init(){
	ImgBack = LoadGraph("CS_pic/back_play_1.png");
	ImgMark = LoadGraph("CS_pic/Mark1.png");
	GetGraphSize(ImgBack, &PicSizeX, &PicSizeY);

	FontMini = CreateFontToHandle(NULL, 12, -1);
}


void CStage::Draw(Vector _mypos){
	Vector DrawPos;

	//背景		
		DrawPos.x = (int)(WORLD_WIDTH+_mypos.x-WINDOW_WIDTH/2) % PicSizeX;		//WORLD_WIDTHを足しているのは画面左端での処理のため
		DrawPos.y = (int)(WORLD_HEIGHT+_mypos.y-WINDOW_HEIGHT/2) % PicSizeY;
		
		DrawRectGraph(0, 0, (int)DrawPos.x, (int)DrawPos.y, PicSizeX-(int)DrawPos.x, PicSizeY-(int)DrawPos.y, ImgBack, FALSE, FALSE);

		for(int i = 0; i <= (WINDOW_WIDTH % PicSizeX) + 1; i++){
			DrawRectGraph(PicSizeX-(int)DrawPos.x+i*PicSizeX, 0, 0, (int)DrawPos.y, PicSizeX, PicSizeY-(int)DrawPos.y, ImgBack, FALSE, FALSE);
		}
		for(int j = 0; j <= (WINDOW_HEIGHT % PicSizeY) + 1; j++){
			DrawRectGraph(0, PicSizeY-(int)DrawPos.y+j*PicSizeY, (int)DrawPos.x, 0, PicSizeX-(int)DrawPos.x, PicSizeY, ImgBack, FALSE, FALSE);
		}

		DrawPos.x = PicSizeX - DrawPos.x;
		DrawPos.y = PicSizeY - DrawPos.y;
		for(int i = 0; i <= (WINDOW_WIDTH % PicSizeX) + 1; i++){
			for(int j = 0; j <= (WINDOW_HEIGHT % PicSizeY) + 1; j++){
				DrawGraph((int)DrawPos.x+(i*PicSizeX), (int)DrawPos.y+(j*PicSizeY),ImgBack,true);	
			}
		}

	//マーカー
		if (AliveStarNum>0){
			if(abs((int)(NearestStar.x))>WINDOW_WIDTH/2+70 || abs((int)(NearestStar.y))>WINDOW_HEIGHT/2+70){
				DrawRotaGraph2(WINDOW_WIDTH/2, WINDOW_HEIGHT/2,  50-min(WINDOW_WIDTH,WINDOW_HEIGHT)/2, 13, 1, GetAngle(NearestStar), ImgMark, true, false);
			}
		}
}

void CStage::DrawCaption(bool _showexplain){
	
	DrawFormatString(0, 0, WHITE, "Stage : %d", StageNum);
	if(HardMode)	DrawString(0, 20, "Mode  : Hard", WHITE);
	else			DrawString(0, 20, "Mode  : Easy", WHITE);

	if ((StageNum==STAGE_MIN || _showexplain)){
		DrawString(WINDOW_WIDTH-180-GetDrawFormatStringWidth("残りのアジトの数"), 10, "残りのアジトの数  →  →  →  →", GRAY) ;
		DrawCenterString(WINDOW_WIDTH/2, 70, "ザコを生んでいる敵のアジトを見つけてはかいせよ！", GRAY) ;
		DrawCenterString(WINDOW_WIDTH/2, 100, "アジトはオレンジ色の印の方向にあるぞ！", GRAY) ;
		DrawCenterString(WINDOW_WIDTH/2, WINDOW_HEIGHT-110, "ヒント1：ザコやアジト自体にあたってもダメージはありません　　　", GRAY);
		DrawCenterString(WINDOW_WIDTH/2, WINDOW_HEIGHT-85, "ヒント2：アジト中央にめりこむと四方向のショットすべてがヒットし", GRAY);
		DrawCenterString(WINDOW_WIDTH/2, WINDOW_HEIGHT-65, "　　　　 とても多くのダメージを与えられます　　　　　　　　　　", GRAY);
	}

	DrawStringToHandle(WINDOW_WIDTH-GetDrawFormatStringWidthToHandle(FontMini, "↑↓←→:移動　Esc:自死　Esc長押し:ゲーム終了 "), WINDOW_HEIGHT-20, "↑↓←→:移動　Esc:自死　Esc長押し:ゲーム終了 ", GRAY, FontMini);
}

void CStage::DrawStarCount(){
	for( int i=1; i<=AliveStarNum; i++){
		DrawString(WINDOW_WIDTH-i*30, 10, "☆", GREEN);
	}
}
void CStage::DrawEnemyCount(int _alive_enemynum){
	DrawFormatString(WINDOW_WIDTH-100, 400, GRAY, "ザコの数：%d", _alive_enemynum);
}


bool CStage::LastStage(){
	if( StageNum == STAGE_MAX && HardMode ){
		return true;
	}else{
		return false;
	}
}


int CStage::GetStageNum(){
	CheckStageNum();
	return StageNum;
}
void CStage::SetStageNumMin(){
	StageNum = STAGE_MIN;
}


void CStage::SetStageNum(int _stagenum){
	StageNum = _stagenum;
	CheckStageNum();
}
void CStage::ChangeStageNum(bool _add){
	if (_add) StageNum++;
	if (!_add) StageNum--;
	CheckStageNum();
}

void CStage::CheckStageNum(){
	if (StageNum<STAGE_MIN) StageNum = STAGE_MAX;
	if (StageNum>STAGE_MAX) StageNum = STAGE_MIN;
}


void CStage::SetNearestStar(Vector nearest_star){
	NearestStar = nearest_star;
}
double CStage::GetAngle(Vector _targetpos){
		/*
		if(Pos.x-_targetpos.x>WORLD_WIDTH/2){
			_targetpos.x+=WORLD_WIDTH;
		}else if(Pos.x-_targetpos.x<-WORLD_WIDTH/2){
			_targetpos.x-=WORLD_WIDTH;
		}
		if(Pos.y-_targetpos.y>WORLD_HEIGHT/2){
			_targetpos.y+=WORLD_HEIGHT;
		}else if(Pos.y-_targetpos.y<-WORLD_HEIGHT/2){
			_targetpos.y-=WORLD_HEIGHT;
		}*/

	double angle;
		angle = atan((_targetpos.y)/(_targetpos.x));
		if(_targetpos.x < 0) angle+=PI ;
		if(angle < 0) angle+=PI*2;

	return angle;
}


bool CStage::SetDifficulity(){
	if (StageNum==STAGE_MAX){
		HardMode=true;
		return true;
	}else{
		return false;
	}
}
bool CStage::GetDifficulity(){
	return HardMode;
}
void CStage::ChangeDifficulity(){
	HardMode = !HardMode;
}
void CStage::SetAliveStarNum(int _num){
	AliveStarNum = _num;
}

int CStage::GetAliveStarNum(){
	return AliveStarNum;
}
