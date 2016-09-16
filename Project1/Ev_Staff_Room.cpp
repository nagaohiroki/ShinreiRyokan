//======================================
//ロビーに出る扉
//======================================
const TCHAR* Lobby_Door::name(){return _T("Lobby_Door");}
Lobby_Door::Lobby_Door()
{
	//当たり判定
	Msh.push_back(&pBox);
	pBox.Type(x_cube);
	pBox.drawSkip=TRUE;
	pBox.HitMode(CT_OBB,CB_NONE);
	//ドア枠
	Msh.push_back(&pWaku);
	pWaku.Type(x_wood_door_waku);
	pWaku.objScal=D3DXVECTOR3(0.8f,0.9f,1.0f);
	pWaku.ShadowFlag=FALSE;
	pWaku.SetPare(&pBox.mWorld);
	//ドア
	Msh.push_back(&pDoor);
	pDoor.Type(x_wood_door);
	pDoor.SetPare(&pWaku.mWorld);
	pDoor.objPos.x=-0.47f;
	pDoor.ShadowFlag=FALSE;
	//ドアノブ
	Msh.push_back(&pNobu);
	pNobu.Type(x_doornobu);
	pNobu.SetPare(&pDoor.mWorld);
	pNobu.objPos=D3DXVECTOR3(0.82f,0.75f,0);
	pNobu.ShadowFlag=FALSE;	
}
VOID Lobby_Door::Update()
{
	//移動
	if(pBox.HitObj.Reaction == 1)
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	{
		P->CheckSE(Personal::SE_OPEN);	
		m_pPare->FldChange(new Lobby,&D3DXVECTOR3(12.00f,0.00f,13.20f),270.0f);
	}
}
//======================================
//机
//======================================
const TCHAR* Desk::name(){return _T("Desk");}
Desk::Desk()
{
	//机
	desk.Type(x_desk);
	desk.Bias = 0.3f;
	desk.MeshCol = D3DXVECTOR4(0.4f,0.4f,0.4f,1.0f);
	Msh.push_back(&desk);
	//当たり判定
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.SetPare(&desk.mWorld);
	hitbox.objPos =D3DXVECTOR3(0.25f,0.0f,0.25f);
	hitbox.drawSkip = TRUE;
	Msh.push_back(&hitbox);
	//テキスト
	text.init(this);
	text.s(_T("机の中にはなにもない"));
}
VOID Desk::Update()
{
	if(hitbox.HitObj.Reaction == 1)
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	{
		text.StartText(P);
	}
	text.Update(P,ML);
}

//======================================
//机
//======================================
const TCHAR* KeyDesk::name(){return _T("KeyDesk");}
KeyDesk::KeyDesk()
{
	//机
	desk.Type(x_desk);
	desk.Bias = 0.3f;
	desk.MeshCol = D3DXVECTOR4(0.4f,0.4f,0.4f,1.0f);
	Msh.push_back(&desk);
	//当たり判定
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.SetPare(&desk.mWorld);
	hitbox.objPos =D3DXVECTOR3(0.25f,0.0f,0.25f);
	hitbox.drawSkip = TRUE;
	Msh.push_back(&hitbox);
	//テキスト
	text.init(this);
	text.s(_T("【机の鍵】を使った"));
	text.s(_T("机の中には何も無い"));
	//テキスト1
	text1.init(this);
	text1.s(_T("机の引き出しには鍵がかかっている"));

	//鍵がかかってる音
	lock.Set(wav_keylock);
	lock.m_b3DSound = TRUE;
	Snd.push_back(&lock);
	//開錠音
	unlock.Set(wav_dooropen);
	unlock.Filter.Type = BandPassFilter;
	unlock.Filter.OneOverQ = 0.1f;
	unlock.m_b3DSound = TRUE;
	Snd.push_back(&unlock);
}
VOID KeyDesk::Update()
{
	
	if(P->FM.iGetedFlag(ITEM_DESK_KEY))
	if(!P->FM.iGetFlag(ITEM_DESK_KEY))
	{
		return;
	}
	
	
	if(hitbox.HitObj.Reaction == 1)
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	{ 
		if(P->FM.iGetedFlag(ITEM_DESK_KEY))
		{
			//開錠
			unlock.Emi.Position = desk.objPos;
			unlock.Start(ML);
			text.StartText(P);
		}
		else
		{
			//鍵がかかってる
			lock.Emi.Position = desk.objPos;
			lock.Start(ML);

			text1.StartText(P);
		}
	
	}
	text1.Update(P,ML);
	int t = text.Update(P,ML);

	//鍵を捨てる
	if(t == 2)
	{
		P->FM.iRelease(ITEM_DESK_KEY);
	}
		
	
}

//======================================
//ホワイトボード
//======================================
const TCHAR* WhiteBord::name(){return _T("WhiteBord");}
WhiteBord::WhiteBord()
{
	flag = 0;
	frame = 0;

	//ホワイトボード
	white.Type(x_whitebord);
	white.Bias = 0.3f;
	Msh.push_back(&white);

	hitbox.Type(x_cube);
	hitbox.drawSkip = TRUE;
	hitbox.HitMode(CT_OBB,CB_PLUS);
	hitbox.objScal = D3DXVECTOR3(4.054777f,7.0f,0.362946f);
	hitbox.objPos  = D3DXVECTOR3(0.0f,0.0f,0.0f);
	Msh.push_back(&hitbox);

	head.Type(x_sphere);
	head.HitMode(CT_SPHERE,CB_NONE);
	head.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 0.3f;
	head.drawSkip = TRUE;
	Msh.push_back(&head);

	rot.SetKey(0,0.0f);
	rot.SetKey(90,20.0f);
	rot.SetKey(100,70.0f);
	
	se.Set(wav_oop);
	se.m_b3DSound = TRUE;
	se.Filter.Frequency = 0.1f;
	Snd.push_back(&se);
}
VOID WhiteBord::Update()
{
	head.SetHit(ML);
	hitbox.SetHit(ML);
	hitbox.objPos = white.objPos;
	hitbox.YPR = white.YPR;
	head.objPos = P->obj.objPos + D3DXVECTOR3(0.0f,1.0f,0.0f);
	if(	P->FM.EventFlag >= TL_WHITEBORD)
	{
		white.YPR.x = 70.0f;
		hitbox.YPR.x = 70.0f;
		return;
	}
	if(flag == 0)
	{
		if(P->FM.iGetedFlag(ITEM_DESK_KEY))
		if(!P->FM.iGetFlag(ITEM_DESK_KEY))
		{
			flag = 1;
	
		}	
	}
	if(flag == 1)
	{
		frame++;
		if(frame > 100)
		{
			se.Emi.Position = white.objPos;
			se.Start(ML);
			flag = 2;
		}
		float r = rot.Val1(frame);
		white.YPR.x =  r;
		//白板に当たるとゲームオーバー
		if(frame > 90)
		{
			
			if(ML->Col.Hit(&head.HitObj,&hitbox.HitObj))
			{
				m_pPare->FldChange(new Gameover,&D3DXVECTOR3(0.0f,0.0f,0.0f),0.0f);
				
			}
		}
	}
	if(flag == 2)
	{
		P->FM.EventFlag = TL_WHITEBORD;
	}
}
VOID WhiteBord::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,
		_T("%s\n")
		_T("flag = %d\n")
		,t
		,flag
		
		);
}

//======================================
//鍵
//======================================
const TCHAR* Key203::name(){return _T("Key203");}
Key203::Key203()
{
	
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.drawSkip = TRUE;
	hitbox.MeshCol.w = 0.5f;
	Msh.push_back(&hitbox);
	
	key.Type(x_key);
	key.SetPare(&hitbox.mWorld);
	key.objScal = D3DXVECTOR3(0.15f,0.15f,0.15f);
	Msh.push_back(&key);
	
	text.init(this);
	text.s(_T("【203号室の鍵】を手に入れた"));

}
VOID Key203::Update()
{
	if(P->FM.iGetedFlag(ITEM_203_KEY))
	{
		key.drawSkip = TRUE;
		return;
	}
	if(hitbox.HitObj.Reaction == 1)
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	{
		P->CheckSE(Personal::SE_ITEM);
		text.StartText(P);
	}
	if(text.Update(P,ML) == 1)
	{
		P->FM.iGet(ITEM_203_KEY);
	}
	
}

//======================================
//椅子
//======================================
const TCHAR* StaffChair::name(){return _T("StaffChair");}
StaffChair::StaffChair()
{
	chair.HitMode(CT_OBB,CB_PLUS);
	chair.Type(x_dining_chair);
	chair.SpColm = 0.0f;
	Msh.push_back(&chair);
	chair1.Type(x_dining_chair);
	chair1.SpColm = 0.0f;
	chair1.SetPare(&chair.mWorld);
	chair1.objPos = D3DXVECTOR3(0.0f,0.75f,-0.15f);
	chair1.YPR = D3DXVECTOR3(180.0f,15.0f,0.0f);
	Msh.push_back(&chair1);
}

//======================================
//支配人の机
//======================================
const TCHAR* MasterDesk::name(){return _T("MasterDesk");}
MasterDesk::MasterDesk()
{
	//机
	desk.Type(x_desk);
	desk.Bias = 0.3f;
	desk.MeshCol = D3DXVECTOR4(0.4f,0.4f,0.4f,1.0f);
	Msh.push_back(&desk);

	//机
	desk1.Type(x_desk);
	desk1.Bias = 0.3f;
	desk1.MeshCol = D3DXVECTOR4(0.4f,0.4f,0.4f,1.0f);
	desk1.objPos = D3DXVECTOR3(0.1f,1.05f,0.1f);
	desk1.YPR = D3DXVECTOR3(180.0f,10.0f,0.0f);
	desk1.SetPare(&desk.mWorld);
	Msh.push_back(&desk1);
	//当たり判定
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.SetPare(&desk.mWorld);
	hitbox.objPos =D3DXVECTOR3(0.25f,0.0f,0.25f);
	hitbox.drawSkip = TRUE;
	Msh.push_back(&hitbox);
	//当たり判定1
	hitbox1.Type(x_cube);
	hitbox1.HitMode(CT_OBB,CB_PLUS);
	hitbox1.SetPare(&desk.mWorld);
	hitbox1.drawSkip = TRUE;
	hitbox1.objScal = D3DXVECTOR3(1.5f,6.0f,1.7f);
	Msh.push_back(&hitbox1);
	//テキスト
	text.init(this);
	
text.s(_T("引き出しにノートがある"));
text.s(_T("この旅館の支配人の日誌のようだ"));
text.s(_T("6/4\n改装工事が当初の予定より長引いている。"));
text.s(_T("早く終わらせてもらいたいが、\nこればっかりは待つしかないだろう"));
text.s(_T("11/2\nここには幽霊がいるようだ。"));
text.s(_T("夜な夜な泣き声が聞こえたり、\n物が隠されたりする"));
text.s(_T("色々対策をしたが、\nあまり効果は無いようだ"));
text.s(_T("しかし、長く勤めているが、\n霊に心当たりがない"));
text.s(_T("死者が出るような事件事故は無いし、\n特にいわくのある土地でもない"));
text.s(_T("従業員の一人が生霊かもしれないと言っていた。"));
text.s(_T("生霊?"));
text.s(_T("12/11\n経営が厳しくなってきた。"));
text.s(_T("幽霊の件もあるが、\n改装工事が長引いてシーズンとかぶってしまったのが大きい。"));
text.s(_T("1/20\n来月いっぱいで解散する事になった。"));
text.s(_T("建物はとある製薬会社が買い取るらしい\n社員とは何度か会った。怪しい連中だ"));
text.s(_T("2/26\n今日で解散だ。\n良き仲間と仕事を出来たことに感謝したい"));
text.s(_T("・・・・・"));
text.s(_T("ノートはここで終わっている"));

	/*
	text.s(_T("引き出しにノートがある"));
	text.s(_T("支配人の日誌のようだ"));
	
	text.s(_T("11/10\nこの旅館には幽霊がいる"));
	text.s(_T("物を隠したり音を立てたりするくらいで、\n悪い霊ではないと私は思ってる"));
	text.s(_T("従業員たちは色々対策をしていたが、\n効果は無さそうだ"));

	text.s(_T("9/2\n旅館の経営が厳しくなってきた"));
	text.s(_T("幽霊の件もあるが\nこのタイプの旅館が時代遅れになってきてるのだろう"));

	text.s(_T("10/5\n建物は製薬会社が買い取るらしい\n社員とは何度か会った"));
	text.s(_T("口にはしないが怪しい連中だ"));

	text.s(_T("11/9\n今日で解散だ"));
	text.s(_T("長く働いてきただけに少しさびしい気持ちもある"));
	
	text.s(_T("・・・・・"));
	text.s(_T("ノートはここで終わっている"));
	*/
	/*
	text.s(_T("引き出しの中にノートがある"));
	text.s(_T("支配人の日誌のようだ"));
	text.s(_T("日誌を読んだ"));
	text.s(_T("11/10\nこの旅館には幽霊がいる"));
	text.s(_T("物を隠したり物音を立てたりするくらいで特に害も無い"));
	text.s(_T("5/4\n新入りがきた\n真面目で飲み込みも早い"));
	text.s(_T("幽霊のことを話すと少し怪訝な顔をしたが\n怖がる様子はない"));
	text.s(_T("少し対策をすると言っていた\n私は賛成しかねた"));
	text.s(_T("5/20\nおふだより食塩水の方が効果があると報告してきた"));
	text.s(_T("翌日、204号室で何かを探していた\n食塩水を隠されたらしい"));
	text.s(_T("7/10\n今日、従業員全員に今後のことを話した\n皆、察していたのか驚く者はいなかった"));
	text.s(_T("建物はとある製薬会社が買い取る\n社員とは何度か会った"));
	text.s(_T("口にはしないが怪しい連中だ"));
	text.s(_T("8/9\n今日で解散だ。みんなの行き先は決まっている\n幸運な事だ"));
	text.s(_T("長い間働いてきたが\n奇妙で良い思い出ばかりだ"));
	text.s(_T("ただ、新入りとあの子の小競り合いが\n見られなくなるのは少々寂しい"));
	text.s(_T("新しい遊び相手が見つかると良いが"));
	text.s(_T("・・・・・"));
	text.s(_T("ノートはここで終わっている"));
	*/
}
VOID MasterDesk::Update()
{
	if( hitbox.HitObj.Reaction == 1 )
	if( P->Check )
	if( P->Mode != Personal::MODE_EVENT )
	{
		text.StartText(P);
	}
	text.Update(P,ML);
}
