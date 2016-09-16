#pragma once

class CBullet
{
private:
	TCHAR txt[500];
	CObjMesh dobj;
	
public:
	CObjSound SEHit;
	float Energy;
	float G;
	BOOL Move;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 vec;
	CObjMesh Bullet;
	D3DXMATRIX mC;
	CBullet();
	VOID Init(D3DXVECTOR3*,D3DXVECTOR3*);
	VOID Reset();
	VOID draw(MyLibrary*);
	VOID HitEvent(std::vector<CollObj*>*,MyLibrary* );
	VOID Debug(int,TCHAR*);
	VOID Attach(D3DXMATRIX*);

};