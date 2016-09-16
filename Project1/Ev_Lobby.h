#pragma once
namespace Ev{
//====================================================
//ìGï‡Ç≠
//====================================================
class EnemyWalk : public Scene
{
	int flag;
	int frame;
	AKey<D3DXVECTOR3> ap;
	CObjSound bgm;
public:
	const TCHAR* name();
	EnemyWalk();	
	VOID Set();
	VOID Update();
};
//====================================================
//êHì∞î‡éËëO
//====================================================
class Dining_Door : public Scene
{
	CObjText roomPlate;	
	CObjMesh pBox;
	CObjMesh pWaku; 
	CObjMesh pDoor;
	CObjMesh pNobu;
	CObjMesh pPlate;
	CObjSound se;
	CObjSound unlock;
	GameText text;
	GameText text1;
public:
	const TCHAR* name();
	Dining_Door();
	VOID Update();
};
//====================================================
//êHì∞î‡âú
//====================================================
class Dining_Door2 : public Scene
{
	CObjText roomPlate;	
	CObjMesh pBox;
	CObjMesh pWaku; 
	CObjMesh pDoor;
	CObjMesh pNobu;
	CObjMesh pPlate;
	CObjSound se;
	GameText text;
public:
	const TCHAR* name();
	Dining_Door2();
	VOID Update();
};
//====================================================
//è]ã∆àıé∫î‡
//====================================================
class Staff_Door : public Scene
{
	CObjText roomPlate;	
	CObjMesh pBox;
	CObjMesh pWaku; 
	CObjMesh pDoor;
	CObjMesh pNobu;
	CObjMesh pPlate;
	CObjSound se;
	CObjSound unlock;
	GameText text;
	GameText text1;
public:
	const TCHAR* name();
	Staff_Door();
	VOID Update();
};
//============================================
//ÉçÉrÅ[ëã
//============================================
class LobbyWindow : public Scene
{
	CObjMesh pMado;
	CObjMesh pGlass;
	CObjMesh pKaten;
public:
	const TCHAR *name();
	LobbyWindow();
};
//============================================
//êAñÿ
//============================================
class Ueki : public Scene
{
	CObjMesh pPlanter;
	CObjMesh pUeki;
public:
	const TCHAR *name();
	Ueki();
};

};