#pragma once
namespace Ev{
//===========================================
//2�K����
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
//���̋@
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
//203�����h�A
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
//�S�~������
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