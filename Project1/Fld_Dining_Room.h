#pragma once
namespace Fld{


//======================================================
//êHì∞
//======================================================
class Dining_Room : public Scene
{
private:
	Scene* pHitSikiri;
	Scene* pHitSikiri1;

	Scene* pHitSikiriUe;
	Scene* pHitSikiriL;
	Scene* pHitSikiriR;
	
	Scene* pHitKichin;
	Scene* pHitKichin1;

	Scene* pHitKichinBoiler;
	Scene* pHitKichinBoiler1;


	Scene* pDoor;
	Scene* pDoor1;
	Scene* pRoom;
	Scene* pLight;
	Scene* pLight1;
	
	Scene* pMado;
	Scene* pMado1;
	
	Scene* pChair;
	Scene* pEnemy;
public:
	Dining_Room();
	VOID Set();
	VOID Update();
};


}//namespace Fld