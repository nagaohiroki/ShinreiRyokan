#pragma once
namespace Fld{
class Fld_203 : public Scene
{
	Scene* pHitOsiire;
	Scene* pHitTokonoma;
	Scene* pHitEngawa;
	Scene* pHitEngawa1;
	Scene* pHitTokoUe;
	Scene* pHitTanas;
	Scene* pHitSikiriUe;
//	Scene* pHitSaka; 
//	Scene* pHitSakaGen; 
	Scene* pRoom;
	Scene* pDoor;
	Scene* pDoorBath;
	Scene* pDenki;
	Scene* pMado;
	Scene* pBathText;
	Scene* pKey;
	Scene* pEnemy;
public:
	Fld_203();
	VOID Set();
	VOID Update();

};
};