#pragma once 
namespace Ev
{
//==============================================
//�����p�g�C���h�A
//==============================================
class Rest_Women_Door : public Scene
{
	CObjMesh pDoor;
	CObjMesh pGreen;
	CObjMesh pRed;
	CObjSound gan;	
	CObjSound oop;
	int frameDoor;
	int frameLock;
	AKey<float> KeyLock;
	AKey<float> DoorRot;

public:
	const TCHAR *name();
	Rest_Women_Door();
	VOID Set();
	VOID Update();
};
//==============================================
//��
//==============================================
class Rest_Women_Key : public Scene
{
	CObjMesh key;
	GameText text;
public:
	const TCHAR *name();
	Rest_Women_Key();
	VOID Update();
};
//==============================================
//�e�L�X�g
//==============================================
class Rest_Women_Text : public Scene
{
	CObjMesh hitbox;
	CObjSound gan;
	GameText text;
public:
	const TCHAR *name();
	Rest_Women_Text();
	VOID Update();
};
};