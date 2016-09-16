//===========================================
//ラジカセ
//===========================================
const TCHAR* Razikase::name(){return _T("Razikase");}
Razikase::Razikase()
{
	//ヌルオブジェクト
	NullObj.Type(x_cube);
	NullObj.drawSkip = TRUE;
	Msh.push_back(&NullObj);
	//当たり判定
	hitbox.Type(x_cube);
	hitbox.drawSkip = TRUE;
	hitbox.HitMode(CT_OBB,CB_PLUS);
	hitbox.SetPare(&NullObj.mWorld);
	hitbox.objScal = D3DXVECTOR3(1.0f,3.0f,1.0f);
	hitbox.objPos = D3DXVECTOR3(0.0f,0.65f,0.0f);
	Msh.push_back(&hitbox);
	//桶
	float h = 0.15f;
	for(int i = 0; i < SEN_MAX;i++)
	{
		Msh.push_back(&senmen[i]);
		senmen[i].Type(x_bath_oke);
		senmen[i].SetPare(&NullObj.mWorld);
		senmen[i].objPos = D3DXVECTOR3(0.0f,h * (float)(i + 1),0.0f);
		senmen[i].YPR.x = 180.0f;
		senmen[i].ShadowFlag = FALSE;
	}
	//ラジカセ
	razikase.SetPare(&NullObj.mWorld);
	razikase.Type(x_razikase);
	razikase.objPos = D3DXVECTOR3(0.0f,(float)SEN_MAX * h,-0.1f);
	razikase.HitMode(CT_OBB,CB_PLUS);
	Msh.push_back(&razikase);
	//鍵
	Key.Type(x_key);
	Key.SetPare(&razikase.mWorld);
	Key.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f)* 0.2f;
	Key.objPos = D3DXVECTOR3(0.0f,0.0f,0.02f);
	Key.YPR.x = 90.0f;
	Key.MeshCol =D3DXVECTOR4(0.5f,0.5f,0.5f,1.0f);
	Key.SpCol.w = 0.0f;
	Key.SpColm = 1.0f;
	Key.BloomColor = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f)* 20.0f;
	Key.HitMode(CT_OBB,CB_NONE);
	Msh.push_back(&Key);
	//bgm
	bgm.Set(wav_karappo);
	bgm.m_b3DSound = TRUE;
	bgm.m_bLoop = TRUE;
	bgm.Filter.OneOverQ = 0.5f;
	bgm.m_fVol = 0.8f;
	Snd.push_back(&bgm);
	//se
	se.Set(wav_oop);
	se.m_b3DSound = TRUE;
	se.m_fVol = 1.0f;
	se.Filter.Frequency = 0.3f;
	Snd.push_back(&se);
	//キーSE
	KeySe.m_b3DSound = TRUE;
	KeySe.Filter.OneOverQ = 0.5f;
	KeySe.Set(wav_suzumusi);
	Snd.push_back(&KeySe);
	

	//ラジカセアニメーション
	frame = 0; 
	flag = 0;
	
	p.SetKey(0,D3DXVECTOR3(0.0f,(float)SEN_MAX * h,0.0f));
	p.SetKey(40,D3DXVECTOR3(0.0f,(float)SEN_MAX * h,0.0f));
	p.SetKey(70,D3DXVECTOR3(0.0f,0.0f,-1.0f));
	rx.SetKey(0,0.0);
	rx.SetKey(30,-90.0);
	rx.SetKey(60,-180.0);
	rx.SetKey(70,-90.0);
	//鍵アニメーション
	kp.SetKey(0,D3DXVECTOR3(0.0f,0.0f,0.02f));
	kp.SetKey(70,D3DXVECTOR3(0.0f,0.0f,0.02f));
	kp.SetKey(100,D3DXVECTOR3(0.0f,1.0f,0.02f));

	kr.SetKey(0,D3DXVECTOR3(0.0f,90.0f,270.0f));
	kr.SetKey(70,D3DXVECTOR3(0.0f,90.0f,270.0f));
	kr.SetKey(100,D3DXVECTOR3(400.0f,90.0f,270.0f));

	//テキスト
	text.init(this);
	text.s(_T("【机の鍵】を手に入れた"));

}
VOID Razikase::Update()
{
	//アイテム持っていれば
	if(P->FM.iGetedFlag(ITEM_DESK_KEY))
	{
		razikase.objPos = D3DXVECTOR3(0.0f,0.0f,-1.0f);
		razikase.YPR.x = -90.0f;
		Key.drawSkip = TRUE;
		return;
	}
	//持っていない場合
	if(flag == 0)
	{
		if(razikase.HitObj.Reaction == 2)
		{
			flag = 1;
			P->AtcBullet(&razikase.mWorld);
		
		}
		bgm.Emi.Position = D3DXVECTOR3(NullObj.mWorld._41,NullObj.mWorld._42,NullObj.mWorld._43);
		bgm.Start(ML);
	}
	else if(flag == 1)
	{
		frame++;
		//SE
		if( frame == 60)
		{
			se.Emi.Position = D3DXVECTOR3(NullObj.mWorld._41,NullObj.mWorld._42,NullObj.mWorld._43);
			se.Start(ML);
			KeySe.Emi.Position = D3DXVECTOR3(Key.mWorld._41,Key.mWorld._42,Key.mWorld._43);
			KeySe.Start(ML);
		}
		if(frame > 100)
		{
			flag = 2;
			bgm.Stop(ML,0.0f);
			KeySe.Stop(ML,0.0f);
		}
		razikase.objPos = p.Val1(frame);
		razikase.YPR.x = rx.Val1(frame);
		Key.objPos = kp.Val1(frame);
		Key.YPR = kr.Val1(frame);
	}
	else if(flag == 2)
	{
		if(P->Check) 
		if(P->Mode != Personal::MODE_EVENT )
		if(Key.HitObj.Reaction == 1)
		{
			text.StartText(P);
			P->CheckSE(Personal::SE_ITEM);
	
		}
		if(text.Update(P,ML) == 1)
		{
			P->FM.iGet(ITEM_DESK_KEY);
			Key.drawSkip = TRUE;
			flag = 3;
		}
	}
}

VOID Razikase::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,_T("%s\n")
		_T("bgm.m_fVol = %f\n")
		_T("bgm.Filter.Frequency = %f\n")
		_T("flag = %d\n")

		,t
		,bgm.m_fVol
		,bgm.Filter.Frequency
		,flag
		);
}

