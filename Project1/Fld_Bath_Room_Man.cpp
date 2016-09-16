//=====================================================
//男湯
//=====================================================
Bath_Room_Man::Bath_Room_Man(){}
VOID Bath_Room_Man::Set()
{	
	P->FM.FldType = FD_Bath_Room_Man;
	pMoveDatui = NewObj(new HitFlag);
	pMoveDatui->Ob()->objPos=D3DXVECTOR3(0.0f,0.0f,-4.90f);
	pMoveDatui->Ob()->objScal=D3DXVECTOR3(3.00f,1.00f,1.00f);
	
	//洗い場あたり判定
	pHitAraiba = NewObj(new HitBox);
	pHitAraiba->Ob()->objPos=D3DXVECTOR3(-4.80f,0.20f,-2.98f);
	pHitAraiba->Ob()->objScal=D3DXVECTOR3(1.00f,1.00f,8.10f);
	//バスタブあたり判定
	pHitBath = NewObj(new HitBox);
	pHitBath->Ob()->objPos=D3DXVECTOR3(2.30f,-0.05f,1.0f);
	pHitBath->Ob()->objScal=D3DXVECTOR3(10.70f,1.00f,1.0f);
	//バスタブあたり判定1	
	pHitBath1  = NewObj(new HitBox);
	pHitBath1->Ob()->objPos=D3DXVECTOR3(-0.12f,-0.05f,2.58f);
	pHitBath1->Ob()->objScal=D3DXVECTOR3(1.00f,1.00f,6.13f);

	
	//階段
	pHitKaidan = NewObj(new HitBox);
	pHitKaidan ->Ob()->objPos = D3DXVECTOR3(0.369865f,-0.379158f,4.542747f);
	pHitKaidan ->Ob()->objScal= D3DXVECTOR3( 2.656518f,1.0f,1.6f);
	pHitKaidan ->Ob()->YPR = D3DXVECTOR3( 0.0f,0.0f,143.0f);

	//浴場
	pRoom = NewObj(new drawObj);
	pRoom->Ob()->Type(x_bath_room_men);
	pRoom->Ob()->ShadowFlag=FALSE;
	pRoom->Ob()->MeshCol = D3DXVECTOR4(0.6f,0.6f,0.6f,1.0f);
	//シャワー
	pSw = NewObj(new drawObj);
	pSw->Ob()->Type(x_bath_shower);
	pSw->Ob()->objPos=D3DXVECTOR3(-4.83f,0.00f,-1.70f);

	//シャワー1
	pSw1 = NewObj(new drawObj);
	pSw1->Ob()->Type(x_bath_shower);
	pSw1->Ob()->objPos=D3DXVECTOR3(-4.83f,0.00f,-3.00f);

	//シャワー2
	pSw2 = NewObj(new drawObj);
	pSw2->Ob()->Type(x_bath_shower);
	pSw2->Ob()->objPos=D3DXVECTOR3(-4.83f,0.00f,-4.30f);


	//椅子
	pChair = NewObj(new drawHitObj);
	pChair->Ob()->Type(x_bath_chair);
	pChair->Ob()->objPos=D3DXVECTOR3(-3.90f,0.00f,-1.70f);
	pChair->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);


	//椅子
	pChair1 = NewObj(new drawHitObj);
	pChair1->Ob()->Type(x_bath_chair);
	pChair1->Ob()->objPos=D3DXVECTOR3(-3.90f,0.00f,-3.00f);
	pChair1->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);


	//椅子
	pChair2 = NewObj(new drawHitObj);
	pChair2->Ob()->Type(x_bath_chair);
	pChair2->Ob()->objPos=D3DXVECTOR3(-3.90f,0.00f,-4.30f);
	pChair2->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);


	//桶
	pOke = NewObj(new drawHitObj);
	pOke->Ob()->Type(x_bath_oke);
	pOke->Ob()->objPos=D3DXVECTOR3(-4.40f,0.00f,-1.70f);


	//桶
	pOke1 = NewObj(new drawHitObj); 
	pOke1->Ob()->Type(x_bath_oke);
	pOke1->Ob()->objPos=D3DXVECTOR3(-4.40f,0.00f,-3.00f);

	//桶
	pOke2 = NewObj(new drawHitObj);
	pOke2->Ob()->Type(x_bath_oke);
	pOke2->Ob()->objPos=D3DXVECTOR3(-4.40f,0.00f,-4.30f);
	//窓
	pMado = NewObj(new Mado_S);
	pMado->Ob()->objPos=D3DXVECTOR3(2.50f,1.60f,5.00f);
	pMado->Ob()->objScal=D3DXVECTOR3(2.90f,2.00f,1.00f);
	
	//窓
	pMado1 = NewObj(new Mado_S);
	pMado1->Ob()->objPos=D3DXVECTOR3(5.00f,1.60f,3.00f);
	pMado1->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);
	pMado1->Ob()->objScal=D3DXVECTOR3(2.90f,2.00f,1.00f);
	
	//鏡
	pMirror = NewObj(new Mirror);
	pMirror->Fvf[0]->YPR.y = 270.0f;
	pMirror->Fvf[0]->objPos = D3DXVECTOR3(-5.2f,1.0f,-2.6f);
	pMirror->Fvf[0]->objScal = D3DXVECTOR3(4.7f,1.3f,1.0f);
	
	//ラジカセ
	pRazikase = NewObj(new Razikase);
	pRazikase->Ob()->objPos = D3DXVECTOR3(4.6f,-0.42f,4.5f);
	pRazikase->Ob()->YPR = D3DXVECTOR3(0.0f,90.0f,0.0f);
	//フィールドの当たり判定-------------------------------------------------------------
	ML->Audio.Audio.Effect = AE_BATHROOM;
	//フォグ
	ML->E.Fs.Col.x = 0.410000f;
	ML->E.Fs.Col.y = 0.409167f;
	ML->E.Fs.Col.z = 0.500000f;
	ML->E.Fs.Far = 16.0f;
	ML->E.Fs.Near = -33.000000f;
	ML->E.Fs.use = 1;
	EriaHit(&D3DXVECTOR3(-4.8f,-0.0f,-4.9f),&D3DXVECTOR3(4.8f,3.0f,4.9f));
}
VOID Bath_Room_Man::Update()
{
	//移動判定
	if(P->Check)
	{
		if(pMoveDatui->HitObjFlag(0))
		{
			P->CheckSE(Personal::SE_SLIDE);
			FldChange(new Fld::Bath_Datui_Man,&D3DXVECTOR3(1.10f,0.00f,1.80f),180.0f);
		}
	}
	//地面判定
	if(P->obj.objPos.x > 0.0f && P->obj.objPos.z > 0.5f)
	{
		EriaHit(&D3DXVECTOR3(-4.8f,-0.42f,-4.9f),&D3DXVECTOR3(4.8f,3.0f,4.9f));

	}
	else
	{
		EriaHit(&D3DXVECTOR3(-4.8f,0.0f,-4.9f),&D3DXVECTOR3(4.8f,3.0f,4.9f));
	}
	//カメラ
	ML->E.cam.CamSet(&D3DXVECTOR3(-4.9f,2.9f,-4.9f),&P->obj.objPos);
}