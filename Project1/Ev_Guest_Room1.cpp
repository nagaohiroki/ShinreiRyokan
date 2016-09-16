
//=========================
//メモ
//=========================
const TCHAR *Memo::name(){return _T("Memo");}
Memo::Memo()
{
	flag = 0;
	frame = 0;
	//開き
	Msh.push_back(&hit);
	hit.Type(x_cube);
	hit.HitMode(CT_OBB,CB_NONE);
	hit.drawSkip = TRUE;
	//閉じ
	Msh.push_back(&hit1);
	hit1.Type(x_cube);
	hit1.HitMode(CT_OBB,CB_NONE);
	hit1.SetPare(&hit.mWorld);
	hit1.objPos = D3DXVECTOR3(-1.0f,0.0f,0.0f);
	hit1.drawSkip = TRUE;
	//ふすま
	Msh.push_back(&husuma);
	husuma.Type(x_husuma);
	husuma.SetPare(&hit.mWorld);
	husuma.ShadowFlag = FALSE;
	//テキスト
	text.init(this);
	text.s(_T("紙切れが落ちてる"));
	text.s(_T("紙にはこう書かれている"));
	text.s(_T("お札だとあまり良くなかったらしいです"));
	text.s(_T("食塩水の方が効果があったようなので戻しておきます"));
	text.s(_T("そっちの方がお客様も怖がらないと思うので"));

	//スライドアニメーション
	slide.SetKey(0,0.0f);
	slide.SetKey(10,0.0f);
	slide.SetKey(20,-0.85f);
	slide.SetKey(30,-0.85f);
	//SE
	se.Set(wav_sa);
	se.m_b3DSound = TRUE;
}
VOID Memo::Update()
{
	
	husuma.objPos.x = slide.Val(frame);
	//SE
	se.Emi.Position = husuma.objPos;
	if(frame == 15){se.Start(ML);}
//	if(se.Sv(ML)->Time() > 0.5f){se.Stop(ML,0.0f);}
	if(flag == 0)
	{
		frame--;
		if(frame < 0){frame = 0;}

		//ふすまを開ける
		//調べる
		if(P->Check)
		{
			if(hit.HitObj.Reaction == 1){	flag = 1;}
		}
	
	}
	else
	{
		frame++;
		if(frame > 29){frame = 29;}

		if(P->Check)
		{
			//ふすまを閉じる
			if(hit1.HitObj.Reaction == 1)
			{
				flag = 0;
			}
			else if(hit.HitObj.Reaction == 1)
			{
				if(P->Mode != Personal::MODE_EVENT)
				{
					text.StartText(P);

				}
			}
		}
		text.Update(P,ML);
	}

}
VOID Memo::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,
		_T("%s")
		_T("flag = %d\n")
		_T("frame = %d\n")
		,t
		,flag
		,frame
		);
}
//=========================
//メモ紙
//=========================
const TCHAR *Memokami::name(){return _T("Memokami");}
Memokami::Memokami()
{
	Fvf.push_back(&kami);
}
//=========================
//電話
//=========================
const TCHAR *Tel::name(){return _T("Tel");}
Tel::Tel()
{
	tel.Type(x_tel);
	tel.HitMode(CT_OBB,CB_PLUS);
	Msh.push_back(&tel);

	text.init(this);
	text.s(_T("薬はテーブルの上にあります"));
	text.s(_T("出来るだけ早く飲んでください\n(テーブルに近づき、Zキーで調べる)"));
	text.s(_T("こちらから許可が無い限り部屋の外に出る事はできません"));
	text.s(_T("なにか非常事態が起きた際は早急にご連絡ください"));

	text1.init(this);
	text1.s(_T("............."));
	text1.s(_T("何もきこえない。壊れているのだろうか"));

}
VOID Tel::Update()
{
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	if(tel.HitObj.Reaction == 1)
	{
		//薬飲む前
		if(P->FM.EventFlag < 5){text.StartText(P);}
		//飲んだ後
		else{text1.StartText(P);}
	}
	text1.Update(P,ML);
	text.Update(P,ML);
}

//=========================================
//金庫
//=========================================
const TCHAR *Kinko::name(){return _T("Kinko");}
Kinko::Kinko()
{
	//金庫
	Msh.push_back(&pKinko);
	pKinko.Type(x_kinko);
	pKinko.Bias=0.05f;
	pKinko.HitMode(CT_OBB,CB_PLUS);
	//金庫のドア
	Msh.push_back(&pDoor);
	pDoor.Type(x_kinko_door);
	pDoor.Type(x_kinko_door);
	pDoor.SetPare(&pKinko.mWorld);
	pDoor.objPos=D3DXVECTOR3(-0.18f,0.04f,0.18f);
	pDoor.Bias=0.05f;
	//テキスト
	close.init(this);
	close.s(_T("金庫は開かない。異様に冷たい"));

	open.init(this);
	open.s(_T("中に鍵がある"));
	open.s(_T("【205号室の鍵】を手に入れた"));

	//SE
	se.Set(wav_dooropen);
	se.m_b3DSound = TRUE;
	se.Filter.OneOverQ = 0.05f;
	//ドアアニメーション
	flag = 0;
	frame = 0;
	rot.SetKey(0,0.0f);
	rot.SetKey(50,-90.0f);

}
VOID Kinko::Update()
{
	//調べる
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	if(pKinko.HitObj.Reaction == 1)
	{
		
		if(P->FM.EventFlag < TL_GUEST_ENEMY_END)
		{
			//しまっている
			close.StartText(P);
		}
		else
		{
			if(!P->FM.iGetedFlag(ITEM_GUEST_KEY))
			{
				if(flag == 2)
				{
					open.StartText(P);
				}
				if(flag == 0)
				{
					//オープン
					se.Emi.Position = pKinko.objPos;
					se.Start(ML);
					flag = 1;
				}
			}
	
		}

	}
	//ドアを開ける
	if(flag == 1)
	{
		frame ++;
		if(frame > 45)
		{
			flag = 2;
		}
		pDoor.YPR.y = rot.Val(frame);
	}


	//テキスト更新
	close.Update(P,ML);
	int o = open.Update(P,ML);
	//鍵取得
	if(o == 1)
	{
	
		if(	!P->FM.iGetedFlag(ITEM_GUEST_KEY))
		{
			P->CheckSE(Personal::SE_ITEM);
			P->FM.iGet(ITEM_GUEST_KEY);
		}
	}

}
//=========================================
//TV
//=========================================
const TCHAR *TV::name(){return _T("TV");}
TV::TV()
{
	//テレビ
	tv.Type(x_tv);
	tv.HitMode(CT_OBB,CB_PLUS);
	tv.Bias = 0.3f;
	Msh.push_back(&tv);
	//テキスト
	text.init(this);
	text.s(_T("テレビはつかない。壊れているようだ"));

}
VOID TV::Update()
{
	//調べる
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	if(tv.HitObj.Reaction == 1)
	{
		text.StartText(P);
	}
	text.Update(P,ML);
}

//=========================================
//冷蔵庫
//=========================================
const TCHAR *Reizouko::name(){return _T("Reizouko");}
Reizouko::Reizouko()
{
	Msh.push_back(&pReizou);
	pReizou.Type(x_reizouko);
	pReizou.Bias=0.15f;
	pReizou.HitMode(CT_OBB,CB_PLUS);
	//冷蔵庫のドア
	Msh.push_back(&pDoor);
	pDoor.Type(x_reizouko_door);
	pDoor.SetPare(&pReizou.mWorld);
	pDoor.objPos=D3DXVECTOR3(-0.27f,0.05f,0.28f);
	pDoor.Bias=0.5f;
	//フラグ
	flag = 0;
	//フレーム
	frame = 0;
	anim.SetKey(0,0.0f);
	anim.SetKey(10,-45.0f);
	anim.SetKey(50,-90.0f);
	//サウンド
	open.Set(wav_dooropen);
	open.m_b3DSound = TRUE;
	open.Filter.OneOverQ = 0.05f;
	Snd.push_back(&open);

	close.Set(wav_doorclose);
	close.m_b3DSound = TRUE;
	close.Filter.OneOverQ = 0.05f;
	Snd.push_back(&close);

	text.init(this);
	text.s(_T("冷蔵庫の中には何もない"));
	text.s(_T("当然、中に入ることはできない"));
}	
VOID Reizouko::Update()
{
	if(pReizou.HitObj.Reaction == 1)
	{
		if(P->Check)
		if(P->Mode != Personal::MODE_EVENT)	
		{
			if(flag == 0){flag = 1;}
			if(flag == 2)
			{
				text.StartText(P);
			}
		}
	}
	else
	{
		if(flag == 2){flag = 3;}
	}
	//アニメーション
	if(flag == 1)
	{
		frame++;
		if(frame > 48){flag = 2;}
		if(frame == 3)
		{
			open.Emi.Position = pReizou.objPos;
			open.Start(ML);
		}
	}
	
	if(flag == 3)
	{
		frame--;
		if(frame < 1){flag = 0;}	
		if(frame == 3)
		{
			close.Emi.Position = pReizou.objPos;
			close.Start(ML);
		}
	}
	text.Update(P,ML);
	pDoor.YPR.y = anim.Val(frame);
}

//=========================================
//チュートリアル
//=========================================
const TCHAR *Tutorial::name(){return _T("Tutorial");}
Tutorial::Tutorial()
{
	//当たり判定箱
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.Type(x_cube);
	hitbox.drawSkip= TRUE;
	hitbox.MeshCol.w = 0.5f;
	Msh.push_back(&hitbox);
	//紙
	paper.objScal = D3DXVECTOR3( 0.4f,0.3f,1.0f);
	paper.YPR = D3DXVECTOR3( 90.0f,20.0f,0.0f);
	paper.SetPare(&hitbox.mWorld);
	Fvf.push_back(&paper);
	//テキスト
	text.init(this);
	text.s(_T("[操作方法]\nZか左クリック･･･調べる。Xを押したままだとダーツを投げる\nXか右クリック･･･狙う"));
	text.s(_T("Space･･･メニューを開く\nCかホイールボタン･･･マウスモードON/OFFを切り替える\n(マウスモードONだとマウスカーソルが非表示になります)"));
	text.s(_T("Alt+Enter同時押し･･･フルスクリーン・ウィンドウモード切替"));
	text.s(_T("Esc･･･ゲーム終了・フルスクリーンの時はウィンドウモードに切替\n(ゲーム終了する際はセーブをお忘れなく)"));
}
VOID Tutorial::Update()
{
	if( hitbox.HitObj.Reaction == 1 )
	if( P->Check )
	if( P->Mode != Personal::MODE_EVENT )
	{
		text.StartText(P);
	}
	text.Update(P,ML);
}
