//コンストラクタ
CSound::CSound()
{
	m_iCount = 0;
}
//デストラクタ
CSound::~CSound()
{
	for(std::vector<SVoice*>::iterator it = m_pSv.begin(); it != m_pSv.end(); ++it)
	{
		SAFE_DELETE(*it);
	}
}
//指定サウンドのソースを作成
HRESULT CSound::Load(int wav,Arc_Files* af,FILE* fp,CXAudio2* pAudio,int* num,X3DVoiceState* x3d)
{
	if(m_iCount == 0)
	{
		//wavの作成
		char *ptr = new char[af->af[wav].size];
		fseek(fp,af->af[wav].point, SEEK_SET);
		fread(ptr,sizeof(char),af->af[wav].size,fp);	
		if(FAILED(m_Lw.Open(ptr,af->af[wav].size)))
		{
			TCHAR txt[100];
			_stprintf_s(txt,100,_T("Fail:%s\n"),af->af[wav].name);
			CFile().Debug(txt);
			return  E_FAIL;
		}
		SAFE_DELETE(ptr);
	}
	//SourceVoiceの作成
	BOOL exi = FALSE;
	for(std::vector<SVoice*>::iterator it = m_pSv.begin(); it != m_pSv.end(); ++it)
	{
		//空き要素があった場合
		if(*it == NULL)
		{
			exi = TRUE;
			*num = it - m_pSv.begin();
			m_pSv[*num] = new SVoice;
			break;
		}
	}
	//空き要素が無かった場合新規作成
	if(exi == FALSE)
	{
		m_pSv.push_back(new SVoice);
		*num = m_pSv.size() -1;
	}
	if(FAILED(m_pSv[*num]->Create(pAudio,&m_Lw,x3d)))
	{
		TCHAR txt[100];
		_stprintf_s(txt,100,_T("Fail:%s Count%d\n"),af->af[wav].name,m_iCount);
		CFile().Debug(txt);
	}
	//カウントを増やす
	m_iCount++;
	return S_OK;
}
//全てのSVoiceを更新
HRESULT CSound::Update()
{
	for(std::vector<SVoice*>::iterator it = m_pSv.begin(); it != m_pSv.end(); ++it)
	{
		if(*it)
		{
			if(FAILED((*it)->Update()))
			{
				CFile().Debug(_T("Fail:UpdateSound\n"));
				return E_FAIL;
			}
		}
	}	
	return S_OK;
}
//SVoiceを解放してカウントを減らす
int CSound::Release(int num)
{
	SAFE_DELETE(m_pSv[num]);
	m_iCount--;
	return m_iCount; 
}