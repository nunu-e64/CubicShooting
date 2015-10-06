#pragma once
#include "DxLib.h"
#include "Define.h"
#include "stdlib.h"
#include "Mine.h"
#include "Star.h"
#include "Enemy.h"
#include "MyBall.h"
#include "EnemyBall.h"
#include "Stage.h"
#include "Clock.h"
#include "Opening.h"
#include "Ranking.h"


/*当時はdeleteの必要性どころか存在すら認知してなかった模様ｗｗｗこれは酷いｗｗｗ*/
CMine Mine;
CMyBall *MyBall = new CMyBall[MY_BALL_NUM];
CEnemyBall *EnemyBall = new CEnemyBall[ENEMY_BALL_NUM];
CStar *Star = new CStar[STAR_NUM];
CEnemy *Enemy = new CEnemy[ENEMY_NUM];

CStage Stage;
CClock Clock;
COpening Beginning;
CRanking Ranking;

CEnemy *EnemyModel = new CEnemy[30];
CEnemyBall *EnemyBallModel = new CEnemyBall[30];


void GameAwake(){		//ゲーム起動時処理
	
	srand(GetNowCount());	//srand(1);		$

	
	Beginning.Init();
	Stage.Init();
	Mine.Init();

	for (int i=0; i<MY_BALL_NUM; i++){
		MyBall[i].Init();
	}

	
	//Ranking.Init();	//$

	//131128_1036
	EnemyBallModel[0].Appear(6, 1, 30, 0);
	EnemyBallModel[1].Appear(4, 4, 80, 1);
	EnemyBallModel[2].Appear(4, 2, 40, 0);
	EnemyBallModel[3].Appear(4, 3, 60, 4);
	EnemyBallModel[4].Appear(4, 2, 40, 3);
	EnemyBallModel[5].Appear(4, 3, 40, 4);
	EnemyBallModel[6].Appear(3, 2, 30, 3);
	EnemyBallModel[7].Appear(4, 4, 40, 0);
	EnemyBallModel[8].Appear(7, 3, 30, 0);
	EnemyBallModel[9].Appear(5, 5, 120, 1);
	EnemyBallModel[10].Appear(5, 3, 60, 2);
	EnemyBallModel[11].Appear(6, 5, 250, 4);
	EnemyBallModel[12].Appear(5, 4, 60, 3);
	EnemyBallModel[13].Appear(5, 5, 60, 4);
	EnemyBallModel[14].Appear(4, 4, 30, 3);
	EnemyBallModel[15].Appear(5, 6, 60, 0);


	//131128_1036
	EnemyModel[0].Appear(4, 10, 3000, 1, 0, EnemyBallModel[0].GetPower(), 10);
	EnemyModel[1].Appear(1, 10, 1500, 4, 1, EnemyBallModel[1].GetPower(), 50);
	EnemyModel[2].Appear(6, 10, 1000, 2, 2, EnemyBallModel[2].GetPower(), 10);
	EnemyModel[3].Appear(0, 20, 1500, 4, 3, EnemyBallModel[3].GetPower(), 10);
	EnemyModel[4].Appear(2, 30, 4000, 3, 4, EnemyBallModel[4].GetPower(), 10);
	EnemyModel[5].Appear(2, 20, 1500, 4, 5, EnemyBallModel[5].GetPower(), 10);
	EnemyModel[6].Appear(1, 20, 6000, 1, 6, EnemyBallModel[6].GetPower(), 8);
	EnemyModel[7].Appear(2, 20, 1500, 4, 7, EnemyBallModel[7].GetPower(), 30);
	EnemyModel[8].Appear(5, 10, 4000, 1, 8, EnemyBallModel[8].GetPower(), 10);
	EnemyModel[9].Appear(1, 10, 2000, 4, 9, EnemyBallModel[9].GetPower(), 50);
	EnemyModel[10].Appear(7, 10, 1500, 2, 10, EnemyBallModel[10].GetPower(), 5);
	EnemyModel[11].Appear(0, 20, 200, 4, 11, EnemyBallModel[11].GetPower(), 4);
	EnemyModel[12].Appear(3, 30, 5000, 3, 12, EnemyBallModel[12].GetPower(), 5);
	EnemyModel[13].Appear(2, 20, 2000, 4, 13, EnemyBallModel[13].GetPower(), 4);
	EnemyModel[14].Appear(1, 20, 7000, 1, 14, EnemyBallModel[14].GetPower(), 5);
	EnemyModel[15].Appear(4, 30, 2000, 4, 15, EnemyBallModel[15].GetPower(), 25);

}

void AllFalse(){
	for( int i  = 0; i < STAR_NUM; i++){
		Star[i].SetAlive(false);
		Star[i].SetVisible(false);
	}
	for( int i  = 0; i < ENEMY_NUM; i++){
		Enemy[i].SetAlive(false);
	}
	for( int i  = 0; i < ENEMY_BALL_NUM; i++){
		EnemyBall[i].SetAlive(false);
	}
	for( int i  = 0; i < MY_BALL_NUM; i++){
		MyBall[i].SetAlive(false);
	}
	Mine.SetAlive(false);
	Mine.SetVisible(false);
}

void Awake(){		//ステージ開始

	AllFalse();
	Clock.Awake();
	
	Mine.Awake(Stage.GetDifficulity());

	int loopcount=0;
	while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0  ){
		if (loopcount/20 % 4 == 0) DrawString(WINDOW_WIDTH/2-50, WINDOW_HEIGHT/2-100, "Now Loading", WHITE);
		if (loopcount/20 % 4 == 1) DrawString(WINDOW_WIDTH/2-50, WINDOW_HEIGHT/2-100, "Now Loading.", WHITE);
		if (loopcount/20 % 4 == 2) DrawString(WINDOW_WIDTH/2-50, WINDOW_HEIGHT/2-100, "Now Loading..", WHITE);
		if (loopcount/20 % 4 == 3) DrawString(WINDOW_WIDTH/2-50, WINDOW_HEIGHT/2-100, "Now Loading...", WHITE);
		loopcount++;
		if(loopcount=80)break;
	}

	//星出現
	int StarNum;
	switch(Stage.GetStageNum()){
		case 0:		//練習ステージ
			StarNum = min(STAR_NUM, 1);
			Star[0].Appear(1*WORLD_WIDTH/3, 1*WORLD_HEIGHT/2, 0.1, rand(), 0, 342, 4, 1000, 1, 1500);
			break;
		case 1:
			StarNum = min(STAR_NUM, 2);
			Star[0].Appear(0*WORLD_WIDTH/StarNum, 0*WORLD_HEIGHT/StarNum, 0.1, rand(), 0, 344, 2, 622, 4, 923);
			Star[1].Appear(1*WORLD_WIDTH/StarNum, 1*WORLD_HEIGHT/StarNum, 0.1, rand(), 0, 330, 6, 624, 1, 910);
			break;
		case 2:
			StarNum = min(STAR_NUM, 3);
			Star[0].Appear(0*WORLD_WIDTH/StarNum, 0*WORLD_HEIGHT/StarNum, 0.1, rand(), 4, 333, 6, 618, 5, 918);
			Star[1].Appear(1*WORLD_WIDTH/StarNum, 1*WORLD_HEIGHT/StarNum, 0.1, rand(), 0, 336, 3, 629, 7, 916);
			Star[2].Appear(2*WORLD_WIDTH/StarNum, 2*WORLD_HEIGHT/StarNum, 0.1, rand(), 2, 346, 0, 633, 4, 929);
			break;
		case 3:
			StarNum = min(STAR_NUM, 4);
			Star[0].Appear(0*WORLD_WIDTH/StarNum, 0*WORLD_HEIGHT/StarNum, 0.25, rand(), 0, 342, 1, 627, 7, 908);
			Star[1].Appear(1*WORLD_WIDTH/StarNum, 1*WORLD_HEIGHT/StarNum, 0.25, rand(), 8, 317, 1, 602, 7, 917);
			Star[2].Appear(2*WORLD_WIDTH/StarNum, 2*WORLD_HEIGHT/StarNum, 0.25, rand(), 4, 310, 0, 611, 11, 910);
			Star[3].Appear(3*WORLD_WIDTH/StarNum, 3*WORLD_HEIGHT/StarNum, 0.25, rand(), 12, 330, 0, 601, 3, 890);
			break;
		case 4:
			StarNum = min(STAR_NUM, 4);
			Star[0].Appear(0*WORLD_WIDTH/StarNum, 0*WORLD_HEIGHT/StarNum, 0.25, rand(), 4, 340, 8, 614, 5, 914);
			Star[1].Appear(1*WORLD_WIDTH/StarNum, 1*WORLD_HEIGHT/StarNum, 0.25, rand(), 4, 324, 6, 619, 9, 890);
			Star[2].Appear(2*WORLD_WIDTH/StarNum, 2*WORLD_HEIGHT/StarNum, 0.25, rand(), 4, 311, 9, 609, 14, 893);
			Star[3].Appear(3*WORLD_WIDTH/StarNum, 3*WORLD_HEIGHT/StarNum, 0.25, rand(), 4, 319, 5, 616, 14, 916);
			break;
		case 5:
			StarNum = min(STAR_NUM, 5);
			Star[0].Appear(0*WORLD_WIDTH/StarNum, 0*WORLD_HEIGHT/StarNum, 0.4, rand(), 6, 338, 8, 627, 12, 907);
			Star[1].Appear(1*WORLD_WIDTH/StarNum, 1*WORLD_HEIGHT/StarNum, 0.4, rand(), 7, 341, 9, 608, 10, 923);
			Star[2].Appear(2*WORLD_WIDTH/StarNum, 2*WORLD_HEIGHT/StarNum, 0.4, rand(), 6, 330, 8, 622, 12, 929);
			Star[3].Appear(3*WORLD_WIDTH/StarNum, 3*WORLD_HEIGHT/StarNum, 0.4, rand(), 7, 342, 9, 623, 10, 900);
			Star[4].Appear(4*WORLD_WIDTH/StarNum, 4*WORLD_HEIGHT/StarNum, 0.4, rand(), 6, 324, 8, 625, 12, 922);
			break;
		case 6:
			StarNum = min(STAR_NUM, 6);
			Star[0].Appear(0*WORLD_WIDTH/StarNum, 0*WORLD_HEIGHT/StarNum, 0.25, rand(), 0, 344, 14, 601, 8, 908);
			Star[1].Appear(1*WORLD_WIDTH/StarNum, 1*WORLD_HEIGHT/StarNum, 0.25, rand(), 0, 336, 14, 632, 8, 891);
			Star[2].Appear(2*WORLD_WIDTH/StarNum, 2*WORLD_HEIGHT/StarNum, 0.25, rand(), 0, 343, 14, 616, 8, 891);
			Star[3].Appear(3*WORLD_WIDTH/StarNum, 3*WORLD_HEIGHT/StarNum, 0.25, rand(), 0, 330, 14, 622, 8, 923);
			Star[4].Appear(4*WORLD_WIDTH/StarNum, 4*WORLD_HEIGHT/StarNum, 0.25, rand(), 0, 314, 14, 604, 8, 890);
			Star[5].Appear(5*WORLD_WIDTH/StarNum, 5*WORLD_HEIGHT/StarNum, 0.25, rand(), 0, 310, 14, 605, 8, 913);
			break;
		case 7:
			StarNum = min(STAR_NUM, 4);
			Star[0].Appear(0*WORLD_WIDTH/StarNum, 0*WORLD_HEIGHT/StarNum, 0.4, rand(), 0, 319, 12, 600, 10, 928);
			Star[1].Appear(1*WORLD_WIDTH/StarNum, 1*WORLD_HEIGHT/StarNum, 0.4, rand(), 4, 337, 8, 626, 9, 914);
			Star[2].Appear(2*WORLD_WIDTH/StarNum, 2*WORLD_HEIGHT/StarNum, 0.4, rand(), 0, 349, 12, 637, 10, 910);
			Star[3].Appear(3*WORLD_WIDTH/StarNum, 3*WORLD_HEIGHT/StarNum, 0.4, rand(), 4, 324, 8, 624, 9, 928);
			break;
		case 8:
			StarNum = min(STAR_NUM, 4);
			Star[0].Appear(0*WORLD_WIDTH/StarNum, 0*WORLD_HEIGHT/StarNum, 0.5, rand(), 9, 335, 12, 608, 15, 917);
			Star[1].Appear(1*WORLD_WIDTH/StarNum, 1*WORLD_HEIGHT/StarNum, 1.0, rand(), 11, 320, 14, 634, 15, 911);
			Star[2].Appear(2*WORLD_WIDTH/StarNum, 2*WORLD_HEIGHT/StarNum, 0.5, rand(), 9, 346, 8, 604, 10, 929);
			Star[3].Appear(3*WORLD_WIDTH/StarNum, 3*WORLD_HEIGHT/StarNum, 1.0, rand(), 11, 326, 12, 636, 10, 923);
			break;
		case 9:
			StarNum = min(STAR_NUM, 4);
			Star[0].Appear(0*WORLD_WIDTH/StarNum, 0*WORLD_HEIGHT/StarNum, 0.4, rand(), 14, 310, 12, 628, 13, 902);
			Star[1].Appear(1*WORLD_WIDTH/StarNum, 1*WORLD_HEIGHT/StarNum, 0.4, rand(), 14, 349, 13, 617, 15, 927);
			Star[2].Appear(2*WORLD_WIDTH/StarNum, 2*WORLD_HEIGHT/StarNum, 0.4, rand(), 14, 310, 12, 624, 13, 908);
			Star[3].Appear(3*WORLD_WIDTH/StarNum, 3*WORLD_HEIGHT/StarNum, 0.4, rand(), 14, 321, 13, 604, 15, 895);
			Star[4].Appear(4*WORLD_WIDTH/StarNum, 4*WORLD_HEIGHT/StarNum, 2.0, rand(), 11, 317, 10, 619, 9, 904);
			break;
		default:
			break;
	}
	
}

bool GameLoop(){

	switch(Clock.GetGameMode()){
	case MODE_END:
		return false;
		break;
	case MODE_TITLE :
		Title() ;
		return true;	break;
	case MODE_CHOICE:
		Choice();
		Awake();
		return true;	break;
	case MODE_GAMEOVER:
		if( GameOver())Awake();
		break;
	case MODE_GAMECLEAR:
		if( GameClear())Awake();
		break;
	}

	if (Clock.GetGameMode() == MODE_END) return false;
	if (!Clock.GetGameMode()==MODE_PLAYING) return true;
	if(!Clock.Main())return false;

	
	//勝敗判定
	for( int i  = 0; i < STAR_NUM; i++){
		if(Star[i].GetVisible())break;
		if(i == STAR_NUM-1) {
			Clock.SetGameMode(MODE_GAMECLEAR);
		}
	}

	if(!Mine.GetVisible()){
		if (!Mine.GetAlive()){
			Clock.SetGameMode(MODE_GAMEOVER);
		}
		return true;
	}

	//自死
	if (CheckHitKey(KEY_INPUT_ESCAPE)) Mine.SetAlive(false);


	//背景描画とスターレーダーの描画
	Stage.Draw(Mine.GetPos());
	
	//星移動と描画と最も近い星位置の判定
	Vector nearest_star;
	nearest_star.Set(WORLD_WIDTH/2, WORLD_HEIGHT/2);
	for( int i  = 0; i < STAR_NUM; i++){
		Star[i].Move();
		Star[i].Draw(Mine.GetPos(), Clock.GetTime());
		nearest_star = Star[i].NearestStar(nearest_star);
	}
	Stage.SetNearestStar(nearest_star);
	
	//敵弾移動と描画
	for( int i  = 0; i < ENEMY_BALL_NUM; i++){
		if(EnemyBall[i].GetAlive()){
			EnemyBall[i].Move(Clock.GetTime());
			EnemyBall[i].Draw(Mine.GetPos());
			
			//敵弾判定（自機）
			EnemyBall[i].JudgeMine(&Mine, Clock.GetTime());
		}
	}
	//敵弾発射
	for( int i  = 0; i < ENEMY_NUM; i++){
		if(Enemy[i].GetAlive()){
			if((Clock.GetTime()-Enemy[i].GetAppearTime())%Enemy[i].GetShootTime()==0){
				for( int j  = 0; j < ENEMY_BALL_NUM; j++){
					if(!EnemyBall[j].GetAlive()){
						if(EnemyBall[j].Appear(&EnemyBallModel[Enemy[i].GetBallType()], &Enemy[i], Mine.GetPos(), Clock.GetTime(), rand()))break;
					}
				}
			}
		}
	}

	//敵移動と描画
	for( int i  = 0; i < ENEMY_NUM; i++){
		Enemy[i].Move(Mine.GetPos(), Star[Enemy[i].GetMomStar()].GetPos(), Clock.GetTime());
		Enemy[i].Draw(Mine.GetPos());
	}
	//敵出現
	for( int i  = 0; i < STAR_NUM; i++){
		if(Star[i].GetAlive()){
			for( int j  = 0; j < 3; j++){
				if(Star[i].EnemyBirthNow(Clock.GetTime(), j)){
					for( int k  = 0; k < ENEMY_NUM; k++){
						if(!Enemy[k].GetAlive()){
							if(Enemy[k].Appear(&EnemyModel[Star[i].EnemyBirthKind[j]], Star[i].GetPos(), Clock.GetTime(), rand(), i))break;
						}
					}
				}
			}
		}
	}


	//自弾移動と描画
	for( int i  = 0; i < MY_BALL_NUM; i++){
		if(MyBall[i].GetAlive()){
			MyBall[i].Move(Clock.GetTime());
			
			//自弾判定（敵）
			for(int j = 0; j < ENEMY_NUM; j++){
				if(Enemy[j].GetAlive()){
					if(MyBall[i].JudgeEnemy(&Enemy[j]))break;
				}
			}
			//自弾判定（星）
			for(int j = 0; j < STAR_NUM; j++){
				if(Star[j].GetAlive()){
					if(MyBall[i].JudgeStar(&Star[j]))break;
				}
			}
			MyBall[i].Draw(Mine.GetPos());
		}
	}

	//自弾発射
	if(Mine.GetAlive() && Clock.GetTime()%Mine.GetShootTime()==0){
		int shotnum = 0;
		for( int i  = 0; i < MY_BALL_NUM; i++){
			if(!MyBall[i].GetAlive()){
				if(MyBall[i].Shoot(&Mine, shotnum, Clock.GetTime()))shotnum++;
				if(shotnum==4)break;
			}
		}
	}

	//自機移動と描画
	Mine.Move();
	Mine.Draw(Clock.GetTime());

	//残存Star数表示
	int alive_starnum=0;
		for (int i=0; i<STAR_NUM; i++){	if (Star[i].GetAlive()) alive_starnum++;}
	Stage.SetAliveStarNum(alive_starnum);
	Stage.DrawStarCount();

	//残存Enemy数表示
	int alive_enemynum=0;
		for (int i=0; i<ENEMY_NUM; i++){	if (Enemy[i].GetAlive()) alive_enemynum++;}
	//Stage.DrawEnemyCount(alive_enemynum);

	
	//文字表示
	if (abs(Mine.GetPos().x)<10 && abs(WORLD_HEIGHT/2-Mine.GetPos().y)<10){
		Stage.DrawCaption(true);
	}else{
		Stage.DrawCaption(false);
	}

	return true;
}


bool Opening(){
	Clock.SetGameMode(MODE_OPENING);
	Clock.SetNowTime();
	Beginning.Awake(Clock.GetTime());

	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){	
		if(!Clock.Main())break;
		if(Beginning.Main(Clock.GetTime(), true)==-1){
			Clock.SetGameMode(MODE_TITLE);
			break;
		}
	}
	return true;
}


bool Title(){
	Clock.SetNowTime();
	Beginning.Awake(Clock.GetTime());
	
	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){	
		if(!Clock.Main())break;
		if( Beginning.Main(Clock.GetTime(), false) == -2){
			Clock.SetGameMode(MODE_CHOICE);
			break;
		}
	}
	return false;
}

bool Choice(){
	bool PressedL = true;
	bool PressedR = true;
	bool PressedD = true;
	bool PressedU = true;
	bool PressedRETURN = true;

	Clock.SetNowTime();
	//Stage.SetStageNumMin();

	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){
		if(!Clock.Main())break;
		
		DrawString( WINDOW_WIDTH/2 - 90, WINDOW_HEIGHT-100, "Press ENTER to START", WHITE); 
		DrawFormatString(WINDOW_WIDTH/2 - 60, 100, WHITE,"←　STAGE %d　→", Stage.GetStageNum()) ;
		DrawCenterString(WINDOW_WIDTH/2, 180, "↑", WHITE);
		if (Stage.GetDifficulity()){
			DrawCenterString(WINDOW_WIDTH/2, 210, "HARD", WHITE);
		}else{
			DrawCenterString(WINDOW_WIDTH/2, 210, "EASY", WHITE);		
		}
		DrawCenterString(WINDOW_WIDTH/2, 240, "↓", WHITE);

		if((CheckHitKey(KEY_INPUT_RETURN)||(!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_1)==0))||CheckHitKey(KEY_INPUT_SPACE)) && !PressedRETURN){
			Clock.SetGameMode(MODE_PLAYING);
			break;
		}else if((!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_RIGHT)==0)) && !PressedR){
			Stage.ChangeStageNum(true);
			PressedR = true;
		}else if((!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_LEFT)==0)) && !PressedL){
			Stage.ChangeStageNum(false);
			PressedL = true;
		}else if((!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_DOWN)==0)) && !PressedD){
			Stage.ChangeDifficulity();
			PressedD = true;
		}else if((!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_UP)==0)) && !PressedU){
			Stage.ChangeDifficulity();
			PressedU = true;
		}

		if(!(CheckHitKey(KEY_INPUT_RETURN)||(!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_1)==0))||CheckHitKey(KEY_INPUT_SPACE))) PressedRETURN = false;
		if(!(!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_RIGHT)==0))) PressedR = false;
		if(!(!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_LEFT)==0))) PressedL = false;
		if(!(!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_UP)==0))) PressedU = false;
		if(!(!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_DOWN)==0))) PressedD = false;


	}
	return true;
}

bool GameClear(){
	//Clock.SetNowTime();

	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){
			
		if(!Clock.Main())return false;

		SetFontSize(GetFontSize()+5);
		DrawFormatString(WINDOW_WIDTH/2 - 80, 50, WHITE, "Stage%d Clear!", Stage.GetStageNum());
		SetFontSize(GetFontSize()-5);


		if (Stage.LastStage()){
			
			DrawCenterString(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, "Congratulations!", WHITE);
			DrawCenterString(WINDOW_WIDTH/2, WINDOW_HEIGHT-70, "Press BACK SPACE to BACK to TITLE", WHITE);
			
			if((CheckHitKey(KEY_INPUT_BACK)||(!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_2)==0)))){
				Clock.SetGameMode(MODE_TITLE);
				return false;
			}

		}else{
			
			DrawCenterString(WINDOW_WIDTH/2,WINDOW_HEIGHT-100, "Press ENTER to GO NEXT", WHITE);
			DrawCenterString(WINDOW_WIDTH/2, WINDOW_HEIGHT-70, "Press BACK SPACE to BACK to TITLE", WHITE);
			if((CheckHitKey(KEY_INPUT_RETURN)||(!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_1)==0))||CheckHitKey(KEY_INPUT_SPACE))){
				Clock.SetGameMode(MODE_PLAYING);
				Stage.SetDifficulity();
				Stage.ChangeStageNum(true);
				return true;
			}else if((CheckHitKey(KEY_INPUT_BACK)||(!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_2)==0)))){
				Clock.SetGameMode(MODE_TITLE);
				return false;
			}
		}
	}
	return false;
}

bool GameOver(){
	//Clock.SetNowTime();

	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0  ){
		
		if(!Clock.Main())return false;

		SetFontSize(GetFontSize()+5);
		DrawFormatString(WINDOW_WIDTH/2-90, 50, WHITE, "Gameover Stage%d", Stage.GetStageNum());
		SetFontSize(GetFontSize()-5);

		DrawString(WINDOW_WIDTH/2-130, WINDOW_HEIGHT-100, "Press ENTER to RESTART", WHITE);
		DrawString(WINDOW_WIDTH/2-130, WINDOW_HEIGHT-70, "Press BACK SPACE to BACK to TITLE", WHITE);
		if((CheckHitKey(KEY_INPUT_RETURN)||(!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_1)==0))||CheckHitKey(KEY_INPUT_SPACE))){
			Clock.SetGameMode(MODE_PLAYING);
			return true;
		}else if((CheckHitKey(KEY_INPUT_BACK)||(!((GetJoypadInputState( DX_INPUT_KEY_PAD1 )&PAD_INPUT_2)==0)))){
			Clock.SetGameMode(MODE_TITLE);
			return false;
		}
	}
	return false;
}