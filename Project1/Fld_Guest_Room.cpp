//==========================================================
//個室
//==========================================================
Guest_Room::Guest_Room()
{
}

VOID Guest_Room::Set()
{	
	P->FM.FldType = FD_Guest_Room;
	//当たり判定オブジェクト-----------------------------------
	
	//押入れ
	pHitOsiire = NewObj(new Ev::HitBox);
	pHitOsiire->Ob()->objPos=D3DXVECTOR3(-4.00f,1.40f,1.30f);
	pHitOsiire->Ob()->objScal=D3DXVECTOR3(4.10f,5.90f,9.30f);
	//床の間(テレビ横)
	pHitTokonoma = NewObj(new Ev::HitBox);
	pHitTokonoma->Ob()->objPos=D3DXVECTOR3(0.82f,1.50f,3.43f);
	pHitTokonoma->Ob()->objScal=D3DXVECTOR3(1.3f,5.80f,2.00f);
	//縁側
	pHitEngawa = NewObj(new Ev::HitBox);
	pHitEngawa->Ob()->objPos=D3DXVECTOR3(3.10f,1.40f,2.50f);
	pHitEngawa->Ob()->objScal=D3DXVECTOR3(0.70f,5.80f,2.50f);
	//縁側1
	pHitEngawa1 = NewObj(new Ev::HitBox);
	pHitEngawa1->Ob()->objPos=D3DXVECTOR3(3.10f,1.40f,-2.60f);
	pHitEngawa1->Ob()->objScal=D3DXVECTOR3(0.70f,5.80f,2.50f);
	//床の間上
	pHitTokoUe = NewObj(new Ev::HitBox);
	pHitTokoUe->Ob()->objPos=D3DXVECTOR3(0.0f,2.28f,3.57f);
	pHitTokoUe->Ob()->objScal=D3DXVECTOR3(11.93f,2.5f,2.0f);
	//小さいたんす
	pHitTanas = NewObj(new Ev::HitBox);
	pHitTanas->Ob()->objPos=D3DXVECTOR3(-2.36f,1.14f,3.22f);
	pHitTanas->Ob()->objScal=D3DXVECTOR3(2.28f,4.0f,1.0f);
	//仕切り上
	pHitSikiriUe = NewObj(new Ev::HitBox);
	pHitSikiriUe->Ob()->objPos=D3DXVECTOR3(3.11f,2.18f,0.0f);
	pHitSikiriUe->Ob()->objScal=D3DXVECTOR3(0.5f,2.28f,14.1f);
	//描画オブジェクト-----------------------------------
	//部屋
	pRoom = NewObj(new Ev::drawObj);
	pRoom->Ob()->ShadowFlag=FALSE;
	pRoom->Ob()->Type(x_room);
	pRoom->Ob()->SpCol.w=50.0f;
	//ドア-------------------------------------------------------２階廊下へ移動
	pDoor = NewObj(new Door);
	pDoor->Ob()->objPos=D3DXVECTOR3(-4.86f,0.00f,-2.18f);
	pDoor->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);
	//バスルームへのドア
	pDoorBath = NewObj(new bathdoor);
	pDoorBath->Ob()->objPos=D3DXVECTOR3(-2.012070f, 0.0f,-2.9f);
	//電気
	pDenki = NewObj(new Denki);
	pDenki->Ob()->objPos=D3DXVECTOR3(0,2.8f,0);
	//窓
	pMado=NewObj(new Ev::Mado_S);
	pMado->Ob()->objPos=D3DXVECTOR3(4.83f,1.22f,0.00f);
	pMado->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);
	pMado->Ob()->objScal=D3DXVECTOR3(1.20f,1.40f,1.50f);
	//ふすま
	pHusuma = NewObj(new Ev::Memo);
	pHusuma->Ob()->objPos=D3DXVECTOR3(-3.05f,0.11f,1.62f);
	pHusuma->Ob()->YPR=D3DXVECTOR3(0.00f,-90.00f,0.00f);
	//ふすま1
	pHusuma1 = NewObj(new Ev::drawObj);
	pHusuma1->Ob()->Type(x_husuma);
	pHusuma1->Ob()->objPos=D3DXVECTOR3(-3.09f,0.11f,0.79f);
	pHusuma1->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);
	pHusuma1->Ob()->ShadowFlag=FALSE;
	//ふすま2
	pHusuma2 = NewObj(new Ev::drawObj);
	pHusuma2->Ob()->Type(x_husuma);
	pHusuma2->Ob()->objPos=D3DXVECTOR3(-2.16f,0.76f,3.03f);
	pHusuma2->Ob()->objScal=D3DXVECTOR3(0.61f,0.58f,1.00f);
	pHusuma2->Ob()->ShadowFlag=FALSE;
	//ふすま3
	pHusuma3 = NewObj(new Ev::drawObj);
	pHusuma3->Ob()->Type(x_husuma);
	pHusuma3->Ob()->objPos=D3DXVECTOR3(-2.66f,0.76f,3.08f);
	pHusuma3->Ob()->YPR=D3DXVECTOR3(0.00f,180.00f,0.00f);
	pHusuma3->Ob()->objScal=D3DXVECTOR3(0.61f,0.58f,1.00f);
	pHusuma3->Ob()->ShadowFlag=FALSE;
	//TV
	pTV = NewObj(new TV);
	pTV->Ob()->objPos=D3DXVECTOR3(0.10f,0.00f,3.30f);
	pTV->Ob()->YPR=D3DXVECTOR3(0.00f,180.00f,0.00f);
	//テーブル
	pTable = NewObj(new Ev::drawHitObj);
	pTable->Ob()->Type(x_table);
	pTable->Ob()->objPos=D3DXVECTOR3(-0.60f,0.00f,0.00f);
	pTable->Ob()->objScal=D3DXVECTOR3(2.00f,1.00f,2.00f);
	//テーブル1
	pTable1 = NewObj(new Ev::drawHitObj);
	pTable1->Ob()->Type(x_table);
	pTable1->Ob()->objPos=D3DXVECTOR3(4.3f,0.00f,-1.0f);
	
	//椅子	
	pChair = NewObj(new Ev::Chair);
	pChair->Ob()->objPos=D3DXVECTOR3(4.35f,0.00f,-2.30f);
	pChair->Ob()->YPR=D3DXVECTOR3(0.00f,181.00f,0.00f);
	//椅子1
	pChair1 = NewObj(new Ev::Chair);
	pChair1->Ob()->objPos=D3DXVECTOR3(4.35f,0.00f,0.70f);
	//座椅子
	pZaisu=NewObj(new Ev::drawHitObj);
	pZaisu->Ob()->Type(x_zaisu);
	pZaisu->Ob()->objPos=D3DXVECTOR3(-0.60f,0.00f,1.10f);
	pZaisu->Ob()->SpColm=0.0f;
	pZaisu->Ob()->MeshCol=D3DXVECTOR4(2.0f,2.0f,2.0f,1.0f);
	//座椅子1
	pZaisu1 = NewObj(new Ev::drawHitObj);
	pZaisu1->Ob()->Type(x_zaisu);
	pZaisu1->Ob()->objPos=D3DXVECTOR3(-0.60f,0.00f,-1.10f);
	pZaisu1->Ob()->YPR=D3DXVECTOR3(0,180.0f,0);
	pZaisu1->Ob()->SpColm=0.0f;
	pZaisu1->Ob()->MeshCol=D3DXVECTOR4(2.0f,2.0f,2.0f,1.0f);	


	//冷蔵庫
	pReizouko=NewObj(new Reizouko);
	pReizouko->Ob()->objPos=D3DXVECTOR3(3.60f,0.00f,2.80f);
	pReizouko->Ob()->YPR=D3DXVECTOR3(0.00f,180.00f,0.00f);
	//電話
	pTel=NewObj(new Tel);
	pTel->Ob()->objPos=D3DXVECTOR3(1.4f,0.0f,3.21f);
	pTel->Ob()->YPR=D3DXVECTOR3(0.00f,180.00f,0.00f);
	//金庫
	pKinko=NewObj(new Kinko);
	pKinko->Ob()->objPos=D3DXVECTOR3(-1.5f,0.0f,3.20f);
	pKinko->Ob()->YPR=D3DXVECTOR3(0.00f,180.00f,0.00f);

	
	//最初のイベント
	if(P->FM.EventFlag == TL_INTRO_2)
	{
		pEvent = NewObj(new Ev::IntroGuest);
	}
	//薬
	pDrug = NewObj(new Drug);
	pDrug->Ob()->objPos = D3DXVECTOR3(-1.2f,0.33f,-0.75f);
	if(P->FM.EventFlag < TL_DRUG_START )
	{

		//ドアテキスト
		pDoorText = NewObj(new DoorText);
		pDoorText ->Ob()->objPos=D3DXVECTOR3(-2.012070f, 0.124773f,-2.9f);
	
	}
	//ダーツ
	pDarts = NewObj(new Darts);
	pDarts->Ob()->objPos = D3DXVECTOR3(-0.16f,0.35f,0.64f);

	//ダーツボード
	if(!P->FM.iGetedFlag(ITEM_MASUI))
	{
		pDartsbord = NewObj(new Dartsbord);
	//	pDartsbord->Ob()->objPos = D3DXVECTOR3(3.0f,1.9f,2.5f);
		pDartsbord->Ob()->objPos = D3DXVECTOR3(3.0f,1.9f,1.5f);
		
		pDartsbord->Ob()->YPR= D3DXVECTOR3(90.0f,270.0f,0.0f);
	}

	//廊下側の鍵
	if(!P->FM.iGetedFlag(ITEM_GUEST_KEY) || P->FM.iGetFlag(ITEM_GUEST_KEY))
	{
		pF3DoorText = NewObj(new  F2_DoorText);
		pF3DoorText->Ob()->objPos = D3DXVECTOR3(-4.86f,0.00f,-2.18f);
	}
	//メモの紙
	pMemokami = NewObj(new Memokami);
	pMemokami->Fvf[0]->objPos = D3DXVECTOR3( -3.363f,0.765f,1.798f);
	pMemokami->Fvf[0]->objScal = D3DXVECTOR3( 0.13f,0.13f,1.0f);
	pMemokami->Fvf[0]->YPR = D3DXVECTOR3( 90.0f,0.0f,0.0f);
	//チュートリアル
	pTutorial = NewObj(new Tutorial);
	pTutorial->Ob()->objPos = D3DXVECTOR3( -1.07f,0.348f,0.681f);

	//エリアをまたいだ場合
	if(P->FM.EventFlag ==TL_GUEST_ENEMY_START)
	{
		P->FM.enemy.Level = 0;
		if(P->FM.enemy.mode == Enemy::MODE_STALK || P->FM.enemy.mode == Enemy::MODE_STALK_ATTACK)
		{
			pEnemy = NewObj(new Enemy);
			pBathEnemy = NewObj(new EnemyGuestBath);
			pActiveEnemy = NewObj(new ActiveEnemy);
			if(P->FM.enemy.mode == Enemy::MODE_STALK)
			{
				P->FM.enemy.pos = D3DXVECTOR3(-1.7f,0.35f,-0.5f);
				P->FM.enemy.rot = 0.0f;
			}
			if(P->FM.enemy.mode == Enemy::MODE_STALK_ATTACK)
			{
				P->FM.enemy.pos = D3DXVECTOR3(-1.7f,0.35f,-2.5f);
				P->FM.enemy.rot = 180.0f;
			}
		}
	}
	//オーディオ
	ML->Audio.Audio.Effect = AE_LIVINGROOM;
	//シェーダ-----------------------------------------------------------------
	
	//ライト
	ML->E.Ls.Near=12.40f;
	ML->E.Ls.Far=15.00f;
	ML->E.Ls.Pos=D3DXVECTOR3(0.00f,14.40f,0.20f);
	if(P->FM.EventFlag >= TL_DRUG_GUNGUN)
	{
		ML->E.Ls.Col = D3DXVECTOR4(0.8f,0.8f,0.9f,1.0f);
	}
	else{ML->E.Ls.Col = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);}
	//フォグ
	ML->E.Fs.Col = D3DXVECTOR3(0.58f,0.58f,0.7f);
	ML->E.Fs.Far = 30.000015f;
	ML->E.Fs.Near = 0.000000f;
	ML->E.Fs.use = 1;
	//フィールドの当たり判定-------------------------------------------------------------
	EriaHit(&D3DXVECTOR3(-4.8f,0.00f,-2.9f),&D3DXVECTOR3(4.8f,2.8f,3.5f));
}
VOID Guest_Room::Update()
{		
	//２階廊下にでる
	if(P->FM.iGetedFlag(ITEM_GUEST_KEY))
	if(!P->FM.iGetFlag(ITEM_GUEST_KEY))
	if(pDoor->HitObjFlag(0))
	{
		if(P->Check)
		{			
			P->CheckSE(Personal::SE_OPEN);
			FldChange(new F3, &D3DXVECTOR3(-13.00f,2.55f,30.2f),0.0f);
		}
	}
	if(P->FM.EventFlag >= 5 )
	{
		//バスルームに入る
		if(pDoorBath->HitObjFlag(0))
		{
			if(P->Check)
			{
			
				P->CheckSE(Personal::SE_OPEN);
				FldChange(new Guest_Bath, &D3DXVECTOR3(0.0f,0.35f,1.3f),-180.0f);
			}
		}
	}

	D3DXVECTOR3 Eye(0,0,-5.0f);
	D3DXVECTOR3 At(0,0,0);
	Eye=D3DXVECTOR3(2.7f,2.46f,-2.9f);
	At=P->obj.objPos;	
	if(P->obj.objPos.x>=3.0f)
	{
		Eye=D3DXVECTOR3(4.7f,2.05f,-2.9f);
	}
	ML->E.cam.CamSet(&Eye,&At);
}
