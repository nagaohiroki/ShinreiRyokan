//コンストラクタ
CSurTex::CSurTex()
{
	m_pTexSurface = NULL;//テクスチャから取得するサーフェース	
	m_pTexZ = NULL;		 //テクスチャ用のZ バッファー
	m_pSurfTex = NULL;	 //返すよう

	W = 0;
	H = 0;
	Fmt = D3DFMT_A8R8G8B8;
	Z = FALSE;

}
//デストラクタ
CSurTex::~CSurTex(){Reset();}
//リセット
VOID CSurTex::Reset()
{	
	SAFE_RELEASE(m_pTexSurface);
	SAFE_RELEASE(m_pTexZ);
	SAFE_RELEASE(m_pSurfTex);
}

//レストア
HRESULT CSurTex::Restore(LPDIRECT3DDEVICE9 dev)
{
	HRESULT hr = Create(dev,Z,W,H,Fmt);
	if(FAILED(hr)){return E_FAIL;}
	return S_OK;
}
//dev,Zバッファの有無,横,縦,パス,フォーマット,バックバッファカラー
HRESULT CSurTex::Create(LPDIRECT3DDEVICE9 dev,BOOL z,UINT w,UINT h,D3DFORMAT fmt)
{

	W = w;
	H = h;
	Fmt = fmt;
	Z = z;
	if(z == TRUE)
	{
		// テクスチャへのレンダリングに使うZバッファーの作成
		if (FAILED(dev->CreateDepthStencilSurface(
			w,h,			// Zバッファのサイズ
			D3DFMT_D16,
			D3DMULTISAMPLE_NONE,
			0,
			FALSE,					// Zバッファの制御方法の指定（常に0にしておく）
			&m_pTexZ,			// Zバッファの格納先を示すポインタのアドレス
			NULL)))					// 常にNULLを指定
		{			
			CFile().Debug(_T("サーフェイスの作成に失敗しました\n"));
			return E_FAIL;
		}
	}
	// レンダリングターゲットとして使用するテクスチャの作成
	if( FAILED(dev->CreateTexture(
						w,h,			// テクスチャのサイズ 
						1,						// テクスチャレベルの数
	     				D3DUSAGE_RENDERTARGET,	// レンダリングターゲットとして利用することを明示
						fmt,		// テクスチャフォーマット（RGBAの～モードを設定）
	      				D3DPOOL_DEFAULT,		// テクスチャメモリの確保方法（D3DPOOL_DEFAULTが無難）
		  				&m_pSurfTex,		// テクスチャの格納先を示すポインタのアドレス
						NULL)))					// 常にNULLを指定
	{
		CFile().Debug(_T("サーフェイステクスチャの作成に失敗しました\n"));
		return E_FAIL;
	}	
	// テクスチャからレンダリングターゲットにするサーフェースの取得
	if( FAILED(m_pSurfTex->GetSurfaceLevel(0, &m_pTexSurface)))
	{
		CFile().Debug(_T("サーフェイスの取得に失敗しました\n"));
		return E_FAIL;
	}	
	return S_OK;
}
//サーフェイス開始
HRESULT CSurTex::Begin(LPDIRECT3DDEVICE9 dev,int pass,D3DXVECTOR4* color)
{
	if(FAILED(dev->SetRenderTarget(pass,m_pTexSurface))){return E_FAIL;}
	// テクスチャ用のZバッファを設定
	if(m_pTexZ != NULL)
	{
		if(FAILED(dev->SetDepthStencilSurface(m_pTexZ))){return E_FAIL;}
		if(FAILED(dev->Clear(0L,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DXCOLOR(color->x,color->y,color->z,color->w),1.0f, 0L))){return E_FAIL;}
	}
	return S_OK;
}
