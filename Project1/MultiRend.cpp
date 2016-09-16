//------------------------------------
//サーフェイスのステータス
//------------------------------------
CSTexState::CSTexState()
{
	m_bUse =TRUE;
	m_uiW = 4;
	m_uiH = 4;
	m_iPass = 0;
	m_bZ = FALSE;
	m_Fmt = D3DFMT_A8R8G8B8;
	m_vColor = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);

}

VOID CSTexState::Set(BOOL use,UINT w,UINT h,int pass,BOOL z,D3DFORMAT fmt,D3DXVECTOR4* color)
{
	m_bUse =use;
	m_uiW = w;
	m_uiH = h;
	m_iPass = pass;
	m_bZ = z;
	m_Fmt = fmt;
	m_vColor = *color;
}

//------------------------------------
//サーフェイスの要素
//------------------------------------
CSTex::CSTex()
{
	m_pTexSurface = NULL; // テクスチャから取得するサーフェース	
	m_pTexZ = NULL;		  // テクスチャ用のZ バッファー
	m_pSurfTex = NULL;	  //返すよう
	m_pState = NULL;//ステータス
}
CSTex::~CSTex()
{
	Reset();
}


HRESULT CSTex::Set(LPDIRECT3DDEVICE9 dev,CSTexState* State)
{
	m_pState = State; 
	if(m_pState->m_bZ == TRUE)
	{
		// テクスチャへのレンダリングに使うZバッファーの作成
		if (FAILED(dev->CreateDepthStencilSurface(
			m_pState->m_uiW,m_pState->m_uiH,			// Zバッファのサイズ
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
						m_pState->m_uiW,m_pState->m_uiH,			// テクスチャのサイズ 
						1,						// テクスチャレベルの数（本著では常に１に設定）
	     				D3DUSAGE_RENDERTARGET,	// レンダリングターゲットとして利用することを明示
						m_pState->m_Fmt,		// テクスチャフォーマット（RGBAの～モードを設定）
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

HRESULT CSTex::Begin(LPDIRECT3DDEVICE9 dev)
{
	if(FAILED(dev->SetRenderTarget(m_pState->m_iPass,m_pTexSurface))){return E_FAIL;}
	// テクスチャ用のZバッファを設定
	if(m_pTexZ != NULL)
	{
		if(FAILED(dev->SetDepthStencilSurface(m_pTexZ))){return E_FAIL;}
		if(FAILED(dev->Clear(0L,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DXCOLOR(m_pState->m_vColor.x,m_pState->m_vColor.y,m_pState->m_vColor.z,m_pState->m_vColor.w),
			1.0f, 0L))){return E_FAIL;}
	}
	return S_OK;
}

VOID CSTex::Reset()
{
	SAFE_RELEASE(m_pTexSurface);
	SAFE_RELEASE(m_pTexZ);
	SAFE_RELEASE(m_pSurfTex);
}
HRESULT CSTex::Restore(LPDIRECT3DDEVICE9 dev)
{
	if(FAILED(Set(dev,m_pState))){return E_FAIL;}
	return S_OK;
}
LPDIRECT3DTEXTURE9 CSTex::Retex()
{
	return m_pSurfTex;
}
//--------------------------------
//全体のサーフェイス
//--------------------------------
CSurf::CSurf()
{
	m_pBackbuffer = NULL; 
	m_pBackZ = NULL;
	m_ppCSTex = NULL;
	m_iNum = 0;
}
CSurf::~CSurf()
{
	if(m_ppCSTex != NULL)
	{
		int i;
		for(i=0;i<m_iNum;i++)
		{
			SAFE_DELETE(m_ppCSTex[i]);
		}
		SAFE_DELETE_ARRAY(m_ppCSTex);
	}
	SAFE_RELEASE(m_pBackbuffer);
	SAFE_RELEASE(m_pBackZ);	
}
HRESULT CSurf::Create(LPDIRECT3DDEVICE9 dev,int num)
{
	if(num <= 0){return E_FAIL;}
	m_iNum = num;
	m_ppCSTex = new CSTex*[m_iNum];
	int i;
	for(i = 0; i < num; i++)
	{
		m_ppCSTex[i] = NULL;
	}
	//バッファの保存
	if(FAILED(dev->GetRenderTarget(0, &m_pBackbuffer)))
	{
		CFile().Debug(_T("バックバッファー退避失敗\n"));
		return E_FAIL;
	}   
	if(FAILED(dev->GetDepthStencilSurface(&m_pBackZ)))
	{
		CFile().Debug(_T("深度バッファー退避失敗\n"));
		return E_FAIL;
	}
	return S_OK;
}
HRESULT CSurf::End(LPDIRECT3DDEVICE9 dev)
{
	//レンダリングをバックバッファに戻す
	if(FAILED(dev->SetRenderTarget(0,m_pBackbuffer))){return E_FAIL;}
	if(FAILED(dev->SetDepthStencilSurface(m_pBackZ))){return E_FAIL;}
	return S_OK;
}
HRESULT CSurf::Reset()
{
	SAFE_RELEASE(m_pBackbuffer);
	SAFE_RELEASE(m_pBackZ);	
	int i;
	for(i=0;i<m_iNum;i++)
	{
		m_ppCSTex[i]->Reset();
	}
	return S_OK;
}
HRESULT CSurf::Restore(LPDIRECT3DDEVICE9 dev)
{
	//バッファの保存
	if(FAILED(dev->GetRenderTarget(0, &m_pBackbuffer)))
	{
		CFile().Debug(_T("バックバッファー退避失敗\n"));
		return E_FAIL;
	}   
	if(FAILED(dev->GetDepthStencilSurface(&m_pBackZ)))
	{
		CFile().Debug(_T("深度バッファー退避失敗\n"));
		return E_FAIL;
	}
	int i;
	for(i = 0;i < m_iNum; i++)
	{
		if(m_ppCSTex[i] != NULL)
		{
			if(FAILED(m_ppCSTex[i]->Restore(dev))){return E_FAIL;}
		}
	}
	return S_OK;
}


HRESULT CSurf::Begin(int num,LPDIRECT3DDEVICE9 dev)
{
	if(FAILED(m_ppCSTex[num]->Begin(dev))){return E_FAIL;}
	return S_OK;
}

LPDIRECT3DTEXTURE9 CSurf::Retex(int num)
{
	return m_ppCSTex[num]->Retex();
}

//データのロードと破棄
HRESULT CSurf::Load(LPDIRECT3DDEVICE9 dev,CSTexState* ppState)
{
	int i;
	for(i=0;i<m_iNum;i++)
	{
		if(ppState[i].m_bUse == TRUE)
		{
			if(m_ppCSTex[i] == NULL)
			{
				m_ppCSTex[i] = new CSTex;
				if(FAILED(m_ppCSTex[i]->Set(dev,&ppState[i])))
				{
					return E_FAIL;
				}
			}
		}
		else
		{
			SAFE_DELETE(m_ppCSTex[i]);
		}
	}
	return S_OK;
}