#pragma once
namespace Ev{
//==========================================
//�H����
//==========================================
class Dining_Door_In : public Scene
{
	CObjMesh pBox;
	CObjMesh pWaku; 
	CObjMesh pDoor;
	CObjMesh pNobu;
	CObjSound se;
	GameText text;
public:
	const TCHAR* name();
	Dining_Door_In();
	VOID Update();
};
//===========================================
//�_�C�j���O�Z�b�g
//===========================================
class DiningSet:public Scene
{	
	CObjMesh pTable;
	CObjMesh pChair;
	CObjMesh pChair1;
	CObjMesh pChair2;
	CObjMesh pChair3;
public:
	const TCHAR *name();
	DiningSet();
};
//===========================================
//�u����
//===========================================
class Keikou: public Scene
{
	CObjMesh pKeikou;
	CObjMesh pLight;
	CObjMesh pLight1;
public:
	const TCHAR *name();
	Keikou();
	VOID Update();
	
};
//===========================================
//�؈֎q
//===========================================
class Wood_Chair : public Scene
{
	CObjMesh chair;
	CObjMesh Key;
	CObjSound se;
	GameText text;
	int flag;
	int frame;

public:
	const TCHAR *name();
	Wood_Chair();
	VOID Set();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};

};