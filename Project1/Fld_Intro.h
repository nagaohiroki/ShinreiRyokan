#pragma once
namespace Fld{

//オープニング
class Intro : public Scene
{
	Scene* pIntro;
	Scene* pIntroCut;
public:
	Intro();
	VOID Set();
	VOID Update();
	VOID UI();	
};


}