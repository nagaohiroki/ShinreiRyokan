#pragma once
namespace Ev
{
//=========================================
//トイレのメモ	
//=========================================
class ToileMemo : public Scene 
{
	enum{MEMO_MAX = 4};
	CObjMesh hitbox;
	CObjFVF memo[MEMO_MAX];
	GameText text;
public:
	const TCHAR *name();
	ToileMemo(int);
	VOID Update();
};
//=========================================
//トイレドア
//=========================================
class Rest_Men_door:public Scene
{
private:
	int frame;
	int flag;
	AKey<float> door;
	CObjMesh pDoor;
	CObjMesh pGreen;
	CObjMesh pRed;
	CObjSound gan;
public:
	const TCHAR *name();
	//鍵青
	Rest_Men_door();
	VOID Update();
};
//=========================================
//トイレ	
//=========================================
class Rest_Men_Toile : public Scene
{
	CObjMesh pToile;
	CObjMesh pHuta;
	CObjMesh hitbox;
	GameText text;
	GameText text1;
	CObjSound gan;
	CObjSound oop;
	CObjSound water;
	int flag;	//進行フラグ
	int gtframe;
	int hutaframe;
	int GOFlag;//0鍵取得1ゲームオーバー
	//トイレふた
	AKey<float> rot;
	//gtアニメ
	AKey<float> prot;
	AKey<D3DXVECTOR3> pos;
public:
	Rest_Men_Toile(int );
	VOID Set();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};
};