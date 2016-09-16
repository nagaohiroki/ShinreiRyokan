#pragma once
namespace Ev{
//===========================================
//2階非常口
//===========================================
class F3_EXIT : public Scene
{
	CObjMesh hitbox;
	CObjSound se;
	GameText text;
public:
	
	const TCHAR *name();
	F3_EXIT();
	VOID Update();
};
//===========================================
//自販機
//===========================================
class F3_Zihanki : public Scene
{
	
	CObjMesh pZihanki;
	GameText text;
	GameText text1;
public:
	const TCHAR *name();
	F3_Zihanki();
	VOID Update();
};
//===========================================
//203号室ドア
//===========================================
class Door203 : public Scene
{
	CObjText roomPlate;	
	CObjMesh pBox;
	CObjMesh pWaku; 
	CObjMesh pDoor;
	CObjMesh pNobu;
	CObjMesh pPlate;
	CObjMesh pBlack;
	CObjSound se;
	CObjSound open;

	GameText text;
	AKey<float> rot;
	int flag;
	int frame;
public:
	
	const TCHAR *name();
	Door203();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};
//===========================================
//ゴミ箱メモ
//===========================================
class DustMemo : public Scene
{
	CObjMesh dust;
	GameText text;
public:
	const TCHAR *name();
	DustMemo();
	VOID Update();
};
};