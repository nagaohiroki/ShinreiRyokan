#pragma once
namespace Fld{
//=========================================================
//テスト用部屋
//=========================================================
class TestRoom : public Scene
{
private:
	Scene* pFloor;
	Scene* pMess;
	Scene* pMess1;
	Scene* pItem;
	Scene* pPart;
	Scene* pMoveChange;
	Scene* pCamChar;
	Scene* pCamSet1;
	Scene* pEnemy;
public:
	TestRoom();
	VOID Set();
	VOID Update();
	VOID draw();
	VOID UI();
	VOID DebugText(TCHAR* t,int len);
	
};

}