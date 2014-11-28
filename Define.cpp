#include "DxLib.h"
#include "Define.h"

void DrawCenterString(int x, int y, const TCHAR *String, int color){
	
	DrawString(x-GetDrawStringWidth(String, strlen(String))/2, y, String, color); 

}
