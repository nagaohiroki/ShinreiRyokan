#pragma once
namespace Fld
{	
//=====================================================
//’j“’
//=====================================================
class Bath_Room_Man : public Scene
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
	Scene* pRazikase;
public:
	Bath_Room_Man();
	VOID Set();
	VOID Update();
};

}