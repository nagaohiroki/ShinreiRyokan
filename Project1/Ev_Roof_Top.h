#pragma once
namespace Ev{
//======================================
//ボイラー
//======================================
class Boiler :public Scene
{
	int flag;
	int frame;
	AKey<D3DXVECTOR3> p;
	AKey<D3DXVECTOR3> r;

	int frame1;
	AKey<D3DXVECTOR3> gata;

	CObjMesh boiler;
	CObjMesh black;
	CObjMesh huta;
	CObjMesh hutaNull;
	CObjMesh hitbody;
	CObjMesh hithuta;
	CObjMesh FldHit;
	CObjSound bgm;
	CObjSound se;
	CObjSound ban;
	CObjSound oop;
	GameText text;
	GameText text1;

public:	
	const TCHAR* name();//クラスの名前	
	Boiler();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};
//======================================
//屋上扉
//======================================
class DoorRoofTop : public Scene
{
	CObjMesh pBox;
	CObjMesh pWaku; 
	CObjMesh pDoor;
	CObjMesh pNobu;
	GameText text;
	CObjSound se;
	CObjSound oop;
public:	
	const TCHAR* name();//クラスの名前	
	DoorRoofTop();
	VOID Update();
};

};