#pragma once
namespace Ev
{
//=========================
//����
//=========================
class Memo : public Scene
{
	AKey<float> slide;
	int frame;
	int flag;
	//�����蔻��
	CObjMesh hit;
	CObjMesh hit1;
	CObjMesh husuma;
	//�e�L�X�g
	GameText text;
	//��
	CObjSound se;
public:
	
	const TCHAR *name();
	Memo();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};
//=========================
//������
//=========================
class Memokami : public Scene
{
	CObjFVF kami;
public:
	const TCHAR *name();
	Memokami();
};
//=======================
//TEL
//=======================
class Tel : public Scene
{
	GameText text;
	GameText text1;
	CObjMesh tel;
public:
	const TCHAR *name();
	Tel();
	VOID Update();
};
//=========================================
//����
//=========================================
class Kinko:public Scene
{

	AKey<float> rot;
	int flag;
	int frame;
	CObjSound se;
	CObjMesh pKinko;
	CObjMesh pDoor;
	GameText close;
	GameText open;

public:
	const TCHAR *name();
	Kinko();
	VOID Update();
};
//=========================================
//TV
//=========================================
class TV : public Scene
{
	CObjMesh tv;
	GameText text;
public:
	
	const TCHAR *name();
	TV();
	VOID Update();
};

//=========================================
//�①��
//=========================================
class Reizouko:public Scene
{
	int flag;
	int frame;
	CObjMesh pReizou;
	CObjMesh pDoor;
	CObjSound open;
	CObjSound close;
	GameText text;
	AKey<float> anim;
public:
	const TCHAR *name();
	Reizouko();
	VOID Update();
};
//=========================================
//�`���[�g���A��
//=========================================
class Tutorial : public Scene
{
	CObjMesh hitbox;
	CObjFVF paper;
	GameText text;
public:
	
	const TCHAR *name();
	Tutorial();
	VOID Update();
};
};