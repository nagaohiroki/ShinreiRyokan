//�e�N�X�`���f�[�^------------------------------------------------------
//�R���X�g���N�^
CTexture::CTexture()
{
	m_iCount = 0;
	m_pTex = NULL;
}
//�f�X�g���N�^
CTexture::~CTexture()
{
	SAFE_RELEASE(m_pTex);
}
//�쐬
HRESULT CTexture::Create(int num,LPDIRECT3DDEVICE9 dev,Arc_Files* af,FILE* fp)
{
	if(m_iCount == 0)
	{
		char* ptr = new char[af->af[num].size];
		fseek(fp,af->af[num].point, SEEK_SET);
		fread(ptr,sizeof(char),af->af[num].size,fp);	
		if(FAILED(D3DXCreateTextureFromFileInMemory(dev,ptr,af->af[num].size,&m_pTex)))
		{
			SAFE_DELETE(ptr);
			TCHAR tt[100];
			_stprintf_s(tt,100,_T("Fail:%s \n"),af->af[num].name);
			CFile().Debug(tt);
			return E_FAIL;
		}
		SAFE_DELETE(ptr);
	}
	m_iCount++;
	return S_OK;
}
//�J�E���g�����炷1�ȉ��Ȃ�j��
int CTexture::Release()
{
	m_iCount--;
 	return  m_iCount;
}	

//-------------------------------------------------------------------------
//�R���X�g���N�^
CTextureManager::CTextureManager(){}
//�f�X�g���N�^
CTextureManager::~CTextureManager()
{
	for(mapc::iterator it = tex.begin(); it != tex.end(); ++it)
	{
		SAFE_DELETE((*it).second);
	}
}
//�e�N�X�`���̓ǂݍ���(���łɂ���ꍇ�̓J�E���g�𑝂₷)
HRESULT CTextureManager::Load(int n,LPDIRECT3DDEVICE9 dev,Arc_Files* af,FILE* fp)
{	
	if(n < 0){return E_FAIL;}
	mapc::iterator it = tex.find(n);
	if(it == tex.end())
	{
		typedef std::pair<int,CTexture*> p; 
		tex.insert(p(n,new CTexture));
		it = tex.find(n);
	}
	(*it).second->Create(n,dev,af,fp);
	return S_OK;
}

std::map<int,CTexture*>::iterator CTextureManager::load(int n,LPDIRECT3DDEVICE9 dev,Arc_Files* af,FILE* fp)
{
	if(n < 0){return tex.end();}
	mapc::iterator it = tex.find(n);
	if(it == tex.end())
	{
		typedef std::pair<int,CTexture*> p; 
		tex.insert(p(n,new CTexture));
		it = tex.find(n);
	}
	(*it).second->Create(n,dev,af,fp);
	return it;
}


//�J�E���g�����炷1�ȉ��Ȃ�j��
VOID CTextureManager::Release(int n)
{	
	if(n < 0){return;}
	mapc::iterator it = tex.find(n);
	if(it != tex.end())
	{
		if((*it).second)
		{
			if((*it).second->Release() <= 0)
			{
				SAFE_DELETE((*it).second);	
				tex.erase(n);
			}
		}
	}
}	
//�e�N�X�`����Ԃ�
LPDIRECT3DTEXTURE9 CTextureManager::Retex( int n )
{
	if(n < 0){return NULL;}
	mapc::iterator it = tex.find(n);
	if(it != tex.end())
	{
		return (*it).second->m_pTex;
	}
	return NULL;
}
//�f�o�b�O
VOID CTextureManager::Debug(TCHAR* txt,int len,Arc_Files* af)
{
	for(mapc::iterator it = tex.begin(); it != tex.end(); ++it)
	{
		int k = (*it).first;
		_stprintf_s(txt,len,_T("%sMesh:%d%s Count%d\n")
				,txt
				,k
				,af->af[k].name
				,(*it).second->m_iCount
				);
	}
}

