//=============================================
//ŽžŒv
//=============================================
const TCHAR* Clock::name(){return _T("Clock");}
Clock::Clock()
{
	se.Set(wav_step2);
	se.m_b3DSound = TRUE;
	se.Filter.OneOverQ = 0.5f;
	se.m_fVol = 0.5f;
	Snd.push_back(&se);
	//“–‚½‚è”»’è” 
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.drawSkip = TRUE;
	Msh.push_back(&hitbox);
	//ŽžŒv”Õ
	clock.SetPare(&hitbox.mWorld);
	clock.Type(x_clock);
	clock.ShadowFlag= FALSE; 
	clock.objScal = D3DXVECTOR3(0.6f,0.6f,1.0f); 
	clock.objPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	Msh.push_back(&clock);

	//ŽžjNULL
	hNull.drawSkip = TRUE;
	hNull.Type(x_cube);
	hNull.SetPare(&clock.mWorld);
	hNull.objPos = D3DXVECTOR3(0.0f,0.0f,0.05f);
	hNull.objScal = D3DXVECTOR3(0.04f,0.3f,0.02f);
	Msh.push_back(&hNull);
	//Žžj
	hour.Type(x_cube);
	hour.SetPare(&hNull.mWorld);
	hour.objPos = D3DXVECTOR3(0.0f,0.25f,0.0f);
	hour.ShadowFlag = FALSE;
	hour.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	Msh.push_back(&hour);

	//•ªjNULL
	mNull.SetPare(&clock.mWorld);
	mNull.drawSkip = TRUE;
	mNull.Type(x_cube);
	mNull.objPos = D3DXVECTOR3(0.0f,0.0f,0.05f);
	mNull.objScal = D3DXVECTOR3(0.02f,0.6f,0.02f);
	Msh.push_back(&mNull);
	//•ªj
	min.Type(x_cube);
	min.SetPare(&mNull.mWorld);
	min.objPos = D3DXVECTOR3(0.0f,0.25f,0.0f);
	min.ShadowFlag = FALSE;
	min.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	Msh.push_back(&min);
	//•bjNULL
	sNull.drawSkip = TRUE;
	sNull.Type(x_cube);
	sNull.SetPare(&clock.mWorld);
	sNull.objPos = D3DXVECTOR3(0.0f,0.0f,0.05f);
	sNull.objScal = D3DXVECTOR3(0.01f,0.7f,0.02f);
	//•bj
	Msh.push_back(&sNull);
	sec.Type(x_cube);
	sec.SetPare(&sNull.mWorld);
	sec.objPos = D3DXVECTOR3(0.0f,0.25f,0.0f);
	sec.ShadowFlag = FALSE;
	sec.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	Msh.push_back(&sec);
	//ŽžŠÔ‘«‚·
	w = 3600 * 1 ; 
	w2 = 0;
	//ƒtƒ‰ƒO
	flag = 0;
}
VOID Clock::Update()
{
	
	if(flag == 0)
	{
		if(hitbox.HitObj.Reaction == 2)
		{
			flag = 1;
			w2 = w;
		}
	}
	else if(flag == 1)
	{
		w += 100;
		se.Start(ML);
		se.Emi.Position = hitbox.objPos;
		if( w - w2 >= 3600 )
		{
			flag = 0;
		}
	}
	//5ŽžˆÈ~‚É‚È‚Á‚½‚çƒ^ƒCƒ€ƒ‰ƒCƒ“‚ði‚ß‚é
	if(P->FM.EventFlag <= TL_ENEMY_WALK)
	{
		if(18000 <= w )
		{
			P->FM.EventFlag = TL_TIME5;
		}
	}
	if(86400 < w ){ w = 0;}

	//Žž
//	SYSTEMTIME st;
//	GetLocalTime(&st);
	sNull.SetHit(ML);
	mNull.SetHit(ML);
	hNull.SetHit(ML);
	WORD ws = /*st.wSecond + st.wMinute * 60 + st.wHour * 60 * 60 +*/ w;
	WORD s = ws % 60;
	WORD m = ws / 60 % 60;;
	WORD h = ws / 60 / 60;;
	sNull.YPR.z = (float)s / 60.0f * 360.0f;
	mNull.YPR.z = (float)m / 60.0f * 360.0f + sNull.YPR.z / 60.0f;
	hNull.YPR.z = (float)h / 12.0f * 360.0f + mNull.YPR.z / 12.0f;
	
}
VOID Clock::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,_T("%s\n")
		_T("w = %d\n")
		_T("flag = %d\n")
		,t,w,flag);
}

//=============================================
//’£‚èŽ†‚Æ••½
//=============================================
const TCHAR* Datui_Harigami::name(){return _T("Datui_Harigami");}
Datui_Harigami::Datui_Harigami()
{
	//“–‚½‚è”»’è
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.Type(x_cube);
	hitbox.drawSkip = TRUE;
	Msh.push_back(&hitbox);
	//’£‚èŽ†
	kami.SetPare(&hitbox.mWorld);
	kami.objPos = D3DXVECTOR3(0.18f,1.0f,-0.12f);
	kami.objScal = D3DXVECTOR3(0.2f,0.4f,0.0f);
	Fvf.push_back(&kami);
	//SE
	se.Set(wav_keylock);
	se.m_b3DSound = TRUE;
	Snd.push_back(&se);
	//ƒeƒLƒXƒg(´‘|’†)
	text.init(this);
	text.s(_T("‚ ‚©‚È‚¢"));
	text.s(_T("’£‚èŽ†‚ª’£‚Á‚Ä‚ ‚é"));
	text.s(_T("\"´‘|’† 5:00 ‚Ü‚Å“ü—‹ÖŽ~\""));
	//ƒeƒLƒXƒg(‚ ‚©‚È‚¢)
	text1.init(this);
	text1.s(_T("‚ ‚©‚È‚¢"));	
}
VOID Datui_Harigami::Update()
{

	if(P->FM.EventFlag < TL_TIME5)
	{
		//´‘|’†
		if(P->Check)
		if(hitbox.HitObj.Reaction == 1)
		if(P->Mode != Personal::MODE_EVENT)
		{
			text.StartText(P);
			se.Start(ML);
			se.Emi.Position = hitbox.objPos;
		}
		text.Update(P,ML);
	}
	else
	{
		if(P->FM.enemy.mode == Enemy::MODE_STALK_ATTACK)
		{
			//“GoŒ»Žž
			if(P->Check)
			if(hitbox.HitObj.Reaction == 1)
			if(P->Mode != Personal::MODE_EVENT)
			{
				text1.StartText(P);
				se.Start(ML);
				se.Emi.Position = hitbox.objPos;

			}
			text1.Update(P,ML);
		}
		else
		{
			//•’Ê‚ÉˆÚ“®‚Å‚«‚é
			if(P->Check)
			if(hitbox.HitObj.Reaction == 1)
			if(P->Mode != Personal::MODE_EVENT)
			{
				P->CheckSE(Personal::SE_OPEN);
				m_pPare->FldChange(new Bath_Room_Woman,&D3DXVECTOR3(-10.00f,0.00f,-4.20f),0.0f);
			}
		}
	}
}

//=============================================
//oŒû••½
//=============================================
const TCHAR* Datui_Door::name(){return _T("Datui_Door");}
Datui_Door::Datui_Door()
{
	//“–‚½‚è”»’è
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.Type(x_cube);
	hitbox.drawSkip = TRUE;
	Msh.push_back(&hitbox);
	//SE
	se.Set(wav_keylock);
	se.m_b3DSound = TRUE;
	Snd.push_back(&se);
	//ƒeƒLƒXƒg(´‘|’†)
	text.init(this);
	text.s(_T("‚ ‚©‚È‚¢"));
}
VOID Datui_Door::Update()
{
	if(P->FM.enemy.mode == Enemy::MODE_STALK_ATTACK)
	{
		//“GoŒ»Žž
		if(P->Check)
		if(hitbox.HitObj.Reaction == 1)
		if(P->Mode != Personal::MODE_EVENT)
		{
			text.StartText(P);
			se.Start(ML);
			se.Emi.Position = hitbox.objPos;

		}
		text.Update(P,ML);
	}
	else
	{
		//•’Ê‚ÉˆÚ“®‚Å‚«‚é
		if(P->Check)
		if(hitbox.HitObj.Reaction == 1)
		if(P->Mode != Personal::MODE_EVENT)
		{
			P->CheckSE(Personal::SE_OPEN);
			m_pPare->FldChange(new Bath_Pass,&D3DXVECTOR3(-3.0f,0.00f,0.80f),180.0f);
		}
	}
}

//=============================================
//“GoŒ»
//=============================================
const TCHAR* Datui_Enemy::name(){return _T("Datui_Enemy");}
Datui_Enemy::Datui_Enemy()
{
	se.Set(wav_oop);
	Snd.push_back(&se);

	voice.Set(wav_voice);
	voice.m_b3DSound = TRUE;
	Snd.push_back(&voice);

	bgm.Set(wav_fish);
	Snd.push_back(&bgm);


	wait = 0;
}
VOID Datui_Enemy::Set()
{
	
}
VOID Datui_Enemy::Update()
{
	//UŒ‚ƒ‚[ƒh
	if(P->FM.enemy.mode == Enemy::MODE_CLEAR)
	{
		if(	P->FM.EventFlag == TL_TIME5 )
		{
			if(P->FPSFlag == FALSE)
			{
				P->FM.enemy.mode = Enemy::MODE_SEARCH;
				//“GoŒ»ˆÊ’u

				D3DXVECTOR3 v = D3DXVECTOR3(-5.0f,0.35f,0.0f) -  P->obj.objPos;
				D3DXVec3Normalize(&v,&v);
				P->FM.enemy.pos = P->obj.objPos + v;

				se.Start(ML);
			}
		}
	}
	else if(P->FM.enemy.mode == Enemy::MODE_SEARCH)
	{
		D3DXVECTOR3 v(P->obj.objPos - P->FM.enemy.pos);
		D3DXVec3Normalize(&v,&v);
		P->FM.enemy.rot = D3DXToDegree(atan2f(v.x,v.z)) * 0.5f;
		voice.Start(ML);
		voice.Emi.Position = P->FM.enemy.pos;
		bgm.Start(ML);

		wait++;
		if(wait > 80)
		{
			bgm.Stop(ML,0.0f);
			voice.Stop(ML,0.0f);
			P->FM.enemy.mode = Enemy::MODE_STALK_ATTACK;
		}

	}
	//Ž€–S
	else if(P->FM.enemy.mode == Enemy::MODE_REMOVE)
	{
		P->FM.EventFlag = TL_DATUI_ENEMY_END;
		P->FM.enemy.mode = Enemy::MODE_CLEAR;
	}
}
//ƒfƒoƒbƒO
VOID Datui_Enemy::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,_T("%s\n")
		_T("wait = %d\n")
		,t
		,wait
		);
}
