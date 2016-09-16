//==============================================================================
//三階フロア
//==============================================================================
F3::F3(){}
VOID F3::Set()
{
	P->FM.FldType = FD_F3;
	//2階フラグ
	//移動オブジェクト-----------------------------------
	pMoveF2 = NewObj(new Ev::HitBox);
	pMoveF2->Ob()->objPos=D3DXVECTOR3(8.20f,0.10f,10.0f);
	pMoveF2->Ob()->objScal=D3DXVECTOR3(5.60f,6.00f,2.40f);
	pMoveF2->Ob()->drawSkip=TRUE;
	//当たり判定オブジェクト------------------------------
	//階段右手前の壁
	pHitWall = NewObj(new HitBox);
	pHitWall->Ob()->objPos=D3DXVECTOR3(6.44f,7.10f,-2.50f);
	pHitWall->Ob()->objScal=D3DXVECTOR3(14.60f,30.30f,32.50f);

	//階段右奥の壁
	pHitWall1 = NewObj(new HitBox);
	pHitWall1->Ob()->objPos=D3DXVECTOR3(4.81f,5.28f,33.57f);
	pHitWall1->Ob()->objScal=D3DXVECTOR3(8.10f,21.70f,100.10f);

	//階段
	pHitKaidan = NewObj(new HitBox);
	pHitKaidan->Ob()->objPos=D3DXVECTOR3(4.20f,0.00f,7.40f);
	pHitKaidan->Ob()->objScal=D3DXVECTOR3(9.00f,5.80f,8.10f);
	pHitKaidan->Ob()->YPR=D3DXVECTOR3(0.00f,0.00f,-38.00f);

	//２階床
	pHitFloor = NewObj(new HitBox);
	pHitFloor->Ob()->objPos=D3DXVECTOR3(-27.10f,-0.74f,20.40f);
	pHitFloor->Ob()->objScal=D3DXVECTOR3(120.60f,13.20f,150.20f);

	//踊り場
	pHitOboriba = NewObj(new HitBox);
	pHitOboriba->Ob()->objPos=D3DXVECTOR3(10.20f,4.62f,11.20f);
	pHitOboriba->Ob()->objScal=D3DXVECTOR3(15.10f,5.70f,23.80f);
	//階段天井
	pHitOboribaTenjo = NewObj(new HitBox);
	pHitOboribaTenjo->Ob()->objPos=D3DXVECTOR3(3.42f,5.43f,7.37f);
	pHitOboribaTenjo->Ob()->objScal=D3DXVECTOR3(15.29f,1.0f,6.43f);
	pHitOboribaTenjo->Ob()->YPR=D3DXVECTOR3(0.0f,0.0f,145.59f);
	//内壁階段側
	pHitUtikabe = NewObj(new HitBox);
	pHitUtikabe->Ob()->objPos=D3DXVECTOR3(-8.22f,4.00f,16.58f);
	pHitUtikabe->Ob()->objScal=D3DXVECTOR3(32.50f,20.30f,52.20f);

	//内壁奥側
	pHitUtikabe1 = NewObj(new HitBox);
	pHitUtikabe1->Ob()->objPos=D3DXVECTOR3(-21.08f,3.60f,-0.55f);
	pHitUtikabe1->Ob()->objScal=D3DXVECTOR3(46.30f,20.00f,97.78f);

	//描画オブジェクト-------------------------------------
	//ライト
	pLight = NewObj(new Ev::Light);
	pLight->Ob()->objPos=D3DXVECTOR3(-4.8f,5.7f,-0.8f);

	pLight1 = NewObj(new Ev::Light);
	pLight1->Ob()->objPos=D3DXVECTOR3(1.30f,5.70f,17.00f);

	pLight2 = NewObj(new Ev::Light);
	pLight2->Ob()->objPos=D3DXVECTOR3(-9.60f,5.70f,31.00f);

	pLight3 = NewObj(new Ev::Light);
	pLight3->Ob()->objPos=D3DXVECTOR3(-20.60f,5.70f,28.10f);

	//窓
	pMado = NewObj(new Ev::Mado_S);
	pMado->Ob()->objPos=D3DXVECTOR3(0.00f,3.85f,32.64f);
	//窓
	pMado1 = NewObj(new Ev::Mado_S);
	pMado1->Ob()->objPos=D3DXVECTOR3(-15.00f,3.85f,32.64f);

	//窓
	pMado2 = NewObj(new Ev::Mado_S);
	pMado2->Ob()->objPos=D3DXVECTOR3(2.77f,3.85f,16.00f);
	pMado2->Ob()->YPR=D3DXVECTOR3(0,90.0f,0);

	//窓
	pMado3 = NewObj(new Ev::Mado_S);
	pMado3->Ob()->objPos=D3DXVECTOR3(2.77f,3.85f,24.00f);
	pMado3->Ob()->YPR=D3DXVECTOR3(0,90.0f,0);


	//二階のフィールドオブジェクト
	pF2 = NewObj(new Ev::drawObj);
	pF2->Ob()->Type(x_f2);
	pF2->Ob()->ShadowFlag=FALSE;
	pF2->Ob()->SpColm=0.0f;
	
	//自販機
	pZihanki = NewObj(new Ev::F3_Zihanki);
	pZihanki->Ob()->objPos=D3DXVECTOR3(-9.00f,2.55f,-3.50f);
	pZihanki->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);

	//自販機1
	pZihanki1 = NewObj(new Ev::F3_Zihanki);
	pZihanki1->Ob()->objPos=D3DXVECTOR3(-9.00f,2.55f,-4.70f);
	pZihanki1->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);

	//自販機2
	pZihanki2 = NewObj(new Ev::F3_Zihanki);
	pZihanki2->Ob()->objPos=D3DXVECTOR3(-6.40f,2.55f,-5.60f);
	//自販機3
	pZihanki3 = NewObj(new Ev::F3_Zihanki);
	pZihanki3->Ob()->objPos=D3DXVECTOR3(-7.70f,2.55f,-5.60f);
	//ゴミ箱
	pTrash = NewObj(new DustMemo);
	pTrash->Ob()->objPos=D3DXVECTOR3(-9.00f,2.55f,-1.50f);
	pTrash->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);

	//椅子
	pChair = NewObj(new Ev::Chair);
	pChair->Ob()->objPos=D3DXVECTOR3(-3.20f,2.55f,1.0f);
	//椅子
	pChair1 = NewObj(new Ev::Chair);
	pChair1->Ob()->objPos=D3DXVECTOR3(-3.20f,2.55f,-2.50f);
	pChair1->Ob()->YPR=D3DXVECTOR3(0.00f,-181.00f,0.00f);
	//椅子
	pChair2 =NewObj(new Ev::Chair);
	pChair2->Ob()->objPos=D3DXVECTOR3(-5.80f,2.55f,-2.60f);
	pChair2->Ob()->YPR=D3DXVECTOR3(0.00f,-180.00f,0.00f);
	//椅子
	pChair3 =NewObj(new Ev::Chair);
	pChair3->Ob()->objPos=D3DXVECTOR3(-5.90f,2.55f,0.80f);

	//テーブル
	pTable = NewObj(new drawHitObj);
	pTable->Ob()->Type(x_table);
	pTable->Ob()->objPos=D3DXVECTOR3(-5.90f,2.55f,-0.70f);
	pTable->Ob()->YPR=D3DXVECTOR3(0.00f,-90.00f,0.00f);

	//テーブル
	pTable1 = NewObj(new drawHitObj);
	pTable1->Ob()->Type(x_table);
	pTable1->Ob()->objPos=D3DXVECTOR3(-3.20f,2.55f,-0.60f);
	pTable1->Ob()->YPR=D3DXVECTOR3(0.00f,-90.00f,0.00f);
	//消火器
	if(!P->FM.iGetedFlag(ITEM_SYOUKAKI))
	{
		pSyoukaki = NewObj(new Ev::Syoukaki);
		pSyoukaki->Ob()->objPos=D3DXVECTOR3(-6.0f,2.55f,-3.25f);
	}
	//誘導灯
	pExit = NewObj(new drawObj);
	pExit->Ob()->Type(x_exit);
	pExit->Ob()->objPos=D3DXVECTOR3(-24.80f,4.35f,31.29f);
	pExit->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);
	pExit->Ob()->SpCol.w=1.0f;
	pExit->Ob()->BloomColor=D3DXVECTOR4(0.0f,2.0f,0.0f,2.0f);
	pExit->Ob()->ShadowFlag=FALSE;

	//ドア----------------------------------------------------------各部屋に移動
	
	//201号室
	pDoor201 = NewObj(new Ev::Door201);
	pDoor201->Ob()->objPos=D3DXVECTOR3(-0.23f,2.55f,7.00f);
	pDoor201->Ob()->YPR=D3DXVECTOR3(0,-90.0f,0);
	//202号室
	pDoor202 = NewObj(new Ev::Door202);
	pDoor202->Ob()->objPos=D3DXVECTOR3(-0.23f,2.55f,18.00f);
	pDoor202->Ob()->YPR=D3DXVECTOR3(0,-90.0f,0);

	//203号室
	pDoor203 = NewObj(new Door203);
	pDoor203->Ob()->objPos=D3DXVECTOR3(-4.00f,2.55f,29.5f);
	pDoor203->Ob()->YPR=D3DXVECTOR3(0,180.0f,0);
	//204号室
	pDoor204 = NewObj(new Ev::Door(205,Door::F1_KEY,Door::F2_WOOD));
	pDoor204->Ob()->objPos=D3DXVECTOR3(-13.00f,2.55f,29.50f);
	pDoor204->Ob()->YPR=D3DXVECTOR3(0,180.0f,0);

	//男子トイレ
	pDoorMan = NewObj(new Ev::Door);
	pDoorMan->Ob()->objPos=D3DXVECTOR3(-18.90f,2.55f,23.72f);
	pDoorMan->Ob()->YPR=D3DXVECTOR3(0.00f,180.00f,0.00f);

	//女子トイレ
	pDoorWoman = NewObj(new Ev::Door);
	pDoorWoman->Ob()->objPos=D3DXVECTOR3(-21.0f,2.55f,23.72f);
	pDoorWoman->Ob()->YPR=D3DXVECTOR3(0.00f,180.00f,0.00f);

	//非常口
	pDoorExit = NewObj(new Door(Door::F0_NO,Door::F1_NO,Door::F2_EXIT));
	pDoorExit->Ob()->objPos=D3DXVECTOR3(-24.80f,2.55f,31.30f);
	pDoorExit->Ob()->YPR=D3DXVECTOR3(0.00f,-90.00f,0.00f);	
	
	//非常口1(屋上への)
	pDoorExit1 = NewObj(new DoorRoof);
	pDoorExit1->Ob()->objPos=D3DXVECTOR3(2.80f,2.55f,11.50f);
	pDoorExit1->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);
	//壁
	pKabe = NewObj(new Ev::drawObj);
	pKabe->Ob()->objPos=D3DXVECTOR3(0,2.55f,0);
	pKabe->Ob()->Type(x_kabe);
	pKabe->Ob()->objPos=D3DXVECTOR3(2.80f,2.55f,10.04f);
	pKabe->Ob()->objScal=D3DXVECTOR3(0.99f,11.22f,3.06f);
	pKabe->Ob()->MeshCol=D3DXVECTOR4(0.40f,0.40f,0.40f,1.00f);	
	pKabe->Ob()->SpColm=0.50f;

	//イントロイベント
	if(P->FM.EventFlag == TL_INTRO_1)
	{
		pIntroCut  = NewObj(new Ev::IntroCut);
		pIntroEvent = NewObj(new Ev::IntroF2Cam);
	}

	//防火シャッター
	pBouka = NewObj(new Shutter);
	pBouka->Ob()->objPos = D3DXVECTOR3(2.83f,2.55f,7.13f);
	//防火シャッタースイッチ
	pBoukaSwitch = NewObj(new BoukaSwitch);
	pBoukaSwitch->Ob()->objPos = D3DXVECTOR3(2.76f,3.38f,4.44f);
	pBoukaSwitch->Ob()->YPR = D3DXVECTOR3(0.0f,90.0f,90.0f);
	//非常口テキスト
	pExitText = NewObj(new F3_EXIT);
	pExitText ->Ob()->objPos = D3DXVECTOR3(-24.80f,2.55f,31.30f);
	//隠された扉
	pSecret = NewObj(new Secret_Door);
	pSecret->Ob()->objPos = D3DXVECTOR3(-8.00f,2.55f,32.62f);
	//魚最後
	if(P->FM.EventFlag >= TL_READ_TIPS)
	{
		pLastFish = NewObj(new FishGhost);
 	}
	//オーディオ
	ML->Audio.Audio.Effect = AE_HALLWAY;
	//シェーダ-----------------------------------------------------------------
	//ライト
	ML->E.Ls.Near=43.50f;
	ML->E.Ls.Far=30.60f;
	ML->E.Ls.Pos=D3DXVECTOR3(-8.10f,57.10f,12.70f);
	ML->E.Ls.At=D3DXVECTOR3(-8.10f,0.00f,12.80f);
	ML->E.Ls.Pars=45.00f;	
	ML->E.Ls.Col=D3DXVECTOR4(0.5f,0.5f,0.75f,1.00f);
	//フォグ
	ML->E.Fs.Near=-3.0f;
	ML->E.Fs.Far=48.0f;
	ML->E.Fs.Col=D3DXVECTOR3(0.5f,0.5f,0.75f);
	ML->E.Fs.use = TRUE;
	//エリア全体の当たり判定---------------------------------------------------------------------------------------------
	EriaHit(&D3DXVECTOR3(-24.8f,0.0f,-6.0f),&D3DXVECTOR3(9.5f,5.7f,32.6f));

}

VOID F3::Update()
{
	//移動---------------------------------------------------------------------
	//二階へ
	if(pMoveF2->HitObjFlag(0))
	{
		FldChange(new Lobby,&D3DXVECTOR3(8.72f,3.14f,26.0f),0.0f);
	}
	if(P->Check)
	{		
		
		//204号室へ
		if(pDoor204->HitObjFlag(0))
		{
			P->CheckSE(Personal::SE_OPEN);
			FldChange(new Guest_Room,&D3DXVECTOR3(-3.95f,0.40f,-2.27f),90.0f);
		}
		//男子トイレへ
		if(pDoorMan->HitObjFlag(0))
		{
			P->CheckSE(Personal::SE_OPEN);
			FldChange(new Fld::Rest_Men,&D3DXVECTOR3(0,0,-2.3f),0.0f);
		}
		//女子トイレへ
		if(pDoorWoman->HitObjFlag(0))
		{
			P->CheckSE(Personal::SE_OPEN);
			FldChange(new Fld::Rest_Women,&D3DXVECTOR3(0,0,-2.3f),0.0f);
		}		
	}
	//カメラ設定-----------------------------------------------------
	//手前側広め通路
	D3DXVECTOR3 Eye(2.7f,5.0f,3.5f);
	D3DXVECTOR3 At(P->obj.objPos);	
	//通路側
	if(P->obj.objPos.z > 3.2f)
	{
		//Eye
		Eye=D3DXVECTOR3(1.49f,4.99f,0.36f);
		//At
		At=D3DXVECTOR3(1.48f,4.66f,1.31f);

	}
	//通路奥
	if(P->obj.objPos.z > 29.5f)
	{
		//Eye
		Eye=D3DXVECTOR3(5.0f,3.93f,31.02f);
		//At
		At=D3DXVECTOR3(0.47f,3.71f,30.91f);
	}

	//通路奥広め通路
	if(P->obj.objPos.x < -16.5f)
	{
		//Eye
		Eye=D3DXVECTOR3(-16.5f,5.27f,24.0f);
		//At
		At=P->obj.objPos;
		if(At.z<=25.0f){At.z=25.0f;}
	}

	if(P->obj.objPos.x > 2.8f)
	{
		//二階へのカメラ
		Eye=D3DXVECTOR3(1.0f,5.37f,7.13f); 
		At=D3DXVECTOR3(9.0f,0.0f,7.13f);
		//屋上へのカメラ
		if(P->obj.objPos.y > 2.0f)
		if(P->obj.objPos.z > 8.5f)
		{
			Eye=D3DXVECTOR3(0.0f,4.0f,11.5f);
			At=D3DXVECTOR3(9.0f,5.0f,11.5f);
		}
	}
	ML->E.cam.CamSet(&Eye,&At);	
}