#pragma once
//=======================================================
//パーソナルデータ
//=======================================================
class Personal
{
private:
	//照準
	CObjFVF sight;
	//ショットのトリガ
	BOOL TrgRelease;
	//キャンセルカウント用
	int CanselCount;
	Menu menu;
	//進行値
	D3DXVECTOR3 NextPos;
	//接触ベクトル
	D3DXVECTOR3 HitVec;	
	//マイライブラリ
	MyLibrary* ML;
	//キー変更の更新
	int MoveKey;
	//キャラの注視点	
	D3DXVECTOR3 AtPos;
	//移動ベクトル
	D3DXVECTOR3 tes;
	//足音
	CObjSound Step;	
	CObjSound MenuOpen;	
	CObjSound ItemGet;
	enum SLCT_MAX{SMAX = 3};
	CObjSound slct[SMAX];
	//始点デバッグ用
//	CObjMesh At;
	//ショット
	std::vector<CBullet*> Blt;
	int m_iDelay;	
	UINT m_iCount;
	//ページ
	int m_iPage;
	//FPSカメラ移動量
	D3DXVECTOR2 EyeRot;
	
	//debug用FPS
	VOID FPSMode();
	//状態
	VOID ActiveMode();
	VOID EventMode();
	VOID MenuMode();
	VOID DamageMode();
	VOID DeadMode();
public:
	//FPSモードフラグ	
	BOOL FPSFlag;
	//SE
	enum Player_SE
	{
		SE_CANSEL,
		SE_CHECK,
		SE_STEP,
		SE_ITEM,
		SE_OPEN,
		SE_SLIDE,
		SE_SELECT,

	};
	//状態	
	enum Player_Mode
	{
		MODE_EVENT,
		MODE_ACTIVE,
		MODE_MENU,
		MODE_DAMAGE,
	};	
	Player_Mode Mode;
	//グローバルBGM
	CObjSound *BGM;	
 	int ReLoad;
	//フラグマネージャ
	FlagManager FM;		
	//主人公モデル
	gt_Model  gt;		
	//調べるフラグ
	BOOL Check;	
	//キャンセルフラグ
	BOOL Cansel;
	//当たり判定用オブジェクト
	CObjMesh obj;	
	//コンストラクタ
	Personal();	
	virtual ~Personal();	
	//準備
	VOID Set(MyLibrary*);
	//更新
	VOID Update();	
	//描画
	VOID draw();
	//UIの描画
	VOID Ui();
	//ヒットイベント
	VOID HitEvent(std::vector<CollObj*>*);
	//弾が敵にくっつく
	VOID AtcBullet(D3DXMATRIX*);
	//弾のリセット
	VOID ResetBullet();
	//デバッグ用テキスト
	VOID DebugText(TCHAR*,int);
	//debugボタン
	VOID DButton(DebugButton*);	
	//プレイヤーが発するSE
	VOID CheckSE(Player_SE);
};


