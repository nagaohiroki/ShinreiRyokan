
//==========================================================================
//女子トイレ
//==========================================================================
Rest_Women::Rest_Women()
{
}
VOID Rest_Women::Set()
{
	P->FM.FldType = FD_Rest_Women;
	//あたり判定------------------------------------------------------------------------
	//洗面台
	pHitSenmen = NewObj(new HitBox);
	pHitSenmen->Ob()->objPos=D3DXVECTOR3(-1.50f,0.00f,-2.00f);
	pHitSenmen->Ob()->objScal=D3DXVECTOR3(2.30f,2.20f,4.10f);
	//仕切り
	pHitSikiri = NewObj(new HitBox);
	pHitSikiri->Ob()->objPos=D3DXVECTOR3(-1.3f,0.00f,0.33f);
	pHitSikiri->Ob()->objScal=D3DXVECTOR3(3.50f,6.80f,5.5f);
	//描画------------------------------------------------------------------------
	//出入り口
	pExit = NewObj(new Door);
	pExit->Ob()->objPos=D3DXVECTOR3(0,0,-3.0f);
	//部屋全体
	pRoom = NewObj(new drawObj);
	pRoom->Ob()->Type(x_women_rest);
	pRoom->Ob()->ShadowFlag=FALSE;
	pRoom->Ob()->Bias=0.02f;
	pRoom->Ob()->SpColm=0.0f;
	//ドア
	pDoor = NewObj(new drawObj);
	pDoor->Ob()->ShadowFlag = FALSE;
	pDoor->Ob()->Type(x_rest_door);
	pDoor->Ob()->objPos=D3DXVECTOR3(-0.46f,0.00f,-0.70f);
	pDoor->Ob()->YPR=D3DXVECTOR3(0.00f,180.00f,0.00f);
	//ドア
	pDoor1 = NewObj(new drawObj);
	pDoor1->Ob()->ShadowFlag = FALSE;
	pDoor1->Ob()->Type(x_rest_door);
	pDoor1->Ob()->objPos=D3DXVECTOR3(-0.46f,0.00f,0.60f);
	pDoor1->Ob()->YPR=D3DXVECTOR3(0.00f,180.00f,0.00f);
	//ドア
	pDoor2 = NewObj(new Rest_Women_Door);
	pDoor2->Ob()->objPos=D3DXVECTOR3(-0.46f,0.00f,1.96f);
	//ハンドル
	pHandle = NewObj(new Rest_handle);
	pHandle->Ob()->objPos=D3DXVECTOR3(-1.47f,0.555f,-1.46f);
	//ハンドル
	pHandle1 = NewObj(new Rest_handle);
	pHandle1->Ob()->objPos=D3DXVECTOR3(-1.47f,0.555f,-2.46f);
	//通気口
	pDact = NewObj(new drawObj);
	pDact->Ob()->Type(x_tdact);
	pDact->Ob()->objPos=D3DXVECTOR3(0.00f,1.90f,3.00f);
	pDact->Ob()->ShadowFlag=FALSE;
	//ライト
	pLight = NewObj(new Light);
	pLight->Ob()->objPos=D3DXVECTOR3(0.00f,2.20f,1.00f);
	//鏡
	pMirror = NewObj(new Mirror);
	pMirror->Fvf[0]->objPos = D3DXVECTOR3(-2.01f,1.0f,-2.0f);	
	pMirror->Fvf[0]->objScal = D3DXVECTOR3(1.7f,1.0f,1.0f);	
	pMirror->Fvf[0]->YPR = D3DXVECTOR3(0.0f,270.0f,0.0f);	
	//トイレ
	pToile = NewObj(new Toile);
	pToile->Ob()->objPos = D3DXVECTOR3(-1.8f,0.0f,2.4f);
	pToile->Ob()->YPR.y = 90.0f;
	//*
	if(!P->FM.iGetedFlag(ITEM_ROOF_KEY))
	{
		//敵
		pEnemy = NewObj(new Enemy);
		P->FM.enemy.HP = 5;
		P->FM.enemy.pos = D3DXVECTOR3(-1.0f,0.35f,2.3f);
		P->FM.enemy.rot = 90.0f;
		P->FM.enemy.Level = 0;

		//鍵
		pKey = NewObj(new Rest_Women_Key);
		pKey->Ob()->objPos = D3DXVECTOR3(1.0f,0.0f,2.55f);
		pKey->Ob()->YPR.y = 50.0f;
		//テキスト
		pText = NewObj(new Rest_Women_Text);
		pText->Ob()->objPos=D3DXVECTOR3(0,0,-3.0f);
	
	}
	//*/
	//シェーダ-----------------------------------------------------------------
	//オーディオ-------------------------------------------------------------
	ML->Audio.Audio.Effect = AE_SMALLROOM;
	//シェーダ-----------------------------------------------------------------
	//ライト
	ML->E.Ls.Near=6.50f;
	ML->E.Ls.Far=10.40f;
	ML->E.Ls.Pos=D3DXVECTOR3(0.00f,10.00f,1.00f);
	ML->E.Ls.Col = D3DXVECTOR4(0.7f,0.7f,0.8f,1.0f);
	//フォグ
	ML->E.Fs.Col.x = 0.600000f;
	ML->E.Fs.Col.y = 0.600000f;
	ML->E.Fs.Col.z = 0.700000f;
	ML->E.Fs.Far = 13.727310f;
	ML->E.Fs.Near = 3.000000f;
	ML->E.Fs.use = 1;
	//フィールドの当たり判定-------------------------------------------------------------
	EriaHit(&D3DXVECTOR3(-2.0f,0.0f,-2.9f),&D3DXVECTOR3(1.95f,2.2f,2.90f));
}
VOID Rest_Women::Update()
{
	//敵がいるときは開かない
	if(P->FM.enemy.mode != Enemy::MODE_STALK_ATTACK)
	{
		if(pExit->HitObjFlag(0))
		{		
			if(P->Check)
			{
				P->CheckSE(Personal::SE_OPEN);
				FldChange(new F3,&D3DXVECTOR3(-21.0f,2.55f,24.42f),0.0f);
			}

		}
	}
	D3DXVECTOR3 Eye(1.9f,1.8f,-2.9f);
	D3DXVECTOR3 At(P->obj.objPos);

	if(P->obj.objPos.z > 1.5f)
	{
		Eye = D3DXVECTOR3(3.0f,1.5f,2.0f); 
		At = D3DXVECTOR3(-1.8f,0.0f,2.0f);
	}
	ML->E.cam.CamSet(&Eye,&At);
}