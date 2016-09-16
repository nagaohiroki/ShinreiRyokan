#pragma once
namespace Ev{

class Ending : public Scene
{
	CObjFVF black;
	CObjText osimai;
	GameText text;
	AKey<D3DXVECTOR3> eye;
	AKey<float> fade;
	AKey<float> alpha;

	int flag;
	int frame;
public:
	const TCHAR* name();
	Ending();
	
	VOID Set();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};
};