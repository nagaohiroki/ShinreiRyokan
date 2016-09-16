//=======================================================
//脱衣所(女湯)
//=======================================================
Bath_Datui_Woman::Bath_Datui_Woman(){}
VOID Bath_Datui_Woman::Set()
{
	P->FM.FldType = FD_Bath_Datui_Woman;
	//あたり判定---------------------------------------------------------------------------
	//洗面
	pHitSenmen = NewObj(new HitBox);
	pHitSenmen->Ob()->objPos=D3DXVECTOR3(-2.93f,0.058f,1.637f);
	pHitSenmen->Ob()->objScal=D3DXVECTOR3(2.00f,1.74f,4.520f);

	//入り口
	pMovePass = NewObj(new Ev::Datui_Door);
	pMovePass->Ob()->objPos=D3DXVECTOR3(-3.17f,0.00f,-2.50f);

	//女湯へ
	pMoveBath = NewObj(new Datui_Harigami);
	pMoveBath->Ob()->objPos=D3DXVECTOR3(-6.10f,0.00f,2.50f);
	pMoveBath->Ob()->objScal=D3DXVECTOR3(2.60f,1.00f,1.00f);
	//描画オブジェクト---------------------------------------------------------------------------
	//フィールド全体
	pDatui = NewObj(new drawObj);
	pDatui->Ob()->Type(x_bath_datui_woman);
	pDatui->Ob()->ShadowFlag=FALSE;
	pDatui->Ob()->SpColm=0.0f;
	//体重計
	pTaiju = NewObj(new Ev::drawHitObj);
	pTaiju->Ob()->Type(x_taijukei);
	pTaiju->Ob()->objPos=D3DXVECTOR3(-3.00f,0.00f,0.00f);
	pTaiju->Ob()->YPR=D3DXVECTOR3(0.00f,-90.00f,0.00f);
	pTaiju->Ob()->Bias=0.16f;

	//かご
	pKago = NewObj(new Ev::drawHitObj);
	pKago->Ob()->Type(x_kagidana);
	pKago->Ob()->objPos=D3DXVECTOR3(-7.15f,-0.50f,-1.70f);
	pKago->Ob()->objScal=D3DXVECTOR3(1.00f,1.00f,0.80f);

	//扇風機
	pSenpu = NewObj(new Senpu);
	pSenpu->Ob()->objPos=D3DXVECTOR3(-5.00f,0.00f,-2.10f);

	//ミラー
	pMirror = NewObj(new Mirror);
	pMirror->Fvf[0]->YPR = D3DXVECTOR3(0.0f,90.0f,0.0f);
	pMirror->Fvf[0]->objPos = D3DXVECTOR3(-2.4f,1.0f,1.6f);	
	pMirror->Fvf[0]->objScal = D3DXVECTOR3(2.7f,1.0f,1.0f);

	//時計
	pClock = NewObj(new Clock);
	pClock->Ob()->objPos = D3DXVECTOR3(-7.5f,1.75f,2.1f);
	pClock->Ob()->YPR = D3DXVECTOR3(0.0f,90.0f,0.0f);
	//敵
	if(P->FM.EventFlag < TL_TIME5)
	{	
		P->FM.enemy.Level = 0;
		P->FM.enemy.HP = 5;
		P->FM.enemy.pos = D3DXVECTOR3(-5.0f,0.35f,0.0f);
		pEnemy = NewObj(new Enemy);
		pDatuiEnemy = NewObj(new Datui_Enemy);
	}
	//オーディオ---------------------------------------------
	ML->Audio.Audio.Effect = AE_LIVINGROOM;
	//シェーダ-----------------------------------------------------------------
	//ライト
	ML->E.Ls.Near=34.5f;	
	ML->E.Ls.Far=42.5f;
	ML->E.Ls.Pos=D3DXVECTOR3(0.00f,40.30f,1.00f);
	ML->E.Ls.At=D3DXVECTOR3(0.00f,0.00f,0.00f);
	ML->E.Ls.Col=D3DXVECTOR4(1.0f,1.0f,1.0f,1.00f);
	//フォグ
	ML->E.Fs.Near=-50.00f;
	ML->E.Fs.Far=120.00f;
	ML->E.Fs.Col=D3DXVECTOR3(0.5f,0.5f,0.75f);
	ML->E.Fs.use = TRUE;
	//フィールドの当たり判定-------------------------------------------------------------
	EriaHit(&D3DXVECTOR3(-7.40f,0.0f,-2.40f),&D3DXVECTOR3(-2.70f,2.0f,2.40f));
}
VOID Bath_Datui_Woman::Update()
{
	ML->E.cam.CamSet(&D3DXVECTOR3(-7.45f,1.9f,2.0f),&P->obj.objPos);
}
