#pragma once

class CSurface
{
private:
	typedef std::vector<CSurTex*> sur;
	sur Sur;
	//バックバッファ
	LPDIRECT3DSURFACE9 m_pBackbuffer;
	//バックバッファ用のZバッファー
	LPDIRECT3DSURFACE9 m_pBackZ;	 
public:
	CSurface();
	virtual ~CSurface();	
	HRESULT Create(LPDIRECT3DDEVICE9);
	HRESULT End(LPDIRECT3DDEVICE9);
	CSurTex* Set(LPDIRECT3DDEVICE9,BOOL,UINT,UINT,D3DFORMAT);
	HRESULT Reset();
	HRESULT Restore(LPDIRECT3DDEVICE9);
};