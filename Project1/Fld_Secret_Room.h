#pragma once
//====================================
//�B���ꂽ����
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