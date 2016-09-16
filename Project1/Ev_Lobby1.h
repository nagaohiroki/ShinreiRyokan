#pragma once
namespace Ev{
//====================================================
//ê≥ñ å∫ä÷
//====================================================
class LobbyIriguti : public Scene
{
private:
	CObjMesh pIri;
	CObjMesh pDoor;
	CObjMesh pGlass;
	CObjMesh pGlass1;
	CObjMesh pGlass2;
	CObjMesh pGlass3;
	CObjMesh hitbox;
	CObjSound lock;
	CObjSound unlock;
	GameText text;
	GameText text1;
public:
	const TCHAR *name();
	LobbyIriguti();	
	VOID Update();
};
//====================================================
//à÷éq
//====================================================
class LobbyChair : public Scene
{
	int frame;
	int flag;
	CObjMesh chair;
	CObjMesh pLhand;
	CObjMesh pRhand;
	AKey<D3DXVECTOR3> pos;
	AKey<D3DXVECTOR3> rot;
public:
	const TCHAR *name();
	LobbyChair();
	VOID Set();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};

};