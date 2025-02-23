//月夜
//stage.h
//2020.05.20

//#pragma  once

//定数
//ﾏｯﾌﾟﾁｯﾌﾟ画像
#define MAP_X 40		//デフォルト
#define MAP_Y 40
#define MAP_START_Y 40	//はじまりの村
#define MAP_START_X 40
#define MAP_M_X 40		//モブ
#define MAP_M_Y 40
#define MAPI_X 40		//石橋担当
#define MAPI_Y 40
#define MAP_ONI2_X		25
#define MAP_ONI2_Y		25

#define MAPA_X 40		//荒木担当
#define MAPA_Y 40
#define MAP_CHIP_X 9
#define MAP_CHIP_Y 9
#define CHIP_SIZE_X 32
#define CHIP_SIZE_Y 32



//ｲﾍﾞﾝﾄID
enum STAGE_ID {
	STAGE_ID_START,
	STAGE_ID_MOB,
	STAGE_ID_ONI,
	STAGE_ID_ONI2,
	STAGE_ID_KAPPA,
	STAGE_ID_MAX
};

//ｲﾍﾞﾝﾄ情報
enum EVENT_ID {
	EVENT_ID_NON,
	EVENT_ID_ZAKO,
	EVENT_ID_KAPPA,
	EVENT_ID_KAIDAN,
	EVENT_ID_KAIDAN2,
	EVENT_ID_DOKU,
	EVENT_ID_DOKUTU,
	EVENT_ID_DAMAGE,		//ﾀﾞﾒｰｼﾞ
	EVENT_ID_STOP,			//止まる
	EVENT_ID_SPEEDDOWN,		//動きが遅くなる
	EVENT_ID_MAX
};

//extern宣言
extern XY mapPos;
extern XY mapSize;
extern STAGE_ID stageID;		//ｽﾃｰｼﾞID
extern int map[MAP_Y][MAP_X];
extern XY gatePos[MAGIC_TYPE_MAX -1];


//ﾌﾟﾛﾄﾀｲﾌﾟ宣言
void StageSystemInit(void);					//ｽﾃｰｼﾞ情報の初期化
void StageGameInit(void);					//ｽﾃｰｼﾞ情報のｹﾞｰﾑ初期化
void StageGameDraw(void);					//ｹﾞｰﾑ画面の表示処理

XY Pos2Index(XY pos);						//ﾋﾟｸｾﾙ座標系ｶﾗﾏｯﾌﾟ配列系ﾆ変換する

bool IsPass(XY pos);						//指定した座標が通過可能かを返す true:通過できる

EVENT_ID GetEvent(XY pos);					//指定した座標が特別にｲﾍﾞﾝﾄを起こすかを確認する 戻り値:ｲﾍﾞﾝﾄID

void SetMapData(STAGE_ID stageID);			//ｽﾃｰｼﾞﾃﾞｰﾀをﾏｯﾌﾟ配列ﾆｺﾋﾟｰする
void MapRange();

STAGE_ID GetMapDate(void);