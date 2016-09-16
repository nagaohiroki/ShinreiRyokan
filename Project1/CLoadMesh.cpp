//�}�e���A��---------------------------------------------------------------------
//�R���X�g���N�^
CMtrl::CMtrl()
{
	_stprintf_s(TexName,MAX_PATH,_T(""));
	ZeroMemory(&m_Mtrl,sizeof(D3DMATERIAL9));
	m_iTex = -1;
	m_iNTex = -1;
	m_iTexPass = fx::Mesh;
}
//�e�N�X�`���̖��O�Ńe�N�X�`���ԍ���Ԃ�
int CMtrl::ReTexNum(TCHAR* name,Arc_Files* af)
{
	unsigned int i;
	for(i = 0; i < MAX_arc; i++)
	{
		if(_tcscmp(name,af->af[i].name) == NULL){return i;}
	}
	return -1;
}
//�e�N�X�`���̃i���o�[��Ԃ�
VOID CMtrl::SetTexNum(Arc_Files* af)
{		
	m_iTex = ReTexNum(TexName,af);
	if( m_iTex != -1 )
	{
		//���ʂ̃e�N�X�`���̂�
		m_iTexPass = fx::Mesh_Tex;
		//a���̃e�N�X�`��
		if(_tcsstr(TexName,_T(".png")) != 0){m_iTexPass = fx::Mesh_AlphaTex;	} 
		//�o���v�}�b�v��T��
		TCHAR BumpMap[MAX_PATH] = _T("");
		TCHAR BumpMap2[MAX_PATH] = _T("");
		_stprintf_s(BumpMap,MAX_PATH,_T("%s"),TexName);
		unsigned int i;
		unsigned int bm = _tcsnlen(BumpMap,MAX_PATH);
		for( i = 0; i < bm ; i++)
		{
			if(BumpMap[i] == '.')
			{
				BumpMap[i] = '\0';
				break;
			}
		}				
		_stprintf_s(BumpMap2,MAX_PATH,_T("normal_%s.bmp"),BumpMap);
		m_iNTex = ReTexNum(BumpMap2,af);
		//�������ꍇ
		if( m_iNTex != -1 ){m_iTexPass = fx::Mesh_Bump;}				
	}		
}
//���f��---------------------------------------------------------------------
//�R���X�g���N�^
CModel::CModel()
{
	m_iCount = 0;	
	m_pMesh = NULL;	// �V�X�e�����̃��b�V���I�u�W�F�N�g
	m_dwMatNum = 0;	// ���b�V�������̐�
	TexPass = fx::Mesh;//�e�N�X�`���������Ă��邩�̃t���O
	Max = D3DXVECTOR3(0.0f,0.0f,0.0f);//�ő咸�_
	Min = D3DXVECTOR3(0.0f,0.0f,0.0f);;//�ŏ����_
	ren = D3DXVECTOR3(0.0f,0.0f,0.0f);;//�e���a
	Center = D3DXVECTOR3(0.0f,0.0f,0.0f);;//���̒��S�_
	Sren = 0.0f;//���̔��a
	
}
//�f�X�g���N�^
CModel::~CModel()
{
	SAFE_RELEASE(m_pMesh);
}

//�}�e���A���A�e�N�X�`���A�T�C�Y�̎擾
HRESULT CModel::LoadMtrl(LPD3DXBUFFER pBuffer,LPDIRECT3DDEVICE9 dev,Arc_Files* af)
{
	//�}�e���A����e�N�X�`���̖��̂Ȃǂ̏����擾����B
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)pBuffer->GetBufferPointer();
	DWORD i;
	for(i = 0; i < m_dwMatNum; i++)
	{
		//�}�e���A���̐ݒ�
		CMtrl Matel;
		Matel.m_Mtrl = pMat[i].MatD3D;
		Matel.m_Mtrl.Ambient = Matel.m_Mtrl.Diffuse;
		//�e�N�X�`���̖��O���擾
		if(pMat[i].pTextureFilename != NULL && lstrlenA(pMat[i].pTextureFilename))
		{					
			
#ifdef UNICODE//���j�R�[�h�ɕϊ�
			MultiByteToWideChar(CP_ACP,0,pMat[i].pTextureFilename,-1,Matel.TexName,MAX_PATH);
#else		  //�}���`�o�C�g�ɕϊ�
			_stprintf_s(Matel.TexName,MAX_PATH,_T("%s"),pMat[i].pTextureFilename);
#endif
		}	
		//�e�N�X�`���ԍ����擾
		Matel.SetTexNum(af);
		//�G�t�F�N�g�p�X�擾
		TexPass = Matel.m_iTexPass;
		//�}�e���A����ǉ�
		m_pCMtrl.push_back(Matel);
	}
	
	//�ő咸�_,�ŏ����_,�e�ӂ̔��a
	BYTE* byte   = NULL;//�o�C�g��
	DWORD NumVer = m_pMesh->GetNumVertices();
	DWORD GetFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());
	//�o�b�t�@�̃��b�N
	if(SUCCEEDED(m_pMesh->LockVertexBuffer(0,(VOID**)&byte)))
	{	
		//�ő咸�_,�ŏ����_
		if(FAILED(D3DXComputeBoundingBox((D3DXVECTOR3*)byte,NumVer,GetFVF,&Min,&Max)))
		{
			CFile().Debug(_T("���b�V���傫���̎擾���s\n"));
			return E_FAIL;
		}
		//���E���̔��a
		if(FAILED(D3DXComputeBoundingSphere((D3DXVECTOR3*)byte,NumVer,GetFVF,&Center,&Sren)))
		{
			CFile().Debug(_T("���b�V���傫���̎擾���s\n"));
			return E_FAIL;
		}
		//�o�b�t�@�̃A�����b�N
		m_pMesh->UnlockVertexBuffer();
	}
	else
	{
		CFile().Debug(_T("���b�V�����b�N���s\n"));	
		return E_FAIL;
	}
	//�e���a
	ren.x = (fabs(Max.x) + fabs(Min.x)) / 2;
	ren.y = (fabs(Max.y) + fabs(Min.y)) / 2;
	ren.z = (fabs(Max.z) + fabs(Min.z)) / 2;
	//�@���̎擾
	if(FAILED(SetNormal(dev)))
	{
		CFile().Debug(_T("�@���̎擾���s\n"));
		return E_FAIL;
	}
	return S_OK;
}
//�@���}�b�v�̍쐬
HRESULT CModel::SetNormal(LPDIRECT3DDEVICE9 dev)
{	
	if(TexPass == fx::Mesh_Bump)
	{	
		D3DVERTEXELEMENT9 decl[]=
		{
	   	  {0,  0, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	      {0, 12, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0},
	      {0, 24, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},
	      {0, 36, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
	      {0, 48, D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	      D3DDECL_END()
		};
		LPD3DXMESH pMesh=NULL;
		if(FAILED(m_pMesh->CloneMesh(m_pMesh->GetOptions(),decl,dev,&pMesh)))
		{
			SAFE_RELEASE(m_pMesh);
			CFile().Debug(_T("�N���[�����b�V���������s\n"));
			return E_FAIL;
		}
		if(FAILED(D3DXComputeNormals(pMesh,NULL)))
		{
			SAFE_RELEASE(m_pMesh);
			CFile().Debug(_T("�@���t�����s\n"));
			return E_FAIL;
		}

		if(FAILED(D3DXComputeTangent(pMesh,0,0,0,TRUE,NULL)))
		{
			SAFE_RELEASE(m_pMesh);
			CFile().Debug(_T("�ڃx�N�g���t�����s\n"));
			return E_FAIL;
		}	
		SAFE_RELEASE(m_pMesh);
		m_pMesh=pMesh;
	}
	return S_OK;
}
//���������烂�f����ǂݍ���
HRESULT CModel::LoadModel(LPDIRECT3DDEVICE9 dev,int num,Arc_Files* af,FILE* fp)
{
	if(m_iCount == 0)
	{	
		char* ptr = new char[af->af[num].size];
		fseek(fp,af->af[num].point, SEEK_SET);
		fread(ptr,sizeof(char),af->af[num].size,fp);	
		int size = (int)af->af[num].size;
		//�ꎞ�o�b�t�@�p
		LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
		//X�t�@�C���̓ǂݍ���
		if( FAILED( D3DXLoadMeshFromXInMemory(
			ptr,
			size,
			D3DXMESH_SYSTEMMEM, 
			dev, 
			NULL, 
			&pD3DXMtrlBuffer,
			NULL,
			&m_dwMatNum,
			&m_pMesh)))
		{		
			SAFE_DELETE(ptr);
			TCHAR tt[100];
			_stprintf_s(tt,100,_T("Fail:%s \n"),af->af[num].name);
			CFile().Debug(tt);
			return E_FAIL;
		}	
		//�������̔j��
		SAFE_DELETE(ptr);
		//�}�e���A���A�T�C�Y�A�e�N�X�`���̎擾
		if(FAILED(LoadMtrl(pD3DXMtrlBuffer,dev,af))){return E_FAIL;}
		SAFE_RELEASE(pD3DXMtrlBuffer);
	}
	//�J�E���g��i�߂�
	m_iCount++;	
	return S_OK;
}
//���f���̃J�E���g
int CModel::Release()
{
	m_iCount--;
	return m_iCount;
}
//�e�X==========================================================================
CModelManager::CModelManager(){}
CModelManager::~CModelManager()
{
	for(mapc::iterator it = Mod.begin(); it != Mod.end(); ++it)
	{
		SAFE_DELETE((*it).second);
	}
}
std::map<int,CModel*>::iterator CModelManager::Load(int n,LPDIRECT3DDEVICE9 dev,Arc_Files* af,FILE* fp)
{
	mapc::iterator it = Mod.find(n);
	if(it == Mod.end())
	{
		typedef std::pair<int,CModel*> p; 
		Mod.insert(p(n,new CModel));
		it = Mod.find(n);
	}
	(*it).second->LoadModel(dev,n,af,fp);
	return it;
}
VOID CModelManager::Release(int n)
{
	mapc::iterator it = Mod.find(n);
	if(it != Mod.end())
	{
		if((*it).second)
		{
			if((*it).second->Release() <= 0)
			{
				SAFE_DELETE((*it).second);	
				Mod.erase(n);
			}
		}
	}
}

//�f�o�b�O
VOID CModelManager::Debug(TCHAR* txt,int len,Arc_Files* af)
{

	for(mapc::iterator it = Mod.begin(); it != Mod.end(); ++it)
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
