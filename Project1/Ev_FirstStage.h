#pragma once
//�ŏ��̕����̃C�x���g
namespace Ev{

//=====================================
//�C���g���C�x���g1�ŏ�
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
//�C���g���C�x���g2�O�̌�
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
//�C���g���C�x���g3�O�J����
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
//�C���g���C�x���g4F2�J����
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
//�C���g���C�x���g�Ō�^�C�g���R�[��
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
//�ŏ��̃C�x���g
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
//�C�x���g�J�b�g
//=====================================
class IntroCut : public Scene
{
public:
	IntroCut();
	VOID Update();
};
};