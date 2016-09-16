//=======================================================================================
//フォントのセットここでフォントを読み込む
//=======================================================================================
//コンストラクタ
CText::CText()
{
	m_pFont=NULL;
	PosX = 10;
	PosY = 10;
	color = D3DXVECTOR4(0.0f,1.0f,1.0f,1.0f);
}
//デストラクタ
CText::~CText()
{
	SAFE_RELEASE(m_pFont); 	
}
//テキストの作成
HRESULT CText::Create(LPDIRECT3DDEVICE9 dev)
{

	//*
	const TCHAR* FONT_N = _T("ＭＳ Ｐゴシック");	
	//フォントＭＳ　Ｐゴシックを読み込む
	if( FAILED( D3DXCreateFont(
		dev,//デバイスのポインタ
		15,//高さ 
		0,//幅 
		0, //太さ
		1,//ミニマップのレベル
		FALSE,//斜体にするときはTRUE
		DEFAULT_CHARSET,//文字セット
		OUT_DEFAULT_PRECIS, //フォントの選択方法
		DEFAULT_QUALITY,//品質
		DEFAULT_PITCH|FF_DONTCARE,//フォントのピッチとファミリ
		FONT_N,//フォント名
		&m_pFont)))//LPD3DXFONTのポインタ
		{
			TCHAR cautionString[260];
			_stprintf_s( cautionString,260, _T("フォント『%s』が見つかりませんでした\n"), FONT_N);
			CFile().Debug(cautionString);
			return E_FAIL;
		}	
	return S_OK;
}

//フォントスプライトのリセット
HRESULT CText::Reset()
{
	if(m_pFont != NULL)
	{
		if(FAILED(m_pFont->OnLostDevice()))
		{
			CFile().Debug(_T("フォントリセット失敗\n"));
			return E_FAIL;

		}

	}
	return S_OK;
}
//リセット後の再構築
HRESULT CText::Restore()
{

	if(m_pFont!= NULL)
	{
		if(FAILED(m_pFont->OnResetDevice()))
		{
			CFile().Debug(_T("フォント後取得失敗\n"));
			return E_FAIL;
		}
	}
	return S_OK;
}

//テキストの描画
VOID    CText::draw(const TCHAR *String)
{
	if(m_pFont != NULL)
	{
		RECT rc = {PosX,PosY,2000,2000};//テキストの場所		
		m_pFont->DrawText(NULL,String,-1,&rc,DT_LEFT|DT_TOP,D3DCOLOR_COLORVALUE(color.x,color.y,color.z,color.w));
	}
}

VOID CText::draw(const TCHAR *String,int x,int y)
{
	if(m_pFont != NULL)
	{
		RECT rc = {x,y,2000,2000};//テキストの場所		
		m_pFont->DrawText(NULL,String,-1,&rc,DT_LEFT|DT_TOP,D3DCOLOR_COLORVALUE(color.x,color.y,color.z,color.w));
	}
}