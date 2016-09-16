#pragma once

//======================================================
//フォントテクスチャ
//======================================================
class CFontTex
{
private:
		
public:
	LPDIRECT3DTEXTURE9 pTex;
	RECT rect;
	TCHAR c[2];
	CFontTex();
 	virtual ~CFontTex();
	HRESULT Create(const TCHAR*,LPDIRECT3DDEVICE9,TCHAR* ,int);

};