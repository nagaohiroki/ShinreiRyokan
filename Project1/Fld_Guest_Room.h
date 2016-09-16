#pragma once
namespace Fld{
	//==========================================================
//ŒÂŽº
//==========================================================
class Guest_Room : public Scene
{
private:
	Scene* pHitOsiire;
	Scene* pHitTokonoma;
	Scene* pHitEngawa;
	Scene* pHitEngawa1;
	Scene* pHitTokoUe;
	Scene* pHitTanas;
	Scene* pHitSikiriUe;
	Scene* pRoom;
	Scene* pDoor;
	Scene* pDoorBath;
	Scene* pDenki;
	Scene* pMado;

	Scene* pHusuma;
	Scene* pHusuma1;
	Scene* pHusuma2;
	Scene* pHusuma3;
	Scene* pTV;
	Scene* pTable;
	Scene* pTable1;
	Scene* pChair;
	Scene* pChair1;
	Scene* pZaisu;
	Scene* pZaisu1;	
	
	Scene* pReizouko;
	Scene* pTel;
	Scene* pKinko;
	//ƒCƒxƒ“ƒg
	Scene* pEvent;

	Scene* pDrug;
	Scene* pDoorText;
	Scene* pDarts;
	Scene* pDartsbord;
	Scene* pF3DoorText;
	Scene* pMemokami;
	Scene* pTutorial;
	//“G
	Scene* pEnemy;
	Scene* pActiveEnemy;
	Scene* pBathEnemy;
public:
	Guest_Room();
	VOID Set();
	VOID Update();
};
}