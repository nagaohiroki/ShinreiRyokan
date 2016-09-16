#pragma once
namespace Ev{
//==============================================
//山道イベント
//==============================================
class SandouEvent :  public Scene
{
public:
	const TCHAR* name(); 
	SandouEvent();
	VOID Set();
	VOID Update();
};
};