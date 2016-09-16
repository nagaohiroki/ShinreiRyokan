//ゲームオーバーイベント
Ev_GameOver::Ev_GameOver()
{
	Eff = FALSE;
	frame = 0;
	slctNum = 0;
	slct = 0;
	//テキスト
	UiTxt.push_back(&text);
	text.objPos.y = -160.0f;
	text.SetText(_T("途中から始める\nタイトルに戻る"));
	text.drawSkip = TRUE;
	//ゲームオーバー字
	go.SetText(_T("GameOver"));
	go.intrval.x = 3.0f;
	go.objScal = D3DXVECTOR3(1.5f,1.5f,1.0f);
	go.MeshCol.w = 0.0f;
	go.objPos = D3DXVECTOR3(-200.0f,0.0f,0.0f);
	UiTxt.push_back(&go);

	//選択肢
	Ui.push_back(&select);
	select.drawSkip = TRUE;
	//アルファ
	alpha.SetKey(0,0.0f);
	alpha.SetKey(50,0.5f);
	alpha.SetKey(100,0.0f);
	//ノイズ音
	sa.Filter.Frequency = 0.3f;
	sa.Set(wav_sa);
	Snd.push_back(&sa);
	//BGM
	bgm.Set(wav_ooo);
	bgm.m_bLoop = TRUE;
	bgm.m_fVol = 0.5f;
	Snd.push_back(&bgm);

}
VOID Ev_GameOver::Set()
{
	P->Mode = Personal::MODE_EVENT;
	P->gt.drawSkip = TRUE;
	
}
VOID Ev_GameOver::SChange()
{
	switch(P->FM.FldType)
	{
	case FD_Guest_Room:
	case FD_Guest_Bath:
		P->FM.EventFlag = TL_DRUG_GUNGUN;
		P->FM.enemy.HP = 5;
		P->FM.enemy.mode = Enemy::MODE_CLEAR;
		m_pPare->FldChange(new Fld::Guest_Room,&D3DXVECTOR3(-2.0f,0.42f,-1.9f),180.0f);
		break;
	case FD_Rest_Men:
		m_pPare->FldChange(new F3,&D3DXVECTOR3(-18.90f,2.55f,24.42f),180.0f);
		break;
	case FD_Rest_Women:
		P->FM.enemy.HP = 5;
		P->FM.enemy.mode = Enemy::MODE_CLEAR;
		P->FM.iRemove(ITEM_ROOF_KEY);
		m_pPare->FldChange(new F3,&D3DXVECTOR3(-21.0f,2.55f,24.42f),180.0f);
		break;
	case FD_Roof_Top:
		P->FM.EventFlag = TL_GUEST_ENEMY_END;
		P->FM.enemy.HP = 5;
		P->FM.enemy.mode = Enemy::MODE_CLEAR;
		m_pPare->FldChange(new Roof_Kai,&D3DXVECTOR3(0.84f,2.30f,-1.3f),180.0f);
		break;
	case FD_Bath_Datui_Woman:
		P->FM.EventFlag = TL_ENEMY_WALK;
		P->FM.enemy.HP = 5;
		P->FM.enemy.mode = Enemy::MODE_CLEAR;
		m_pPare->FldChange(new Bath_Pass,&D3DXVECTOR3(-3.0f,0.00f,0.80f),0.0f);
		break;
	case FD_TestRoom:
		m_pPare->FldChange(new Fld::TestRoom,&D3DXVECTOR3(0.0f,0.0f,0.0f),90.0f);
		P->FM.enemy.mode = Enemy::MODE_CLEAR;
		break;

	case FD_Staff_Room:
		m_pPare->FldChange(new Fld::Lobby,&D3DXVECTOR3(12.00f,0.00f,13.20f),90.0f);
		P->FM.EventFlag = TL_DATUI_ENEMY_END;
		P->FM.iGet(ITEM_DESK_KEY);
		break;
		
	case FD_203:
		P->FM.enemy.HP = 5;
		P->FM.enemy.mode = Enemy::MODE_CLEAR;
		m_pPare->FldChange(new Fld::F3,&D3DXVECTOR3(-4.00f,2.55f,30.5f),180.0f);
		P->FM.iRemove(ITEM_GENKAN_KEY);	
		P->FM.iGet(ITEM_203_KEY);
		break;
	case FD_Soto:
		m_pPare->FldChange(new Fld::Soto,&D3DXVECTOR3(2.50f,0.35f,13.5f),90.0f);
		break;
	default:
		P->FM.enemy.HP = 5;
		P->FM.enemy.mode = Enemy::MODE_CLEAR;
		m_pPare->FldChange(new Fld::Title,&D3DXVECTOR3(0.0f,0.0f,0.0f),90.0f);//想定外
		break;
	}
}

VOID Ev_GameOver::Update()
{	
	//アルファ
	frame++;

	//演出フェード
	if(Eff == FALSE)
	{
		//ちかちか
		if(frame == 50 || frame == 70 || frame == 100 )
		{
			sa.Start(ML);
		}
		if(frame == 50 || frame == 70 || (frame >= 90 && frame <= 100) || frame >= 150)
		{

			go.MeshCol.w = 1.0f;
		}
		else{go.MeshCol.w = 0.0f;}
		//演出カット
		if(P->Check || frame == 200)
		{
			go.MeshCol.w = 1.0f;
			select.drawSkip = FALSE;
			text.drawSkip = FALSE;
			Eff = TRUE;
			frame = 0;
		}
		return;
	}
	//BGM
	bgm.Start(ML);
	if(frame > alpha.MaxKey()){frame = 0;}
	select.MeshCol.w = alpha.Val(frame);
	//テキスト
	float xsize = (text.vol.x + (float)ML->CSMin.FontSize * text.objScal.x  * 0.5f) * 0.5f;
	float ysize = ((float)ML->CSMin.FontSize * text.objScal.y * text.intrval.y);
	select.objPos.x = text.objPos.x + xsize;
	select.objPos.y = text.objPos.y - ysize * (float)slctNum;
	select.objScal.x = 250.0f; 
	select.objScal.y = ((float)ML->CSMin.FontSize * text.objScal.y);
	//テキスト
	text.objPos.x = -xsize;
	//ゲームオーバーテキスト
	//マウスロック
	ML->C.MouseLock(TRUE,ML->hW);
	if(	slct != slctNum)
	{
		P->CheckSE(Personal::SE_SELECT);
	}
	slct = slctNum;
	
	if(ML->C.getkey.k0m1 == 0)
	{
		//キーボード
		if(ML->C.UP.T() || ML->C.DOWN.T())
		{
			slctNum = 1 - slctNum; 
		}
	}
	else
	{
		//マウス
		if(ML->GV.mPos.y > text.objPos.y - ysize * 0.5f){slctNum = 0;}
		else{slctNum = 1;}
	}
	//決定
	if(P->Check)
	{
		if(slctNum == 0)
		{
			//コンテニュー
			ML->C.MouseLock(FALSE,ML->hW);	
			P->Mode = Personal::MODE_ACTIVE;
			SChange();
		}
		else
		{
			//タイトルに戻る
			m_pPare->FldChange(new Fld::Title,&D3DXVECTOR3(0.0f,0.0f,0.0f),0.0f);
		}
	}
}
VOID Ev_GameOver::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,
		_T("%s\n")
		_T("%d")
		
		,t
		,slctNum
	
		);
}
