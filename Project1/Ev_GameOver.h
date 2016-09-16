#pragma once
//ゲームオーバーイベント
namespace Ev
{
class Ev_GameOver : public Scene
{
	int slct;
	//演出
	BOOL Eff;
	int frame;
	int slctNum;
	CObjText text;
	CObjText go;
	CObjFVF select;
	CObjSound sa;
	CObjSound bgm;
	
	AKey<float> alpha;

	VOID SChange();
public:
	Ev_GameOver();
	VOID Set();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};
};