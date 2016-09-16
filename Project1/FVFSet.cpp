//======================================================================
//FVF
//======================================================================
//コンストラクタ
FVF::FVF()
{
	m_pVertexBuffer = NULL;
}
//デストラクタ
FVF::~FVF()
{
	SAFE_RELEASE(m_pVertexBuffer);
}
//頂点バッファの作成
HRESULT FVF::CreateVertex(LPDIRECT3DDEVICE9 dev)
{
	//FVFの読み込み
	//バッファの読み込み
	if(FAILED(dev->CreateVertexBuffer(
		sizeof(CUSTOMVERTEX)*4,
		D3DUSAGE_WRITEONLY,
		FVF_CUSTOM,
		D3DPOOL_MANAGED,
		&m_pVertexBuffer,
		NULL )))
	{
		CFile().Debug(_T("FVF取得失敗\n"));
		return E_FAIL;
	}	
	return S_OK;
}
//頂点のステータスをセット
HRESULT FVF::SetVertex(LPDIRECT3DVERTEXBUFFER9 vb)
{
	//バッファの初期化
	CUSTOMVERTEX v[4]=
	{
		{-0.5f, 0.5f,0.0f,0.0f,0.0f},
		{ 0.5f, 0.5f,0.0f,1.0f,0.0f},
		{-0.5f,-0.5f,0.0f,0.0f,1.0f},
		{ 0.5f,-0.5f,0.0f,1.0f,1.0f},
	};
	 VOID *pData;
     if(SUCCEEDED(vb->Lock(0, sizeof(CUSTOMVERTEX)*4, (VOID**)&pData, 0)))
	 {
        memcpy(pData,v, sizeof(CUSTOMVERTEX)*4);
        vb->Unlock();
	 }
	 else
	 {
		 CFile().Debug(_T("FVFロック失敗\n"));
		 return E_FAIL;
	 }
	return S_OK;
}

//FVFを読み込み
HRESULT FVF::Create(LPDIRECT3DDEVICE9 dev)
{
	
	HRESULT hr = S_OK;
	hr = CreateVertex(dev);
	if(FAILED(hr)){return E_FAIL;}
	hr = SetVertex(m_pVertexBuffer);
	if(FAILED(hr)){return E_FAIL;}
	return S_OK;
}

//ストリームのセット
VOID FVF::SetStream(LPDIRECT3DDEVICE9 dev)
{
	dev->SetStreamSource( 0,m_pVertexBuffer,0,sizeof(CUSTOMVERTEX));
	dev->SetFVF(FVF_CUSTOM);

}

//====================================================
//テクスチャ反転
//====================================================
FVFMirror::FVFMirror(){}
HRESULT FVFMirror::SetVertex(LPDIRECT3DVERTEXBUFFER9 vb)
{
	//バッファの初期化
	CUSTOMVERTEX v[4]=
	{
		{-0.5f, 0.5f,0.0f,1.0f,0.0f},
		{ 0.5f, 0.5f,0.0f,0.0f,0.0f},
		{-0.5f,-0.5f,0.0f,1.0f,1.0f},
		{ 0.5f,-0.5f,0.0f,0.0f,1.0f},
	};
	 VOID *pData;
     if(SUCCEEDED(vb->Lock(0, sizeof(CUSTOMVERTEX)*4, (VOID**)&pData, 0)))
	 {
        memcpy(pData,v, sizeof(CUSTOMVERTEX)*4);
        vb->Unlock();
	 }
	 else
	 {
		 CFile().Debug(_T("FVFロック失敗\n"));
		 return E_FAIL;
	 }
	return S_OK;
}
