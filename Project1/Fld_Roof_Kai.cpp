//============================================================
//屋上階段室
//============================================================
Roof_Kai::Roof_Kai(){}
VOID Roof_Kai::Set()
{
	P->FM.FldType = FD_Roof_Kai;
	//あたり判定オブジェクト---------------------------------------------------------------------
	//階段
	pHitKaidan = NewObj(new HitBox);
	pHitKaidan->Ob()->objPos=D3DXVECTOR3(-0.90f,0.0f,0.2f);
	pHitKaidan->Ob()->objScal=D3DXVECTOR3(2.80f,1.00f,3.20f);
	pHitKaidan->Ob()->YPR=D3DXVECTOR3(-45.00f,0.00f,0.00f);
	//階段1
	pHitKaidan1 = NewObj(new HitBox);
	pHitKaidan1->Ob()->objPos=D3DXVECTOR3(0.90f,1.19f,-0.112801f);
	pHitKaidan1->Ob()->YPR=D3DXVECTOR3(45.0f,0.00f,0.00f);
	pHitKaidan1->Ob()->objScal=D3DXVECTOR3(2.40f,1.00f,4.90f);
	//踊り場
	pHitFloor = NewObj(new HitBox);
	pHitFloor->Ob()->objPos=D3DXVECTOR3(0.00f,0.29f,1.40f);
	pHitFloor->Ob()->objScal=D3DXVECTOR3(6.20f,1.70f,2.10f);
	//踊り場1
	pHitFloor1 = NewObj(new HitBox);
	pHitFloor1->Ob()->objPos=D3DXVECTOR3(0.00f,2.06f,-1.550f);
	pHitFloor1->Ob()->objScal=D3DXVECTOR3(6.10f,1.00f,1.60f);
	//踊り場1の柵
	pHitFloorKabe = NewObj(new HitBox);
	pHitFloorKabe->Ob()->objPos=D3DXVECTOR3(-0.70f,2.70f,-1.00f);
	pHitFloorKabe->Ob()->objScal=D3DXVECTOR3(3.60f,1.50f,1.00f);
	//柱
	pHitHasira = NewObj(new HitBox);
	pHitHasira->Ob()->objPos=D3DXVECTOR3(0.00f,1.50f,-0.00f);
	pHitHasira->Ob()->objScal=D3DXVECTOR3(1.10f,7.10f,3.30f);
	//柱1
	pHitHasira1 = NewObj(new HitBox);
	pHitHasira1->Ob()->objPos=D3DXVECTOR3(0.10f,0.90f,-1.50f);
	pHitHasira1->Ob()->objScal=D3DXVECTOR3(1.00f,4.10f,2.90f);
	//描画オブジェクト---------------------------------------------------------------------------
	//3階への扉
	pDoor = NewObj(new Ev::Door(Door::F0_NO,Door::F1_NO,Door::F2_EXIT));
	pDoor->Ob()->objPos=D3DXVECTOR3(-0.87f,0.00f,-2.0f);
	//屋上への扉
	pDoor1 = NewObj(new Ev::Door(Door::F0_NO,Door::F1_NO,Door::F2_EXIT));
	pDoor1->Ob()->objPos=D3DXVECTOR3(0.84f,2.30f,-2.0f);
	pDoor1->Ob()->YPR=D3DXVECTOR3(0,180.0f,0);
	//階段部屋
	pRoom = NewObj(new drawObj);
	pRoom->Ob()->Type(x_roof_kai);
	pRoom->Ob()->SpColm=0.0f;
	pRoom->Ob()->ShadowFlag=FALSE;
	//窓
	pMado = NewObj(new Mado_S);
	pMado->Ob()->objPos=D3DXVECTOR3(-0.60f,3.40f,-2.00f);
	pMado->Ob()->YPR=D3DXVECTOR3(0.00f,180.00f,0.00f);
	pMado->Ob()->objScal=D3DXVECTOR3(0.60f,0.70f,1.00f);
	//オーディオ----------------------------------------------------------------
	ML->Audio.Audio.Effect = AE_STONEROOM;
	//シェーダ-----------------------------------------------------------------
	//フォグ
	//ライト
	ML->E.Ls.Near=5.00f;
	ML->E.Ls.Far=25.00f;
	ML->E.Ls.Pos=D3DXVECTOR3(0.00f,9.00f,0.20f);
	ML->E.Ls.Col = D3DXVECTOR4(0.6f,0.6f,0.6f,1.0f);
	//フィールドの当たり判定-------------------------------------------------------------
	EriaHit(&D3DXVECTOR3(-1.40f,0.0f,-1.90f),&D3DXVECTOR3(1.40f,4.5f,1.90f));
}
VOID Roof_Kai::Update()
{
	if(P->Check)
	{
		//3階
		if(pDoor->HitObjFlag(0))
		{
			P->CheckSE(Personal::SE_OPEN);
			FldChange(new F3,&D3DXVECTOR3(2.10f,2.55f,11.50f),-90.0f);
		}

		//屋上
		if(pDoor1->HitObjFlag(0))
		{
			P->CheckSE(Personal::SE_OPEN);
			FldChange(new Roof_Top,&D3DXVECTOR3(4.20f,0.00f,-1.25f),270.0f);
		}
	}
	//カメラ
	ML->E.cam.CamSet(&D3DXVECTOR3(-1.2f,4.18f,1.8f),&P->obj.objPos);
}