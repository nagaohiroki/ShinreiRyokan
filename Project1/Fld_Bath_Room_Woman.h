#pragma once
namespace Fld
{
	
//=====================================================
//èóìí
//=====================================================
class Bath_Room_Woman : public Scene
{
private:
	Scene* pMoveDatui;
	Scene* pHitAraiba;
	Scene* pHitBath;
	Scene* pHitBath1;
	Scene* pHitKaidan;
	Scene* pRoom;
	Scene* pSw;
	Scene* pSw1;
	Scene* pSw2;
	Scene* pChair;
	Scene* pChair1;
	Scene* pChair2;
	Scene* pOke;
	Scene* pOke1;
	Scene* pOke2;
	Scene* pMado;
	Scene* pMado1;
	Scene* pMirror;
	Scene* pKey;
public:
	Bath_Room_Woman();
	VOID Set();
	VOID Update();
};
}