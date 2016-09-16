#pragma once
namespace Ev{
//=======================================
//�J����
//=======================================
//�Œ�J�����͈͎w��
class CamFix : public Scene
{
	CObjMesh Eye;
	CObjMesh At;
	CObjMesh Hit;
	VOID Init();
public:
	const TCHAR* name();
	CamFix();
	CamFix(D3DXVECTOR3*,D3DXVECTOR3*);
	VOID Update();
};

//�Œ�J�����͈͎w��Ȃ�
class CamFixFree : public Scene
{
	CObjMesh Eye;
	CObjMesh At;
	VOID Init();
public:
	const TCHAR* name();
	CamFixFree();
	CamFixFree(D3DXVECTOR3*,D3DXVECTOR3*);
	VOID Update();
};
//�v���C���[�ǔ��J����
class CamChar : public Scene
{
	CObjMesh pCam;
public:
	const TCHAR* name();
	CamChar();
	CamChar(D3DXVECTOR3* Pos);
	VOID Set();
	VOID Update();
};
}//namespace Ev