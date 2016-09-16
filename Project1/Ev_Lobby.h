#pragma once
namespace Ev{
//====================================================
//�G����
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
//�H������O
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
//�H������
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
//�]�ƈ�����
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
//���r�[��
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
//�A��
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