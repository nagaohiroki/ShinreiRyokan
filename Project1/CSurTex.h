#pragma once

class CSurTex
{
private:
	LPDIRECT3DSURFACE9 m_pTexSurface;//テクスチャから取得するサーフェース	
	LPDIRECT3DSURFACE9 m_pTexZ;		 //テクスチャ用のZ バッファー

	UINT W,H;
	D3DFORMAT Fmt;
	BOOL Z;

public:
	LPDIRECT3DTEXTURE9 m_pSurfTex;	 //返すよう
	//コンストラクタ
	CSurTex();
	//デストラクタ
	virtual ~CSurTex();
	//リセット
	VOID Reset();
	//レストア
	HRESULT Restore(LPDIRECT3DDEVICE9);
	//サーフェイス開始
	HRESULT Begin(LPDIRECT3DDEVICE9,int,D3DXVECTOR4*);
	//作成(dev,Zバッファの有無,横,縦,フォーマット
	HRESULT Create(LPDIRECT3DDEVICE9,BOOL,UINT,UINT,D3DFORMAT);
};