#pragma once
//最初の部屋のイベント
namespace Ev{

//=====================================
//イントロイベント1最初
//=====================================
class IntroFirst : public Scene
{
	enum
	{
		f0 = 0,
		f1 = 100,
		f2 = 200,
		f3 = 300,
		f4 = 400,
	};
	int frame;
	CObjFVF back;
	CObjText text0;
	AKey<float> atxt1;

public:
	IntroFirst();
	VOID Set();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};
//=====================================
//イントロイベント2外の後
//=====================================
class IntroSoto : public Scene
{	
	enum
	{
		f0 = 0,
		f1 = 100,
		f2 = 200,
		f3 = 300,
		f4 = 400,
		f5 = 800,
		f6 = 850,
	};
	int frame;
	CObjFVF back;
	CObjText text0;
	AKey<float> atxt0;
public:
	IntroSoto();
	VOID Set();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};
//=====================================
//イントロイベント3外カメラ
//=====================================
class IntroSotoCam : public Scene
{
	AKey<D3DXVECTOR3> aeye;
	int frame;
public:
	IntroSotoCam();
	VOID Set();
	VOID Update();
	VOID DebugText(TCHAR* t,int l);
	VOID DebugBtn(DebugButton*);
};
//=====================================
//イントロイベント4F2カメラ
//=====================================
class IntroF2Cam : public Scene
{
	int frame;	
	AKey<D3DXVECTOR3> aEye;
	CObjSound Step;
	
public:
	IntroF2Cam ();
	VOID Set();
	VOID Update();
	VOID DebugText(TCHAR* t,int l);
	VOID DebugBtn(DebugButton*);
};

//=====================================
//イントロイベント最後タイトルコール
//=====================================
class IntroTitleCall : public Scene
{
	CObjSound DoorOpen;
	int frame;
	CObjFVF back;
	CObjText text0;
	CObjText title;
	AKey<float> aback;
	AKey<float> atext;
	AKey<float> atitle;

//	CObjFVF cen;
public:
	IntroTitleCall();
	VOID Set();
	VOID Update();
	VOID DebugText(TCHAR* t,int l);
};
//=====================================
//最初のイベント
//=====================================
class IntroGuest : public Scene
{
	int frame;
	BOOL TextStart;
	BOOL frameStop;
	GameText Gt;
	CObjSound DoorClose;
	CObjSound DoorOpen;
	AKey<D3DXVECTOR3> aPos;
	AKey<D3DXVECTOR3> aRot;
	AKey<D3DXVECTOR3> aNeck;
public:
	const TCHAR* name();
	IntroGuest();
	VOID Set();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};
//=====================================
//イベントカット
//=====================================
class IntroCut : public Scene
{
public:
	IntroCut();
	VOID Update();
};
};