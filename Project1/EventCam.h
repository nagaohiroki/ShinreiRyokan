#pragma once
namespace Ev{
//=======================================
//カメラ
//=======================================
//固定カメラ範囲指定
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

//固定カメラ範囲指定なし
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
//プレイヤー追尾カメラ
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