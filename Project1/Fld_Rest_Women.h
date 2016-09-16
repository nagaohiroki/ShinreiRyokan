#pragma once
namespace Fld{	
	
//==========================================================================
//èóéqÉgÉCÉå
//==========================================================================
class Rest_Women :public Scene
{
private:
	Scene* pHitSenmen;
	Scene* pHitSikiri;	
	Scene* pExit;
	Scene* pRoom;
	Scene* pDoor;
	Scene* pDoor1;
	Scene* pDoor2;
	Scene* pHandle;
	Scene* pHandle1;
	Scene* pDact;
	Scene* pLight;
	Scene* pMirror;
	Scene* pToile;

	Scene* pEnemy;
	Scene* pKey;
	Scene* pText;
public:
	Rest_Women();
	VOID Set();
	VOID Update();
};


}