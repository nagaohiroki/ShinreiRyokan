#pragma once
class CObjSurf
{
	CSurTex* stex;

public:
	D3DFORMAT fmt;
	int pass;
	D3DXVECTOR4 color;
	UINT w,h;
	BOOL z;
	CObjSurf();
	virtual ~CObjSurf();
	VOID Set(MyLibrary*);
	VOID Begin(MyLibrary*);
	LPDIRECT3DTEXTURE9 Tex();
};