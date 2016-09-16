
//==========================================
//フォントテクスチャを登録
//==========================================
CString::CString()
{
	FontSize = 24;
	_stprintf_s(FontName,LF_FACESIZE,_T("ＭＳ 明朝"));
}

CString::~CString()
{
	for(vFont::iterator it = cfont.begin();it != cfont.end();++it)
	{
		SAFE_DELETE(*it);
	}
}
VOID CString::Reset()
{
	//D3DPOOL_DEFAULTを使っているのでリセット時解放
	for(vFont::iterator it = cfont.begin();it != cfont.end();++it)
	{
		SAFE_DELETE(*it);
	}
	cfont.clear();
}

VOID CString::SetFont(const TCHAR* font,int size)
{
	_stprintf_s(FontName,LF_FACESIZE,_T("%s"),font);
	//サイズ5以下は指定できない
	if(size <= 5){size = 6;}
	FontSize = size;
}

//文字が登録されているかチェックする.その後指定文字の配列を返す
int CString::FontSetCheck(LPDIRECT3DDEVICE9 dev,const TCHAR* str)
{
	for(vFont::iterator it = cfont.begin();it != cfont.end();++it)
	{
		//すでに登録されていた場合終了
#if _UNICODE
		if((*it)->c[0] == str[0]){return it - cfont.begin();}
#else
		if(IsDBCSLeadByte(*str))
		{
			//マルチバイトの場合
			if((*it)->c[0] == str[0])
			{
				if((*it)->c[1] == str[1]){return it - cfont.begin();;}		
			}
		}
		else
		{  
			//シングルバイトの場合
			if((*it)->c[0] == str[0]){return it - cfont.begin();;}
		}		
#endif
	}
	//登録されていないので登録する
	cfont.push_back(new CFontTex);
	size_t Last = cfont.size() - 1;
	if(FAILED(cfont[Last]->Create(str,dev,FontName,FontSize)))
	{
		CFile().Debug(_T("フォントの作成失敗\n"));	
		return -1;
	}

	return Last;
}

CFontTex* CString::SetFontTex(LPDIRECT3DDEVICE9 dev,const TCHAR* str)
{
	for(vFont::iterator it = cfont.begin();it != cfont.end();++it)
	{
		//すでに登録されていた場合終了
#if _UNICODE
		if((*it)->c[0] == str[0]){return *it;}
#else
		if(IsDBCSLeadByte(*str))
		{
			//マルチバイトの場合
			if((*it)->c[0] == str[0])
			{
				if((*it)->c[1] == str[1]){return *it;}		
			}
		}
		else
		{  
			//シングルバイトの場合
			if((*it)->c[0] == str[0]){return *it;}
		}		
#endif
	}
	//登録されていないので登録する
	cfont.push_back(new CFontTex);
	size_t Last = cfont.size() - 1;
	if(FAILED(cfont[Last]->Create(str,dev,FontName,FontSize)))
	{
		CFile().Debug(_T("フォントの作成失敗\n"));	
		return NULL;
	}
	/*
	else
	{
		//debug
		TCHAR Debug[50];
		_stprintf_s(Debug,50,_T("%s\n"),cfont[Last]->c);
		CFile().Debug(Debug);		
	}
	//*/
	return cfont[Last];
}

VOID CString::Debug(TCHAR* t,int l)
{
	for(vFont::iterator it = cfont.begin();it != cfont.end();++it)
	{
		_stprintf_s(t,l,_T("%s%s\n"),t,(*it)->c);
	}

}