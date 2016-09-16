
//=======================================================
//脱衣所男
//=======================================================
Bath_Datui_Man::Bath_Datui_Man()
{
}
VOID Bath_Datui_Man::Set()
{
	P->FM.FldType = FD_Bath_Datui_Man;
	//あたり判定---------------------------------------------------------------------------
	//入り口
	pMovePass = NewObj(new Ev::HitFlag);
	pMovePass->Ob()->objPos=D3DXVECTOR3(-2.00f,0.00f,-2.50f);
	pMovePass->Ob()->MeshCol=D3DXVECTOR4(1.00f,1.00f,1.00f,0.50f);
	//男湯へ
	pMoveBath = NewObj(new Ev::HitFlag);
	pMoveBath->Ob()->objPos=D3DXVECTOR3(1.10f,0.00f,2.50f);
	pMoveBath->Ob()->objScal=D3DXVECTOR3(2.60f,1.00f,1.00f);
	//洗面
	pHitSenmen = NewObj(new HitBox);
	pHitSenmen->Ob()->objPos=D3DXVECTOR3(-2.11f,0.118f,1.65f);
	pHitSenmen->Ob()->objScal=D3DXVECTOR3(2.00f,1.50f,4.574f);
	pHitSenmen->Ob()->MeshCol=D3DXVECTOR4(1.00f,1.00f,1.00f,0.50f);	
	//描画オブジェクト---------------------------------------------------------------------------
	//フィールド全体
	pDatui = NewObj(new drawObj);
	pDatui->Ob()->Type(x_bath_datui_man);
	pDatui->Ob()->ShadowFlag=FALSE;
	pDatui->Ob()->SpColm=0.0f;
	//体重計
	pTaiju = NewObj(new Ev::drawHitObj);
	pTaiju->Ob()->Type(x_taijukei);
	pTaiju->Ob()->objPos=D3DXVECTOR3(-2.00f,0.00f,0.00f);
	pTaiju->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);
	pTaiju->Ob()->Bias=0.16f;


	//かご
	pKago = NewObj(new Ev::drawHitObj);
	pKago->Ob()->Type(x_kagidana);
	pKago->Ob()->objPos=D3DXVECTOR3(2.05f,-0.50f,-1.70f);
	pKago->Ob()->objScal=D3DXVECTOR3(1.00f,1.00f,0.80f);

	//扇風機
	pSenpu = NewObj(new Senpu);
	pSenpu->Ob()->objPos=D3DXVECTOR3(0.00f,0.00f,-2.10f);
	//鏡
	pMirror = NewObj(new Mirror);
	pMirror ->Fvf[0]->objPos = D3DXVECTOR3(-2.6f,1.0f,1.8f);
	pMirror ->Fvf[0]->objScal=D3DXVECTOR3(2.2f,1.0f,1.0f);
	pMirror ->Fvf[0]->YPR = D3DXVECTOR3(0.0f,270.0f,0.0f);
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
	EriaHit(&D3DXVECTOR3(-2.3f,0.0f,-2.4f),&D3DXVECTOR3(2.3f,2.0f,2.4f));

}
VOID Bath_Datui_Man::Update()
{
	if(P->Check)
	{
		//通路へ
		if(pMovePass ->HitObjFlag(0))
		{
			P->CheckSE(Personal::SE_SLIDE);
			FldChange(new Bath_Pass,&D3DXVECTOR3(-0.85f,0.00f,0.80f),180.0f);
		}
		//浴場へ
		if(pMoveBath->HitObjFlag(0))	
		{
			P->CheckSE(Personal::SE_SLIDE);
			FldChange(new Fld::Bath_Room_Man,&D3DXVECTOR3(0.0f,0.0f,-4.20f),0.0f);
		}
	}

	D3DXVECTOR3 Eye;
	D3DXVECTOR3 At;
	Eye=D3DXVECTOR3(2.45f,1.9f,2.0f);
	At=P->obj.objPos;
	ML->E.cam.CamSet(&Eye,&At);
}
