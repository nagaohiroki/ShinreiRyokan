#pragma once
namespace Fld
{
	
//=======================================================
//�E�ߏ�(�j��)
//=======================================================
class Bath_Datui_Man : public Scene
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
public:
	Bath_Datui_Man();
	VOID Set();
	VOID Update();
};

}