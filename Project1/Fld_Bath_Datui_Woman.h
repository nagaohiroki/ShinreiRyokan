#pragma once
namespace Fld
{
	
//=======================================================
//íEàﬂèä(èóìí)
//=======================================================
class Bath_Datui_Woman : public Scene
{
private:
	Scene* pMovePass;
	Scene* pMoveBath;
	Scene* pHitSenmen;
	Scene* pDatui;
	Scene* pTaiju;
	Scene* pKago;
	Scene* pSenpu;
	Scene* pMirror;
	Scene* pClock;
	Scene* pEnemy;
	Scene* pDatuiEnemy;
public:
	Bath_Datui_Woman();
	VOID Set();
	VOID Update();
};

}