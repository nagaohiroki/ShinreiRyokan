#pragma once
namespace Ev{
//======================================
//�{�C���[
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
	const TCHAR* name();//�N���X�̖��O	
	Boiler();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};
//======================================
//�����
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
	const TCHAR* name();//�N���X�̖��O	
	DoorRoofTop();
	VOID Update();
};

};