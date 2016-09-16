#pragma once
class Item_Light : public Scene
{
	GameText gt;
	CObjMesh Box;	
public:
	const TCHAR *name();
	Item_Light();
	VOID Update();
};


class Message : public Scene
{
	CObjSound mSnd;
	CObjMesh Box;
	GameText gt;

public:
	const TCHAR *name();
	Message();
	VOID Update();

	VOID DebugText(TCHAR* dt,int Len);
};

