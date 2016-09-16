//====================================
//201号室のバスルーム
//====================================
Fld_201_Bath::Fld_201_Bath(){}
VOID Fld_201_Bath::Set()
{
	P->FM.FldType = FD_201_Bath;
	//部屋
	pRoom = NewObj(new drawObj);
	pRoom->Ob()->Type(x_guestbath);
	pRoom->Ob()->ShadowFlag = FALSE;
	pRoom->Ob()->MeshCol = D3DXVECTOR4(0.5f,0.5f,0.5f,1.0f);
	//流し
	pSink = NewObj(new drawObj);
	pSink ->Ob()->Type(x_tsink);
	pSink ->Ob()->objPos = D3DXVECTOR3(0.5f,0.55f,-2.0f);
	//トイレ
	pToile = NewObj(new Ev::Toile);
	pToile ->Ob()->objPos = D3DXVECTOR3(-1.68f,0.0f,-1.69f);
	pToile ->Ob()->YPR = D3DXVECTOR3(0.0f,90.0f,0.0f);
	//ドア
	pDoor = NewObj(new bathdoor);
	pDoor->Ob()->objPos.z = 2.0f;
	//ライト
	pLight =NewObj(new Light);
	pLight->Ob()->objPos=D3DXVECTOR3(0.00f,2.00f,0.00f);
	//浴槽の当たり判定
	pHitBath = NewObj(new HitBox);
	pHitBath->Ob()->objPos = D3DXVECTOR3(1.4f,0.17f,-1.0f);
	pHitBath->Ob()->objScal = D3DXVECTOR3(2.0f,1.6f,4.0f);
	//空調
	pAir = NewObj(new drawObj);
	pAir->Ob()->Type(x_tdact);
	pAir->Ob()->objPos = D3DXVECTOR3(-1.33f,0.03f,-1.0f);
	pAir->Ob()->YPR = D3DXVECTOR3(90.0f,60.0f,0.0f);
	//空調スイッチ
	pAirSwitch = NewObj(new AirSwitch);
	pAirSwitch->Ob()->objPos = D3DXVECTOR3(-2.0f,0.7f,-1.0f);
	pAirSwitch->Ob()->YPR = D3DXVECTOR3(0.0f,270.0f,0.0f);
	//穴
	pBlackBox = NewObj(new drawObj);
	pBlackBox->Ob()->Type(x_cube);
	pBlackBox->Ob()->MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	pBlackBox->Ob()->SpCol.w = 20.0f;
	pBlackBox->Ob()->objPos = D3DXVECTOR3(-2.24f,1.73f,-1.62f);
	pBlackBox->Ob()->objScal = D3DXVECTOR3(1.0f,0.8f,0.8f);
	pBlackBox->Ob()->ShadowFlag = FALSE;
	//オーディオ-------------------------------------------------------------
	ML->Audio.Audio.Effect = AE_BATHROOM;
	//ライト
	ML->E.Ls.Near=6.50f;
	ML->E.Ls.Far=10.40f;
	ML->E.Ls.Col = D3DXVECTOR4(0.7f,0.7f,0.8f,1.0f);
	//フォグ
	ML->E.Fs.Col.x = 0.600000f;
	ML->E.Fs.Col.y = 0.600000f;
	ML->E.Fs.Col.z = 0.700000f;
	ML->E.Fs.Far = 13.727310f;
	ML->E.Fs.Near = 3.000000f;
	ML->E.Fs.use = 1;

	//フィールドの当たり判定-------------------------------------------------------------
	EriaHit(&D3DXVECTOR3(-2.0f,0.0f,-2.0f),&D3DXVECTOR3(2.0f,2.0f,2.0f));

}
VOID Fld_201_Bath::Update()
{	
	if(pDoor->HitObjFlag(0))
	{
		if(P->Check)
		{
			P->CheckSE(Personal::SE_OPEN);
			FldChange(new Fld_201, &D3DXVECTOR3(-2.0f,0.42f,-1.9f),  0.0f);
		}
	}
	D3DXVECTOR3 Eye(0,0,-5.0f);
	D3DXVECTOR3 At(0,0,0);
	Eye=D3DXVECTOR3(1.9f,1.9f,-1.9f);
	At = P->obj.objPos;	
	ML->E.cam.CamSet(&Eye,&At);
}
