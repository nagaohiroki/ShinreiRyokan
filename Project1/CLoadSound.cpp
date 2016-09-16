
//�T�E���h�}�l�[�W��---------------------------------------------------------------------------------------------
//�R���X�g���N�^
CSoundManager::CSoundManager(){}
//�f�X�g���N�^
CSoundManager::~CSoundManager()
{
	for(mapc::iterator it = Sound.begin();it != Sound.end(); ++it)
	{
		SAFE_DELETE((*it).second);
	}
}
//�I�[�f�B�I�I�u�W�F�N�g�̍쐬
HRESULT CSoundManager::Create()
{
	if(FAILED(Audio.Create())){return E_FAIL;}
	return S_OK;
}
//�T�E���h��ǂݍ���(num�ɔz�񂪋A���Ă���)
HRESULT CSoundManager::Load(int n,Arc_Files* af,FILE* fp,int* num, X3DVoiceState* x3d)
{
	mapc::iterator it = Sound.find(n);
	if(it == Sound.end())
	{
		typedef std::pair<int,CSound*> p; 
		Sound.insert(p(n,new CSound));
		it = Sound.find(n);
	}
	if(FAILED((*it).second->Load(n,af,fp,&Audio,num,x3d))){return E_FAIL;}
	return S_OK;
}
//�I�[�f�B�I�I�u�W�F�N�g�A�S�ẴT�E���h��Ԃ�
HRESULT CSoundManager::Update()
{
	if(FAILED(Audio.Update())){return E_FAIL;}
	for(mapc::iterator it = Sound.begin(); it != Sound.end(); ++it)
	{
		if((*it).second){(*it).second->Update();	}
	}
	return S_OK;
}
//wav��index���w�肵�ĉ��
VOID CSoundManager::Release(int wav,int num)
{
	mapc::iterator it = Sound.find(wav);
	if(it != Sound.end())
	{
		if((*it).second->Release(num) <= 0)
		{
			SAFE_DELETE((*it).second);	
			Sound.erase(wav);
		}
	}
}
//SVoice��Ԃ�
SVoice* CSoundManager::Sv(int w,int n)
{
	mapc::iterator it = Sound.find(w);
	if(it != Sound.end())
	{
		return (*it).second->m_pSv[n];
	}
	return NULL;
}
//�f�o�b�O
VOID CSoundManager::Debug(TCHAR* txt,int len,Arc_Files* af)
{
	for(mapc::iterator it = Sound.begin(); it != Sound.end(); ++it)
	{
		int k = (*it).first;
		_stprintf_s(txt,len,_T("%swav:%d%s Count%d\n")
				,txt
				,k
				,af->af[k].name
				,(*it).second->m_iCount
				);
	}
}
