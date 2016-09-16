
//==========================================
//�t�H���g�e�N�X�`����o�^
//==========================================
CString::CString()
{
	FontSize = 24;
	_stprintf_s(FontName,LF_FACESIZE,_T("�l�r ����"));
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
	//D3DPOOL_DEFAULT���g���Ă���̂Ń��Z�b�g�����
	for(vFont::iterator it = cfont.begin();it != cfont.end();++it)
	{
		SAFE_DELETE(*it);
	}
	cfont.clear();
}

VOID CString::SetFont(const TCHAR* font,int size)
{
	_stprintf_s(FontName,LF_FACESIZE,_T("%s"),font);
	//�T�C�Y5�ȉ��͎w��ł��Ȃ�
	if(size <= 5){size = 6;}
	FontSize = size;
}

//�������o�^����Ă��邩�`�F�b�N����.���̌�w�蕶���̔z���Ԃ�
int CString::FontSetCheck(LPDIRECT3DDEVICE9 dev,const TCHAR* str)
{
	for(vFont::iterator it = cfont.begin();it != cfont.end();++it)
	{
		//���łɓo�^����Ă����ꍇ�I��
#if _UNICODE
		if((*it)->c[0] == str[0]){return it - cfont.begin();}
#else
		if(IsDBCSLeadByte(*str))
		{
			//�}���`�o�C�g�̏ꍇ
			if((*it)->c[0] == str[0])
			{
				if((*it)->c[1] == str[1]){return it - cfont.begin();;}		
			}
		}
		else
		{  
			//�V���O���o�C�g�̏ꍇ
			if((*it)->c[0] == str[0]){return it - cfont.begin();;}
		}		
#endif
	}
	//�o�^����Ă��Ȃ��̂œo�^����
	cfont.push_back(new CFontTex);
	size_t Last = cfont.size() - 1;
	if(FAILED(cfont[Last]->Create(str,dev,FontName,FontSize)))
	{
		CFile().Debug(_T("�t�H���g�̍쐬���s\n"));	
		return -1;
	}

	return Last;
}

CFontTex* CString::SetFontTex(LPDIRECT3DDEVICE9 dev,const TCHAR* str)
{
	for(vFont::iterator it = cfont.begin();it != cfont.end();++it)
	{
		//���łɓo�^����Ă����ꍇ�I��
#if _UNICODE
		if((*it)->c[0] == str[0]){return *it;}
#else
		if(IsDBCSLeadByte(*str))
		{
			//�}���`�o�C�g�̏ꍇ
			if((*it)->c[0] == str[0])
			{
				if((*it)->c[1] == str[1]){return *it;}		
			}
		}
		else
		{  
			//�V���O���o�C�g�̏ꍇ
			if((*it)->c[0] == str[0]){return *it;}
		}		
#endif
	}
	//�o�^����Ă��Ȃ��̂œo�^����
	cfont.push_back(new CFontTex);
	size_t Last = cfont.size() - 1;
	if(FAILED(cfont[Last]->Create(str,dev,FontName,FontSize)))
	{
		CFile().Debug(_T("�t�H���g�̍쐬���s\n"));	
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