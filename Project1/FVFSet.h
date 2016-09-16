#pragma once
//=============================================================================
//FVF設定
//=============================================================================
//FVF
class FVF
{
private:
	//FVFのタイプ
	enum{ FVF_CUSTOM = D3DFVF_XYZ| D3DFVF_TEX1 };
	//頂点バッファ
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;
	//頂点バッファの作成
	HRESULT CreateVertex(LPDIRECT3DDEVICE9);
protected:
	//バッファのステータス
	struct CUSTOMVERTEX
	{	
		float	x,y,z;	//頂点位置
		float	u,v;	//テクスチャ座標
	};	
	//バッファのステータスをセットする
	virtual HRESULT SetVertex(LPDIRECT3DVERTEXBUFFER9);

public:
	//コンストラクタ
	FVF();
	//デストラクタ
	virtual ~FVF();
	//作成
	HRESULT Create(LPDIRECT3DDEVICE9);
	//ストリームを準備
	VOID SetStream(LPDIRECT3DDEVICE9);	

};

//====================================================
//テクスチャ反転
//====================================================
class FVFMirror : public FVF
{
public:
	FVFMirror(); 
	HRESULT SetVertex(LPDIRECT3DVERTEXBUFFER9);
};