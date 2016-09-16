#pragma once
namespace Ev{
//===================================
//�d�C
//===================================
class Denki202 : public Scene
{
	int flag;
	int frame;
	int framefall;
	float power;
	flashlight fl;
	CObjMesh pCube;
	CObjMesh pCable;
	CObjMesh pDenki;
	CObjMesh hitbox;
	CObjSound gon;
	GameText text;
	AKey<D3DXVECTOR3> rot;
	AKey<D3DXVECTOR3> r;
	AKey<D3DXVECTOR3> p;
public:
	const TCHAR *name();
	Denki202();
	VOID Update();
	VOID draw();
	VOID DebugText(TCHAR*,int);
};
//===================================
//�e�L�X�g�o�X���[�����J���Ȃ�
//===================================
class BathDoor202 : public Scene
{
	CObjMesh hitbox;
	CObjSound gatya;
	GameText text;
public:
	const TCHAR *name();
	BathDoor202();
	VOID Update();
};
};