
//==============================================
//公衆電話
//==============================================
const TCHAR* publictel::name(){return _T("publictel");}
publictel::publictel()
{
	//電話
	tel.Type(x_publictel);
	tel.HitMode(CT_OBB,CB_PLUS);
	Msh.push_back(&tel);
	//当たり判定
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.SetPare(&tel.mWorld);
	hitbox.objPos = D3DXVECTOR3(0.0f,0.0f,0.4f);
	hitbox.objScal = D3DXVECTOR3(0.3f,1.0f,1.0f);
	hitbox.drawSkip = TRUE;
	Msh.push_back(&hitbox);
	//ガラスの壁0
	glass0.Type(x_cube);
	glass0.SetPare(&tel.mWorld);
	glass0.MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f);
	glass0.objPos = D3DXVECTOR3(-0.265f, 0.9f,0.0f);
	glass0.objScal = D3DXVECTOR3(0.01f,1.3f,0.75f);
	Msh.push_back(&glass0);
	//ガラスの壁1
	glass1.Type(x_cube);
	glass1.SetPare(&tel.mWorld);
	glass1.MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f);
	glass1.objPos = D3DXVECTOR3(0.265f, 0.9f,0.0f);
	glass1.objScal = D3DXVECTOR3(0.01f,1.3f,0.75f);
	Msh.push_back(&glass1);
	//ドアヌル
	doornull.Type(x_cube);
	doornull.SetPare(&tel.mWorld);
	doornull.objPos = D3DXVECTOR3(-0.25, 0.910995f,0.217522f);
	doornull.YPR = D3DXVECTOR3(0.0f,90.0f,0.0f);
	doornull.MeshCol = D3DXVECTOR4(1.0f,1.0f,0.0f,0.5f);
	doornull.drawSkip = TRUE;
	Msh.push_back(&doornull);
	//ドア
	door.Type(x_cube);
	door.SetPare(&doornull.mWorld);
	door.MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f);
	door.objScal = D3DXVECTOR3(0.01f,1.25f,1.0f);
	door.objPos = D3DXVECTOR3(0.0f,0.0f,0.25f *	door.objScal.z);
	Msh.push_back(&door);
	//バックグラウンド
	black.objScal = D3DXVECTOR3(500.0f,500.0f,0.0f);
	black.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f);
	Ui.push_back(&black);
	//アニメーション
	flag  = 0;
	frame = 0;
	rot.SetKey(0,90.0f);
	rot.SetKey(20,-40.0f);
	//フェード
	framefade = 0;
	fade.SetKey(0,0.0f);
	fade.SetKey(100,1.0f);

	//テキスト
	text.init(this);
	text.s(_T("この公衆電話で助けを呼べそうだ"));
	text.s(_T("助けを呼ぶ?\n呼ぶ\n呼ばない"),3,2);
	//エンディングテキスト
	textEnding.init(this);
	textEnding.s(_T("少しして、救助の人が到着し下山することができた"));
	//エンディングテキスト1
	textEnding1.init(this);
	textEnding1.s(_T("あれから会社と連絡はとれなかったが"));
	textEnding1.s(_T("後日アルバイト代と思われるお金が家に送られてきた"));
	textEnding1.s(_T("しばらくして旅館は取り壊されたらしい"));
	textEnding1.s(_T("今でも時々、あの夜の出来事を思い出す"));
	textEnding1.s(_T("あの幽霊はどうしているのだろう"));

	//ドアを開ける音
	open.m_b3DSound = TRUE;
	open.Set(wav_dooropen);
	open.Filter.OneOverQ = 0.05f;
	Snd.push_back(&open);
	//ドアを閉める音
	close.Set(wav_doorclose);
	close.m_b3DSound = TRUE;
	close.Filter.OneOverQ = 0.05f;
	Snd.push_back(&close);

	//朝になる
	frameMorning = 0;
	//ラストBGM
	bgm.Set(wav_asa);
	bgm.m_bLoop = TRUE;
	bgm.m_fVol = 0.5f; 
	bgm.m_fNoise = 0.001f;
	Snd.push_back(&bgm);

	//クレジット
	Credit.SetText(_T(" "));
	Credit.drawSkip = TRUE;
	Credit.objPos = D3DXVECTOR3(-100.0f,50.0f,0.0f);
	Credit.MeshCol.w = 0.0f; 
	UiTxt.push_back(&Credit);
	frameCredit = 0;
	fadeCredit.SetKey(0,0.0f);
	fadeCredit.SetKey(200,1.0f);
	fadeCredit.SetKey(350,1.0f);
	fadeCredit.SetKey(500,0.0f);

	//おしまい
	osimai.SetText(_T("おしまい"));
	osimai.drawSkip = TRUE;
	osimai.MeshCol.w = 0.0f; 
	UiTxt.push_back(&osimai);
	frameOsimai = 0;
	fadeEnd.SetKey(0,0.0f);
	fadeEnd.SetKey(10,0.0f);
	fadeEnd.SetKey(200,1.0f);

	light.SetKey(0,D3DXVECTOR4(0.80f,0.80f,1.00f,1.00f));
	light.SetKey(500,D3DXVECTOR4(1.00f,1.00f,1.00f,1.00f));

	fog.SetKey(0,D3DXVECTOR3(0.14f,0.14f,0.29f));
	fog.SetKey(500,D3DXVECTOR3(0.7f,0.7f,0.8f));

}
VOID publictel::Set()
{
	black.objScal = D3DXVECTOR3((float)ML->GV.ClientWidth,(float)ML->GV.ClientHeight,0.0f);
}

VOID publictel::Update()
{
	//電話ボックス１
	if(hitbox.HitObj.Reaction == 1)
	{
		if(P->Check)
		{
			if(P->Mode != Personal::MODE_EVENT)
			{
		 		D3DXVECTOR3 vr( tel.objPos - P->obj.objPos ); 
				D3DXVec3Normalize(&vr,&vr);				
				P->obj.YPR.y = D3DXToDegree(atan2f(vr.x,vr.z));
				//ドア開ける
				if(flag == 0)
				{
					open.Start(ML);
					open.Emi.Position = tel.objPos;
					flag = 1;
				}
				else if(flag == 2)
				{
					text.StartText(P);
				}
			}
		}
	}
	else
	{
		if(	flag == 2 ){flag = 3;}
	}
	//助けを呼ぶ
	if(text.Update(P,ML) == 3)
	{
		//虫の鳴き声Stop
		P->BGM->Stop(ML,0.0f);
		SAFE_DELETE(P->BGM);
		//bgmスタート
		bgm.Start(ML);
		flag = 4;
	}
	//ドア開ける
	if(flag == 1)
	{
		frame++;
		if(frame > rot.MaxKey())
		{
			flag = 2;
		}
	}
	//ドアを閉める
	else if(flag == 3)
	{
		frame--;
		if( frame <= 0 )
		{
			close.Start(ML);
			close.Emi.Position = tel.objPos;
			frame = 0;
			flag = 0;
		}
	}	
	//エンディング
	else if(flag == 4)
	{
		P->Mode = Personal::MODE_EVENT;
	
		//フェードイン
		framefade++;
		if(framefade > fade.MaxKey())
		{
			flag = 5;	
		}
	}
	//エンディング2
	else if(flag == 5)
	{
		textEnding.StartText(P);		
		flag = 6;
	}
	else if(flag == 6)
	{
		P->Mode = Personal::MODE_EVENT;
	}
	else if(flag == 7)
	{
		frame = 0;
		P->gt.drawSkip = TRUE;
		P->Mode = Personal::MODE_EVENT;
		ML->E.cam.Eye = D3DXVECTOR3(3.990000f,0.850000f,13.810574f);
		ML->E.cam.At = D3DXVECTOR3(3.702059f,1.006435f,14.755359f);
		//フェード解除
		framefade--;
		if( framefade <= 0 ){framefade = 0;}
		//朝日

		frameMorning++;
		if(frameMorning > 500)
		{
			flag = 8;
		}
	}
	else if( flag == 8 )
	{
		frame = 0;
		P->gt.drawSkip = TRUE;
		P->Mode = Personal::MODE_EVENT;
		ML->E.cam.Eye = D3DXVECTOR3(3.990000f,0.850000f,13.810574f);
		ML->E.cam.At = D3DXVECTOR3(3.702059f,1.006435f,14.755359f);
		//ブラックアウト
		framefade++;
		if( framefade > fade.MaxKey() )	{flag = 9;}
	}
	else if( flag == 9 )
	{
		flag = 10;
		textEnding1.StartText(P);
	}
	else if( flag == 10 )
	{
		P->gt.drawSkip = TRUE;
		P->Mode = Personal::MODE_EVENT;
	}
	else if( flag == 11 )
	{
		//タイトルに戻る
		m_pPare->FldChange(new Fld::Gameover,&D3DXVECTOR3(0.0f,0.0f,0.0f),0.0f);	
	}
	//フラグを進める
	if( textEnding.Update(P,ML) == 1 )
	{ 
		flag = 7;
	}
	//==============================================
	//ラストテキスト修正の可能性あり
	//==============================================
	if( textEnding1.Update(P,ML) ==5 )
	{
		flag = 11;
	}

	ML->E.Ls.Col = light.Val1(frameMorning);
	ML->E.Fs.Col = fog.Val1(frameMorning);

	doornull.SetHit(ML);
	doornull.YPR.y = rot.Val1(frame);
	black.MeshCol.w = fade.Val1(framefade);
}
VOID publictel::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,
		_T("%s\n")
		_T("flag = %d\n")
		,t
		,flag
		);
}
