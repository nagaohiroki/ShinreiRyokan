//======================================================================
//FVF
//======================================================================
//�R���X�g���N�^
FVF::FVF()
{
	m_pVertexBuffer = NULL;
}
//�f�X�g���N�^
FVF::~FVF()
{
	SAFE_RELEASE(m_pVertexBuffer);
}
//���_�o�b�t�@�̍쐬
HRESULT FVF::CreateVertex(LPDIRECT3DDEVICE9 dev)
{
	//FVF�̓ǂݍ���
	//�o�b�t�@�̓ǂݍ���
	if(FAILED(dev->CreateVertexBuffer(
		sizeof(CUSTOMVERTEX)*4,
		D3DUSAGE_WRITEONLY,
		FVF_CUSTOM,
		D3DPOOL_MANAGED,
		&m_pVertexBuffer,
		NULL )))
	{
		CFile().Debug(_T("FVF�擾���s\n"));
		return E_FAIL;
	}	
	return S_OK;
}
//���_�̃X�e�[�^�X���Z�b�g
HRESULT FVF::SetVertex(LPDIRECT3DVERTEXBUFFER9 vb)
{
	//�o�b�t�@�̏�����
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
		 CFile().Debug(_T("FVF���b�N���s\n"));
		 return E_FAIL;
	 }
	return S_OK;
}

//FVF��ǂݍ���
HRESULT FVF::Create(LPDIRECT3DDEVICE9 dev)
{
	
	HRESULT hr = S_OK;
	hr = CreateVertex(dev);
	if(FAILED(hr)){return E_FAIL;}
	hr = SetVertex(m_pVertexBuffer);
	if(FAILED(hr)){return E_FAIL;}
	return S_OK;
}

//�X�g���[���̃Z�b�g
VOID FVF::SetStream(LPDIRECT3DDEVICE9 dev)
{
	dev->SetStreamSource( 0,m_pVertexBuffer,0,sizeof(CUSTOMVERTEX));
	dev->SetFVF(FVF_CUSTOM);

}

//====================================================
//�e�N�X�`�����]
//====================================================
FVFMirror::FVFMirror(){}
HRESULT FVFMirror::SetVertex(LPDIRECT3DVERTEXBUFFER9 vb)
{
	//�o�b�t�@�̏�����
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
		 CFile().Debug(_T("FVF���b�N���s\n"));
		 return E_FAIL;
	 }
	return S_OK;
}
