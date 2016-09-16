//�R���X�g���N�^
CSound::CSound()
{
	m_iCount = 0;
}
//�f�X�g���N�^
CSound::~CSound()
{
	for(std::vector<SVoice*>::iterator it = m_pSv.begin(); it != m_pSv.end(); ++it)
	{
		SAFE_DELETE(*it);
	}
}
//�w��T�E���h�̃\�[�X���쐬
HRESULT CSound::Load(int wav,Arc_Files* af,FILE* fp,CXAudio2* pAudio,int* num,X3DVoiceState* x3d)
{
	if(m_iCount == 0)
	{
		//wav�̍쐬
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
	//SourceVoice�̍쐬
	BOOL exi = FALSE;
	for(std::vector<SVoice*>::iterator it = m_pSv.begin(); it != m_pSv.end(); ++it)
	{
		//�󂫗v�f���������ꍇ
		if(*it == NULL)
		{
			exi = TRUE;
			*num = it - m_pSv.begin();
			m_pSv[*num] = new SVoice;
			break;
		}
	}
	//�󂫗v�f�����������ꍇ�V�K�쐬
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
	//�J�E���g�𑝂₷
	m_iCount++;
	return S_OK;
}
//�S�Ă�SVoice���X�V
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
//SVoice��������ăJ�E���g�����炷
int CSound::Release(int num)
{
	SAFE_DELETE(m_pSv[num]);
	m_iCount--;
	return m_iCount; 
}