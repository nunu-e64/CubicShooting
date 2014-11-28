#pragma once
#include "DxLib.h"
#include "Define.h"



int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);	//ウィンドウサイズ変更
	ChangeWindowMode( TRUE ) ; // ウインドウモードに変更
	SetDrawScreen( DX_SCREEN_BACK ); //描画先を画面裏に
	SetWindowText(GAME_TITLE);

	if( DxLib_Init() == -1 ) return -1 ; // ＤＸライブラリ初期化
		
		SetTransColor( 255 , 0 , 255 ) ;	//透過色指定（マゼンダ）
		//SetMouseDispFlag( false );	//マウスカーソルを表示しない
			
		GameAwake();
		Opening();

        while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0){
			
			if(!GameLoop()) break;

        }
        
        DxLib_End(); // DXライブラリ終了処理
        return 0;
}  
