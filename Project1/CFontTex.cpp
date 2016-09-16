//======================================================
//�t�H���g�e�N�X�`��
//======================================================
CFontTex::CFontTex()
{
	RECT r={0,0,0,0}; 
	rect = r;
	pTex = NULL;
	_stprintf_s(c,2,_T(""));
}

CFontTex::~CFontTex()
{
	SAFE_RELEASE(pTex);
}
HRESULT CFontTex::Create(const TCHAR* str,LPDIRECT3DDEVICE9 dev,TCHAR* FontName ,int FontSize)
{
	//�Ȃ������p���Ƒ傫��10�s�N�Z�����w��ł��Ȃ�(���p�̎��Ƀe�N�Z����5�ɂȂ�Ǝ��s����)
	if(pTex != NULL){return E_FAIL;}
	//�t�H���g�̍쐬

	LOGFONT lf=
	{
		FontSize,
		0, 0, 0, 0, 0, 0, 0,
		SHIFTJIS_CHARSET,
		OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN
	};
	_stprintf_s(lf.lfFaceName,LF_FACESIZE,_T("%s"),FontName);
	//�t�H���g�n���h��
	HFONT hFont = CreateFontIndirect(&lf);
	//�f�o�C�X�R���e�L�X�g�̎擾
	HDC hdc = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc,hFont);
	//�����R�[�h�̎擾
	UINT code = 0;
#if _UNICODE
	code = (UINT)*str; 
	c[0] = str[0];
#else
	//�}���`�o�C�g�̏ꍇ�o�C�g���ɂ���ĕ���
	if(IsDBCSLeadByte(*str))
	{ 
		code = (BYTE)str[0]<<8 | (BYTE)str[1];
		c[0] = str[0];
		c[1] = str[1];
	}
	else
	{ 
		code = str[0];
		c[0] = str[0];
	}
#endif
	//�t�H���g�r�b�g�}�b�v���擾
	TEXTMETRIC TM;
	GetTextMetrics(hdc,&TM);
	GLYPHMETRICS GM;
	CONST MAT2 Mat={{0,1},{0,0},{0,0},{0,1}};
	DWORD size = GetGlyphOutline(hdc,code,GGO_GRAY4_BITMAP,&GM,0,NULL,&Mat);
	BYTE *ptr = NULL;
	//���p�S�p�X�y�[�X���������ꍇ�Ȃɂ��Ȃ�
	if( size != 0 ){	ptr = new BYTE[size];	}
	GetGlyphOutline(hdc,code,GGO_GRAY4_BITMAP,&GM,size,ptr,&Mat);
	//�f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���̊J��
	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
	ReleaseDC(NULL, hdc);
	//�T�C�Y�̎Z�o
	rect.left = 0;
	rect.right = GM.gmCellIncX;
	rect.top  = 0;
	rect.bottom = TM.tmHeight;

	//���p�S�p�X�y�[�X���������ꍇ��̃e�N�X�`��
	if(!size)
	{	
		int bmp_w = GM.gmBlackBoxX + (4-(GM.gmBlackBoxX%4))%4;//�r�b�g�}�b�v�̕�
		int bmp_h = GM.gmBlackBoxY;//�r�b�g�}�b�v�̍���
		ptr= new BYTE[bmp_w * bmp_h];
		memset( ptr, 0x00, bmp_w * bmp_h);
	}	
	//�e�N�X�`���̍쐬
	if(FAILED(dev->CreateTexture( GM.gmCellIncX, TM.tmHeight, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pTex, NULL)))
 	if(FAILED(dev->CreateTexture(GM.gmCellIncX,	TM.tmHeight,1, 0,D3DFMT_A8R8G8B8,D3DPOOL_MANAGED,&pTex,	NULL)))
	{
		CFile().Debug(_T("�t�H���g�e�N�X�`���̍쐬�Ɏ��s���܂���\n"));
		SAFE_DELETE_ARRAY(ptr);
		return E_FAIL;
	}
	//�e�N�X�`���Ƀt�H���g�r�b�g�}�b�v����������
	D3DLOCKED_RECT LockedRect;
	if(FAILED(pTex->LockRect(0, &LockedRect, NULL, D3DLOCK_DISCARD)))
	if(FAILED(pTex->LockRect(0, &LockedRect, NULL, 0 )))
	{
		CFile().Debug(_T("�e�N�X�`�����b�N���s\n"));
		SAFE_DELETE_ARRAY(ptr);	
		return E_FAIL;
	}
	
	//�t�H���g������������
	//�����o���ʒu(����)
	int iOfs_x = GM.gmptGlyphOrigin.x;
	int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y; 
	//�t�H���g�r�b�g�}�b�v�̕���
	int iBmp_w = GM.gmBlackBoxX + (4-(GM.gmBlackBoxX % 4)) % 4;
	int iBmp_h = GM.gmBlackBoxY;
	//�A���t�@�l�̒i�K
	int Level  = 17;
	FillMemory(LockedRect.pBits,LockedRect.Pitch * TM.tmHeight,0);
	DWORD Alpha,Color;
	int x,y;
	for(y = iOfs_y; y < iOfs_y + iBmp_h; y++ )
	{
		for(x = iOfs_x; x < iOfs_x + (int)GM.gmBlackBoxX; x++ )
		{
			Alpha = (255 * ptr[x - iOfs_x + iBmp_w * (y - iOfs_y)]) / (Level - 1);
			Color = 0x00ffffff | (Alpha << 24);
		//	Color = 0x00ffffff | (Alpha<<24) | 0x33000000;
			memcpy((BYTE*)LockedRect.pBits + LockedRect.Pitch * y + 4 * x,&Color,sizeof(DWORD));
	
		}
	}
	pTex->UnlockRect(0);	
	SAFE_DELETE_ARRAY(ptr);
	return S_OK;
}
