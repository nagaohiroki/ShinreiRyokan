#pragma once 
namespace Ev{
//=============================================
//���v
//=============================================
class Clock : public Scene
{
	CObjSound se;
	CObjMesh hitbox;
	CObjMesh clock;
	CObjMesh hNull;
	CObjMesh mNull;
	CObjMesh sNull;
	CObjMesh hour;
	CObjMesh min;
	CObjMesh sec;
	WORD  w;
	unsigned int w2;
	int flag;
public:
	const TCHAR* name();
	Clock();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};
//=============================================
//���莆�ƕ���
//=============================================
class Datui_Harigami : public Scene
{
	CObjMesh hitbox;
	CObjFVF kami;
	CObjSound se;
	GameText text;
	GameText text1;
public:
	const TCHAR* name();
	Datui_Harigami ();
	VOID Update();
};
//=============================================
//�o������
//=============================================
class Datui_Door : public Scene
{
	CObjMesh hitbox;
	CObjSound se;
	GameText text;
public:
	const TCHAR* name();
	Datui_Door();
	VOID Update();


};
//=============================================
//�G�o��
//=============================================
class Datui_Enemy : public Scene
{
	CObjSound voice;
	CObjSound bgm;
	CObjSound se;
	int wait;
public:
	const TCHAR* name();
	Datui_Enemy();
	VOID Set();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};



};