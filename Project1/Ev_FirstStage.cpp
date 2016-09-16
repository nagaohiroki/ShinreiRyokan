//=====================================
//イントロイベント開始
//=====================================
IntroFirst::IntroFirst()
{
	frame = 0;	

	Ui.push_back(&back);
	back.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	
	UiTxt.push_back(&text0);
	text0.SetText(_T("      アルバイトに応募した\n新薬のテストに協力するアルバイトだ"));
	text0.MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,0.0f);
	text0.objPos = D3DXVECTOR3(-220.0f,32.0f,0.0f);
	text0.objScal= D3DXVECTOR3(1.0f,1.0f,1.0f);
	text0.intrval.y = 2.0f;
	atxt1.SetKey(f0,0.0f);
	atxt1.SetKey(f1,1.0f);
	atxt1.SetKey(f3,1.0f);
	atxt1.SetKey(f4,0.0f);	
	
}
VOID IntroFirst::Set()
{
	P->Mode = Personal::MODE_EVENT;
	P->gt.drawSkip = TRUE;
	back.objScal = D3DXVECTOR3((float)ML->GV.ClientWidth,(float)ML->GV.ClientHeight,0.0f);

	P->BGM = new CObjSound;
	P->BGM->Set(wav_opening);
	P->BGM->m_fVol = 1.0f;
}
VOID IntroFirst::Update()
{
	P->BGM->Start(ML);
	frame++;
	text0.MeshCol.w = atxt1.Val1(frame);
	if( frame > f4 )
	{
		m_pPare->FldChange(new Fld::Soto,&D3DXVECTOR3(0.0f,0.0f,0.0f),0.0f);
	
	}	
}
VOID IntroFirst::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,_T("%sf%d"),t,frame);
}
//=====================================
//イントロイベント外カメラ
//=====================================
IntroSotoCam::IntroSotoCam()
{
	frame = 0;

	aeye.SetKey(0,D3DXVECTOR3(1.4f,4.77f,2.0f));
	aeye.SetKey(200,D3DXVECTOR3(1.4f,4.77f,15.0f));
}
VOID IntroSotoCam::Set()
{	

	P->Mode = Personal::MODE_EVENT;
	P->gt.Null.drawSkip = TRUE;
}
VOID IntroSotoCam::Update()
{
	frame++;
	ML->E.cam.CamSet(&aeye.Val1(frame),&D3DXVECTOR3(0.0f,0.0f,56.0f));

	if(frame > 200)
	{
		m_pPare->FldChange(new Fld::Intro,&D3DXVECTOR3(0.0f,0.0f,0.0f),0.0f);
		
		P->FM.EventFlag = TL_INTRO_1;
		
	}
}
VOID IntroSotoCam::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,_T("%sf%d"),t,frame);
}


VOID IntroSotoCam::DebugBtn(DebugButton*)
{
}
//=====================================
//イントロイベント2外カメラの後
//=====================================
IntroSoto::IntroSoto()
{
	frame = 0;	
	Ui.push_back(&back);
	back.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	UiTxt.push_back(&text0);
	text0.SetText(_T("  担当者の車に乗せられ\n山奥にある施設に向かった"));
	text0.MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,0.0f);
	text0.objPos = D3DXVECTOR3(-165.0f,32.0f,0.0f);
	text0.intrval.y = 2.0f;
	atxt0.SetKey(f0,0.0f);
	atxt0.SetKey(f1,1.0f);
	atxt0.SetKey(f3,1.0f);
	atxt0.SetKey(f4,0.0f);

}
VOID IntroSoto::Set()
{	
	back.objScal = D3DXVECTOR3((float)ML->GV.ClientWidth,(float)ML->GV.ClientHeight,0.0f);
}
VOID IntroSoto::Update()
{
	frame++;
	text0.MeshCol.w = atxt0.Val1(frame);
	
	if(frame > f4)
	{
		m_pPare->FldChange(new Fld::F3,&D3DXVECTOR3(0.0f,0.42f,2.0f),180.0f);

	}

}
VOID IntroSoto::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,_T("%sf%d"),t,frame);
}
//=====================================
//イントロイベントカメラF2
//=====================================
IntroF2Cam::IntroF2Cam()
{
	
	frame = 0;

	enum
	{
		f0 = 0,
		f1 = 200,
	};
	aEye.SetKey(f0,D3DXVECTOR3(-10.0f,3.5f,32.0f));
	aEye.SetKey(f1,D3DXVECTOR3(-12.5f,3.5f,32.0f));
	//足音
	Snd.push_back(&Step);
	Step.Set(wav_step2);
	Step.m_b3DSound = TRUE;
	Step.m_fVol =5.0f;
	Step.Filter.Frequency =0.1f;//こもり具合  0.0f~1.0f
    Step.Filter.OneOverQ =0.1f;//鋭さ 0.0f~1.5f	XAUDIO2_MAX_FILTER_ONEOVERQ;
    Step.Filter.Type = LowPassFilter;//湿度?		
	Step.Emi.Position = D3DXVECTOR3(-13.0f,3.5f,30.0f);


}
VOID IntroF2Cam::Set()
{
	
}
VOID IntroF2Cam::Update()
{
	//足音
	if(frame % 50 == 0){Step.Start(ML);}
	ML->Audio.Audio.Effect = AE_UNDERWATER;
	
	ML->E.cam.CamSet(&aEye.Val1(frame),&D3DXVECTOR3(-13.0f,3.5f,30.0f));
	frame++;
	if(frame > 200)
	{
		P->FM.EventFlag = TL_INTRO_2;
		m_pPare->FldChange(new Fld::Intro,&D3DXVECTOR3(0.0f,0.42f,2.0f),180.0f);
		

	}
}
VOID IntroF2Cam::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,_T("%sf%d"),t,frame);
}
VOID IntroF2Cam::DebugBtn(DebugButton* ){}



//=====================================
//イントロイベント最後タイトルコール
//=====================================
IntroTitleCall::IntroTitleCall()
{
	frame = 0;
	back.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	Ui.push_back(&back);

	text0.SetText(_T("  元々旅館だったのか\n静けさと陰気さを帯びていた"));
	text0.intrval.y = 2.0f;
	text0.objPos = D3DXVECTOR3(-165.0f,32.0f,0.0f);
	UiTxt.push_back(&text0);

//	title.SetText(_T("霊のいる旅館"));
	title.SetText(_T("心霊旅館"));
//	title.SetText(_T("幽霊旅館"));
//	title.SetText(_T("幽霊の体温"));

//	title.SetText(_T("独りの霊"));

	title.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f);
	UiTxt.push_back(&title);
	
	enum
	{
		f0 = 0,
		f1 = 100,
		f2 = 300,
		f3 = 500,
		f4 = 800,
		f5 = 900,
		f6 = 1000,


	};
	//バックのカラー
	aback.SetKey(f0,0.0f);
	aback.SetKey(f2,0.0f);
	aback.SetKey(f3,1.0f);
	aback.SetKey(f4,1.0f);
	aback.SetKey(f5,0.0f);
	aback.SetKey(f6,0.0f);


	//テキストのアルファ
	atext.SetKey(f0,0.0f);
	atext.SetKey(f1,1.0f);
	atext.SetKey(f2,1.0f);
	atext.SetKey(f3,0.0f);

	//タイトルのアルファ
	atitle.SetKey(f0,0.0f);
	atitle.SetKey(f3,0.0f);
	atitle.SetKey(f4,1.0f);
	atitle.SetKey(f5,1.0f);
	atitle.SetKey(f6,0.0f);

	//ドア音
	Snd.push_back(&DoorOpen);
	DoorOpen.Set(wav_dooropen);
	DoorOpen.m_b3DSound = TRUE;
	DoorOpen.Emi.Position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	/*
	cen.MeshCol.x = 0.0f;
	cen.objScal = D3DXVECTOR3(10.0f,10.0f,10.0f);
	Ui.push_back(&cen); 
	*/
}
VOID IntroTitleCall::Set()
{
	back.objScal = D3DXVECTOR3((float)ML->GV.ClientWidth,(float)ML->GV.ClientHeight,0.0f);
	ML->Audio.Audio.Effect = AE_UNDERWATER;
	
}
VOID IntroTitleCall::Update()
{
	//タイトルをセンターに
	title.objPos.x = -(title.vol.x * 0.5f + (title.objScal.x * (float)ML->CSMin.FontSize) * 0.5f);

	float bc = aback.Val1(frame);
	back.MeshCol = D3DXVECTOR4(bc,bc,bc,1.0f);
	text0.MeshCol.w = atext.Val1(frame);
	title.MeshCol.w = atitle.Val1(frame);
	//ドア
	if(frame == 0){DoorOpen.Start(ML);}
	
	frame++;
	if(frame > 1000)
	{
		P->gt.drawSkip = FALSE;
		SAFE_DELETE(P->BGM);
		m_pPare->FldChange(new Fld::Guest_Room,&D3DXVECTOR3(1.4f,0.42f,-2.4f),180.0f);
		ML->Audio.Audio.Effect = 0;
	}
}
VOID IntroTitleCall::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,_T("%sf%d\nvox %f"),t,frame,title.vol.x);
}

//=====================================
//最初のイベント
//=====================================
const TCHAR* IntroGuest::name(){return _T("IntroGuest");}
IntroGuest::IntroGuest()
{
	frame = 0;
	DoorClose.Set(wav_doorclose);
	DoorClose.m_b3DSound = TRUE;
	DoorClose.Emi.Position = D3DXVECTOR3(-4.86f,0.00f,-2.18f);

	DoorOpen.Set(wav_dooropen);
	DoorOpen.m_b3DSound = TRUE;
	DoorOpen.Emi.Position = D3DXVECTOR3(-4.86f,0.00f,-2.18f);

	aPos.SetKey(0,D3DXVECTOR3(-1.4f,0.42f,-2.4f));
	aPos.SetKey(100,D3DXVECTOR3(1.4f,0.42f,-2.4f));
	aPos.SetKey(200,D3DXVECTOR3(1.4f,0.42f,1.4f));

	aRot.SetKey(0,D3DXVECTOR3(0.0f,90.0f,0.0f));
	aRot.SetKey(100,D3DXVECTOR3(0.0f,90.0f,0.0f));
	aRot.SetKey(120,D3DXVECTOR3(0.0f,0.0f,0.0f));	
	aRot.SetKey(200,D3DXVECTOR3(0.0f,0.0f,0.0f));
	aRot.SetKey(400,D3DXVECTOR3(0.0f,0.0f,0.0f));
	aRot.SetKey(410,D3DXVECTOR3(0.0f,-110.0f,0.0f));
	
	TextStart = FALSE;
	frameStop= FALSE;
	Gt.init(this);
	Gt.s(_T("担当\n薬はテーブルの上に置いてあります"));
	Gt.s(_T("担当\n何かあったら電話でご連絡下さい"));
	Gt.s(_T("担当\n時間が来たらお迎えにあがります"));
	Gt.s(_T("担当\nそれまでこの部屋でおくつろぎ下さい"),4);

	//首振り
	aNeck.SetKey(0,D3DXVECTOR3(0.0f,0.0f,0.0f));
	aNeck.SetKey(100,D3DXVECTOR3(0.0f,-40.0f,0.0f));
	aNeck.SetKey(200,D3DXVECTOR3(0.0f,40.0f,0.0f));
	aNeck.SetKey(400,D3DXVECTOR3(0.0f,0.0f,0.0f));
	aNeck.SetKey(450,D3DXVECTOR3(0.0f,0.0f,0.0f));
	aNeck.SetKey(460,D3DXVECTOR3(15.0f,0.0f,0.0f));
	aNeck.SetKey(470,D3DXVECTOR3(0.0f,0.0f,0.0f));
	aNeck.SetKey(480,D3DXVECTOR3(15.0f,0.0f,0.0f));
	aNeck.SetKey(490,D3DXVECTOR3(0.0f,0.0f,0.0f));
	aNeck.SetKey(500,D3DXVECTOR3(0.0f,0.0f,0.0f));
}
VOID IntroGuest::Set()
{
	P->Mode = Personal::MODE_EVENT;
}
VOID IntroGuest::Update()
{
	if(P->FM.EventFlag != TL_INTRO_2){return;}
	
	//アニメーション
	P->obj.objPos = aPos.Val1(frame);
	P->obj.YPR = aRot.Val1(frame);
	//首の振り向き
	P->gt.neck.YPR += aNeck.Val1(frame);

	//フレームカウント増やす
	if(!frameStop)
	{
		if(frame == 440){frameStop = TRUE;}		
		if(frame == 510){frameStop = TRUE;}
		if(601 > frame){frame++;}
		else
		{
			P->FM.EventFlag = TL_INTRO_END;
			P->Mode = Personal::MODE_ACTIVE;
		}
	}
	//足音
	if(frame < 200)
	{
		P->CheckSE(Personal::SE_STEP);
		P->gt.MotionType = gt_Anim::Motion_Walk;	
	}
	else{P->gt.MotionType = gt_Anim::Motion_Wait;}
	//ドア音
	if(frame == 220 || frame == 520){DoorOpen.Start(ML);}
	if(frame == 300 || frame == 600){DoorClose.Start(ML);}

	//テキスト
	if(frame > 380 )
	{
		if(!TextStart)
		{
			TextStart = TRUE;
			Gt.StartText(P);
		}
	}

	//テキスト
	int on = Gt.Update(P,ML);	
	if(on == 2)
	{
	
		frame = 441;
		frameStop = FALSE;
	}
	//最後過ぎたら
	if(on == 4)
	{
		frame = 511;
		frameStop = FALSE;
		
	}
}
VOID IntroGuest::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,
		_T("%s\n")
		_T("frame = %d\n")
		_T("frameStop = %d\n")
		
		,t
		,frame
		,frameStop
		);
}
//=====================================
//最初のイベント
//=====================================
IntroCut::IntroCut(){}
VOID IntroCut::Update()
{
	if(P->Check)
	{
		P->gt.drawSkip = FALSE;
		P->Mode = Personal::MODE_ACTIVE;
		P->FM.EventFlag = TL_INTRO_END;
		SAFE_DELETE(P->BGM);
		m_pPare->FldChange(new Fld::Guest_Room,&D3DXVECTOR3(1.4f,0.42f,1.4f),-110.0f);
	}
}
