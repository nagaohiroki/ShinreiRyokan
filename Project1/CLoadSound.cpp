
//サウンドマネージャ---------------------------------------------------------------------------------------------
//コンストラクタ
CSoundManager::CSoundManager(){}
//デストラクタ
CSoundManager::~CSoundManager()
{
	for(mapc::iterator it = Sound.begin();it != Sound.end(); ++it)
	{
		SAFE_DELETE((*it).second);
	}
}
//オーディオオブジェクトの作成
HRESULT CSoundManager::Create()
{
	if(FAILED(Audio.Create())){return E_FAIL;}
	return S_OK;
}
//サウンドを読み込む(numに配列が帰ってくる)
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
//オーディオオブジェクト、全てのサウンドを返す
HRESULT CSoundManager::Update()
{
	if(FAILED(Audio.Update())){return E_FAIL;}
	for(mapc::iterator it = Sound.begin(); it != Sound.end(); ++it)
	{
		if((*it).second){(*it).second->Update();	}
	}
	return S_OK;
}
//wavとindexを指定して解放
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
//SVoiceを返す
SVoice* CSoundManager::Sv(int w,int n)
{
	mapc::iterator it = Sound.find(w);
	if(it != Sound.end())
	{
		return (*it).second->m_pSv[n];
	}
	return NULL;
}
//デバッグ
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
