#pragma once
namespace Fld
{	
//======================================================
//˜L‰º
//======================================================
class Bath_Pass : public Scene
{
private:
	Scene* pMoveMan;
	Scene* pMoveWoman;
	Scene* pMoveExit;
	Scene* pHitPass;
	Scene* pHitKaidan;
	Scene* pPass;
	Scene* pBench;
	Scene* pExitDoor;
	Scene* pExitLamp;
	Scene* pZihanki;
	Scene* pExitMessage;
public:
	Bath_Pass();
	VOID Set();
	VOID Update();
	
};



}//namespace Fld