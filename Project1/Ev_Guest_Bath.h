#pragma once
namespace Ev
{
//====================================
//空調のスイッチ
//====================================
class AirSwitch : public Scene 
{
	GameText text;
	CObjMesh hitbox;
	CObjMesh pBase;
	CObjMesh pSwitch;
public:
	const TCHAR *name();
	AirSwitch();
	VOID Update();
};
//====================================
//空調
//====================================
class Air : public Scene 
{
	int frame;
	AKey<float> anim;
	CObjMesh Null;
	CObjMesh air;
	CObjSound gangan;
	CObjSound airSe;
public:
	const TCHAR *name();
	Air();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};
};