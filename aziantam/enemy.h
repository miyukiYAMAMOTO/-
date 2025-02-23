

//-----定数定義
#define ENEMY	 20  
#define ENEMY_MAX ENEMY * 3		//	敵の数

#define DAMAGE_NORMAL	2		//同属性ﾀﾞﾒｰｼﾞ量
#define DAMAGE_HIGH		3		//有利属性ﾀﾞﾒｰｼﾞ量
#define DAMAGE_LOW		1		//不利属性ﾀﾞﾒｰｼﾞ量


//-----列挙型
//モブ
enum ENEMY_MOB
{
	ENEMY_I_MOB,	//石橋担当
	ENEMY_Y_MOB,	//山本担当
	ENEMY_A_MOB,	//荒木担当
	ENEMY_M_MAX
};

//-----関数ﾌﾟﾛﾄﾀｲﾌﾟ宣言
//基本処理
void EnemySystemInit(void);					//ｴﾈﾐｰ情報の初期化
void EnemyReGameInit(void);
void EnemyGameInit(STAGE_ID stageID);
void EnemyControl(XY pPos);					//ｴﾈﾐｰの操作
void EnemyGameDraw(void);					//ｴﾈﾐｰの描画処理
int MoveEnemyX(CHARACTER* enemy, XY playerPos); //自機のX座標に調節するように動かす　戻り値：移動した量
int MoveEnemyY(CHARACTER* enemy, XY playerPos); //自機のY座標に調節するように動かす　戻り値：移動した量
int MoveEnemyXY(CHARACTER* enemy, XY playerPos); //自機のXとYの遠いほうから座標を調節するように動かす　戻り値：移動した量

//当たり判定
bool EnemyHitCheck(XY sPos, int sSize, CHARACTER* shot);		//ｴﾈﾐｰと弾の当たり判定
bool PlayerHitCheck(XY sPos, int sSize);

bool SetEnemyMoment();				//
bool EFlagInit(void);						//敵がステージごとで全滅したか判断用フラグ専用の初期化



extern bool eFlag_mob;
extern bool eFlag_oni;
extern bool eFlag_kappa;