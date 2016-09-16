#pragma once
namespace Fld{	
//==========================================================================
//男子トイレ
//==========================================================================
class Rest_Men: public Scene
{
private:
	Scene* pHitSenmen;
	Scene* pHitSikiri;
	Scene* pHitSikiri1;
	Scene* pHitSikiri2;
	Scene* pHitSikiri3;
	Scene* pRoom;
	Scene* pDoor;
	Scene* pDoor1;
	Scene* pDoor2;
	Scene* pHandle;
	Scene* pHandle1;

	Scene* pDact;
	Scene* pLight;
	Scene* pExit;
	Scene* pMirror;
	Scene* pToile;
	Scene* pToile1;
	Scene* pToile2;
	Scene* pMemo;

public:
	Rest_Men();
	VOID Set();
	VOID Update();
};
}