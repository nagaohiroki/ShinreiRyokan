#pragma once
namespace Ev
{
//=============================================
//薬
//=============================================
class Drug : public Scene
{
	CObjSound se;
	CObjSound Suzumusi;
	CObjSound gangan;
	GameText text;
	CObjMesh bottle;
	CObjMesh hitbox;
	int frame;
	int flag;
	int lightframe;
	AKey<D3DXVECTOR4> light;
public:	
	const TCHAR *name();
	Drug();
	VOID Set();
	VOID Update();
};
//=====================================
//バスルームのドア
//=====================================
class bathdoor : public Scene
{
	CObjSound open;
	CObjSound close;
	CObjMesh hit;
	CObjMesh door;
	CObjMesh waku;
	int frame;
	AKey<float> aopen;
public:
	const TCHAR* name();
	bathdoor();
	VOID Update();
};
//=======================
//バスルームの鍵
//=======================
class DoorText : public Scene
{
	GameText text;
	CObjMesh hitbox;
	CObjSound gatya;
public:	
	const TCHAR *name();
	DoorText();
	VOID Update();
};

//=======================
//F2
//=======================
class F2_DoorText : public Scene
{
	GameText text;	
	GameText text1;
	CObjMesh hitbox;
	CObjSound gatya;
	CObjSound unlock;
public:	
	const TCHAR *name();
	F2_DoorText();
	VOID Update();
};

//=====================
//ダーツ
//=====================
class Darts : public Scene
{
	CObjMesh drug;
	//アニメーションフレーム
	int frame;
	//ダーツの本数
	enum{MAX = 3};
	//表示するダーツ
	CObjMesh darts[MAX];
	//当たり判定箱
	CObjMesh hitbox;
	//テキスト
	GameText text;
	//しびれ薬を手に入れてから
	GameText textmasui;
	//しびれダーツ
	GameText textmsdt;
	//ドリップ
	CObjMesh drip;
	//音
	CObjSound se;
	//アニメーション
	AKey<float> adrip;
public:
	const TCHAR *name();
	Darts();	
	VOID Update();
};
//=====================
//的
//=====================
class Dartsbord : public Scene
{
	BOOL SoundFlag;
	int frame;
	//描画
	CObjMesh dartsbord;
	CObjMesh drug;
	//当たり判定
	CObjMesh hit;
	//軸
	CObjMesh center;
	//サウンド
	CObjSound se;
	//テキスト
	GameText text;
	//アニメーション
	AKey<float> py;//落下
	AKey<float> rx;//回転
public:
	const TCHAR *name();
	Dartsbord();
	VOID Set();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};

};