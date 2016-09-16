CSurface::CSurface()
{
	m_pBackbuffer = NULL;//バックバッファ
	m_pBackZ = NULL;	 //バックバッファ用のZバッファー

}
CSurface::~CSurface()
{
	for(sur::iterator it = Sur.begin(); it != Sur.end(); ++it)
	{
		SAFE_DELETE((*it));
	}
	
	SAFE_RELEASE(m_pBackbuffer);
	SAFE_RELEASE(m_pBackZ);	
}
HRESULT CSurface::Create(LPDIRECT3DDEVICE9 dev)
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
	return S_OK;
}
HRESULT CSurface::End(LPDIRECT3DDEVICE9 dev)
{
	//レンダリングをバックバッファに戻す
	if(FAILED(dev->SetRenderTarget(0,m_pBackbuffer))){return E_FAIL;}
	if(FAILED(dev->SetDepthStencilSurface(m_pBackZ))){return E_FAIL;}
	return S_OK;
}

CSurTex* CSurface::Set(LPDIRECT3DDEVICE9 dev,BOOL z,UINT w,UINT h,D3DFORMAT fmt)
{
	CSurTex *ct = new CSurTex;
	HRESULT hr = ct->Create(dev,z,w,h,fmt);
	if(FAILED(hr)){return NULL;}
	Sur.push_back(ct);
	return ct;
}

HRESULT CSurface::Reset()
{	
	SAFE_RELEASE(m_pBackbuffer);
	SAFE_RELEASE(m_pBackZ);	
	for(sur::iterator it = Sur.begin(); it != Sur.end(); ++it)
	{
		if((*it)){(*it)->Reset();}
	}
	return S_OK;
}
HRESULT CSurface::Restore(LPDIRECT3DDEVICE9 dev)
{
	for(sur::iterator it = Sur.begin(); it != Sur.end(); ++it)
	{
		if((*it)){(*it)->Restore(dev);}
	}
	return S_OK;
}
