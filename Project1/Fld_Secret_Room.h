#pragma once
//====================================
//隠された部屋
//====================================
namespace Fld{
class SecretRoom : public Scene
{
	Scene* pDoor;
	Scene* pRoom;
public:
	SecretRoom();
	VOID Set();
	VOID Update();
};
};