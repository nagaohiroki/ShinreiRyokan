#pragma once
namespace Ev{
//======================================
//ロビーに出る扉
//======================================
class Lobby_Door : public Scene
{
	CObjMesh pBox;
	CObjMesh pWaku; 
	CObjMesh pDoor;
	CObjMesh pNobu;
public:
	const TCHAR* name();
	Lobby_Door();
	VOID Update();
};
//======================================
//机
//======================================
class Desk : public Scene
{
	CObjMesh desk;
	CObjMesh hitbox;
	GameText text;
public:
	const TCHAR* name();
	Desk();
	VOID Update();
};
//======================================
//鍵机
//======================================
class KeyDesk : public Scene
{
	CObjMesh desk;
	CObjMesh hitbox;
	CObjSound unlock;
	CObjSound lock;

	GameText text;
	GameText text1;
public:
	const TCHAR* name();
	KeyDesk();
	VOID Update();
};
//======================================
//ホワイトボード
//======================================
class WhiteBord : public Scene
{
	int flag;
	int frame;
	CObjMesh head;
	CObjMesh Null;
	CObjMesh hitbox;
	CObjMesh white;
	CObjSound se;
	AKey<float> rot;
public:
	const TCHAR* name();
	WhiteBord();
	VOID Update();
	VOID DebugText(TCHAR*,int);

};
//======================================
//鍵
//======================================
class Key203 : public Scene
{
	CObjMesh hitbox;
	CObjMesh key;
	GameText text;
public:
	const TCHAR* name();
	Key203();
	VOID Update();
};
//======================================
//椅子
//======================================
class StaffChair : public Scene
{
	CObjMesh chair;
	CObjMesh chair1;
public:
	const TCHAR* name();
	StaffChair();
};
//======================================
//支配人の机
//======================================
class MasterDesk : public Scene
{
	CObjMesh hitbox;
	CObjMesh hitbox1;
	CObjMesh desk;
	CObjMesh desk1;
	GameText text;
public:
	const TCHAR* name();
	MasterDesk();
	VOID Update();
};
};