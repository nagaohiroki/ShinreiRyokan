#pragma once
namespace Ev
{
//=========================================
//�g�C���̃���	
//=========================================
class ToileMemo : public Scene 
{
	enum{MEMO_MAX = 4};
	CObjMesh hitbox;
	CObjFVF memo[MEMO_MAX];
	GameText text;
public:
	const TCHAR *name();
	ToileMemo(int);
	VOID Update();
};
//=========================================
//�g�C���h�A
//=========================================
class Rest_Men_door:public Scene
{
private:
	int frame;
	int flag;
	AKey<float> door;
	CObjMesh pDoor;
	CObjMesh pGreen;
	CObjMesh pRed;
	CObjSound gan;
public:
	const TCHAR *name();
	//����
	Rest_Men_door();
	VOID Update();
};
//=========================================
//�g�C��	
//=========================================
class Rest_Men_Toile : public Scene
{
	CObjMesh pToile;
	CObjMesh pHuta;
	CObjMesh hitbox;
	GameText text;
	GameText text1;
	CObjSound gan;
	CObjSound oop;
	CObjSound water;
	int flag;	//�i�s�t���O
	int gtframe;
	int hutaframe;
	int GOFlag;//0���擾1�Q�[���I�[�o�[
	//�g�C���ӂ�
	AKey<float> rot;
	//gt�A�j��
	AKey<float> prot;
	AKey<D3DXVECTOR3> pos;
public:
	Rest_Men_Toile(int );
	VOID Set();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};
};