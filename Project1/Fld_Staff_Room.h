#pragma once 
namespace Fld{
//===========================================
//è]ã∆àıé∫
//===========================================
class Staff_Room : public Scene
{
	Scene* pHitBox;
	Scene* pDoor;
	Scene* pRoom;
	Scene* pLack;
	Scene* pLack1;
	Scene* pKey;
	Scene* pWhite;
	Scene* pDesk;
	Scene* pMado;
	Scene* pDesk1;
	Scene* pDesk2;
	Scene* pDesk3;
	Scene* pDesk4;
	Scene* pDesk5;
	Scene* pDesk6;
	Scene* pChair;
	Scene* pChair1;
	Scene* pChair2;
	Scene* pChair3;
public:
	Staff_Room();
	VOID Set();
	VOID Update();
};
};