#pragma once
namespace Ev{
	
//==============================================
//åˆèOìdòb
//==============================================
class publictel : public Scene
{
	CObjMesh tel;
	CObjMesh hitbox;
	CObjMesh glass0;
	CObjMesh glass1;
	CObjMesh doornull;
	CObjMesh door;
	CObjFVF black;
	CObjSound open;
	CObjSound close;
	CObjSound bgm;
	CObjText osimai;
	CObjText Credit;
	AKey<float> rot;
	AKey<float> fade;
	AKey<float> fadeEnd;
	AKey<float> fadeCredit;
	AKey<D3DXVECTOR4> light;
	AKey<D3DXVECTOR3> fog;

	int framefade;
	int frame;
	int flag;
	int frameMorning;
	int frameOsimai;
	int frameCredit;
	GameText text;
	GameText textEnding;	
	GameText textEnding1;
	
public:
	const TCHAR* name();
	publictel();
	VOID Set();
	VOID Update();
	VOID DebugText(TCHAR*,int);

}; 
}