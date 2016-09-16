//基底オブジェクト

//===========================================================================
//FVFテクスチャの描画
//===========================================================================
CObjFVF::CObjFVF()
{	

	ML = NULL;
	TexType = -1;
	MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
	Pass    = fx::FVF;
	D3DXMatrixIdentity(&mWorld);
	objPos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	objScal=D3DXVECTOR3(1.0f,1.0f,1.0f);
	YPR=D3DXVECTOR3(0.0f,0.0f,0.0f);
	Pare=NULL;
	MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
	drawSkip=FALSE;	

}
CObjFVF::~CObjFVF()
{
	if(ML != NULL)
	{
		ML->T.Release(TexType);
	}
}
//親オブジェクトを取得	
VOID CObjFVF::SetPare(const D3DXMATRIX* p)
{
	Pare = p;	
}
//オブジェクトの行列変換
VOID CObjFVF::UpdateMat()
{
	D3DXMATRIX  mS;//スケールの行列
	D3DXMATRIX  mR;//回転の行列
	//行列を初期化
	D3DXMatrixIdentity(&mWorld);
	// 拡大縮小用の行列を設定
	D3DXMatrixScaling(&mS,objScal.x ,objScal.y ,objScal.z );
	//回転設定
	D3DXMatrixRotationYawPitchRoll( &mR ,D3DXToRadian(YPR.y),D3DXToRadian(YPR.x),D3DXToRadian(YPR.z));
	//スケール*回転
	D3DXMatrixMultiply(&mWorld,&mS,&mR);
	//位置は最後に
	mWorld._41=objPos.x;
	mWorld._42=objPos.y;
	mWorld._43=objPos.z;
	//親がある場合
	if(Pare){D3DXMatrixMultiply(&mWorld,&mWorld,Pare);}
}
VOID CObjFVF::SetTex(arc textype)
{
	if(ML == NULL)
	{
		Pass = fx::FVF_Tex;
		TexType = textype;
	}
}
VOID CObjFVF::SetTex(arc textype,fx::Pass pass)
{
	if(ML == NULL)
	{
		Pass = pass;
		TexType = textype;
	}
}


VOID CObjFVF::draw(MyLibrary* ml)
{
	if(drawSkip){return;}
	if(ml->E.ShadowPassNum==1){return;}//シャドウパスの場合はスルー
	if(ML == NULL)
	{
		ML = ml;
		it = ML->T.load(TexType,ML->D,&ML->af,ML->fp);
		
	}
	
	if(TexType == -1){	Pass = fx::FVF;	}
	else
	{
		if(it != ML->T.tex.end()){	ML->E.Tex((*it).second->m_pTex);	}		
	}	
	
	UpdateMat();
	ML->E.mWVP(&mWorld);	
	ML->E.vCol(&MeshCol);
	
	ML->F.SetStream(ML->D);
	
	ML->E.BeginPass(Pass);	
	ML->E.CommitChange();
	ML->D->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2);	
}

VOID CObjFVF::draw(MyLibrary* ml,LPDIRECT3DTEXTURE9 pTex,int fxPass)
{
	if(drawSkip){return;}
	if(ml->E.ShadowPassNum==1){return;}//シャドウパスの場合はスルー
	UpdateMat();
	ml->E.mWVP(&mWorld);	
	ml->E.vCol(&MeshCol);
	ml->F.SetStream(ml->D);
	ml->E.Tex(pTex);
	ml->E.BeginPass(fxPass);	
	ml->E.CommitChange();
	ml->D->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2);	
}
//ミラー描画
VOID CObjFVF::drawMirror(MyLibrary* ml)
{
	if(ml->E.MirrorFlag == FALSE){ return;}
	if(drawSkip)
	{
		ml->E.MirrorFlag = FALSE;		
		return;
	}
	if(ml->E.ShadowPassNum==1){return;}//シャドウパスの場合はスルー
	if(ml->E.MirrorPass == 1 ){return;}//鏡自身は描画しない
	UpdateMat();
	ml->E.mWVP(&mWorld);	
	ml->E.vCol(&MeshCol);
	ml->FMirror.SetStream(ml->D);
	ml->E.Tex(ml->Sf.Retex(SU_MIRROR));
	ml->E.BeginPass(fx::FVF_Tex);	
	ml->E.CommitChange();
	ml->D->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2);
//	ml->E.MirrorPass = 0;

}