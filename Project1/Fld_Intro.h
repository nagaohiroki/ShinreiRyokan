#pragma once
namespace Fld{

//�I�[�v�j���O
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