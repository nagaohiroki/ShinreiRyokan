#pragma once
namespace Fld{

class Guest_Bath : public Scene
{
	Scene* pRoom;
	Scene* pSink;
	Scene* pToile;
	Scene* pDoor;
	Scene* pLight;
	Scene* pHitBath;
	Scene* pEnemy;
	Scene* pEnemyEvent;
	Scene* pActiveEnemy;
	Scene* pAir;
	Scene* pAirSwitch;

public:
	Guest_Bath();
	VOID Set();
	VOID Update();
	VOID DebugText(TCHAR* t,int len);
};
};