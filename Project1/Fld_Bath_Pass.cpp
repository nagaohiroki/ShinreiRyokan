//=============================================
//浴場への廊下
//=============================================
Bath_Pass::Bath_Pass()
{
}
VOID Bath_Pass::Set()
{
	P->FM.FldType = FD_Bath_Pass;

	//脱衣所へ
	pMoveMan = NewObj(new Ev::HitFlag);
	pMoveMan->Ob()->objPos=D3DXVECTOR3(-0.85f,0.00f,1.50f);
	//脱衣所へ
	pMoveWoman = NewObj(new HitFlag);
	pMoveWoman->Ob()->objPos=D3DXVECTOR3(-3.0f,0.00f,1.50f);
	//移動オブジェクト
	pMoveExit = NewObj(new Ev::HitFlag); 
	pMoveExit->Ob()->objPos=D3DXVECTOR3(6.20f,0.80f,0.00f);
	pMoveExit->Ob()->objScal=D3DXVECTOR3(1.00f,1.00f,6.00f);
	//フロア
	pHitPass = NewObj(new Ev::HitBox);
	pHitPass->Ob()->objPos=D3DXVECTOR3(6.00f,0.35f,0.00f);	
	pHitPass->Ob()->objScal=D3DXVECTOR3(7.05f,1.00f,6.00f);
	
	//階段
	pHitKaidan = NewObj(new Ev::HitBox);
	pHitKaidan->Ob()->objPos=D3DXVECTOR3(3.0f,-0.6f,0.0f);
	pHitKaidan->Ob()->objScal=D3DXVECTOR3(5.7f,1.00f,7.0f);
	pHitKaidan->Ob()->YPR=D3DXVECTOR3(0.00f,0.00f,42.658157f);

	//通路
	pPass = NewObj(new Ev::drawObj);
	pPass->Ob()->Type(x_bath_pass);
	pPass->Ob()->ShadowFlag=FALSE;

	//ベンチ
	pBench = NewObj(new drawHitObj);
	pBench->Ob()->Type(x_bath_bench);
	pBench->Ob()->objPos=D3DXVECTOR3(-1.90f,0.00f,-1.20f);
	pBench->Ob()->MeshCol=D3DXVECTOR4(0.50f,0.50f,0.50f,1.00f);

	//非常口
	pExitDoor = NewObj(new Ev::Door(Door::F0_NO,Door::F1_NO,Door::F2_EXIT));
	pExitDoor->Ob()->objPos=D3DXVECTOR3(-7.50f,0.00f,0.00f);
	pExitDoor->Ob()->YPR=D3DXVECTOR3(0.00f,-90.00f,0.00f);

	//非常灯
	pExitLamp = NewObj(new drawObj);
	pExitLamp->Ob()->Type(x_exit);
	pExitLamp->Ob()->SpCol.w=1.0f;
	pExitLamp->Ob()->BloomColor=D3DXVECTOR4(0.0f,2.0f,0.0f,2.0f);
	pExitLamp->Ob()->ShadowFlag=FALSE;
	pExitLamp->Ob()->objPos=D3DXVECTOR3(-7.55f,1.60f,0.00f);
	pExitLamp->Ob()->YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);

	//自販機
	pZihanki = NewObj(new Ev::Zihanki);
	pZihanki->Ob()->objPos=D3DXVECTOR3(2.10f,0.00f,1.10f);
	pZihanki->Ob()->YPR=D3DXVECTOR3(0.00f,180.00f,0.00f);

	//非常口メッセージ
	pExitMessage = NewObj(new Ev::F3_EXIT);
	pExitMessage->Ob()->objPos=D3DXVECTOR3(-7.50f,0.00f,0.00f);
	

	//オーディオ---------------------------------------------
	ML->Audio.Audio.Effect = AE_HALLWAY	;
	//シェーダ-----------------------------------------------------------------
	//ライト
	ML->E.Ls.Near=34.5f;	
	ML->E.Ls.Far=42.5f;
	ML->E.Ls.Pos=D3DXVECTOR3(0.00f,40.30f,1.00f);
	ML->E.Ls.At=D3DXVECTOR3(0.00f,0.00f,0.00f);
	ML->E.Ls.Col=D3DXVECTOR4(0.5f,0.5f,0.75f,1.00f);
	//フォグ
	ML->E.Fs.Near=-50.00f;
	ML->E.Fs.Far=120.00f;
	ML->E.Fs.Col=D3DXVECTOR3(0.5f,0.5f,0.75f);
	ML->E.Fs.use = TRUE;
	//フィールドの当たり判定-------------------------------------------------------------
	EriaHit(&D3DXVECTOR3(-7.4f,0.0f,-1.34f),&D3DXVECTOR3(7.4f,3.0f,1.34f));

}

VOID Bath_Pass::Update()
{
	if(pMoveExit->HitObjFlag(0))
	{
		FldChange(new Lobby,&D3DXVECTOR3(1.00f,0.00f,42.30f),90.0f);
	}
	if(P->Check)
	{
		if(pMoveMan->HitObjFlag(0))
		{
			P->CheckSE(Personal::SE_SLIDE);
			FldChange(new Fld::Bath_Datui_Man,&D3DXVECTOR3(-1.95f,0.00f,-1.80f),0.0f);

		}
		if(pMoveWoman->HitObjFlag(0))
		{
			P->CheckSE(Personal::SE_SLIDE);
			FldChange(new Fld::Bath_Datui_Woman,&D3DXVECTOR3(-3.17f,0.00f,-1.80f),0.0f);

		}
	}
	D3DXVECTOR3 Eye(7.74f,2.45f,-1.06f);
	D3DXVECTOR3 At(6.79f,2.23f,-0.87f);
	ML->E.cam.CamSet(&Eye,&At);
}




