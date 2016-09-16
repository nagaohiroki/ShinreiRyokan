Staff_Room::Staff_Room(){}
VOID Staff_Room::Set()
{
	P->FM.FldType = FD_Staff_Room;
	//当たり判定
	pHitBox = NewObj(new HitBox);
	pHitBox->Ob()->objScal = D3DXVECTOR3(3.569381f,2.00f,6.7f);
	//扉
	pDoor = NewObj(new Lobby_Door);	
	pDoor ->Ob()->objPos = D3DXVECTOR3(0.0f,0.0f,-3.0f);
	//部屋
	pRoom = NewObj(new drawObj);
	pRoom->Ob()->Type(x_staffroom);
	pRoom->Ob()->ShadowFlag = FALSE;
	pRoom->Ob()->SpColm = 0.0f;

	//棚
	pLack = NewObj(new drawHitObj);
	pLack ->Ob()->Type(x_lack);
	pLack ->Ob()->objPos = D3DXVECTOR3(2.3f,0.0f,-1.92f);
	pLack ->Ob()->YPR = D3DXVECTOR3(0.0f,86.4f,0.0f);
	pLack ->Ob()->Bias = 0.3f;
	//棚
	pLack1 = NewObj(new drawHitObj);
	pLack1->Ob()->Type(x_lack);
	pLack1->Ob()->objPos = D3DXVECTOR3(2.81f,0.84f,-0.258f);
	pLack1->Ob()->YPR = D3DXVECTOR3( 247.365311f,85.599998f,0.0f);
	pLack1->Ob()->Bias = 0.3f;

	//ホワイトボード
	pWhite = NewObj(new WhiteBord);
	pWhite->Ob()->objPos = D3DXVECTOR3(-2.3f,0.0f,0.0f);
	pWhite->Ob()->YPR = D3DXVECTOR3(0.0f,90.0f,0.0f);

	//鍵
	pKey = NewObj(new Key203);
	pKey->Ob()->objPos = D3DXVECTOR3(2.292145f,1.526672f,-1.293991f);
	pKey->Ob()->YPR = D3DXVECTOR3(0.0f,20.0,0.0f);

	//窓
	pMado = NewObj(new Mado_S);
	pMado->Ob()->objPos = D3DXVECTOR3(0.0f,1.13f,3.0f);
	pMado->Ob()->objScal = D3DXVECTOR3(1.2f,1.0f,1.0f);
	//机
	pDesk = NewObj(new MasterDesk);
	pDesk->Ob()->objPos = D3DXVECTOR3(2.4f,0.0f,2.15f);
	pDesk->Ob()->YPR = D3DXVECTOR3(0.0f,270.0f,0.0f);

	pDesk1 = NewObj(new Desk);
	pDesk1->Ob()->objPos = D3DXVECTOR3(0.5f,0.0f,-1.2f);
	pDesk1->Ob()->YPR = D3DXVECTOR3(0.0f,90.0f,0.0f);

	pDesk2 = NewObj(new Desk);
	pDesk2->Ob()->objPos = D3DXVECTOR3(0.5f,0.0f,0.0f);
	pDesk2->Ob()->YPR = D3DXVECTOR3(0.0f,80.0f,0.0f);

	pDesk3 = NewObj(new Desk);
	pDesk3->Ob()->objPos = D3DXVECTOR3(0.5f,0.0f,1.2f);
	pDesk3->Ob()->YPR = D3DXVECTOR3(0.0f,90.0f,0.0f);

	pDesk4 = NewObj(new Desk);
	pDesk4->Ob()->objPos = D3DXVECTOR3(-0.5f,0.0f,-1.2f);
	pDesk4->Ob()->YPR = D3DXVECTOR3(0.0f,270.0f,0.0f);

	pDesk5 = NewObj(new KeyDesk);
	pDesk5->Ob()->objPos = D3DXVECTOR3(-0.5f,0.0f,0.0f);
	pDesk5->Ob()->YPR = D3DXVECTOR3(0.0f,270.0f,0.0f);

	pDesk6 = NewObj(new Desk);
	pDesk6->Ob()->objPos = D3DXVECTOR3(-0.5f,0.0f,1.2f);
	pDesk6->Ob()->YPR = D3DXVECTOR3(0.0f,260.0f,0.0f);

	//椅子
	pChair = NewObj(new StaffChair );
	pChair->Ob()->objPos = D3DXVECTOR3(-2.6f,0.0f,2.6f);
	pChair->Ob()->objScal = D3DXVECTOR3(1.0f,1.0f,1.0f);
	//椅子
	pChair1 = NewObj(new drawHitObj);
	pChair1->Ob()->Type(x_dining_chair);
	pChair1->Ob()->SpColm = 0.0f;
	pChair1->Ob()->YPR = D3DXVECTOR3(0.0f,-25.0f,0.0f);
	pChair1->Ob()->objPos = D3DXVECTOR3(-2.0f,0.0f,2.6f);
	pChair1->Ob()->objScal = D3DXVECTOR3(1.0f,1.0f,1.0f);
	//椅子
	pChair2 = NewObj(new drawHitObj);
	pChair2->Ob()->Type(x_dining_chair);
	pChair2->Ob()->SpColm = 0.0f;
	pChair2->Ob()->YPR = D3DXVECTOR3(86.400002f,180.0f,0.0f);
	pChair2->Ob()->objPos = D3DXVECTOR3(2.799362f,0.213516f,0.514549f);
	pChair2->Ob()->objScal = D3DXVECTOR3(1.0f,1.0f,1.0f);
	//椅子
	pChair3 = NewObj(new drawHitObj);
	pChair3->Ob()->Type(x_dining_chair);
	pChair3->Ob()->SpColm = 0.0f;
	pChair3->Ob()->YPR = D3DXVECTOR3(0.0f,21.6f,0.0f);
	pChair3->Ob()->objPos = D3DXVECTOR3(1.07f,0.0f,-1.192413f);
	pChair3->Ob()->objScal = D3DXVECTOR3(1.0f,1.0f,1.0f);
	//オーディオ
	ML->Audio.Audio.Effect = AE_MEDIUMROOM;
	//ライト
	ML->E.Ls.Col=D3DXVECTOR4(0.5f,0.5f,0.75f,1.00f);
	//フォグ
	ML->E.Fs.Near=-50.00f;
	ML->E.Fs.Far=120.00f;
	ML->E.Fs.Col=D3DXVECTOR3(0.5f,0.5f,0.75f);
	ML->E.Fs.use = TRUE;
	//エリア全体の当たり判定-------------------------------------------------------------------------------
	EriaHit(&D3DXVECTOR3(-3.0f,0.0f,-3.0f),&D3DXVECTOR3(3.0f,4.0f,3.0f));
}
VOID Staff_Room::Update()
{
	D3DXVECTOR3 Eye(-2.9f,3.0f,2.9f);
	D3DXVECTOR3 At(0.0f,0.0f,0.0f);
	ML->E.cam.CamSet(&Eye,&P->obj.objPos);
}