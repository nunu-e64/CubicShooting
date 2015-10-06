#include "DxLib.h"
#include "Define.h"
#include "Ranking.h"
#include "math.h"


CRanking::CRanking(){
	
	for (int i=0; i<30; i++){
		for (int j=0; j<3; j++){
			HighScore[j][i]=0;	
			YetResister[j][i] = false;
		}
	}
}

void CRanking::Init(){

	char String[256];
	FileHandle = FileRead_open( "CS_pic/save.csd" ) ;
    if (FileHandle==0) printfDx("ER\n") ;

	for (int i=0; i<30; i++){
		for (int j=0; j<3; j++){
	//	    FileRead_gets(String, 256, FileHandle ) ;
			 //   int a,b,c;  
    //float d;  
    //sscanf(str.c_str(),g%d,%d,%d,%fh,&a,&b,&c,&d);  

			if ( FileRead_scanf(FileHandle , "%d" , &HighScore[i][j])==-1) printfDx("ER\n") ;
/*

			HighScore[j][i] = (int)String;
		    
			FileRead_gets(String, 256, FileHandle ) ;
			YetResister[j][i] = (bool)String;
*/
		    DrawFormatString(j*100, i*20, GetColor(50,j*50,j*50 )," %d ", HighScore[i][j] ) ;
		}
	}

    // ƒtƒ@ƒCƒ‹‚ð•Â‚¶‚é
    FileRead_close( FileHandle ) ;


	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && !CheckHitKeyAll()){
		WaitKey() ;
	}

	WaitKey();
}
	