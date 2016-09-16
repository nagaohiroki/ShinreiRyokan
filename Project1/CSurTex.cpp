//�R���X�g���N�^
CSurTex::CSurTex()
{
	m_pTexSurface = NULL;//�e�N�X�`������擾����T�[�t�F�[�X	
	m_pTexZ = NULL;		 //�e�N�X�`���p��Z �o�b�t�@�[
	m_pSurfTex = NULL;	 //�Ԃ��悤

	W = 0;
	H = 0;
	Fmt = D3DFMT_A8R8G8B8;
	Z = FALSE;

}
//�f�X�g���N�^
CSurTex::~CSurTex(){Reset();}
//���Z�b�g
VOID CSurTex::Reset()
{	
	SAFE_RELEASE(m_pTexSurface);
	SAFE_RELEASE(m_pTexZ);
	SAFE_RELEASE(m_pSurfTex);
}

//���X�g�A
HRESULT CSurTex::Restore(LPDIRECT3DDEVICE9 dev)
{
	HRESULT hr = Create(dev,Z,W,H,Fmt);
	if(FAILED(hr)){return E_FAIL;}
	return S_OK;
}
//dev,Z�o�b�t�@�̗L��,��,�c,�p�X,�t�H�[�}�b�g,�o�b�N�o�b�t�@�J���[
HRESULT CSurTex::Create(LPDIRECT3DDEVICE9 dev,BOOL z,UINT w,UINT h,D3DFORMAT fmt)
{

	W = w;
	H = h;
	Fmt = fmt;
	Z = z;
	if(z == TRUE)
	{
		// �e�N�X�`���ւ̃����_�����O�Ɏg��Z�o�b�t�@�[�̍쐬
		if (FAILED(dev->CreateDepthStencilSurface(
			w,h,			// Z�o�b�t�@�̃T�C�Y
			D3DFMT_D16,
			D3DMULTISAMPLE_NONE,
			0,
			FALSE,					// Z�o�b�t�@�̐�����@�̎w��i���0�ɂ��Ă����j
			&m_pTexZ,			// Z�o�b�t�@�̊i�[��������|�C���^�̃A�h���X
			NULL)))					// ���NULL���w��
		{			
			CFile().Debug(_T("�T�[�t�F�C�X�̍쐬�Ɏ��s���܂���\n"));
			return E_FAIL;
		}
	}
	// �����_�����O�^�[�Q�b�g�Ƃ��Ďg�p����e�N�X�`���̍쐬
	if( FAILED(dev->CreateTexture(
						w,h,			// �e�N�X�`���̃T�C�Y 
						1,						// �e�N�X�`�����x���̐�
	     				D3DUSAGE_RENDERTARGET,	// �����_�����O�^�[�Q�b�g�Ƃ��ė��p���邱�Ƃ𖾎�
						fmt,		// �e�N�X�`���t�H�[�}�b�g�iRGBA�́`���[�h��ݒ�j
	      				D3DPOOL_DEFAULT,		// �e�N�X�`���������̊m�ە��@�iD3DPOOL_DEFAULT������j
		  				&m_pSurfTex,		// �e�N�X�`���̊i�[��������|�C���^�̃A�h���X
						NULL)))					// ���NULL���w��
	{
		CFile().Debug(_T("�T�[�t�F�C�X�e�N�X�`���̍쐬�Ɏ��s���܂���\n"));
		return E_FAIL;
	}	
	// �e�N�X�`�����烌���_�����O�^�[�Q�b�g�ɂ���T�[�t�F�[�X�̎擾
	if( FAILED(m_pSurfTex->GetSurfaceLevel(0, &m_pTexSurface)))
	{
		CFile().Debug(_T("�T�[�t�F�C�X�̎擾�Ɏ��s���܂���\n"));
		return E_FAIL;
	}	
	return S_OK;
}
//�T�[�t�F�C�X�J�n
HRESULT CSurTex::Begin(LPDIRECT3DDEVICE9 dev,int pass,D3DXVECTOR4* color)
{
	if(FAILED(dev->SetRenderTarget(pass,m_pTexSurface))){return E_FAIL;}
	// �e�N�X�`���p��Z�o�b�t�@��ݒ�
	if(m_pTexZ != NULL)
	{
		if(FAILED(dev->SetDepthStencilSurface(m_pTexZ))){return E_FAIL;}
		if(FAILED(dev->Clear(0L,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DXCOLOR(color->x,color->y,color->z,color->w),1.0f, 0L))){return E_FAIL;}
	}
	return S_OK;
}
