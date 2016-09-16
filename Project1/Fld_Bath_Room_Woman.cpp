//=====================================================
//女湯
//=====================================================
Bath_Room_Woman::Bath_Room_Woman()
{
}

VOID Bath_Room_Woman::Set()
{
	P->FM.FldType = FD_Bath_Room_Woman;

	//移動あたり判定	
	pMoveDatui = NewObj(new HitFlag); 
	pMoveDatui->Ob()->objPos=D3DXVECTOR3(-10.00f,0.00f,-4.90f);
	pMoveDatui->Ob()->objScal=D3DXVECTOR3(3.00f,1.00f,1.00f);


	//洗い場あたり判定
	pHitBath = NewObj(new HitBox);
	pHitBath->Ob()->objPos=D3DXVECTOR3(-5.11f,0.20f,-2.98f);
	pHitBath->Ob()->objScal=D3DXVECTOR3(1.00f,1.00f,8.10f);

	//バスタブあたり判定
	pHitBath = NewObj(new HitBox);
	pHitBath->Ob()->objPos=D3DXVECTOR3(-12.34f,-0.05f,1.0f);
	pHitBath->Ob()->objScal=D3DXVECTOR3(10.70f,1.00f,1.0f);
	//バスタブあたり判定1	
	pHitBath1  = NewObj(new HitBox);
	pHitBath1->Ob()->objPos=D3DXVECTOR3(-10.0f,-0.05f,2.58f);
	pHitBath1->Ob()->objScal=D3DXVECTOR3(1.00f,1.00f,6.13f);
	
	//階段
	pHitKaidan = NewObj(new HitBox);
	pHitKaidan->Ob()->objPos = D3DXVECTOR3(-10.245f,-0.379158f,4.542747f);
	pHitKaidan->Ob()->objScal= D3DXVECTOR3( 2.656518f,1.0f,1.6f);
	pHitKaidan->Ob()->YPR = D3DXVECTOR3( 0.0f,0.0f,225.0f);

	//浴場
	pRoom = NewObj(new drawObj);
	pRoom->Ob()->Type(x_bath_room_women);
	pRoom->Ob()->ShadowFlag=FALSE;
	pRoom->Ob()->MeshCol = D3DXVECTOR4(0.6f,0.6f,0.6f,1.0f);

	//シャワー
	pSw = NewObj(new drawObj);
	pSw->Ob()->Type(x_bath_shower);
	pSw->Ob()->objPos=D3DXVECTOR3(-5.18f,0.00f,-1.70f);
	pSw->Ob()->YPR=D3DXVECTOR3(0.00f,180.00f,0.00f);

	//シャワー1
	pSw1 = NewObj(new drawObj);
	pSw1->Ob()->Type(x_bath_shower);
	pSw1->Ob()->objPos=D3DXVECTOR3(-5.18f,0.00f,-3.00f);
	pSw1->Ob()->YPR=D3DXVECTOR3(0.00f,180.00f,0.00f);

	//シャワー2
	pSw2 = NewObj(new drawObj);
	pSw2->Ob()->Type(x_bath_shower);
	pSw2->Ob()->objPos=D3DXVECTOR3(-5.18f,0.00f,-4.30f);
	pSw2->Ob()->YPR=D3DXVECTOR3(0.00f,180.00f,0.00f);

	//椅子
	pChair = NewObj(new drawHitObj);
	pChair->Ob()->Type(x_bath_chair);
	pChair->Ob()->objPos=D3DXVECTOR3(-6.10f,0.00f,-1.70f);
	pChair->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);


	//椅子
	pChair1 = NewObj(new drawHitObj);
	pChair1->Ob()->Type(x_bath_chair);
	pChair1->Ob()->objPos=D3DXVECTOR3(-6.10f,0.00f,-3.00f);
	pChair1->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);


	//椅子
	pChair2 = NewObj(new drawHitObj);
	pChair2->Ob()->Type(x_bath_chair);
	pChair2->Ob()->objPos=D3DXVECTOR3(-6.10f,0.00f,-4.30f);
	pChair2->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);


	//桶
	pOke = NewObj(new drawHitObj);
	pOke->Ob()->Type(x_bath_oke);
	pOke->Ob()->objPos=D3DXVECTOR3(-5.60f,0.00f,-1.70f);


	//桶
	pOke1 = NewObj(new drawHitObj);
	pOke1->Ob()->Type(x_bath_oke);
	pOke1->Ob()->objPos=D3DXVECTOR3(-5.60f,0.00f,-3.00f);

	//桶
	pOke2 = NewObj(new drawHitObj);
	pOke2->Ob()->Type(x_bath_oke);
	pOke2->Ob()->objPos=D3DXVECTOR3(-5.60f,0.00f,-4.30f);
	//窓
	pMado = NewObj(new Mado_S);
	pMado->Ob()->objPos=D3DXVECTOR3(-12.60f,1.60f,5.00f);
	pMado->Ob()->objScal=D3DXVECTOR3(2.90f,2.00f,1.00f);
	
	//窓
	pMado1 = NewObj(new Mado_S);
	pMado1->Ob()->objPos=D3DXVECTOR3(-15.00f,1.60f,2.70f);
	pMado1->Ob()->YPR=D3DXVECTOR3(0.00f,-90.00f,0.00f);
	pMado1->Ob()->objScal=D3DXVECTOR3(2.80f,2.00f,1.00f);
	//鏡
	pMirror = NewObj(new Mirror);
	pMirror->Fvf[0]->YPR.y = 90.0f;
	pMirror->Fvf[0]->objPos = D3DXVECTOR3(-5.0f,1.0f,-2.6f);
	pMirror->Fvf[0]->objScal = D3DXVECTOR3(4.7f,1.3f,1.0f);
	
	//鍵
	if(!P->FM.iGetedFlag(ITEM_DINING_KEY))
	{
		pKey = NewObj(new Dining_Key);
		pKey->Ob()->objPos = D3DXVECTOR3(-12.0f,0.0f,-2.5f);
	}
	//シェーダ-----------------------------------------------------------------
	ML->Audio.Audio.Effect = AE_BATHROOM;
	//フォグ
	//フォグ
	ML->E.Fs.Col.x = 0.410000f;
	ML->E.Fs.Col.y = 0.409167f;
	ML->E.Fs.Col.z = 0.500000f;
	ML->E.Fs.Far = 36.0000f;
	ML->E.Fs.Near = 0.000000f;
	ML->E.Fs.use = 1;
	//ライト
	ML->E.Ls.Col = D3DXVECTOR4(0.5f,0.5f,1.0f,1.0f);

	//フィールドの当たり判定-------------------------------------------------------------
	EriaHit(&D3DXVECTOR3(-15.0f,0.0f,-5.0f),&D3DXVECTOR3(-5.0f,3.0f,5.0f));
}

VOID Bath_Room_Woman::Update()
{
	//移動
	if(P->Check)
	{
		if(pMoveDatui->HitObjFlag(0))
		{
			P->CheckSE(Personal::SE_SLIDE);
			FldChange(new Fld::Bath_Datui_Woman,&D3DXVECTOR3(-6.10f,0.00f,1.80f),180.0f);

		}
	}
	//当たり判定
	if( P->obj.objPos.x < -10.0f && P->obj.objPos.z > 0.5f )
	{
		EriaHit(&D3DXVECTOR3(-15.0f,-0.42f,-5.0f),&D3DXVECTOR3(-5.0f,3.0f,5.0f));
	}
	else
	{
		EriaHit(&D3DXVECTOR3(-15.0f,0.0f,-5.0f),&D3DXVECTOR3(-5.0f,3.0f,5.0f));
	}
	//カメラ
	ML->E.cam.CamSet(&D3DXVECTOR3(-14.9f,2.9f,-4.9f),&P->obj.objPos);
}