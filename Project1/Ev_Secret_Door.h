#pragma once 
namespace Ev{
//=======================================
//‰B‚³‚ê‚½ƒhƒA
//=======================================
class Secret_Door : public Scene
{
	int flag;
	int frame;

	CObjMesh hitbox;
	CObjMesh pWaku; 
	CObjMesh pDoor;
//	CObjMesh pNobu;
	CObjMesh pPlate;
	CObjMesh wall;
	CObjFVF black;
	CObjText roomPlate;	
	CObjSound strip;
	GameText text;
	AKey<float> fade;
public:
	const TCHAR* name();
	Secret_Door();
	VOID Set();
	VOID Update();
};
};