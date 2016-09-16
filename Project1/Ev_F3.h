#pragma once
namespace Ev
{
//================================
//201号室
//================================
class Door201 : public Scene
{
	CObjText roomPlate;	
	CObjMesh pBox;
	CObjMesh pWaku; 
	CObjMesh pDoor;
	CObjMesh pNobu;
	CObjMesh pPlate;
	CObjSound gatya;
	CObjSound pati;
	GameText text;
public:
	const TCHAR *name();
	Door201();
	VOID Update();
};
//================================
//202号室
//================================
class Door202 : public Scene
{
	CObjText roomPlate;	
	CObjMesh pBox;
	CObjMesh pWaku; 
	CObjMesh pDoor;
	CObjMesh pNobu;
	CObjMesh pPlate;
	GameText text;
	GameText text1;

	CObjSound gatya;
	CObjSound unlock;
public:
	const TCHAR *name();
	Door202();
	VOID Update();
};
//================================
//屋上扉
//================================
class DoorRoof : public Scene
{
	CObjMesh pBox;
	CObjMesh pWaku; 
	CObjMesh pDoor;
	CObjMesh pNobu;
	GameText text;
	GameText text1;
	CObjSound gatya;
	CObjSound unlock;
public:
	const TCHAR *name();
	DoorRoof();
	VOID Update();
};
//================================
//消火器
//================================
class Syoukaki : public Scene
{
	CObjMesh syoukaki;
	GameText text;
public:	
	const TCHAR *name();
	Syoukaki();
	VOID Update();
};
//================================
//防火シャッター
//================================
class Shutter : public Scene
{
	CObjMesh NullObj;
	CObjMesh shutter;
	GameText text;
	int frame;
	AKey<float> p;
	CObjSound kata;
	CObjSound dan;

public:
	const TCHAR *name();
	Shutter();
	VOID Set();
	VOID Update();
};
//================================
//防火スイッチ
//================================
class BoukaSwitch : public Scene
{
	CObjMesh hitbox;
	CObjMesh pBase;
	CObjMesh pSwitch;
	GameText dark;
	GameText fire;
	GameText open;
	std::vector<GameText*> msgtxt;
public:
	const TCHAR *name();
	BoukaSwitch();
	VOID Update();
};
};