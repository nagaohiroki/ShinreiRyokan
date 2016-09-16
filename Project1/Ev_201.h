#pragma once
namespace Fld{
//=====================================
//201Œ®
//=====================================
class Key201 : public Scene
{
	CObjMesh hitbox;
	CObjSound unlock;
	GameText text;
public:
	const TCHAR *name();
	Key201();
	VOID Update();

};
//=======================================
//‰ÎŽ–
//=======================================
class Fire : public Scene
{
	int frame;
	int flag;
	CObjParticl fire;
	CObjParticl smoke;
	CObjParticl gush;
	CObjMesh table;
	CObjMesh denki;
	CObjMesh syoukaki;
	CObjSound pati;
	CObjSound syouka;
	GameText textFire;
	
	GameText textNoFire;
public:
	const TCHAR *name();
	Fire();
	VOID Set();
	VOID Update();

};

};