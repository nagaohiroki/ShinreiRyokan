

//================================================================
//ロビーのトイレ
//================================================================
LobbyRestRoom::LobbyRestRoom()
{
}
VOID LobbyRestRoom::Set()
{
	P->FM.FldType = FD_LobbyRestRoom;

	//移動----------------------------------------------------------

	//描画----------------------------------------------------------
	//ドア--------------------------------------------------------------ロビーに移動
	pDoor =NewObj(new Door(Door::F0_WC,Door::F1_KEY_GREEN,Door::F2_WOOD));
	pDoor->Ob()->objPos=D3DXVECTOR3(0,0,-1.8f);

	//トイレルーム
	pRest = NewObj(new drawObj);
	pRest->Ob()->Type(x_restroom);
	pRest->Ob()->SpColm=0.5f;
	pRest->Ob()->ShadowFlag=FALSE;
	
	//トイレットペ-パー
	pToile = NewObj(new drawObj);
	pToile->Ob()->Type(x_tpaper);
	pToile->Ob()->objPos=D3DXVECTOR3(0.91f,0.80f,0.40f);
	pToile->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);

	//排気口
	pDact = NewObj(new drawObj);
	pDact->Ob()->Type(x_tdact);
	pDact->Ob()->objPos=D3DXVECTOR3(0.00f,2.10f,1.80f);
	pDact->Ob()->ShadowFlag=FALSE;

	//流し
	pSink = NewObj(new drawHitObj);
	pSink->Ob()->Type(x_tsink);
	pSink->Ob()->objPos=D3DXVECTOR3(0.96f,0.55f,-0.34f);
	pSink->Ob()->objScal=D3DXVECTOR3(1.20f,1.50f,1.00f);
	pSink->Ob()->YPR=D3DXVECTOR3(0.00f,-90.00f,0.00f);
	
	//トイレ
	pToile = NewObj(new Toile);
	pToile->Ob()->objPos=D3DXVECTOR3(0.2f,0.00f,1.36f);
	pToile->Ob()->YPR=D3DXVECTOR3(0.00f,180.00f,0.00f);
	pToile->Ob()->objScal=D3DXVECTOR3(1.5f,1.5f,1.5f);
	//オーディオ---------------------------------------------------
	ML->Audio.Audio.Effect = AE_SMALLROOM;
	//シェーダ-----------------------------------------------------------------
	//フォグ
	ML->E.Fs.Col=D3DXVECTOR3(1.34f,1.39f,0.99f);
	//ライト
	ML->E.Ls.Near=4.00f;
	ML->E.Ls.Far=6.10f;
	ML->E.Ls.Col=D3DXVECTOR4(1.36f,1.10f,1.00f,1.00f);
	ML->E.Ls.Pos=D3DXVECTOR3(0.00f,5.60f,0.70f);
	//フィールドの当たり判定-------------------------------------------------------------
//	WallXmXZmZ(0.90f,-0.90f,1.80f,-1.80f);
	EriaHit(&D3DXVECTOR3(-0.9f,0.0f,-1.8f),&D3DXVECTOR3(0.9f,2.45f,1.80f));

}

VOID LobbyRestRoom::Update()
{

	//フィールドチェンジ(ロビーへ)
	if(P->Check)
	{
		if(pDoor->HitObjFlag(0))
		{
			P->CheckSE(Personal::SE_OPEN);
			FldChange(new Lobby,&D3DXVECTOR3(-10.0f,0.5f,13.0f),180.0f);
			P->FM.Door=0;
		}
	}
	//カメラ
	ML->E.cam.CamSet(&D3DXVECTOR3(0.0f,2.7f,1.5f),&P->obj.objPos);	
}
