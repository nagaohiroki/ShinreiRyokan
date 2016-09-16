#pragma once
//====================================
//‰B‚³‚ê‚½•”‰®
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