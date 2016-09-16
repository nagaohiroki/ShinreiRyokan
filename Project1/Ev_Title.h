#pragma once
namespace Ev{


class EvTitle : public Scene
{
	
	int PreMS;
	AKey<float> alpha;
	int Key;
	FlagManager Fm[3];
	BOOL LFlag[3];
	enum{IL = 500};
	TCHAR LoadInfo[IL];
	//ロードフラグ
	int LoadNum;
	//項目
	int ModeSelect;
	//ページ
	int NextPage;
	//テキスト
	CObjText tLoad;
	//ロード情報
	CObjText tInfo;
	//操作方法
	CObjText tCtrl;
	//プレイ時間
	enum{TMAX = 50};
	TCHAR tmax[TMAX];
	CObjText tTime;
	//項目
	CObjFVF Choice;
	//タイトルのメニュー
	VOID TitleMenu();
	//ロード画面
	VOID Load();
	//フィールドを入れ替える
	Scene* FLoad(int);
	//タイトル
	CObjText Title;
	//魚
	Fish fish;
	D3DXVECTOR3 fAt;
	int mode;
	int frame;
	float AngleNeck;
	float Rot;
	float neck;
	float body;
	AKey<float> rAnim;
	VOID NeckAngle(D3DXVECTOR3*,float);
	VOID FishUpdate();
public:
	EvTitle();
	const TCHAR* name();//クラスの名前	
	VOID Set();
	VOID Update();
	VOID draw();

	VOID DebugText(TCHAR*,int);
	VOID DebugBtn(DebugButton*);
};
};