#pragma once
namespace Fld{
//==============================================================================
//éOäKÉtÉçÉA
//==============================================================================
class F3 :public Scene
{
private:
	Scene* pMoveF2;
	Scene* pHitWall;
	Scene* pHitWall1;
	Scene* pHitKaidan;
	Scene* pHitFloor;
	Scene* pHitOboriba;
	Scene* pHitOboribaTenjo;
	Scene* pHitUtikabe;
	Scene* pHitUtikabe1;
	Scene* pLight;
	Scene* pLight1;
	Scene* pLight2;
	Scene* pLight3;
	Scene* pMado;
	Scene* pMado1;
	Scene* pMado2;
	Scene* pMado3;

	Scene* pF2;
	Scene* pZihanki;
	Scene* pZihanki1;
	Scene* pZihanki2;
	Scene* pZihanki3;
	Scene* pTrash;
	Scene* pChair;
	Scene* pChair1;
	Scene* pChair2;
	Scene* pChair3;
	Scene* pTable;
	Scene* pTable1;
	Scene* pSyoukaki;
	Scene* pExit;
	Scene* pDoor201;
	Scene* pDoor202;
	Scene* pDoor203;
	Scene* pDoor204;
	Scene* pDoorMan;
	Scene* pDoorWoman;
	Scene* pDoorExit;
	Scene* pDoorExit1;
	Scene* pKabe;
	Scene* pIntroEvent;
	Scene* pIntroCut;
	Scene* pBouka;
	Scene* pBoukaSwitch;
	Scene* pExitText;
	Scene* pSecret;
	Scene* pLastFish;
public:
	F3();
	VOID Set();
	VOID Update();
};
}