#pragma once
#include "DxLib.h"
#include "Define.h"



int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);	//�E�B���h�E�T�C�Y�ύX
	ChangeWindowMode( TRUE ) ; // �E�C���h�E���[�h�ɕύX
	SetDrawScreen( DX_SCREEN_BACK ); //�`������ʗ���
	SetWindowText(GAME_TITLE);

	if( DxLib_Init() == -1 ) return -1 ; // �c�w���C�u����������
		
		SetTransColor( 255 , 0 , 255 ) ;	//���ߐF�w��i�}�[���_�j
		//SetMouseDispFlag( false );	//�}�E�X�J�[�\����\�����Ȃ�
			
		GameAwake();
		Opening();

        while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0){
			
			if(!GameLoop()) break;

        }
        
        DxLib_End(); // DX���C�u�����I������
        return 0;
}  
