#pragma once
namespace Ev{
//==========================================
//ƒhƒA
//==========================================
class ScDoor : public Scene
{
	CObjMesh pBox;
	CObjMesh pWaku; 
	CObjMesh pDoor;
	CObjMesh pNobu;
	CObjMesh pMask;
	CObjMesh pBack;
	CObjSound open;
	CObjFVF black;
	CObjText osimai;
	int flag;
	int frame;
	AKey<float> alpha;
	AKey<float> rot;
	AKey<float> fade;
	AKey<D3DXVECTOR3> at;
	GameText text;

public:
	const TCHAR* name();
	ScDoor();
	
	VOID Set();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};
};