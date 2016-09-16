#pragma once
namespace Fld{


//============================================================
//âÆè„äKíié∫
//============================================================
class Roof_Kai : public Scene
{
private:
	Scene* pHitKaidan;
	Scene* pHitKaidan1;
	Scene* pHitFloor;
	Scene* pHitFloor1;
	Scene* pHitFloorKabe;
	Scene* pHitHasira;
	Scene* pHitHasira1;
	Scene* pDoor;
	Scene* pDoor1;
	Scene* pRoom;
	Scene* pMado;
public:
	Roof_Kai();
	VOID Set();
	VOID Update();
};


}//namespace Fld