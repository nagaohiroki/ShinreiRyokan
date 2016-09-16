#pragma once
namespace Ev
{
//====================================
//�󒲂̃X�C�b�`
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
//��
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