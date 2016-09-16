#pragma once
namespace Ev{
//===============================================
//203çÜé∫Ç©ÇÁèoÇÈî‡
//===============================================
class Door203Exit : public Scene
{

	CObjMesh pBox;
	CObjMesh pWaku; 
	CObjMesh pDoor;
	CObjMesh pNobu;
	CObjMesh pMask;
	CObjSound close;
	CObjSound unlock;
	CObjSound lock;
	int flag;
	int frame;
	int soundEnd;
	AKey<float> rot;
	GameText text;
	GameText text1;
	GameText text2;
public:
	const TCHAR* name();
	Door203Exit();
	VOID Set();
	VOID Update();
};
//===============================================
//ê≥ñ å∫ä÷ÇÃåÆ
//===============================================
class GenkanKey : public Scene
{
	int Time;
	CObjMesh key;
	GameText text;
public:
	const TCHAR* name();
	GenkanKey();
	VOID Update();
	VOID DebugText(TCHAR*,int);

};


};