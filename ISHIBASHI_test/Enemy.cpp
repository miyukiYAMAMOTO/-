//当たり判定
//ｴﾈﾐｰとｼｮｯﾄ
//ｴﾈﾐｰとﾌﾟﾚｲﾔｰ


#include "DxLib.h"
#include "test.h"
#include "Stage.h"
#include "Enemy.h"
#include "Item.h"
#include "Player.h"
#include "effect.h"

//-----外部変数宣言
//ﾓﾌﾞ関連
CHARACTER enemyMob[ENEMY_MAX];				
CHARACTER enemyMobMaster[ENEMY_M_MAX];
int enemyImage[ENEMY_M_MAX][16];

//ﾎﾞｽ関連

//-----ｴﾈﾐｰ情報の初期化
void EnemySystemInit(void)
{
	//-----変数の初期化
	//狐
	enemyMobMaster[ENEMY_I_MOB].charType = ENEMY_I_MOB;			//	ｴﾈﾐｰの種類	：	ｷﾂﾈ
	enemyMobMaster[ENEMY_I_MOB].moveSpeed = 2;					//	ｷﾂﾈの移動量
	enemyMobMaster[ENEMY_I_MOB].lifeMax = 3;					//	ｷﾂﾈの体力最大値
	enemyMobMaster[ENEMY_I_MOB].point = 1;						//	ｷﾂﾈの得点
	//一反木綿
	enemyMobMaster[ENEMY_Y_MOB].charType = ENEMY_Y_MOB;			//	ｴﾈﾐｰの種類	：	一反木綿
	enemyMobMaster[ENEMY_Y_MOB].moveSpeed = 2;					//	一反木綿の移動量
	enemyMobMaster[ENEMY_Y_MOB].lifeMax = 3;					//	一反木綿の体力最大値
	enemyMobMaster[ENEMY_Y_MOB].point = 1;						//	一反木綿の得点
	//海坊主
	enemyMobMaster[ENEMY_A_MOB].charType = ENEMY_A_MOB;			//	ｴﾈﾐｰの種類	：	海坊主						
	enemyMobMaster[ENEMY_A_MOB].moveSpeed = 2;					//	海坊主の移動量
	enemyMobMaster[ENEMY_A_MOB].lifeMax = 3;					//	海坊主の体力最大値
	enemyMobMaster[ENEMY_A_MOB].point = 1;						//	海坊主の得点
	//ﾓﾌﾞまとめて処理
	for (int type = 0; type < ENEMY_M_MAX; type++)
	{
		enemyMobMaster[type].moveDir = DIR_DOWN;
		enemyMobMaster[type].pos = { 150,150 };
		enemyMobMaster[type].size = { 32,32 };
		enemyMobMaster[type].offsetSize = { enemyMobMaster[type].size.x / 2
			, enemyMobMaster[type].size.y / 2 };
		enemyMobMaster[type].life = enemyMobMaster[type].lifeMax;
		enemyMobMaster[type].animCnt = 0;
	}

	//-----ｸﾞﾗﾌｨｯｸの登録
	//石橋担当MOB
	LoadDivGraph("aitem/妖狐.png", 16, 4, 4
		, enemyMobMaster[ENEMY_I_MOB].size.x
		, enemyMobMaster[ENEMY_I_MOB].size.y
		, enemyImage[ENEMY_I_MOB]);
	//山本担当MOB
	LoadDivGraph("aitem/wind_mob_enemy1.png", 16, 4, 4
		, enemyMobMaster[ENEMY_Y_MOB].size.x
		, enemyMobMaster[ENEMY_Y_MOB].size.y
		, enemyImage[ENEMY_Y_MOB]);
	//荒木担当MOB
	LoadDivGraph("aitem/umi0.png", 16, 4, 4
		, enemyMobMaster[ENEMY_A_MOB].size.x
		, enemyMobMaster[ENEMY_A_MOB].size.y
		, enemyImage[ENEMY_A_MOB]);

}

void EnemyGameInit(void)
{
	for (int ene = 0; ene < ENEMY_MAX; ene++)
	{
		enemyMob[ene] = enemyMobMaster[GetRand(ENEMY_M_MAX - 1)];
		if (IsPass(enemyMob[ene].pos))
		{
			enemyMob[ene].pos.x = GetRand(20 * CHIP_SIZE_X - 1);
			enemyMob[ene].pos.y = GetRand(25 * CHIP_SIZE_X - 1);
		}
	}
}

void EnemyControl(XY pPos)
{
	//敵の種類毎に動作を変更する
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		CHARACTER enemyCopy = enemyMob[en];

		//生きているｴﾈﾐｰのみ表示
		if (enemyMob[en].life > 0)
		{
			/*switch (enemyMob[en].charType)
			{
			case ENEMY_I_MOB:
				if (!MoveEnemyX(&enemyCopy, pPos)) MoveEnemyY(&enemyCopy, pPos);
				break;

			case ENEMY_Y_MOB:
				if (!MoveEnemyY(&enemyCopy, pPos)) MoveEnemyX(&enemyCopy, pPos);
				break;

			case ENEMY_A_MOB:
				MoveEnemyXY(&enemyCopy, pPos);
				break;

			default:
				break;
			}*/

			enemyMob[en].moveDir = enemyCopy.moveDir;
			if (IsPass(enemyCopy.pos))
			{
				enemyMob[en].pos = enemyCopy.pos;
			}
			//死んでいる為、敵を生成
			else
			{
				enemyMob[en].life = enemyMob[en].lifeMax;
				enemyMob[en].pos = { 50,50 };
			}

		}
	}

}

void EnemyGameDraw(void)
{
	for (int ene = 0; ene < ENEMY_MAX; ene++)
	{

		if (enemyMob[ene].life > 0)
		{
			enemyMob[ene].animCnt++;

			DrawGraph(enemyMob[ene].pos.x - enemyMob[ene].offsetSize.x + mapPos.x
				, enemyMob[ene].pos.y - enemyMob[ene].offsetSize.y + mapPos.y
				, enemyImage[enemyMob[ene].charType][enemyMob[ene].moveDir * 4 + ((enemyMob[ene].animCnt / 40) % 4)]
				, true);


			DrawBox(enemyMob[ene].pos.x - enemyMob[ene].offsetSize.x + mapPos.x
				, enemyMob[ene].pos.y - enemyMob[ene].offsetSize.y + mapPos.y
				, enemyMob[ene].pos.x - enemyMob[ene].offsetSize.x + enemyMob[ene].size.x + mapPos.x
				, enemyMob[ene].pos.y - enemyMob[ene].offsetSize.y + enemyMob[ene].size.y + mapPos.y
				, 0xFF00FF, false);

			
		}
	}


}


int MoveEnemyX(CHARACTER* enemy, XY player1Pos)
{
	//-----enemy操作
	int diff = player1Pos.x - (*enemy).pos.x;
	int enemySpeed = (*enemy).moveSpeed;
	//X軸
	if (diff >= 0)
	{
		//ｽﾋﾟｰﾄﾞの調整をする
		enemySpeed = diff < enemySpeed ? diff : enemySpeed;

		//X座標が違う場合は敵を移動させる
		(*enemy).pos.x += enemySpeed;
		(*enemy).moveDir = DIR_RIGHT;
	}
	else
	{
		enemySpeed = -diff < enemySpeed ? -diff : enemySpeed;

		(*enemy).pos.x -= enemySpeed;
		(*enemy).moveDir = DIR_LEFT;
	}


	return enemySpeed;

}

//Y座標に動く
int MoveEnemyY(CHARACTER* enemy, XY player1Pos)
{
	//-----enemy操作
	int diff = player1Pos.y - (*enemy).pos.y;
	int enemySpeed = (*enemy).moveSpeed;
	//Y軸
	if (diff >= 0)
	{
		//ｽﾋﾟｰﾄﾞの調整をする
		enemySpeed = diff < enemySpeed ? diff : enemySpeed;

		//Y座標が違う場合は敵を移動させる
		(*enemy).pos.y += enemySpeed;
		(*enemy).moveDir = DIR_DOWN;
	}
	else
	{
		enemySpeed = -diff < enemySpeed ? -diff : enemySpeed;
		//Y座標が違う場合は敵を移動させる
		(*enemy).pos.y -= enemySpeed;
		(*enemy).moveDir = DIR_UP;
	}

	return enemySpeed;

}
//斜めに動く
int MoveEnemyXY(CHARACTER* enemy, XY player1Pos)		// true : 動く、 false : 動かさない
{

	int diffX = player1Pos.x - (*enemy).pos.x;
	int diffY = player1Pos.y - (*enemy).pos.y;
	int enemySpeed = (*enemy).moveSpeed;

	if (abs(diffX) <= abs(diffY))
	{
		//ｽﾋﾟｰﾄﾞの調整をする
		enemySpeed = MoveEnemyY(enemy, player1Pos);
	}
	else
	{
		enemySpeed = MoveEnemyX(enemy, player1Pos);
	}

	return enemySpeed;
}



//-----弾と敵の当たり判定　(true : あたり, false : はずれ)
bool EnemyHitCheck(XY sPos, int sSize)
{
	auto randam = rand() % 100;

	//全ての敵に当たり判定を実施する
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		if (enemyMob[en].life > 0)
		{
			if (((enemyMob[en].pos.x - enemyMob[en].size.x / 2) < (sPos.x + sSize / 2))
				&& ((enemyMob[en].pos.x + enemyMob[en].size.x / 2) > (sPos.x - sSize / 2))
				&& ((enemyMob[en].pos.y - enemyMob[en].size.y / 2) < (sPos.y + sSize / 2))
				&& ((enemyMob[en].pos.y + enemyMob[en].size.y / 2) > (sPos.y - sSize / 2)))
			{

				//当たった時、ｴﾈﾐｰの体力を減らす
				enemyMob[en].life--;

				if (enemyMob[en].life <= 0)
				{
					switch (enemyMob[en].charType)
					{
					case ENEMY_I_MOB:
						DamageEffect(enemyMob[en].pos, MAGIC_TYPE_FIRE);
						if (randam > 5)
						{
							ItemDrop(enemyMob[en].pos, MAGIC_TYPE_FIRE);
						}
						else if (randam <= 5)
						{
							ItemDrop(enemyMob[en].pos, MAGIC_TYPE_HEAL);
						}
						DrawFormatString(0, 400, 0xffffff, "%d", randam);
						break;

					case ENEMY_A_MOB:
						DamageEffect(enemyMob[en].pos, MAGIC_TYPE_WATER);
						if (randam > 5)
						{
							ItemDrop(enemyMob[en].pos, MAGIC_TYPE_WATER);
						}
						else if (randam <= 5)
						{
							ItemDrop(enemyMob[en].pos, MAGIC_TYPE_HEAL);
						}
						DrawFormatString(0, 400, 0xffffff, "%d", randam);
						break;

					case ENEMY_Y_MOB:
						DamageEffect(enemyMob[en].pos, MAGIC_TYPE_WIND);
						if (randam > 5)
						{
							ItemDrop(enemyMob[en].pos, MAGIC_TYPE_WIND);
						}
						else if (randam <= 5)
						{
							ItemDrop(enemyMob[en].pos, MAGIC_TYPE_HEAL);
						}
						DrawFormatString(0, 400, 0xffffff, "%d", randam);
						break;

					case ENEMY_M_MAX:
						break;

					default:
						break;
					}
				}
				
				return true;
			}
		}
	}
	//弾が外れた時
	return false;
}
//当たり判定
bool PlayerHitCheck(XY sPos, int sSize)
{
	//全ての敵に当たり判定を実施する
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		if (enemyMob[en].life > 0)
		{
			if (((enemyMob[en].pos.x - enemyMob[en].size.x / 2) < (sPos.x + sSize / 2))
				&& ((enemyMob[en].pos.x + enemyMob[en].size.x / 2) > (sPos.x - sSize / 2))
				&& ((enemyMob[en].pos.y - enemyMob[en].size.y / 2) < (sPos.y + sSize / 2))
				&& ((enemyMob[en].pos.y + enemyMob[en].size.y / 2) > (sPos.y - sSize / 2)))
			{

				//当たった
				return true;
			}
		}
	}
	//外れた時
	return false;
}

