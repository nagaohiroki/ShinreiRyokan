#pragma once
namespace Fld{

//=======================================================
//çLèÍ
//=======================================================
class Soto: public Scene
{
private:

	Scene* pMoveRobby;
	Scene* pHitKabeR;
	Scene* pHitKabeL;
	Scene* pHitKiadan;
	Scene* pHitKiadan1;
	Scene* pHitKiadan2;
	Scene* pHitKiadan3;
	Scene* pHitHasiraR;
	Scene* pHitHasiraL;
	Scene* pHitYane;

	Scene* pHonkan;
	Scene* pSky;
	Scene* pSoto;
	Scene* pTel;
	Scene* pKusa;
	Scene* pCamChar;
	Scene* pMoon;
	Scene* pIntroCut;
	Scene* pCamEvent;
	Scene* pSotoEvent;
	Scene* pTenYen;
	Scene* pGlass;
	Scene* pCase;
	Scene* pEnding;
public:
	Soto();
	VOID Set();
	VOID Update();
};

}