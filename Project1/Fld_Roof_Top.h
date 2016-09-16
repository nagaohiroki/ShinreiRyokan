#pragma once
namespace Fld{
//==============================================================================
//âÆè„
//==============================================================================
class Roof_Top :public Scene
{
private:
	Scene* pHit_Z0;
	Scene* pHit_Z1;
	Scene* pHit_X0;
	Scene* pHit_X1;
	Scene* pHitKai;
	Scene* pBoiler;
	Scene* pDoorExit;
	Scene* pRoofTop;
	Scene* pSky;
	Scene* pMado;
	Scene* pCamChar;
	Scene* pEnemy;
public:
	Roof_Top();
	VOID Set();
	VOID Update();
};
};//Fld