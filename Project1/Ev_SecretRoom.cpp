//==========================================
//ドア
//==========================================
const TCHAR* ScDoor::name(){return _T("ScDoor");}
ScDoor::ScDoor()
{
	Msh.push_back(&pBox);
	pBox.Type(x_cube);
	pBox.drawSkip=TRUE;
	pBox.HitMode(CT_OBB,CB_NONE);

	Msh.push_back(&pWaku);
	pWaku.Type(x_wood_door_waku);
	pWaku.objScal=D3DXVECTOR3(0.8f,0.9f,1.0f);
	pWaku.ShadowFlag=FALSE;
	pWaku.SetPare(&pBox.mWorld);

	Msh.push_back(&pDoor);
	pDoor.Type(x_wood_door);
	pDoor.SetPare(&pWaku.mWorld);
	pDoor.objPos.x=-0.47f;
	pDoor.ShadowFlag=FALSE;

	Msh.push_back(&pNobu);
	pNobu.Type(x_doornobu);
	pNobu.SetPare(&pDoor.mWorld);
	pNobu.objPos=D3DXVECTOR3(0.82f,0.75f,0);
	pNobu.ShadowFlag=FALSE;
	//バック
	Msh.push_back(&pBack);
	pBack.Type(x_cube);
	pBack.SetPare(&pBox.mWorld);
	pBack.objPos = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pBack.objScal = D3DXVECTOR3(10.0f,10.0f,0.0f);
	pBack.SpCol = D3DXVECTOR4(10.0f,10.0f,10.0f,0.0f);
	pBack.SpColm = 10.0f;
	pBack.BloomColor = D3DXVECTOR4(10.0f,10.0f,10.0f,10.0f);
	pBack.ShadowFlag = FALSE;
	//アルファマスク
	Msh.push_back(&pMask);
	pMask.Type(x_cube);
	pMask.SetPare(&pBox.mWorld);
	pMask.MeshCol.w = 0.0f;
	pMask.SpColm = 0.0f;
	pMask.ShadowFlag = FALSE;
	pMask.Amb = 0.0f;
	pMask.objPos = D3DXVECTOR3(0.0f,0.67f,0.0f);
	pMask.objScal = D3DXVECTOR3(1.52f,3.212f,0.1f);

	//フェード
	black.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	Ui.push_back(&black);
	//SE
	open.Set(wav_dooropen);
	Snd.push_back(&open);

	//アニメーション
	flag = 0;
	frame = 0;
	//ドア開く
	rot.SetKey(0,0.0f);
	rot.SetKey(50,0.0f);
	rot.SetKey(150,130.0f);

	//フェード
	fade.SetKey(0,1.0f);
	fade.SetKey(50,1.0f);
	fade.SetKey(300,0.7f);
	fade.SetKey(500,1.0f);

	//カメラアングル
	at.SetKey(0,D3DXVECTOR3(-4.7f,-0.2f,-2.0f));
	at.SetKey(100,D3DXVECTOR3(-4.7f,-0.2f,-2.0f));
	at.SetKey(300,D3DXVECTOR3(-4.7f,0.1f,-2.0f));
	at.SetKey(400,D3DXVECTOR3(-4.7f,0.1f,-2.0f));
	at.SetKey(500,D3DXVECTOR3(-4.7f,-0.2f,-2.0f));

	//テキスト
	text.init(this);
	text.s(_T("ひどく衰弱していたが、息はあった"));
	text.s(_T("少女をおぶり、外の公衆電話で助けを呼んだ"));
	text.s(_T("救助はすぐに到着し、\n無事旅館を出ることができた。"));
	//クレジット
	osimai.drawSkip = TRUE;
	osimai.MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,0.0f);
	UiTxt.push_back(&osimai);
	//アルファ
	alpha.SetKey(0,0.0f);
	alpha.SetKey(100,1.0f);
	alpha.SetKey(200,1.0f);
	alpha.SetKey(300,0.0f);
	alpha.SetKey(400,1.0f);
	alpha.SetKey(500,1.0f);

}
VOID ScDoor::Set()
{
	black.objScal.x = (float)ML->GV.ClientWidth;
	black.objScal.y = (float)ML->GV.ClientHeight;
	
	SAFE_DELETE(P->BGM);
	P->BGM = new CObjSound;
	P->BGM->m_fNoise = 0.001f;
	P->BGM->m_fVol = 0.5f;
	P->BGM->Set(wav_room);
}

VOID ScDoor::Update()
{
	P->Mode = Personal::MODE_EVENT;
	if(flag == 0)
	{
		//演出
		if( frame == 50 )
		{
			open.Start(ML);
		}
		black.MeshCol.w = fade.Val1(frame);
		pDoor.YPR.y = rot.Val1(frame);
		ML->E.cam.CamSet(&D3DXVECTOR3(2.1f,0.2f,-1.56f),&at.Val1(frame));
		frame++;
		if( frame > 500 )
		{

			text.StartText(P);
			P->BGM->Start(ML);
			flag = 1;

		}

	}
	else if(flag == 2)
	{
		P->FM.EventFlag = TL_ENDING;
		m_pPare->FldChange(new Soto,&D3DXVECTOR3(0.0f,0.0f,0.0f),0.0f);
		
	}
	
	//テキスト終了
	if(text.Update(P,ML) == text.Max())
	{
		flag = 2;
		frame = 0;
	}

	
	
}
VOID ScDoor::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,
		_T("%s\n")
		_T("flag = %d frame = %d\n")
		,t,flag,frame
		);
}
