#pragma once
//=======================================================
//プレイヤーキャラ設定
//=======================================================
//フィールドIndex
enum FIELD
{
	FD_TestRoom,
	FD_Soto,
	FD_Lobby,
	FD_LobbyRestRoom,
	FD_Staff_Room,
	FD_Dining_Room,
	FD_Bath_Pass,
	FD_Bath_Datui_Man,
	FD_Bath_Datui_Woman,
	FD_Bath_Room_Man,
	FD_Bath_Room_Woman,
	FD_Guest_Room,
	FD_Guest_Bath,
	FD_Rest_Men,
	FD_Rest_Women,
	FD_F3,
	FD_Roof_Kai,
	FD_Roof_Top,
	FD_201,
	FD_201_Bath,
	FD_202,
	FD_203,
	FD_Sandou,
	FD_Secret,
};
//タイムライン
enum TIMELINE
{
	TL_INTRO_START,
	TL_INTRO_1,
	TL_INTRO_2,
	TL_INTRO_END,
	TL_DRUG_START,
	TL_DRUG_LIGHT,
	TL_DRUG_GUNGUN,
	TL_GUEST_ENEMY_START,
	TL_GUEST_ENEMY_END,
	TL_ROOF_ENEMY,
	TL_ROOF_DUCT,
	TL_201_OPEN,
	TL_BOUKA_OPEN,
	TL_ENEMY_WALK,	
	TL_TIME5,
	TL_DATUI_ENEMY_END,
	TL_WHITEBORD,
	TL_203_OPEN,
	TL_203_EXIT,
	TL_GOOD_BYE,
	TL_READ_TIPS,
	TL_FISH_WALK1,
	TL_FISH_WALK2,
	TL_SERCRET_DOOR,
	TL_ENDING,
};
//仕掛けフラグ
class TrickFlag
{
public:
	int chairMove;
	int dinigDoor;
	int darts;
	int dartsbord;
	TrickFlag();
	VOID Init();

};
//敵のフラグ
class EnemyFlag
{
public:
	int Level;
	int HP;
	int mode;
	float rot;
	D3DXVECTOR3 pos;
	EnemyFlag();
	VOID Init();
};
//フラグマネージャ
class FlagManager
{
private:	
	
public:
	//プレイ時間の一時保存
	DWORD NTime;
	//敵フラグ
	EnemyFlag enemy;
	//仕掛けのフラグ
	TrickFlag trick;
	//アイテム
	BOOL ItemGet[ITEM_MAX];
	BOOL ItemGeted[ITEM_MAX];
	//プレイ時間
	DWORD PlayTime;
	//セーブした時刻
	tm Local;
	//キャラの向き
	float RotY;
	//フィールドタイプ
	FIELD FldType;
	//キャラの位置
	D3DXVECTOR3 Pos;
	//どこのドアから入ったか
	size_t Door;
	//イベントの進行フラグ
	TIMELINE EventFlag;
	

	FlagManager();
	VOID Init();
	VOID StaticPos(D3DXVECTOR3*,float);
	VOID SaveTime();
	VOID LoadTime();
	VOID ShowData(TCHAR*,int);
	//アイテム
	//アイテムを取得
	VOID iGet(ITEM);
	//捨てる
	VOID iRelease(ITEM);
	//除外(過去に持っていたフラグも破棄する)
	VOID iRemove(ITEM);
	//現在持っているかのフラグ
	BOOL iGetFlag(ITEM);
	//過去に持っていたかのフラグ
	BOOL iGetedFlag(ITEM);



};
//フラグセーブ
class GameSave
{
private:	
	
public:
	enum{MAX_SAVE = 3};
	GameSave();
	BOOL Save(FlagManager*,int);
	BOOL Load(FlagManager*,int);
};