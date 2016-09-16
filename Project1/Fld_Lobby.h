#pragma once
namespace Fld{
//========================================================
//ÉçÉrÅ[
//========================================================
class Lobby : public Scene
{
private:	
	Scene* pMoveF2;
	Scene* pMoveBath;
	Scene* pHitFront;
	Scene* pHitFront1;
	Scene* pHitRightTemae;
	Scene* pHitOdoriba;
	Scene* pHitKaidan;
	Scene* pHitRightOku;
	Scene* pHitKaidanOku;
	Scene* pHitLeft;
	Scene* pHitCeilingFloor;
	Scene* pHitCeilingPass;
	Scene* pHitCeilingStairs;
	Scene* pHitFrontHasira;
	Scene* pCamCenter;
	Scene* pCamKaidan;
	Scene* pLight;
	Scene* pKaiga;
	Scene* pRezi;
	Scene* pKeyBox;
	Scene* pTV;
	Scene* pTableA;
	Scene* pSofa_A;
	Scene* pSofa_A1;
	Scene* pSofa_A2;
	Scene* pTableB;
	Scene* pSofa_B;
	Scene* pSofa_B1;
	Scene* pSofa_B2;
	Scene* pSwitch;
	Scene* pToile;
	Scene* pStuff;
	Scene* pWindow;
	Scene* pWindow1;
	Scene* pLobby;
	Scene* pDoor;
	Scene* pDoor1;
	Scene* pSWindow;
	Scene* pSWindow1;
	Scene* pIriguti;
	Scene* pUeki;
	Scene* pEnemy;
	Scene* pEnemyWalk;
public:
	Lobby();
	VOID Set();
	VOID Update();		
	
};
}