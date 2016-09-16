const TCHAR *Key201::name(){return _T("Key201");}
Key201::Key201()
{
	//当たり判定箱
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.drawSkip = TRUE;
	Msh.push_back(&hitbox);
	//開錠音
	unlock.Set(wav_dooropen);
	unlock.Filter.Type = BandPassFilter;
	unlock.Filter.OneOverQ = 0.1f;
	unlock.m_b3DSound = TRUE;
	Snd.push_back(&unlock);
	//テキスト
	text.init(this);
	text.s(_T("鍵を開けた"));
}
VOID Key201::Update()
{
	unlock.Emi.Position = hitbox.objPos;
	if(hitbox.HitObj.Reaction == 1)
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	{
		if(P->FM.EventFlag >= TL_201_OPEN)
		{
			//効果音
			P->CheckSE(Personal::SE_OPEN);
			m_pPare->FldChange(new F3, &D3DXVECTOR3(0.5f,2.55f,7.00f),90.0f);
		}
		else
		{
			unlock.Start(ML);
			text.StartText(P);
			P->FM.EventFlag = TL_201_OPEN;
		}

	}
	text.Update(P,ML);
}


//=======================================
//火事
//=======================================
const TCHAR *Fire::name(){return _T("Fire");}
Fire::Fire()
{
	//火
	fire.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 5.0f;
	fire.PrtTime = 0.8f;
	fire.Speed = 0.01f;
	fire.Height = 2.5f;
	fire.SetTex(bmp_fire);
	Prt.push_back(&fire);
	//煙
	smoke.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 3.0f;
	smoke.PrtTime = 0.5f;
	smoke.Speed = 0.02f;
	smoke.Height = 2.5f;
	smoke.SetTex(bmp_smoke);
	Prt.push_back(&smoke);
	//テーブル
	table.Type(x_table);
	table.HitMode(CT_OBB,CB_PLUS);
	table.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 1.5f;
	table.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	Msh.push_back(&table);
	//電気
	denki.Type(x_denki);
	denki.HitMode(CT_OBB,CB_PLUS);
	denki.SetPare(&table.mWorld);
	denki.objPos = D3DXVECTOR3(0.0f,0.35f,0.2f);
	denki.YPR = D3DXVECTOR3(0.0f,60.0f,0.0f);
	denki.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) / 1.5f;
	denki.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	Msh.push_back(&denki);
	//消火器
	syoukaki.Type(x_syoukaki);
	syoukaki.drawSkip = TRUE;
	syoukaki.objScal= D3DXVECTOR3(1.0f,1.0f,1.0f) * 10.0f;
	syoukaki.objPos = D3DXVECTOR3(2.0f,1.0f,1.5f); 
	Msh.push_back(&syoukaki); 
	//SE
	pati.Set(wav_fire);
	pati.m_b3DSound = TRUE;
	Snd.push_back(&pati);
	//噴射音
	syouka.Set(wav_water);
	syouka.m_b3DSound = TRUE;
	syouka.Filter.OneOverQ = 0.1f;
	Snd.push_back(&syouka);
	//フラグ
	flag = 0;
	frame = 0;
	//消火テキスト
	textFire.init(this);
	textFire.s(_T("【消火器】をつかった"));

	textNoFire.init(this);
	textNoFire.s(_T("燃えている"));

	//噴射
	gush.SetTex(bmp_smoke);
	gush.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 3.0f;
	gush.YPR = D3DXVECTOR3(0.0f,0.0f,270.0f);
	gush.Ext = 0.0f;
	gush.Height = 3.0f;
	gush.Speed = 0.05f;
	gush.drawSkip = TRUE;
	Prt.push_back(&gush);
}
VOID Fire::Set()
{
	syoukaki.SetPare(&P->gt.Null.mWorld);

	ML->E.Fs.Far = 10.0f;
	ML->E.Fs.Near = 1.5f;
	if(P->FM.iGetedFlag(ITEM_SYOUKAKI))
	{
		if(!P->FM.iGetFlag(ITEM_SYOUKAKI))
		{
			ML->E.Fs.Far = 30.0f;
			ML->E.Fs.Near = 0.0f;

			
		}
	}
}
VOID Fire::Update()
{
	if(P->FM.iGetedFlag(ITEM_SYOUKAKI))
	{
		if(!P->FM.iGetFlag(ITEM_SYOUKAKI))
		{
			if(ML->E.Fs.Far <= 30.0f){ML->E.Fs.Far  += 0.01f;}
			if(ML->E.Fs.Near>=  0.0f){ML->E.Fs.Near -= 0.005f;}
			fire.drawSkip = TRUE;
			smoke.drawSkip = TRUE;
			return;
		}
		else
		{
	
			if(flag == 0)
			{
				pati.Start(ML);
				pati.Emi.Position = table.objPos;
				//調べる
				if(table.HitObj.Reaction == 1)
				if(P->Check)
				if(P->Mode != Personal::MODE_EVENT)
				{
					//テキストスタート
					textFire.StartText(P);		
				}
			}
			//テキスト進める
			if(textFire.Update(P,ML) == 1)
			{
				flag = 1;
			}
			if(flag == 1)
			{
				//噴出のアングル
				D3DXVECTOR3 v(table.objPos - P->obj.objPos);
				D3DXVec3Normalize(&v,&v);
				float angle = D3DXToDegree(atan2f(v.x,v.z));
				gush.objPos = D3DXVECTOR3(syoukaki.mWorld._41,syoukaki.mWorld._42 + 0.5f,syoukaki.mWorld._43);
				gush.YPR.y = angle - 90.0f;
				gush.drawSkip = FALSE; 
				//プレイヤーのアングル
				P->Mode = Personal::MODE_EVENT;
				P->obj.YPR.y = angle;
				//消火器出現
				syoukaki.drawSkip = FALSE;	
				//消火器音
				syouka.Emi.Position = syoukaki.objPos;
				syouka.Start(ML);
				//フレームを進めて消す
				frame++;
				int time = 200;
				if(frame >= time){	flag = 2;}

				//段々小さくなる
				float scl = (float)(time - frame) / (float)time;
				fire.objScal  = D3DXVECTOR3(1.0f,1.0f,1.0f) * 5.0f * scl;
				smoke.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 3.0f * scl;
				gush.objScal  = D3DXVECTOR3(1.0f,1.0f,1.0f) * 3.0f * scl;
			}
			if(flag == 2)
			{
				P->Mode = Personal::MODE_ACTIVE;
				//SE消滅
				syouka.Stop(ML,0.0f);
				pati.Stop(ML,0.0f);		
				//オブジェクト消滅
				syoukaki.drawSkip = TRUE;
				//各パーティクル消滅
				gush.drawSkip = TRUE;
				fire.drawSkip = TRUE;
				smoke.drawSkip = TRUE;
				flag = 3;
			}
			if(flag == 3)
			{
				P->FM.iRelease(ITEM_SYOUKAKI);
			}
		}
		
	}
	else
	{
		if(flag == 0)
		{
				pati.Start(ML);
				pati.Emi.Position = table.objPos;
				//調べる
				if(table.HitObj.Reaction == 1)
				if(P->Check)
				if(P->Mode != Personal::MODE_EVENT)
				{
					//テキストスタート
					textNoFire.StartText(P);		
				}
		}
		//テキスト進める
		textNoFire.Update(P,ML);
	}
}
