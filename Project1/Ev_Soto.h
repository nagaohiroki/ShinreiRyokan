#pragma once
namespace Ev{
//============================================
//BGM
//============================================
class SotoEvent : public Scene
{
public:
	const TCHAR* name();
	SotoEvent();
	VOID Set();
	VOID Update();

};

//============================================
//10‰~
//============================================
class TenYen : public Scene
{
	CObjMesh box;
	Fish fish; 
	int frame;
	int flag;
	int frame1;

	AKey<float> angle;
	AKey<float> nangle;
	AKey<float> alpha;
	AKey<float> posz;
	float neck;
	float body;

	VOID NeckAngle(D3DXVECTOR3*,float);
public:
	const TCHAR* name();
	TenYen();
	VOID Set();
	VOID Update();
	VOID draw();
};
//======================================
//–{ŠÙ
//======================================
class Honkan :public Scene
{
private:

	CObjMesh m_pRyokan;
	CObjMesh m_pIriGuti;
	CObjMesh m_pDoor;
	enum{MADO_NUM = 9};
	class cMado
	{
	public:
		CObjMesh m_pMado;
		CObjMesh m_pCube;
		cMado();
	}m_cMado[MADO_NUM];	
	VOID Mad(cMado* mado,D3DXVECTOR3* Pos);

public:
	const TCHAR *name();
	Honkan();
};
//======================================
//‘‹ƒKƒ‰ƒX
//======================================
class GenGlass : public Scene
{
	CObjMesh glass;
public:
	const TCHAR *name();
	GenGlass();

};

//======================================
//ŒŽ
//======================================
class Moon : public Scene
{
	int flag;
	CObjMesh moon;
public:
	const TCHAR *name();
	Moon();
	VOID Update();
};
//======================================
//???
//======================================
class Case : public Scene
{
	
	CObjMesh hitbox;
	CObjFVF paper;
	GameText text;
public:
	const TCHAR *name();
	Case();
	VOID Update();
};
};