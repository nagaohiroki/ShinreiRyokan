#pragma once
namespace Fld{	
//========================================================
//ロビーのトイレ
//========================================================
class LobbyRestRoom : public Scene
{
private:
	Scene* pDoor;
	Scene* pRest;
	Scene* pPaper;
	Scene* pDact;
	Scene* pSink;
	Scene* pToile;
public:
	LobbyRestRoom();
	VOID Set();
	VOID Update();
};

}