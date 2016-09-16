#pragma once
namespace Ev
{
//=============================================
//��
//=============================================
class Drug : public Scene
{
	CObjSound se;
	CObjSound Suzumusi;
	CObjSound gangan;
	GameText text;
	CObjMesh bottle;
	CObjMesh hitbox;
	int frame;
	int flag;
	int lightframe;
	AKey<D3DXVECTOR4> light;
public:	
	const TCHAR *name();
	Drug();
	VOID Set();
	VOID Update();
};
//=====================================
//�o�X���[���̃h�A
//=====================================
class bathdoor : public Scene
{
	CObjSound open;
	CObjSound close;
	CObjMesh hit;
	CObjMesh door;
	CObjMesh waku;
	int frame;
	AKey<float> aopen;
public:
	const TCHAR* name();
	bathdoor();
	VOID Update();
};
//=======================
//�o�X���[���̌�
//=======================
class DoorText : public Scene
{
	GameText text;
	CObjMesh hitbox;
	CObjSound gatya;
public:	
	const TCHAR *name();
	DoorText();
	VOID Update();
};

//=======================
//F2
//=======================
class F2_DoorText : public Scene
{
	GameText text;	
	GameText text1;
	CObjMesh hitbox;
	CObjSound gatya;
	CObjSound unlock;
public:	
	const TCHAR *name();
	F2_DoorText();
	VOID Update();
};

//=====================
//�_�[�c
//=====================
class Darts : public Scene
{
	CObjMesh drug;
	//�A�j���[�V�����t���[��
	int frame;
	//�_�[�c�̖{��
	enum{MAX = 3};
	//�\������_�[�c
	CObjMesh darts[MAX];
	//�����蔻�蔠
	CObjMesh hitbox;
	//�e�L�X�g
	GameText text;
	//���т�����ɓ���Ă���
	GameText textmasui;
	//���т�_�[�c
	GameText textmsdt;
	//�h���b�v
	CObjMesh drip;
	//��
	CObjSound se;
	//�A�j���[�V����
	AKey<float> adrip;
public:
	const TCHAR *name();
	Darts();	
	VOID Update();
};
//=====================
//�I
//=====================
class Dartsbord : public Scene
{
	BOOL SoundFlag;
	int frame;
	//�`��
	CObjMesh dartsbord;
	CObjMesh drug;
	//�����蔻��
	CObjMesh hit;
	//��
	CObjMesh center;
	//�T�E���h
	CObjSound se;
	//�e�L�X�g
	GameText text;
	//�A�j���[�V����
	AKey<float> py;//����
	AKey<float> rx;//��]
public:
	const TCHAR *name();
	Dartsbord();
	VOID Set();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};

};