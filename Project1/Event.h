#pragma once

namespace Ev{


//テストよう
class Particl : public Scene
{
	CObjParticl Part;
	CObjFVF m_Ui;
	CObjText txt;
	CObjText txt1;	
	TCHAR tx[500];
	flashlight fl;
	CObjSound testSound;
	Fish fish;
public:
	const TCHAR *name();
	Particl();	
	VOID Update();
	VOID draw();
	VOID DebugText(TCHAR*,int);
	VOID DebugBtn(DebugButton*);
};

//鏡
class Mirror : public Scene
{
	CObjFVF Mir;
	CObjFVF state;
public:
	//T,S,R
	Mirror();
	VOID Update();
	VOID draw();
	const TCHAR *name();
};

}//namespace Ev