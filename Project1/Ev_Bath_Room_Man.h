#pragma once
namespace Ev{
//===========================================
//ÉâÉWÉJÉZ
//===========================================
class Razikase : public Scene
{
	enum SEN{SEN_MAX = 10};
	CObjMesh NullObj;
	CObjMesh hitbox;
	CObjMesh senmen[SEN_MAX];
	CObjMesh razikase;
	CObjMesh Key;

	CObjSound bgm;
	CObjSound se;
	CObjSound KeySe;

	int flag;
	int frame;
	AKey<D3DXVECTOR3> p;
	AKey<float> rx;
	AKey<D3DXVECTOR3> kp;
	AKey<D3DXVECTOR3> kr;

	GameText text;

public:
	const TCHAR* name();
	Razikase();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};
};