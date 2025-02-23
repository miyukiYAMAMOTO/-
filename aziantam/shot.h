//#pragma once

//-----定数定義
#define SHOT_ANI		46		//弾のｱﾆﾒｰｼｮﾝ数
#define SHOT_LIFE_MAX	46		//弾の体力
#define SHOT_MAX		20		//弾の総数


//-----関数ﾌﾟﾛﾄﾀｲﾌﾟ宣言
void ShotSystemInit(void);									//弾情報の初期化
void ShotGameInit(void);
void ShotControl(XY pPos, int speed);									//弾の操作
void ShotGameDraw(void);										//弾の描画処理
void CreateShot(XY pPos, DIR pDir, MAGIC_TYPE ptype);		//弾を生成する
void DeleteShot(int index);									//弾を消滅させる

//-----ｸﾞﾛｰﾊﾞﾙ化
extern CHARACTER shot[SHOT_MAX];