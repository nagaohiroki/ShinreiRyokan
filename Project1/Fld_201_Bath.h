#pragma once 
namespace Fld{
//====================================
//201çÜé∫ÇÃÉoÉXÉãÅ[ÉÄ
//====================================
class Fld_201_Bath : public Scene
{
	Scene* pRoom;
	Scene* pSink;
	Scene* pToile;
	Scene* pDoor;
	Scene* pLight;
	Scene* pHitBath;
	Scene* pAir;
	Scene* pAirSwitch;
	Scene* pBlackBox;
public:
	Fld_201_Bath();
	VOID Set();
	VOID Update();
};
};