//=================================================================
//エフェクト
//=================================================================
//エフェクトの設定
CEffect::CEffect()
{
	//ポインタ
	m_pEffect=NULL;	
	//ハンドル
	m_hTechnique=NULL;
	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);
	D3DXMatrixIdentity(&matPxV);	
	ShadowFlag=TRUE;	
	//beginを使用しているかのフラグ	
	BeginFlag=FALSE;
	fxPass=0;
	PassFlag=FALSE;
	CullPos=D3DXVECTOR3(0,0,0);
	Handle=NULL;
	pass=0;
	Fade = 1.0f;

	Tone = D3DXVECTOR4(1.0f,1.8f,5.0f,1.0f);
	MirrorPass = 0;
	MirrorFlag = FALSE;
}

CEffect::~CEffect()
{
	SAFE_DELETE_ARRAY(Handle);
	SAFE_RELEASE(m_pEffect);	//エフェクトの破棄
}

//リセット前に行う
HRESULT CEffect::Reset()
{
	if(m_pEffect != NULL)
	{
		if(FAILED(m_pEffect->OnLostDevice()))
		{
			CFile().Debug(_T("Effectリセット失敗\n"));
			return E_FAIL;
		}
	}
	return S_OK;

}
//リセット後に再取得
HRESULT CEffect::Restore()
{
	if(m_pEffect != NULL)
	{
		if(FAILED(m_pEffect->OnResetDevice()))
		{
			CFile().Debug(_T("Effectリセット後取得失敗\n"));
			return E_FAIL;
		}
	}	
	return S_OK;
}
//ハンドルのセット
HRESULT CEffect::SetHandle()
{
	m_hTechnique = m_pEffect->GetTechniqueByName("TShader");
	//パラメータの読み込み
	D3DXPARAMETER_DESC ParamDesc;
	D3DXEFFECT_DESC desc;
	m_pEffect->GetDesc(&desc);	
	D3DXHANDLE hand = NULL;
	Handle = new D3DXHANDLE[prm::PRM_MAX];
	UINT i;
	for(i=0;i<prm::PRM_MAX;i++)
	{
		hand = m_pEffect->GetParameter(NULL,i);
		if(FAILED(m_pEffect->GetParameterDesc(hand,&ParamDesc)))
		{
			CFile().Debug(_T("Effectのパラメータの取得失敗\n"));
			return E_FAIL;
		}
		Handle[i] = NULL;
		Handle[i] = m_pEffect->GetParameterByName(NULL,ParamDesc.Name);
	}
	//ガウスの重み
	SetGaussWeight(0.001f);
	return S_OK;
}
//メモリからエフェクトファイルを読み込み
HRESULT CEffect::Create(LPDIRECT3DDEVICE9 dev,char* ptr,UINT size)
{
	//エフェクトを作成
	if(FAILED(D3DXCreateEffect(
		dev,
		ptr,
		size,	
		NULL,
		NULL,
		D3DXSHADER_SKIPVALIDATION,
		NULL,
		&m_pEffect,
		NULL)))
	{
		CFile().Debug(_T("エフェクト作成失敗\n"));
		return E_FAIL;
	}
	//パラメータをハンドルにセット
	if(FAILED(SetHandle())){return E_FAIL;}
	return S_OK;
}
//ファイルからエフェクトを作成
HRESULT CEffect::Create(LPDIRECT3DDEVICE9 dev)
{
	
	//エフェクトを作成
	if(FAILED(D3DXCreateEffectFromFile(
		dev,
		_T(".\\mydata\\.\\HLSL\\.\\main_hlsl.cfx"),
		NULL,
		NULL,
		D3DXSHADER_SKIPVALIDATION,
		NULL,
		&m_pEffect,
		NULL)))
	{
		CFile().Debug(_T("HLSL読み込み失敗\n"));
		return E_FAIL;
	}
	//パラメータをハンドルにセット
	if(FAILED(SetHandle())){return E_FAIL;}
	return S_OK;
}

//各パラメータを返す
D3DXHANDLE CEffect::Hn(size_t n)
{
	return Handle[n];
}

//スポットライトのベクトルと位置
VOID CEffect::UpdatePointLight()
{
	D3DXVECTOR3 v;
	//スポットライトのベクトル
	D3DXVec3Normalize(&v,&(PSL.Pos - PSL.Vec));
	m_pEffect->SetVector(Hn(prm::float4_PLightPos),
	&D3DXVECTOR4(PSL.Pos.x,PSL.Pos.y,PSL.Pos.z,PSL.dis));//wは減衰率
	m_pEffect->SetVector(Hn(prm::float4_PLightVec),
	&D3DXVECTOR4(v.x,v.y,v.z,PSL.Lcos));

}

//ポイントライト
VOID CEffect::SetPLCol(D3DXVECTOR4* c)
{
	
	D3DXVECTOR4 Dif;
	//デフューズwが0.0f以下だとライト無効
	Dif.x=c->x * PSL.Col.x * PSL.Col.w;
	Dif.y=c->y * PSL.Col.y * PSL.Col.w;
	Dif.z=c->z * PSL.Col.z * PSL.Col.w;
	Dif.w=0.0f;
	m_pEffect->SetVector(Hn(prm::float4_PLightDif),&D3DXVECTOR4(
		c->x * PSL.Col.x * PSL.Col.w,
		c->y * PSL.Col.y * PSL.Col.w,
		c->z * PSL.Col.z * PSL.Col.w,
		0.0f));
	
}

VOID CEffect::UpdateLight()
{	
#if 0
	//通常のシャドウマップ
	if(Ls==*L){return;}
	Ls=*L;
	//ライト視点のカメラをセット
	D3DXMATRIX mLView;
	D3DXMATRIX mLProj;
    D3DXMatrixLookAtLH(&mLView,
		&Ls.Pos,
		&Ls.At,
		&D3DXVECTOR3( 0,1.0f,0));
    D3DXMatrixPerspectiveFovLH( &mLProj,
		D3DXToRadian(Ls.Pars),
		1.0f,
		Ls.Near,
		Ls.Far );	
	D3DXMatrixMultiply(&matLight,&mLView,&mLProj);
	m_pEffect->SetMatrix(Hn(HN_mLight),&matLight);
#else
	D3DXVECTOR3 Eye = cam.Eye + Ls.EyePlus;
	D3DXVECTOR3 Lvec(Ls.At-Ls.Pos);
	D3DXVECTOR3 Cvec(cam.At-cam.Eye);
	D3DXVec3Normalize(&Lvec,&Lvec);
	D3DXVec3Normalize(&Cvec,&Cvec);
	//LiSPSM
	Lisp.MatLiSPSM(
		&matLight,
		&matView,
		&Lvec,
		&Cvec,
		&Eye,
		D3DXToRadian(Ls.Pars),
		cam.wh.x/cam.wh.y,
		0.1f,Ls.Far
		);
	m_pEffect->SetMatrix(Hn(prm::float4x4_mLight),&matLight);

#endif
}
D3DXVECTOR3 CEffect::LightCol()
{
	return D3DXVECTOR3(Ls.Col.x,Ls.Col.y,Ls.Col.z);
}
VOID CEffect::LightLamSpc(D3DXMATRIX* m,float amb)
{
	if(m_pEffect)
	{
	
		//ライトの位置とカメラの位置(ローカル)
		D3DXVECTOR4 v;
		D3DXMatrixIdentity(&mL);
		//ランバート反射のセット
		D3DXMatrixInverse(&mL,NULL,m);
		D3DXVec4Transform(&v,&D3DXVECTOR4(Ls.Pos,1.0f),&mL);
		D3DXVec4Normalize(&v,&v );
		v.w = Ls.Col.w * 0.5f * amb;//アビエントの強さ
		m_pEffect->SetVector(Hn(prm::float4_vLightDir),&v );

		//鏡面反射
		D3DXMatrixMultiply(&mL,m,&matView);
		D3DXMatrixInverse(&mL,NULL,&mL);
		v=D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
		D3DXVec4Transform(&v,&v,&mL);
		m_pEffect->SetVector(Hn(prm::float3_vEyePos),&v);
		
	}

}

//影の濃さとバイアス
VOID CEffect::ShadowBias(float bias,float shadow)
{
	if(m_pEffect)
	{
		
		m_pEffect->SetVector(Hn(prm::float4_SBias),&D3DXVECTOR4(bias * Ls.Bias,shadow * Ls.Shadow,0,0));
		
	}
}

VOID CEffect::UpdateFog()
{
	//距離フォグ
	float fr = Fs.Far - 2.0f;//最長距離
	float f  =(fr-(Fs.Near - 1.0f));
	m_pEffect->SetInt(Hn(prm::int_vFogUse),Fs.use);//オンオフ
	m_pEffect->SetVector(Hn(prm::float4_vFog),&D3DXVECTOR4(fr/f,-1.0f/f,0,0));//ニアパー
	m_pEffect->SetVector(Hn(prm::float4_vFogColor),&D3DXVECTOR4(Fs.Col.x,Fs.Col.y,Fs.Col.z,0));//色
	
}	

VOID CEffect::UpdateCam()
{
	ShadowPassNum = 0;//パスの変更(通常描画)
	//ビューの設定
	D3DXMatrixLookAtLH(&matView,&cam.Eye,&cam.At,&cam.Up);
	//　投影行列を設定。
	//　視野角、アスペクト比、視覚クリッピング用の最接近距離と最遠方距離の四つが必要
	D3DXMatrixPerspectiveFovLH(	
		&matProj,
		D3DXToRadian(cam.Pars),	// 視野角
		cam.wh.x/cam.wh.y,		// アスペクト比
		cam.Near,		// 最近接距離
		cam.Far);	// 最遠方距離
	// ビューマトリクスの設定
	D3DXMatrixMultiply(&matPxV,&matView,&matProj);	
	m_pEffect->SetMatrix(Hn(prm::float4x4_mVP),&matPxV);
	//カリング
	D3DXVECTOR3 nvec;
	D3DXVec3Normalize(&nvec,&(cam.At - cam.Eye));
	CullPos = cam.Eye + nvec * cam.Far;
	
}	

//各エフェクト
//ワールドトランス
VOID CEffect::mWVP(D3DXMATRIX *m)
{
	if(m_pEffect)
	{
		m_pEffect->SetMatrix(Hn(prm::float4x4_mW),m);
	}

}


//メッシュのカラー
VOID CEffect::vCol(D3DXVECTOR4 *vec)
{
	if(m_pEffect)
	{
		m_pEffect->SetVector(Hn(prm::float4_vColor),vec);
	}
}

//スペキュラカラー
VOID CEffect::SpCol(D3DXVECTOR4 *vec)
{
	if(m_pEffect)
	{
		m_pEffect->SetVector(Hn(prm::float4_SP),vec);
	}
}

//テクスチャをセット
VOID CEffect::Tex(LPDIRECT3DTEXTURE9 pTex)
{
	if(m_pEffect)
	{
		if(pTex)
		{
			m_pEffect->SetTexture(Hn(prm::texture_Tex),pTex);
		}
	}
}

//=================================================================
//シャドウマップ
//================================================================
//パスを変更
//シャドウマップビギン
VOID CEffect::BeginSh()
{
	ShadowPassNum = 1;
	
}

VOID CEffect::ShadowMapSet(LPDIRECT3DTEXTURE9 tex)
{
	if(m_pEffect)
	{
		if(tex)
		{
			m_pEffect->SetTexture(Hn(prm::texture_ShadowTex),tex);
		}
	}
	ShadowPassNum = 0;
}

//====================================================================
//バンプマップ
//====================================================================
//法線マップ(今後モデルに関連したテクスチャをはる)
VOID CEffect::MTex(LPDIRECT3DTEXTURE9 pTex)
{	
	if(m_pEffect)
	{
		if(pTex)
		{
			m_pEffect->SetTexture( Hn(prm::texture_NormalTex),pTex);
		}
	}
}

//=======================================================
//パスの設定
//=======================================================
//パス内の変更を知らせる
VOID CEffect::CommitChange()
{
	if(m_pEffect)
	{
		m_pEffect->CommitChanges();
	}
}
VOID CEffect::begin()
{
	if(m_pEffect)
	{
		if(BeginFlag)
		{
			m_pEffect->EndPass();
			m_pEffect->End();
			BeginFlag=FALSE;
			PassFlag=TRUE;//パス消滅
		}
		m_pEffect->SetTechnique( m_hTechnique );
		m_pEffect->Begin(&pass, 0 );
		BeginFlag=TRUE;
	}
}

//パスの変更があった場合変更する
VOID CEffect::BeginPass(int Pass)
{
	if(m_pEffect)
	{
		if(fxPass != Pass || PassFlag == TRUE)
		{
			m_pEffect->EndPass();
			fxPass=Pass;
			m_pEffect->BeginPass(Pass);
			PassFlag=FALSE;//パス復帰
		}
	}
}
//視錐台カリング
BOOL CEffect::Culling(D3DXVECTOR3* Pos,float len)
{
	D3DXVECTOR3 vec;
	D3DXVec3Normalize(&vec,&CullPos);
	//距離
	if(D3DXVec3Dot(Pos,&vec) > len + cam.Far){	return TRUE;}
	//球の中
	if(D3DXVec3LengthSq(&(*Pos - CullPos)) > (len + cam.Far) * (len + cam.Far)){	return TRUE;}

	return FALSE;
}

//トーンマッピング
VOID CEffect::ToneMap()
{
	if(m_pEffect)
	{
		m_pEffect->SetVector(Hn(prm::float4_PixelUV),&Tone);
	}
}
//ブルームカラー
VOID CEffect::BloomColor(D3DXVECTOR4* bcolor)
{
	if(m_pEffect)
	{
		m_pEffect->SetVector(Hn(prm::float4_BloomColor),bcolor);
	}
}

//ガウスのマップサイズ
VOID CEffect::SetGaussMap(float x,float y)
{	
	if(m_pEffect)
	{
		m_pEffect->SetVector(Hn(prm::float4_GaussMap),&D3DXVECTOR4(1.0f/x,1.0f/y,0.0f,0.0f));
	}
}
//ガウスの重み
VOID CEffect::SetGaussWeight(float dis)
{
	if(m_pEffect)
	{
		const int W_NUM = 6;
		float w[W_NUM];
		int i;
		float Pos=0.0f;
		float total=0.0f;
			for(i = 0;i < W_NUM;i++)
		{
			Pos = 2.0f * (float)i;
			w[i] = expf(-Pos * Pos * dis);
			total += w[i];
		}
		for(i = 0;i < W_NUM;i++)
		{
			w[i] = w[i] / total;
		}
		
		for(i = 1;i < W_NUM;i++)
		{
			w[i] *= 0.5f;
		}
		m_pEffect->SetFloatArray(Hn(prm::float_w),w,6);

	}
}


//スクリーン用
VOID CEffect::ScreenView(LPDIRECT3DDEVICE9 dev,UINT w,UINT h)
{
	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	m._11 = (2.0f / (float)w);
	m._22 = (2.0f / (float)h);
	if(m_pEffect)
	{
		m_pEffect->SetMatrix(Hn(prm::float4x4_mVP),&m);
	}
	//ビューポートの設定
	begin();
	dev->Clear( 0, NULL,D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
}

//エフェクトの更新
VOID CEffect::UpdateEffect(float x,float y)
{
		//フェードインアウト
	Fade -=0.1f;
	if(Fade > 1.0f){Fade=1.0f;}
	if(Fade < 0.0f){Fade=0.0f;}

	cam.wh.x = x;
	cam.wh.y = y;
	UpdateCam();

	UpdateFog();
	UpdatePointLight();
	UpdateLight();
	ToneMap();
}
VOID CEffect::UpdateEffect()
{
	UpdateFog();
	ToneMap();

}

VOID CEffect::InitEffect()
{	
	MirrorFlag = FALSE;
	Mirrorcam.Init();

	Fade  = 1.0f;
	Fs.Init();
	Ls.Init();
	PSL.Init();
	cam.Init();
}