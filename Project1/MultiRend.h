#pragma once//ヘッダーの重複防止
//=============================================================================
//マルチレンダリングターゲット
//=============================================================================
//サーフェイスのステータス
class CSTexState
{
public:
	BOOL		m_bUse;
	UINT        m_uiW;
	UINT        m_uiH;
	int         m_iPass;
	BOOL        m_bZ;
	D3DFORMAT   m_Fmt;
	D3DXVECTOR4 m_vColor;	
	CSTexState();
	VOID Set(BOOL,UINT,UINT,int,BOOL,D3DFORMAT,D3DXVECTOR4*);
};
//サーフェイスの要素
class CSTex
{
private:
	LPDIRECT3DSURFACE9 m_pTexSurface;//テクスチャから取得するサーフェース	
	LPDIRECT3DSURFACE9 m_pTexZ;		 //テクスチャ用のZ バッファー
	LPDIRECT3DTEXTURE9 m_pSurfTex;	 //返すよう
public:
	CSTexState* m_pState;
	CSTex();
	virtual ~CSTex();
	HRESULT Set(LPDIRECT3DDEVICE9,CSTexState*);
	HRESULT Begin(LPDIRECT3DDEVICE9);
	VOID Reset();
	HRESULT Restore(LPDIRECT3DDEVICE9);
	LPDIRECT3DTEXTURE9 Retex();	
};
//サーフェイス
class CSurf
{
private:
	LPDIRECT3DSURFACE9 m_pBackbuffer;//バックバッファ
	LPDIRECT3DSURFACE9 m_pBackZ;	 //バックバッファ用のZバッファー
public:	
	int m_iNum;
	CSTex** m_ppCSTex;
	CSurf();
	virtual ~CSurf();
	HRESULT Create(LPDIRECT3DDEVICE9,int);//作成
	HRESULT End(LPDIRECT3DDEVICE9);//サーフェイス終了
	HRESULT Reset();//リセット
	HRESULT Restore(LPDIRECT3DDEVICE9);//リセット後取得
	HRESULT Begin(int,LPDIRECT3DDEVICE9);//サーフェイス開始
	LPDIRECT3DTEXTURE9 Retex(int);//テクスチャを返す
	HRESULT Load(LPDIRECT3DDEVICE9,CSTexState*);//データのロードと破棄
};