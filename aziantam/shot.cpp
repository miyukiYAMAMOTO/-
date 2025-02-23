#include <DxLib.h>
#include "main.h"
#include "stage.h"
#include "item.h"
#include "shot.h"



//-----外部変数定義
CHARACTER shotMaster[MAGIC_TYPE_MAX];
CHARACTER shot[SHOT_MAX];
int shotImage[MAGIC_TYPE_MAX][SHOT_ANI];


void ShotSystemInit(void)
{
	//-----変数の初期化
	shotMaster[MAGIC_TYPE_FIRE].charType = MAGIC_TYPE_FIRE;
	shotMaster[MAGIC_TYPE_WATER].charType = MAGIC_TYPE_WATER;
	shotMaster[MAGIC_TYPE_WIND].charType = MAGIC_TYPE_WIND;
	shotMaster[MAGIC_TYPE_HEAL].charType = MAGIC_TYPE_HEAL;
	//まとめて処理
	for (int type = 0; type < MAGIC_TYPE_MAX; type++)
	{
		shotMaster[type].moveDir = DIR_DOWN;
		shotMaster[type].size = { 40,40 };
		shotMaster[type].offsetSize = { shotMaster[type].size.x / 2,shotMaster[type].size.y / 2 };
		shotMaster[type].moveSpeed = 4;
		shotMaster[type].pos = { 0,0 };
		shotMaster[type].lifeMax = SHOT_LIFE_MAX;
		shotMaster[type].animCnt = 0;

		//代入
		for (int sh = 0; sh < SHOT_MAX; sh++)
		{
			shot[sh] = shotMaster[type];
			//shot[sh].pos = { 0,0 };
			shot[sh].life = 0;
			//shot[sh].animCnt = 0;
		}
	}

	//------ｸﾞﾗﾌｨｯｸの登録
	//火
	LoadDivGraph("item/fire_soft.png", SHOT_ANI, 8, 8
		, shot[MAGIC_TYPE_FIRE].size.x
		, shot[MAGIC_TYPE_FIRE].size.y
		, shotImage[MAGIC_TYPE_FIRE]);
	//水
	LoadDivGraph("item/water_soft.png", SHOT_ANI, 8, 8
		, shot[MAGIC_TYPE_WATER].size.x
		, shot[MAGIC_TYPE_WATER].size.y
		, shotImage[MAGIC_TYPE_WATER]);
	//風
	LoadDivGraph("item/wind_soft.png", SHOT_ANI, 8, 8
		, shot[MAGIC_TYPE_WIND].size.x
		, shot[MAGIC_TYPE_WIND].size.y
		, shotImage[MAGIC_TYPE_WIND]);
	//回復
	LoadDivGraph("item/life.png", SHOT_ANI, 8, 8
		, shot[MAGIC_TYPE_HEAL].size.x
		, shot[MAGIC_TYPE_HEAL].size.y
		, shotImage[MAGIC_TYPE_HEAL]);
}

void ShotGameInit()
{
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		shot[sh].pos = { 0,0 };
		shot[sh].life = 0;									//	弾の体力
	}
}


void ShotControl(XY pPos, int speed)
{
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		shot[sh].animCnt++;
		//撃っている弾を探す
		if (shot[sh].life > 0)
		{
			//弾を移動させる(火、水、風
			if (shot[sh].moveDir == DIR_RIGHT) shot[sh].pos.x += shot[sh].moveSpeed;
			if (shot[sh].moveDir == DIR_LEFT) shot[sh].pos.x -= shot[sh].moveSpeed;
			if (shot[sh].moveDir == DIR_DOWN) shot[sh].pos.y += shot[sh].moveSpeed;
			if (shot[sh].moveDir == DIR_UP) shot[sh].pos.y -= shot[sh].moveSpeed;
			//プレイヤーに重ねる(回復
			if (shot[sh].charType == MAGIC_TYPE_HEAL)
			{
				if (shot[sh].moveDir == DIR_RIGHT)
				{
					shot[sh].pos.x = pPos.x;
					shot[sh].moveSpeed = speed;
				}
				if (shot[sh].moveDir == DIR_LEFT)
				{
					shot[sh].pos.x = pPos.x;
					shot[sh].moveSpeed = speed;
				}
				if (shot[sh].moveDir == DIR_DOWN)
				{
					shot[sh].pos.y = pPos.y;
					shot[sh].moveSpeed = speed;
				}
				if (shot[sh].moveDir == DIR_UP)
				{
					shot[sh].pos.y = pPos.y;
					shot[sh].moveSpeed = speed;
				}
			}

			//寿命を減らす(射程距離)
			shot[sh].life--;
			if (shot[sh].animCnt > SHOT_ANI)
			{
				shot[sh].animCnt = 0;
			}

		}
	}
}


//-----弾描画処理
void ShotGameDraw(void)
{
	//-----描画
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		if (shot[sh].life > 0)
		{
			shot[sh].animCnt++;
			
			DrawGraph(shot[sh].pos.x - shot[sh].offsetSize.x + mapPos.x
				, shot[sh].pos.y - shot[sh].offsetSize.y + mapPos.y
				, shotImage[shot[sh].charType][shot[sh].animCnt]
				, true);

			//DrawBox(shot[sh].pos.x - shot[sh].offsetSize.x + mapPos.x
			//	, shot[sh].pos.y - shot[sh].offsetSize.y + mapPos.y
			//	, shot[sh].pos.x - shot[sh].offsetSize.x + shot[sh].size.x + mapPos.x
			//	, shot[sh].pos.y - shot[sh].offsetSize.y + shot[sh].size.y + mapPos.y
			//	, 0xFFFFFF, false);
		}
	}
}



//-----弾を生成する
void CreateShot(XY pPos, DIR pDir, MAGIC_TYPE ptype)
{
	//撃っていない弾があれば一発弾を作って発射する
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		//撃っていない弾を探す
		if (shot[sh].life <= 0)
		{
			if (ItemMobControl(ptype))
			{
				//撃っていない弾を発射
				shot[sh].charType = ptype;
				shot[sh].pos = { pPos.x, pPos.y };		//弾の場所
				shot[sh].moveDir = pDir;				//弾の進むべき場所
				shot[sh].life = shot[sh].lifeMax;		//弾を撃ったことにする
			}
		}
		break;
	}
}


//-----弾を消滅させる
void DeleteShot(int index)
{
	shot[index].life = 0;
}
