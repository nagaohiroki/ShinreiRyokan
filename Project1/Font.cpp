//=======================================================================================
//�t�H���g�̃Z�b�g�����Ńt�H���g��ǂݍ���
//=======================================================================================
//�R���X�g���N�^
CText::CText()
{
	m_pFont=NULL;
	PosX = 10;
	PosY = 10;
	color = D3DXVECTOR4(0.0f,1.0f,1.0f,1.0f);
}
//�f�X�g���N�^
CText::~CText()
{
	SAFE_RELEASE(m_pFont); 	
}
//�e�L�X�g�̍쐬
HRESULT CText::Create(LPDIRECT3DDEVICE9 dev)
{

	//*
	const TCHAR* FONT_N = _T("�l�r �o�S�V�b�N");	
	//�t�H���g�l�r�@�o�S�V�b�N��ǂݍ���
	if( FAILED( D3DXCreateFont(
		dev,//�f�o�C�X�̃|�C���^
		15,//���� 
		0,//�� 
		0, //����
		1,//�~�j�}�b�v�̃��x��
		FALSE,//�Α̂ɂ���Ƃ���TRUE
		DEFAULT_CHARSET,//�����Z�b�g
		OUT_DEFAULT_PRECIS, //�t�H���g�̑I����@
		DEFAULT_QUALITY,//�i��
		DEFAULT_PITCH|FF_DONTCARE,//�t�H���g�̃s�b�`�ƃt�@�~��
		FONT_N,//�t�H���g��
		&m_pFont)))//LPD3DXFONT�̃|�C���^
		{
			TCHAR cautionString[260];
			_stprintf_s( cautionString,260, _T("�t�H���g�w%s�x��������܂���ł���\n"), FONT_N);
			CFile().Debug(cautionString);
			return E_FAIL;
		}	
	return S_OK;
}

//�t�H���g�X�v���C�g�̃��Z�b�g
HRESULT CText::Reset()
{
	if(m_pFont != NULL)
	{
		if(FAILED(m_pFont->OnLostDevice()))
		{
			CFile().Debug(_T("�t�H���g���Z�b�g���s\n"));
			return E_FAIL;

		}

	}
	return S_OK;
}
//���Z�b�g��̍č\�z
HRESULT CText::Restore()
{

	if(m_pFont!= NULL)
	{
		if(FAILED(m_pFont->OnResetDevice()))
		{
			CFile().Debug(_T("�t�H���g��擾���s\n"));
			return E_FAIL;
		}
	}
	return S_OK;
}

//�e�L�X�g�̕`��
VOID    CText::draw(const TCHAR *String)
{
	if(m_pFont != NULL)
	{
		RECT rc = {PosX,PosY,2000,2000};//�e�L�X�g�̏ꏊ		
		m_pFont->DrawText(NULL,String,-1,&rc,DT_LEFT|DT_TOP,D3DCOLOR_COLORVALUE(color.x,color.y,color.z,color.w));
	}
}

VOID CText::draw(const TCHAR *String,int x,int y)
{
	if(m_pFont != NULL)
	{
		RECT rc = {x,y,2000,2000};//�e�L�X�g�̏ꏊ		
		m_pFont->DrawText(NULL,String,-1,&rc,DT_LEFT|DT_TOP,D3DCOLOR_COLORVALUE(color.x,color.y,color.z,color.w));
	}
}