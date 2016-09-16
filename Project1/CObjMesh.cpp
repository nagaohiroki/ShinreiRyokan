//===========================================================================
//メッシュオブジェクト
//===========================================================================
CObjMesh::CObjMesh()
{
	ML = NULL;	
	//変数の初期化
	D3DXMatrixIdentity(&mWorld);	
	objPos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	objScal=D3DXVECTOR3(1.0f,1.0f,1.0f);
	YPR=D3DXVECTOR3(0.0f,0.0f,0.0f);
	Pare=NULL;
	MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
	drawSkip=FALSE;
	//描画上方
	MdlType=0;// オブジェクトのモデルの種類
	MeshCol=D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);//らいとの色(wはアルファ)
	SpCol=D3DXVECTOR4(1.0f,1.0f,1.0f,10.0f);//スペキュラ(wはパワー)
	SpColm=0.5f;//スペキュラの総数
	ShadowFlag=TRUE;//影をつけるか	
	Amb=1.0f;//アビエントの明るさ
	Shadow=0.8f;//影の薄さ
	Bias=0.035f;//影のバイアス
	BloomColor=D3DXVECTOR4(1.0f,1.0f,1.0f,0.0f);//ライトブルーム
	Height=0.016f;
	mCustom = NULL;

}
CObjMesh::~CObjMesh()
{
	if(ML != NULL)
	{
		DWORD i;
		for(i = 0; i < itMod->second->m_dwMatNum; i++)
		{
			ML->T.Release(itMod->second->m_pCMtrl[i].m_iTex);
			ML->T.Release(itMod->second->m_pCMtrl[i].m_iNTex);	
		}
		ML->M.Release(MdlType);
	}
}
//親オブジェクトを取得	
VOID CObjMesh::SetPare(const D3DXMATRIX* p)
{
	Pare = p;	
}

//オブジェクトの行列変換
VOID CObjMesh::UpdateMat()
{
	if(mCustom)
	{
		//行列を自分で設定する場合
		mWorld = *mCustom;
	}
	else
	{	//回転
		D3DXMatrixRotationYawPitchRoll(&mWorld,D3DXToRadian(YPR.y),D3DXToRadian(YPR.x),D3DXToRadian(YPR.z));
		//大きさ
		mWorld._11 *= objScal.x; 
		mWorld._12 *= objScal.x; 
		mWorld._13 *= objScal.x; 
		mWorld._21 *= objScal.y; 
		mWorld._22 *= objScal.y; 
		mWorld._23 *= objScal.y; 
		mWorld._31 *= objScal.z; 
		mWorld._32 *= objScal.z; 
		mWorld._33 *= objScal.z; 
		//位置
		mWorld._41 = objPos.x;
		mWorld._42 = objPos.y;
		mWorld._43 = objPos.z;
	}
	
	//親がある場合
	if(Pare)
	{
		D3DXMatrixMultiply(&mWorld,&mWorld,Pare);
	}
	
}
VOID CObjMesh::SetSp()
{
	//行列からスケール
	D3DXVECTOR3 MatScl(
	D3DXVec3Length(&D3DXVECTOR3(mWorld._11,mWorld._12,mWorld._13)),
	D3DXVec3Length(&D3DXVECTOR3(mWorld._21,mWorld._22,mWorld._23)),
	D3DXVec3Length(&D3DXVECTOR3(mWorld._31,mWorld._32,mWorld._33)));
	//内包球の半径
	*HitObj.Len() =itMod->second->Sren * vec3Ari().D3DXVec3Top(&MatScl);
	//中心位置
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	mat._41 = itMod->second->Center.x;
	mat._42 = itMod->second->Center.y;
	mat._43 = itMod->second->Center.z;
	D3DXMatrixMultiply(&mat,&mat,&mWorld);
	HitObj.Pos()->x = mat._41;
	HitObj.Pos()->y = mat._42;
	HitObj.Pos()->z = mat._43;
}
VOID CObjMesh::SetObb()
{
	//行列からスケール
	D3DXVECTOR3 MatScl(
	D3DXVec3Length(&D3DXVECTOR3(mWorld._11,mWorld._12,mWorld._13)),
	D3DXVec3Length(&D3DXVECTOR3(mWorld._21,mWorld._22,mWorld._23)),
	D3DXVec3Length(&D3DXVECTOR3(mWorld._31,mWorld._32,mWorld._33)));
	//中心位置	
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	mat._41 = itMod->second->Center.x;
	mat._42 =itMod->second->Center.y;
	mat._43 = itMod->second->Center.z;
	D3DXMatrixMultiply(&mat,&mat,&mWorld);
	HitObj.Pos()->x = mat._41;
	HitObj.Pos()->y = mat._42;
	HitObj.Pos()->z = mat._43;

	//各方向の
	D3DXVec3Normalize(HitObj.vX(),&D3DXVECTOR3(mWorld._11,mWorld._12,mWorld._13));
	D3DXVec3Normalize(HitObj.vY(),&D3DXVECTOR3(mWorld._21,mWorld._22,mWorld._23));
	D3DXVec3Normalize(HitObj.vZ(),&D3DXVECTOR3(mWorld._31,mWorld._32,mWorld._33));	
	//内包球の半径
	*HitObj.Len() = itMod->second->Sren * vec3Ari().D3DXVec3Top(&MatScl);
	//各辺の半径
	HitObj.Vec()->x = itMod->second->ren.x * MatScl.x;
	HitObj.Vec()->y = itMod->second->ren.y * MatScl.y;
	HitObj.Vec()->z = itMod->second->ren.z * MatScl.z;		
}



VOID CObjMesh::Type(arc xmod)
{
	if(ML == NULL)
	{
		MdlType = xmod;
	}
}
VOID CObjMesh::SetSize(MyLibrary* ml)
{
	if(ML == NULL)
	{
		ML = ml;
		itMod = ML->M.Load(MdlType,ML->D,&ML->af,ML->fp);
		for(DWORD i = 0; i < itMod->second->m_dwMatNum; i++)
		{
	
			itT.push_back( ML->T.load(itMod->second->m_pCMtrl[i].m_iTex, ML->D,&ML->af,ML->fp));
			itNT.push_back(ML->T.load(itMod->second->m_pCMtrl[i].m_iNTex,ML->D,&ML->af,ML->fp));
		}
	}
	UpdateMat();
}
VOID CObjMesh::SetHit(MyLibrary* ml) 
{
	SetSize(ml);

	switch(HitObj.cType)
	{
	case CT_OBB:	SetObb();	break;
	case CT_SPHERE:	SetSp();	break;
	default:break;
	}
	
}
VOID CObjMesh::HitMode(COLLISION_TYPE ct,COLLISION_BACK cb)
{
	HitObj.cType = ct;
	HitObj.cBack = cb;
}

//通常描画
VOID CObjMesh::MeshDraw()
{
	//オブジェクト固有の大きさ
	//親オブジェクト
	//視錐台カリング
	SetSp();//境界球のセット
	if(ML->E.Culling(HitObj.Pos(),*HitObj.Len())){return;}
	DWORD j0;	
	ML->E.mWVP(&mWorld);//ワールドトランス	
	//ポイントスポットライトの反射
	ML->E.LightLamSpc(&mWorld,Amb);
	D3DXVECTOR3 Lc(ML->E.LightCol());
	//鏡面反射の色
	ML->E.SpCol(&D3DXVECTOR4(
		SpCol.x * SpColm * Lc.x,
		SpCol.y * SpColm * Lc.y,
		SpCol.z * SpColm * Lc.z,
		SpCol.w));	//パワー
	//ライトブルームカラー
	ML->E.BloomColor(&D3DXVECTOR4(
		BloomColor.x * BloomColor.w,
		BloomColor.y * BloomColor.w,
		BloomColor.z * BloomColor.w,
		1.0f));
		
	//影の濃さとバイアス
	ML->E.ShadowBias(Bias,Shadow);
	//スポットライト
	ML->E.SetPLCol(&MeshCol);		
	D3DXVECTOR3 v(  MeshCol.x * Lc.x,
					MeshCol.y * Lc.y,
					MeshCol.z * Lc.z);
	ML->E.BeginPass( itMod->second->TexPass);
	for(j0 = 0; j0 < itMod->second->m_dwMatNum; j0++ )
	{	
		//メッシュのカラー
		ML->E.vCol(&D3DXVECTOR4(
			itMod->second->m_pCMtrl[j0].m_Mtrl.Diffuse.r * v.x,
			itMod->second->m_pCMtrl[j0].m_Mtrl.Diffuse.g * v.y,
			itMod->second->m_pCMtrl[j0].m_Mtrl.Diffuse.b * v.z,
			MeshCol.w));
		
		//テクスチャをセット
		if(itT[j0] != ML->T.tex.end())
		{
			ML->E.Tex(itT[j0]->second->m_pTex);
		}

		if(itNT[j0] != ML->T.tex.end())
		{
			ML->E.MTex(itNT[j0]->second->m_pTex);
		}

		ML->E.CommitChange();	
		//メッシュ・サブセットの描画
		itMod->second->m_pMesh->DrawSubset( j0 );
	}
}
VOID CObjMesh::ShadowDraw()
{
	//シャドウマップ	
	if(!ShadowFlag){return;}	
	ML->E.mWVP(&mWorld);//ワールドトランス
	//視錐台カリング
	if(ML->E.Culling(HitObj.Pos(),*HitObj.Len())){return;}
	DWORD j0;
	ML->E.vCol(&D3DXVECTOR4(0.1f,0.1f,0.1f,0.1f));
	switch(itMod->second->TexPass)
	{
	case fx::Mesh_AlphaTex:
		//メッシュ(テクスチャありαテクスチャ用)
		ML->E.BeginPass(fx::ShadowAlphaMap);
		for(j0=0; j0 < itMod->second->m_dwMatNum ; j0++ )
		{
			//テクスチャをセット
			if(itT[j0] != ML->T.tex.end())
			{
				ML->E.Tex(itT[j0]->second->m_pTex);
			}
			ML->E.CommitChange();
			itMod->second->m_pMesh->DrawSubset(j0);
		}			
		break;
	default:
		//メッシュのみで描画
		ML->E.BeginPass(fx::ShadowMap);
		for(j0=0; j0 < itMod->second->m_dwMatNum; j0++ )
		{
			ML->E.CommitChange();
			itMod->second->m_pMesh->DrawSubset(j0);
		}
		break;		
	}	
}

VOID CObjMesh::draw(MyLibrary* ml)
{
	if(drawSkip == TRUE){return;}
	if(ml->E.ShadowPassNum == 0)
	{
		MeshDraw();
	}
	else
	{
		SetSize(ml);//シャドウマップを先に呼び出すので先に取得	
		ShadowDraw();
	}
}