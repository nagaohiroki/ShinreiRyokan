//=================================================================
//�G�t�F�N�g
//=================================================================
//�G�t�F�N�g�̐ݒ�
CEffect::CEffect()
{
	//�|�C���^
	m_pEffect=NULL;	
	//�n���h��
	m_hTechnique=NULL;
	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);
	D3DXMatrixIdentity(&matPxV);	
	ShadowFlag=TRUE;	
	//begin���g�p���Ă��邩�̃t���O	
	BeginFlag=FALSE;
	fxPass=0;
	PassFlag=FALSE;
	CullPos=D3DXVECTOR3(0,0,0);
	Handle=NULL;
	pass=0;
	Fade = 1.0f;

	Tone = D3DXVECTOR4(1.0f,1.8f,5.0f,1.0f);
	MirrorPass = 0;
	MirrorFlag = FALSE;
}

CEffect::~CEffect()
{
	SAFE_DELETE_ARRAY(Handle);
	SAFE_RELEASE(m_pEffect);	//�G�t�F�N�g�̔j��
}

//���Z�b�g�O�ɍs��
HRESULT CEffect::Reset()
{
	if(m_pEffect != NULL)
	{
		if(FAILED(m_pEffect->OnLostDevice()))
		{
			CFile().Debug(_T("Effect���Z�b�g���s\n"));
			return E_FAIL;
		}
	}
	return S_OK;

}
//���Z�b�g��ɍĎ擾
HRESULT CEffect::Restore()
{
	if(m_pEffect != NULL)
	{
		if(FAILED(m_pEffect->OnResetDevice()))
		{
			CFile().Debug(_T("Effect���Z�b�g��擾���s\n"));
			return E_FAIL;
		}
	}	
	return S_OK;
}
//�n���h���̃Z�b�g
HRESULT CEffect::SetHandle()
{
	m_hTechnique = m_pEffect->GetTechniqueByName("TShader");
	//�p�����[�^�̓ǂݍ���
	D3DXPARAMETER_DESC ParamDesc;
	D3DXEFFECT_DESC desc;
	m_pEffect->GetDesc(&desc);	
	D3DXHANDLE hand = NULL;
	Handle = new D3DXHANDLE[prm::PRM_MAX];
	UINT i;
	for(i=0;i<prm::PRM_MAX;i++)
	{
		hand = m_pEffect->GetParameter(NULL,i);
		if(FAILED(m_pEffect->GetParameterDesc(hand,&ParamDesc)))
		{
			CFile().Debug(_T("Effect�̃p�����[�^�̎擾���s\n"));
			return E_FAIL;
		}
		Handle[i] = NULL;
		Handle[i] = m_pEffect->GetParameterByName(NULL,ParamDesc.Name);
	}
	//�K�E�X�̏d��
	SetGaussWeight(0.001f);
	return S_OK;
}
//����������G�t�F�N�g�t�@�C����ǂݍ���
HRESULT CEffect::Create(LPDIRECT3DDEVICE9 dev,char* ptr,UINT size)
{
	//�G�t�F�N�g���쐬
	if(FAILED(D3DXCreateEffect(
		dev,
		ptr,
		size,	
		NULL,
		NULL,
		D3DXSHADER_SKIPVALIDATION,
		NULL,
		&m_pEffect,
		NULL)))
	{
		CFile().Debug(_T("�G�t�F�N�g�쐬���s\n"));
		return E_FAIL;
	}
	//�p�����[�^���n���h���ɃZ�b�g
	if(FAILED(SetHandle())){return E_FAIL;}
	return S_OK;
}
//�t�@�C������G�t�F�N�g���쐬
HRESULT CEffect::Create(LPDIRECT3DDEVICE9 dev)
{
	
	//�G�t�F�N�g���쐬
	if(FAILED(D3DXCreateEffectFromFile(
		dev,
		_T(".\\mydata\\.\\HLSL\\.\\main_hlsl.cfx"),
		NULL,
		NULL,
		D3DXSHADER_SKIPVALIDATION,
		NULL,
		&m_pEffect,
		NULL)))
	{
		CFile().Debug(_T("HLSL�ǂݍ��ݎ��s\n"));
		return E_FAIL;
	}
	//�p�����[�^���n���h���ɃZ�b�g
	if(FAILED(SetHandle())){return E_FAIL;}
	return S_OK;
}

//�e�p�����[�^��Ԃ�
D3DXHANDLE CEffect::Hn(size_t n)
{
	return Handle[n];
}

//�X�|�b�g���C�g�̃x�N�g���ƈʒu
VOID CEffect::UpdatePointLight()
{
	D3DXVECTOR3 v;
	//�X�|�b�g���C�g�̃x�N�g��
	D3DXVec3Normalize(&v,&(PSL.Pos - PSL.Vec));
	m_pEffect->SetVector(Hn(prm::float4_PLightPos),
	&D3DXVECTOR4(PSL.Pos.x,PSL.Pos.y,PSL.Pos.z,PSL.dis));//w�͌�����
	m_pEffect->SetVector(Hn(prm::float4_PLightVec),
	&D3DXVECTOR4(v.x,v.y,v.z,PSL.Lcos));

}

//�|�C���g���C�g
VOID CEffect::SetPLCol(D3DXVECTOR4* c)
{
	
	D3DXVECTOR4 Dif;
	//�f�t���[�Yw��0.0f�ȉ����ƃ��C�g����
	Dif.x=c->x * PSL.Col.x * PSL.Col.w;
	Dif.y=c->y * PSL.Col.y * PSL.Col.w;
	Dif.z=c->z * PSL.Col.z * PSL.Col.w;
	Dif.w=0.0f;
	m_pEffect->SetVector(Hn(prm::float4_PLightDif),&D3DXVECTOR4(
		c->x * PSL.Col.x * PSL.Col.w,
		c->y * PSL.Col.y * PSL.Col.w,
		c->z * PSL.Col.z * PSL.Col.w,
		0.0f));
	
}

VOID CEffect::UpdateLight()
{	
#if 0
	//�ʏ�̃V���h�E�}�b�v
	if(Ls==*L){return;}
	Ls=*L;
	//���C�g���_�̃J�������Z�b�g
	D3DXMATRIX mLView;
	D3DXMATRIX mLProj;
    D3DXMatrixLookAtLH(&mLView,
		&Ls.Pos,
		&Ls.At,
		&D3DXVECTOR3( 0,1.0f,0));
    D3DXMatrixPerspectiveFovLH( &mLProj,
		D3DXToRadian(Ls.Pars),
		1.0f,
		Ls.Near,
		Ls.Far );	
	D3DXMatrixMultiply(&matLight,&mLView,&mLProj);
	m_pEffect->SetMatrix(Hn(HN_mLight),&matLight);
#else
	D3DXVECTOR3 Eye = cam.Eye + Ls.EyePlus;
	D3DXVECTOR3 Lvec(Ls.At-Ls.Pos);
	D3DXVECTOR3 Cvec(cam.At-cam.Eye);
	D3DXVec3Normalize(&Lvec,&Lvec);
	D3DXVec3Normalize(&Cvec,&Cvec);
	//LiSPSM
	Lisp.MatLiSPSM(
		&matLight,
		&matView,
		&Lvec,
		&Cvec,
		&Eye,
		D3DXToRadian(Ls.Pars),
		cam.wh.x/cam.wh.y,
		0.1f,Ls.Far
		);
	m_pEffect->SetMatrix(Hn(prm::float4x4_mLight),&matLight);

#endif
}
D3DXVECTOR3 CEffect::LightCol()
{
	return D3DXVECTOR3(Ls.Col.x,Ls.Col.y,Ls.Col.z);
}
VOID CEffect::LightLamSpc(D3DXMATRIX* m,float amb)
{
	if(m_pEffect)
	{
	
		//���C�g�̈ʒu�ƃJ�����̈ʒu(���[�J��)
		D3DXVECTOR4 v;
		D3DXMatrixIdentity(&mL);
		//�����o�[�g���˂̃Z�b�g
		D3DXMatrixInverse(&mL,NULL,m);
		D3DXVec4Transform(&v,&D3DXVECTOR4(Ls.Pos,1.0f),&mL);
		D3DXVec4Normalize(&v,&v );
		v.w = Ls.Col.w * 0.5f * amb;//�A�r�G���g�̋���
		m_pEffect->SetVector(Hn(prm::float4_vLightDir),&v );

		//���ʔ���
		D3DXMatrixMultiply(&mL,m,&matView);
		D3DXMatrixInverse(&mL,NULL,&mL);
		v=D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
		D3DXVec4Transform(&v,&v,&mL);
		m_pEffect->SetVector(Hn(prm::float3_vEyePos),&v);
		
	}

}

//�e�̔Z���ƃo�C�A�X
VOID CEffect::ShadowBias(float bias,float shadow)
{
	if(m_pEffect)
	{
		
		m_pEffect->SetVector(Hn(prm::float4_SBias),&D3DXVECTOR4(bias * Ls.Bias,shadow * Ls.Shadow,0,0));
		
	}
}

VOID CEffect::UpdateFog()
{
	//�����t�H�O
	float fr = Fs.Far - 2.0f;//�Œ�����
	float f  =(fr-(Fs.Near - 1.0f));
	m_pEffect->SetInt(Hn(prm::int_vFogUse),Fs.use);//�I���I�t
	m_pEffect->SetVector(Hn(prm::float4_vFog),&D3DXVECTOR4(fr/f,-1.0f/f,0,0));//�j�A�p�[
	m_pEffect->SetVector(Hn(prm::float4_vFogColor),&D3DXVECTOR4(Fs.Col.x,Fs.Col.y,Fs.Col.z,0));//�F
	
}	

VOID CEffect::UpdateCam()
{
	ShadowPassNum = 0;//�p�X�̕ύX(�ʏ�`��)
	//�r���[�̐ݒ�
	D3DXMatrixLookAtLH(&matView,&cam.Eye,&cam.At,&cam.Up);
	//�@���e�s���ݒ�B
	//�@����p�A�A�X�y�N�g��A���o�N���b�s���O�p�̍Őڋߋ����ƍŉ��������̎l���K�v
	D3DXMatrixPerspectiveFovLH(	
		&matProj,
		D3DXToRadian(cam.Pars),	// ����p
		cam.wh.x/cam.wh.y,		// �A�X�y�N�g��
		cam.Near,		// �ŋߐڋ���
		cam.Far);	// �ŉ�������
	// �r���[�}�g���N�X�̐ݒ�
	D3DXMatrixMultiply(&matPxV,&matView,&matProj);	
	m_pEffect->SetMatrix(Hn(prm::float4x4_mVP),&matPxV);
	//�J�����O
	D3DXVECTOR3 nvec;
	D3DXVec3Normalize(&nvec,&(cam.At - cam.Eye));
	CullPos = cam.Eye + nvec * cam.Far;
	
}	

//�e�G�t�F�N�g
//���[���h�g�����X
VOID CEffect::mWVP(D3DXMATRIX *m)
{
	if(m_pEffect)
	{
		m_pEffect->SetMatrix(Hn(prm::float4x4_mW),m);
	}

}


//���b�V���̃J���[
VOID CEffect::vCol(D3DXVECTOR4 *vec)
{
	if(m_pEffect)
	{
		m_pEffect->SetVector(Hn(prm::float4_vColor),vec);
	}
}

//�X�y�L�����J���[
VOID CEffect::SpCol(D3DXVECTOR4 *vec)
{
	if(m_pEffect)
	{
		m_pEffect->SetVector(Hn(prm::float4_SP),vec);
	}
}

//�e�N�X�`�����Z�b�g
VOID CEffect::Tex(LPDIRECT3DTEXTURE9 pTex)
{
	if(m_pEffect)
	{
		if(pTex)
		{
			m_pEffect->SetTexture(Hn(prm::texture_Tex),pTex);
		}
	}
}

//=================================================================
//�V���h�E�}�b�v
//================================================================
//�p�X��ύX
//�V���h�E�}�b�v�r�M��
VOID CEffect::BeginSh()
{
	ShadowPassNum = 1;
	
}

VOID CEffect::ShadowMapSet(LPDIRECT3DTEXTURE9 tex)
{
	if(m_pEffect)
	{
		if(tex)
		{
			m_pEffect->SetTexture(Hn(prm::texture_ShadowTex),tex);
		}
	}
	ShadowPassNum = 0;
}

//====================================================================
//�o���v�}�b�v
//====================================================================
//�@���}�b�v(���ヂ�f���Ɋ֘A�����e�N�X�`�����͂�)
VOID CEffect::MTex(LPDIRECT3DTEXTURE9 pTex)
{	
	if(m_pEffect)
	{
		if(pTex)
		{
			m_pEffect->SetTexture( Hn(prm::texture_NormalTex),pTex);
		}
	}
}

//=======================================================
//�p�X�̐ݒ�
//=======================================================
//�p�X���̕ύX��m�点��
VOID CEffect::CommitChange()
{
	if(m_pEffect)
	{
		m_pEffect->CommitChanges();
	}
}
VOID CEffect::begin()
{
	if(m_pEffect)
	{
		if(BeginFlag)
		{
			m_pEffect->EndPass();
			m_pEffect->End();
			BeginFlag=FALSE;
			PassFlag=TRUE;//�p�X����
		}
		m_pEffect->SetTechnique( m_hTechnique );
		m_pEffect->Begin(&pass, 0 );
		BeginFlag=TRUE;
	}
}

//�p�X�̕ύX���������ꍇ�ύX����
VOID CEffect::BeginPass(int Pass)
{
	if(m_pEffect)
	{
		if(fxPass != Pass || PassFlag == TRUE)
		{
			m_pEffect->EndPass();
			fxPass=Pass;
			m_pEffect->BeginPass(Pass);
			PassFlag=FALSE;//�p�X���A
		}
	}
}
//������J�����O
BOOL CEffect::Culling(D3DXVECTOR3* Pos,float len)
{
	D3DXVECTOR3 vec;
	D3DXVec3Normalize(&vec,&CullPos);
	//����
	if(D3DXVec3Dot(Pos,&vec) > len + cam.Far){	return TRUE;}
	//���̒�
	if(D3DXVec3LengthSq(&(*Pos - CullPos)) > (len + cam.Far) * (len + cam.Far)){	return TRUE;}

	return FALSE;
}

//�g�[���}�b�s���O
VOID CEffect::ToneMap()
{
	if(m_pEffect)
	{
		m_pEffect->SetVector(Hn(prm::float4_PixelUV),&Tone);
	}
}
//�u���[���J���[
VOID CEffect::BloomColor(D3DXVECTOR4* bcolor)
{
	if(m_pEffect)
	{
		m_pEffect->SetVector(Hn(prm::float4_BloomColor),bcolor);
	}
}

//�K�E�X�̃}�b�v�T�C�Y
VOID CEffect::SetGaussMap(float x,float y)
{	
	if(m_pEffect)
	{
		m_pEffect->SetVector(Hn(prm::float4_GaussMap),&D3DXVECTOR4(1.0f/x,1.0f/y,0.0f,0.0f));
	}
}
//�K�E�X�̏d��
VOID CEffect::SetGaussWeight(float dis)
{
	if(m_pEffect)
	{
		const int W_NUM = 6;
		float w[W_NUM];
		int i;
		float Pos=0.0f;
		float total=0.0f;
			for(i = 0;i < W_NUM;i++)
		{
			Pos = 2.0f * (float)i;
			w[i] = expf(-Pos * Pos * dis);
			total += w[i];
		}
		for(i = 0;i < W_NUM;i++)
		{
			w[i] = w[i] / total;
		}
		
		for(i = 1;i < W_NUM;i++)
		{
			w[i] *= 0.5f;
		}
		m_pEffect->SetFloatArray(Hn(prm::float_w),w,6);

	}
}


//�X�N���[���p
VOID CEffect::ScreenView(LPDIRECT3DDEVICE9 dev,UINT w,UINT h)
{
	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	m._11 = (2.0f / (float)w);
	m._22 = (2.0f / (float)h);
	if(m_pEffect)
	{
		m_pEffect->SetMatrix(Hn(prm::float4x4_mVP),&m);
	}
	//�r���[�|�[�g�̐ݒ�
	begin();
	dev->Clear( 0, NULL,D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
}

//�G�t�F�N�g�̍X�V
VOID CEffect::UpdateEffect(float x,float y)
{
		//�t�F�[�h�C���A�E�g
	Fade -=0.1f;
	if(Fade > 1.0f){Fade=1.0f;}
	if(Fade < 0.0f){Fade=0.0f;}

	cam.wh.x = x;
	cam.wh.y = y;
	UpdateCam();

	UpdateFog();
	UpdatePointLight();
	UpdateLight();
	ToneMap();
}
VOID CEffect::UpdateEffect()
{
	UpdateFog();
	ToneMap();

}

VOID CEffect::InitEffect()
{	
	MirrorFlag = FALSE;
	Mirrorcam.Init();

	Fade  = 1.0f;
	Fs.Init();
	Ls.Init();
	PSL.Init();
	cam.Init();
}