//#pragma once

//-----定数定義
#define BOX_X		15
#define BOX_Y		SCREEN_SIZE_Y - 220
#define BOX_END_X	SCREEN_SIZE_X - 15
#define BOX_END_Y	SCREEN_SIZE_Y - 5


//-----関数ﾌﾟﾛﾄﾀｲﾌﾟ宣言
void BattleSystemInit(void);		//　ﾎﾞｽ戦情報の初期化	
void BattleGameInit(void);			//						
void BattleControl(void);			//	ﾎﾞｽ戦の操作
void BattleScene(void);				//	ﾎﾞｽ戦のｼｰﾝ
void BattleGameDraw(void);			//　ﾎﾞｽ戦の描画処理

