#pragma once
namespace Fld{
//============================================
//ŽR“¹
//============================================
class Sandou : public Scene
{
	
	Scene* pCamChar;
	Scene* pSky;
	Scene* pSoto;
	Scene* pKusa;
	Scene* pMoon;
	Scene* pEvent;
public:
	Sandou();
	VOID Set();
	VOID Update();
};
};