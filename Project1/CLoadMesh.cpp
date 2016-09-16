//マテリアル---------------------------------------------------------------------
//コンストラクタ
CMtrl::CMtrl()
{
	_stprintf_s(TexName,MAX_PATH,_T(""));
	ZeroMemory(&m_Mtrl,sizeof(D3DMATERIAL9));
	m_iTex = -1;
	m_iNTex = -1;
	m_iTexPass = fx::Mesh;
}
//テクスチャの名前でテクスチャ番号を返す
int CMtrl::ReTexNum(TCHAR* name,Arc_Files* af)
{
	unsigned int i;
	for(i = 0; i < MAX_arc; i++)
	{
		if(_tcscmp(name,af->af[i].name) == NULL){return i;}
	}
	return -1;
}
//テクスチャのナンバーを返す
VOID CMtrl::SetTexNum(Arc_Files* af)
{		
	m_iTex = ReTexNum(TexName,af);
	if( m_iTex != -1 )
	{
		//普通のテクスチャのみ
		m_iTexPass = fx::Mesh_Tex;
		//aつきのテクスチャ
		if(_tcsstr(TexName,_T(".png")) != 0){m_iTexPass = fx::Mesh_AlphaTex;	} 
		//バンプマップを探す
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
		//あった場合
		if( m_iNTex != -1 ){m_iTexPass = fx::Mesh_Bump;}				
	}		
}
//モデル---------------------------------------------------------------------
//コンストラクタ
CModel::CModel()
{
	m_iCount = 0;	
	m_pMesh = NULL;	// システム中のメッシュオブジェクト
	m_dwMatNum = 0;	// メッシュ質感の数
	TexPass = fx::Mesh;//テクスチャが張ってあるかのフラグ
	Max = D3DXVECTOR3(0.0f,0.0f,0.0f);//最大頂点
	Min = D3DXVECTOR3(0.0f,0.0f,0.0f);;//最小頂点
	ren = D3DXVECTOR3(0.0f,0.0f,0.0f);;//各半径
	Center = D3DXVECTOR3(0.0f,0.0f,0.0f);;//球の中心点
	Sren = 0.0f;//球の半径
	
}
//デストラクタ
CModel::~CModel()
{
	SAFE_RELEASE(m_pMesh);
}

//マテリアル、テクスチャ、サイズの取得
HRESULT CModel::LoadMtrl(LPD3DXBUFFER pBuffer,LPDIRECT3DDEVICE9 dev,Arc_Files* af)
{
	//マテリアルやテクスチャの名称などの情報を取得する。
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)pBuffer->GetBufferPointer();
	DWORD i;
	for(i = 0; i < m_dwMatNum; i++)
	{
		//マテリアルの設定
		CMtrl Matel;
		Matel.m_Mtrl = pMat[i].MatD3D;
		Matel.m_Mtrl.Ambient = Matel.m_Mtrl.Diffuse;
		//テクスチャの名前を取得
		if(pMat[i].pTextureFilename != NULL && lstrlenA(pMat[i].pTextureFilename))
		{					
			
#ifdef UNICODE//ユニコードに変換
			MultiByteToWideChar(CP_ACP,0,pMat[i].pTextureFilename,-1,Matel.TexName,MAX_PATH);
#else		  //マルチバイトに変換
			_stprintf_s(Matel.TexName,MAX_PATH,_T("%s"),pMat[i].pTextureFilename);
#endif
		}	
		//テクスチャ番号を取得
		Matel.SetTexNum(af);
		//エフェクトパス取得
		TexPass = Matel.m_iTexPass;
		//マテリアルを追加
		m_pCMtrl.push_back(Matel);
	}
	
	//最大頂点,最小頂点,各辺の半径
	BYTE* byte   = NULL;//バイト数
	DWORD NumVer = m_pMesh->GetNumVertices();
	DWORD GetFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());
	//バッファのロック
	if(SUCCEEDED(m_pMesh->LockVertexBuffer(0,(VOID**)&byte)))
	{	
		//最大頂点,最小頂点
		if(FAILED(D3DXComputeBoundingBox((D3DXVECTOR3*)byte,NumVer,GetFVF,&Min,&Max)))
		{
			CFile().Debug(_T("メッシュ大きさの取得失敗\n"));
			return E_FAIL;
		}
		//境界球の半径
		if(FAILED(D3DXComputeBoundingSphere((D3DXVECTOR3*)byte,NumVer,GetFVF,&Center,&Sren)))
		{
			CFile().Debug(_T("メッシュ大きさの取得失敗\n"));
			return E_FAIL;
		}
		//バッファのアンロック
		m_pMesh->UnlockVertexBuffer();
	}
	else
	{
		CFile().Debug(_T("メッシュロック失敗\n"));	
		return E_FAIL;
	}
	//各半径
	ren.x = (fabs(Max.x) + fabs(Min.x)) / 2;
	ren.y = (fabs(Max.y) + fabs(Min.y)) / 2;
	ren.z = (fabs(Max.z) + fabs(Min.z)) / 2;
	//法線の取得
	if(FAILED(SetNormal(dev)))
	{
		CFile().Debug(_T("法線の取得失敗\n"));
		return E_FAIL;
	}
	return S_OK;
}
//法線マップの作成
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
			CFile().Debug(_T("クローンメッシュ生成失敗\n"));
			return E_FAIL;
		}
		if(FAILED(D3DXComputeNormals(pMesh,NULL)))
		{
			SAFE_RELEASE(m_pMesh);
			CFile().Debug(_T("法線付加失敗\n"));
			return E_FAIL;
		}

		if(FAILED(D3DXComputeTangent(pMesh,0,0,0,TRUE,NULL)))
		{
			SAFE_RELEASE(m_pMesh);
			CFile().Debug(_T("接ベクトル付加失敗\n"));
			return E_FAIL;
		}	
		SAFE_RELEASE(m_pMesh);
		m_pMesh=pMesh;
	}
	return S_OK;
}
//メモリからモデルを読み込む
HRESULT CModel::LoadModel(LPDIRECT3DDEVICE9 dev,int num,Arc_Files* af,FILE* fp)
{
	if(m_iCount == 0)
	{	
		char* ptr = new char[af->af[num].size];
		fseek(fp,af->af[num].point, SEEK_SET);
		fread(ptr,sizeof(char),af->af[num].size,fp);	
		int size = (int)af->af[num].size;
		//一時バッファ用
		LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
		//Xファイルの読み込み
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
		//メモリの破棄
		SAFE_DELETE(ptr);
		//マテリアル、サイズ、テクスチャの取得
		if(FAILED(LoadMtrl(pD3DXMtrlBuffer,dev,af))){return E_FAIL;}
		SAFE_RELEASE(pD3DXMtrlBuffer);
	}
	//カウントを進める
	m_iCount++;	
	return S_OK;
}
//モデルのカウント
int CModel::Release()
{
	m_iCount--;
	return m_iCount;
}
//テス==========================================================================
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

//デバッグ
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
