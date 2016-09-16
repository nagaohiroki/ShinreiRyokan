//================================
//201号室扉
//================================
const TCHAR *Door201::name(){return _T("Door201");}
Door201::Door201()
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

	Msh.push_back(&pPlate);
	pPlate.Type(x_door_plate);
	pPlate.drawSkip = TRUE;
	pPlate.drawSkip = FALSE;
	pPlate.SetPare(&pDoor.mWorld);
	pPlate.objPos=D3DXVECTOR3(0.47f,1.3f,0);
	pPlate.ShadowFlag=FALSE;

	Txt.push_back(&roomPlate);
	roomPlate.objScal=D3DXVECTOR3(0.002f,0.002f,1.0f);
	roomPlate.objPos=D3DXVECTOR3(-0.04f,0.0f,-0.042f);
	roomPlate.drawSkip = FALSE;
	roomPlate.SetText(_T("201"));
	roomPlate.SetPare(&pPlate.mWorld);
	roomPlate.MeshCol=D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);

	text.init(this);
	text.s(_T("鍵がかかっている"));
	text.s(_T("なんだかこげくさい"));
	//鍵音
	gatya.Set(wav_keylock);
	gatya.m_b3DSound = TRUE;
	Snd.push_back(&gatya);
	//火の音
	pati.Set(wav_fire);
	pati.m_b3DSound = TRUE;
	pati.m_fVol = 0.1f;
	pati.m_bLoop = TRUE;
	Snd.push_back(&pati);
}
VOID Door201::Update()
{
	if(!(P->FM.iGetedFlag(ITEM_SYOUKAKI) && !P->FM.iGetFlag(ITEM_SYOUKAKI)))
	{
		pati.Start(ML);
		pati.Emi.Position = pBox.objPos;
	}

	if(pBox.HitObj.Reaction == 1)
	{	
		if(P->Mode != Personal::MODE_EVENT)
		if(P->Check)
		{
			if(P->FM.EventFlag >= TL_201_OPEN)
			{
				P->CheckSE(Personal::SE_OPEN);
				m_pPare->FldChange( new Fld_201,&D3DXVECTOR3(-3.95f,0.40f,-2.27f),90.0f);
			}
			else
			{
				gatya.Start(ML);
				gatya.Emi.Position = pBox.objPos;

				text.StartText(P);
			}
		}
	}
	text.Update(P,ML);
}
//================================
//202号室扉
//================================
const TCHAR *Door202::name(){return _T("Door202");}
Door202::Door202()
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

	Msh.push_back(&pPlate);
	pPlate.Type(x_door_plate);
	pPlate.drawSkip = TRUE;
	pPlate.drawSkip = FALSE;
	pPlate.SetPare(&pDoor.mWorld);
	pPlate.objPos=D3DXVECTOR3(0.47f,1.3f,0);
	pPlate.ShadowFlag=FALSE;

	Txt.push_back(&roomPlate);
	roomPlate.objScal=D3DXVECTOR3(0.002f,0.002f,1.0f);
	roomPlate.objPos=D3DXVECTOR3(-0.04f,0.0f,-0.042f);
	roomPlate.drawSkip = FALSE;
	roomPlate.SetText(_T("202"));
	roomPlate.SetPare(&pPlate.mWorld);
	roomPlate.MeshCol=D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	//テキスト
	text.init(this);
	text.s(_T("鍵がかかっている"));
	//テキスト
	text1.init(this);
	text1.s(_T("【202号室の鍵】をつかった"));
	//鍵音
	gatya.Set(wav_keylock);
	gatya.m_b3DSound = TRUE;
	Snd.push_back(&gatya);
	//開錠音
	unlock.Set(wav_dooropen);
	unlock.Filter.Type = BandPassFilter;
	unlock.Filter.OneOverQ = 0.1f;
	unlock.m_b3DSound = TRUE;
	Snd.push_back(&unlock);

}
VOID Door202::Update()
{
	if(pBox.HitObj.Reaction == 1)
	if(P->Mode != Personal::MODE_EVENT)
	if(P->Check)
	{		
		//鍵を持ってる
		if(P->FM.iGetedFlag(ITEM_202_KEY))
		{
			//開錠
			if(P->FM.iGetFlag(ITEM_202_KEY))
			{
				P->FM.iRelease(ITEM_202_KEY);
				text1.StartText(P);
				unlock.Emi.Position = pBox.objPos;
				unlock.Start(ML);
			}
			//鍵が開いている
			else
			{
				P->CheckSE(Personal::SE_OPEN);
				m_pPare->FldChange( new Fld_202,&D3DXVECTOR3(-3.95f,0.40f,-2.27f),90.0f);
			}
		
		}
		//鍵がかかってる
		else
		{
			text.StartText(P);
			gatya.Emi.Position = pBox.objPos;
			gatya.Start(ML);
		}
	}
	text.Update(P,ML);
	text1.Update(P,ML);
}
//================================
//屋上扉
//================================
const TCHAR *DoorRoof::name(){return _T("DoorRoof");}
DoorRoof::DoorRoof()
{
	Msh.push_back(&pBox);
	pBox.Type(x_cube);
	pBox.drawSkip=TRUE;
	pBox.HitMode(CT_OBB,CB_NONE);

	Msh.push_back(&pWaku);
	pWaku.Type(x_exit_door_waku);
	pWaku.objScal=D3DXVECTOR3(0.8f,0.9f,1.0f);
	pWaku.ShadowFlag=FALSE;
	pWaku.SetPare(&pBox.mWorld);

	Msh.push_back(&pDoor);
	pDoor.Type(x_exit_door);
	pDoor.SetPare(&pWaku.mWorld);
	pDoor.objPos.x=-0.47f;
	pDoor.ShadowFlag=FALSE;

	Msh.push_back(&pNobu);
	pNobu.Type(x_exit_door_nobu);
	pNobu.SetPare(&pDoor.mWorld);
	pNobu.objPos=D3DXVECTOR3(0.82f,0.75f,0);
	pNobu.ShadowFlag=FALSE;	
	pNobu.BloomColor.w = 5.0f;

	//テキスト
	text.init(this);
	text.s(_T("鍵がかかっている"));
	//テキスト
	text1.init(this);
	text1.s(_T("【どこかの鍵】をつかった"));
	//鍵音
	gatya.Set(wav_keylock);
	gatya.m_b3DSound = TRUE;
	Snd.push_back(&gatya);
	//開錠音
	unlock.Set(wav_dooropen);
	unlock.Filter.Type = BandPassFilter;
	unlock.Filter.OneOverQ = 0.1f;
	unlock.m_b3DSound = TRUE;
	Snd.push_back(&unlock);
}
VOID DoorRoof::Update()
{
	if(pBox.HitObj.Reaction == 1)
	if(P->Mode != Personal::MODE_EVENT)
	if(P->Check)
	{		
		//鍵を持ってる
		if(P->FM.iGetedFlag(ITEM_ROOF_KEY))
		{
			//開錠
			if(P->FM.iGetFlag(ITEM_ROOF_KEY))
			{
				P->FM.iRelease(ITEM_ROOF_KEY);
				text1.StartText(P);
				unlock.Emi.Position = pBox.objPos;
				unlock.Start(ML);
			}
			//鍵が開いている
			else
			{
				P->CheckSE(Personal::SE_OPEN);
				m_pPare->FldChange(new Fld::Roof_Kai,&D3DXVECTOR3(-0.87f,0.00f,-1.3f),0.0f);
			}
		
		}
		//鍵がかかってる
		else
		{
			text.StartText(P);
			gatya.Emi.Position = pBox.objPos;
			gatya.Start(ML);

		}
	}
	text.Update(P,ML);
	text1.Update(P,ML);
}

//================================
//消火器
//================================
const TCHAR *Syoukaki::name(){return _T("Syoukaki");}
Syoukaki::Syoukaki()
{
	Msh.push_back(&syoukaki);
	syoukaki.HitMode(CT_OBB,CB_PLUS);
	syoukaki.Type(x_syoukaki);
	syoukaki.Bias = 0.2f;
	text.init(this);
	text.s(_T("【消火器】を手に入れた"));
}
VOID Syoukaki::Update()
{
	if(syoukaki.HitObj.Reaction == 1)
	if(P->Mode != Personal::MODE_EVENT)
	if(P->Check)
	{
		if(!P->FM.iGetedFlag(ITEM_SYOUKAKI))
		{
			P->FM.iGet(ITEM_SYOUKAKI);
			P->CheckSE(Personal::SE_ITEM);
			text.StartText(P);
		}
	}
	if(text.Update(P,ML) == 1)
	{
		syoukaki.drawSkip = TRUE;
	}
	
}
//================================
//防火シャッター
//================================
const TCHAR *Shutter::name(){return _T("Shutter");}
Shutter::Shutter()
{
	//ヌルオブジェクト
	NullObj.Type(x_cube);
	NullObj.drawSkip = TRUE; 
	Msh.push_back(&NullObj);
	//シャッター
	shutter.Type(x_bouka);
	shutter.HitMode(CT_OBB,CB_PLUS);
	shutter.ShadowFlag = FALSE;
	shutter.SetPare(&NullObj.mWorld);
	Msh.push_back(&shutter);
	//テキスト
	text.init(this);
	text.s(_T("シャッターが下りている"));

	frame = 0;
	p.SetKey(0,0.0f);
	p.SetKey(100,3.0f);

	kata.Set(wav_step2);
	kata.m_b3DSound = TRUE;
	kata.Filter.OneOverQ = 0.07f;
	kata.Filter.Frequency = 1.0f;
	kata.m_fVol = 0.2f;
	kata.Filter.Type = BandPassFilter;
	Snd.push_back(&kata);

	dan.Set(wav_keylock);
	dan.m_b3DSound = TRUE;
	dan.Filter.OneOverQ = 0.01f;
	Snd.push_back(&dan);


}
VOID Shutter::Set()
{
	if(P->FM.EventFlag >= TL_BOUKA_OPEN)
	{
		frame = 100;
	}
}
VOID Shutter::Update()
{
	if(shutter.HitObj.Reaction == 1)
	if(P->Mode != Personal::MODE_EVENT)
	if(P->Check)
	{
		text.StartText(P);
	}
	text.Update(P,ML);

	if(P->FM.EventFlag >= TL_BOUKA_OPEN)
	{
		if(frame < 100)
		{
			if(frame == 97)
			{
				dan.Emi.Position = shutter.objPos;
				dan.Start(ML);
			}
			kata.Emi.Position = shutter.objPos;
			kata.Start(ML);
			frame++;
		}
	}
	shutter.objPos.y = p.Val1(frame);

}
//================================
//防火スイッチ
//================================
const TCHAR *BoukaSwitch::name(){return _T("BoukaSwitch");}
BoukaSwitch::BoukaSwitch()
{
	//当たり判定
	Msh.push_back(&hitbox);
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.drawSkip = TRUE;
	//スイッチ基盤
	Msh.push_back(&pBase);
	pBase.Type(x_cube);
	pBase.objScal=D3DXVECTOR3(0.2f,0.4f,0.04f);
	pBase.MeshCol=D3DXVECTOR4(0.6f,0.6f,0.6f,1.0f);
	pBase.SetPare(&hitbox.mWorld);
	pBase.ShadowFlag=FALSE;
	pBase.SpColm=0.0f;
	//スイッチ部分
	Msh.push_back(&pSwitch);
	pSwitch.Type(x_cube);
	pSwitch.SetPare(&pBase.mWorld);
	pSwitch.objScal=D3DXVECTOR3(0.5f,0.15f,0.2f);
	pSwitch.objPos=D3DXVECTOR3(0.0f,0.0f,-0.35f);
	pSwitch.MeshCol=D3DXVECTOR4(0.9f,0.9f,0.9f,1.0f);
	pSwitch.YPR.y=-45.0f;
	pSwitch.ShadowFlag=FALSE;
	
	//ゲームテキスト
	fire.init(this);
	fire.s(_T("シャッターを開ける？\nはい\nいいえ"),1,3);
	fire.s(_T("反応しない"));
	fire.s(_T("\"火事の危険が取り除かれていないと操作できません\"\nと書かれている"));
	msgtxt.push_back(&fire);

	dark.init(this);
	dark.s(_T("シャッターの操作盤みたいだが、\n暗くてよくわからない"));
	msgtxt.push_back(&dark);
	
	open.init(this);
	open.s(_T("シャッターを開ける？\nはい\nいいえ"),4,3);
	msgtxt.push_back(&open);

}
VOID BoukaSwitch::Update()
{
	if(P->FM.EventFlag >= TL_BOUKA_OPEN){return;}
	//非消火
	int fades = 0;
	//消火
	if(P->FM.iGetedFlag(ITEM_SYOUKAKI))
	{
		if(!P->FM.iGetFlag(ITEM_SYOUKAKI)){	fades = 2;}
	}
	//暗い
	if(!P->FM.iGetedFlag(ITEM_LIGHT)){fades = 1;}

	//テキスト
	if(hitbox.HitObj.Reaction == 1)
	if(P->Mode != Personal::MODE_EVENT)
	if(P->Check)
	{
		msgtxt[fades]->StartText(P);
	}
	if( msgtxt[fades]->Update(P,ML) == 4 )
	{
		P->FM.EventFlag = TL_BOUKA_OPEN;
	}
}