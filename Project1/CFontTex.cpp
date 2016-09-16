//======================================================
//フォントテクスチャ
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
	//なぜか半角だと大きさ10ピクセルを指定できない(半角の時にテクセルが5になると失敗する)
	if(pTex != NULL){return E_FAIL;}
	//フォントの作成

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
	//フォントハンドル
	HFONT hFont = CreateFontIndirect(&lf);
	//デバイスコンテキストの取得
	HDC hdc = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc,hFont);
	//文字コードの取得
	UINT code = 0;
#if _UNICODE
	code = (UINT)*str; 
	c[0] = str[0];
#else
	//マルチバイトの場合バイト数によって分岐
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
	//フォントビットマップを取得
	TEXTMETRIC TM;
	GetTextMetrics(hdc,&TM);
	GLYPHMETRICS GM;
	CONST MAT2 Mat={{0,1},{0,0},{0,0},{0,1}};
	DWORD size = GetGlyphOutline(hdc,code,GGO_GRAY4_BITMAP,&GM,0,NULL,&Mat);
	BYTE *ptr = NULL;
	//半角全角スペースが入った場合なにもなし
	if( size != 0 ){	ptr = new BYTE[size];	}
	GetGlyphOutline(hdc,code,GGO_GRAY4_BITMAP,&GM,size,ptr,&Mat);
	//デバイスコンテキストとフォントハンドルの開放
	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
	ReleaseDC(NULL, hdc);
	//サイズの算出
	rect.left = 0;
	rect.right = GM.gmCellIncX;
	rect.top  = 0;
	rect.bottom = TM.tmHeight;

	//半角全角スペースが入った場合空のテクスチャ
	if(!size)
	{	
		int bmp_w = GM.gmBlackBoxX + (4-(GM.gmBlackBoxX%4))%4;//ビットマップの幅
		int bmp_h = GM.gmBlackBoxY;//ビットマップの高さ
		ptr= new BYTE[bmp_w * bmp_h];
		memset( ptr, 0x00, bmp_w * bmp_h);
	}	
	//テクスチャの作成
	if(FAILED(dev->CreateTexture( GM.gmCellIncX, TM.tmHeight, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pTex, NULL)))
 	if(FAILED(dev->CreateTexture(GM.gmCellIncX,	TM.tmHeight,1, 0,D3DFMT_A8R8G8B8,D3DPOOL_MANAGED,&pTex,	NULL)))
	{
		CFile().Debug(_T("フォントテクスチャの作成に失敗しました\n"));
		SAFE_DELETE_ARRAY(ptr);
		return E_FAIL;
	}
	//テクスチャにフォントビットマップを書き込む
	D3DLOCKED_RECT LockedRect;
	if(FAILED(pTex->LockRect(0, &LockedRect, NULL, D3DLOCK_DISCARD)))
	if(FAILED(pTex->LockRect(0, &LockedRect, NULL, 0 )))
	{
		CFile().Debug(_T("テクスチャロック失敗\n"));
		SAFE_DELETE_ARRAY(ptr);	
		return E_FAIL;
	}
	
	//フォント情報を書き込む
	//書き出し位置(左上)
	int iOfs_x = GM.gmptGlyphOrigin.x;
	int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y; 
	//フォントビットマップの幅高
	int iBmp_w = GM.gmBlackBoxX + (4-(GM.gmBlackBoxX % 4)) % 4;
	int iBmp_h = GM.gmBlackBoxY;
	//アルファ値の段階
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
