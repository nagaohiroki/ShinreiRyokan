#pragma once
namespace Ev{
//======================================
//���r�[�ɏo���
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
//��
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
//����
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
//�z���C�g�{�[�h
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
//��
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
//�֎q
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
//�x�z�l�̊�
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