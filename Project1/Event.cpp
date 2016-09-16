//テスト
const TCHAR *Particl::name(){return _T("Particl");}
Particl::Particl()
{	
	txt.SetText(_T("Hello\nWorld"));
	txt.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	UiTxt.push_back(&txt);

	txt1.SetText(_T("Hello\nWorld"));
	txt1.objScal.x = 0.01f;
	txt1.objScal.y = 0.01f;

	Txt.push_back(&txt1);

	m_Ui.SetTex(bmp_note);
	m_Ui.objScal = D3DXVECTOR3(0.0f,0.0f,0.0f);
	Ui.push_back(&m_Ui);

	Part.objPos.x = 6.0f;
	Part.SetTex(bmp_fire);
	Prt.push_back(&Part);

	_stprintf_s(tx,500,_T(""));
	
		

//	testSound.m_fNoise = 0.05f;
//	testSound.m_fVol = 4.0f;
//	testSound.ConeSet(TRUE);
	testSound.Set(wav_sa);
//	testSound.Filter.Type = BandPassFilter;
//	testSound.m_bLoop = TRUE;
	Snd.push_back(&testSound);
	
}
VOID Particl::Update()
{
	if(ML->C.Q.K())
	{
		testSound.Start(ML);
	//	P->FM.enemy.mode = Enemy::MODE_STALK;
	//	P->FM.enemy.HP = 5;
	}
	if(ML->C.V.K())
	{
		testSound.Stop(ML,0.0f);
	}
	fish.Update(ML);
}

VOID Particl::draw()
{
	fish.draw(ML);
}
VOID Particl::DebugText(TCHAR* t,int l)
{
	//*
		_stprintf_s(t,l,_T("%s\n%f")
		,t,testSound.Sv(ML)->Time()
	);
	//*/
}

//デバッグボタン
VOID Particl::DebugBtn(DebugButton*)
{

}


//Mirror
Mirror::Mirror()
{	
	Fvf.push_back(&state);
}
const TCHAR *Mirror::name(){return _T("Mirror");}
VOID Mirror::Update()
{
	//ステータスを移す

	Mir.objPos = state.objPos;
	Mir.objScal = state.objScal;
	Mir.YPR= state.YPR;

	//鏡の視点
	D3DXVECTOR3 d,c,at,n,n2;
	D3DXVec3Normalize(&n,&D3DXVECTOR3(Mir.mWorld._11,Mir.mWorld._12,Mir.mWorld._13));
	D3DXVec3Normalize(&n2,&D3DXVECTOR3(Mir.mWorld._21,Mir.mWorld._22,Mir.mWorld._23));
	D3DXVec3Cross(&d,&n,&n2);
	D3DXVec3Normalize(&c,&D3DXVECTOR3( Mir.objPos - ML->E.cam.Eye));	
	D3DXVec3Normalize(&at,&(c - 2.0f* D3DXVec3Dot(&c,&d)*d));
	//鏡用のカメラ補正
	ML->E.Mirrorcam.Pars = 35.0f;
	ML->E.Mirrorcam.wh.x = Mir.objScal.x;
	ML->E.Mirrorcam.wh.y =  Mir.objScal.y;
	ML->E.Mirrorcam.Near = D3DXVec3Length(&(Mir.objScal.y * d)) + 0.1f;
	ML->E.Mirrorcam.Eye = Mir.objPos + Mir.objScal.y * d; 
	ML->E.Mirrorcam.At = Mir.objPos+ at;
	ML->E.MirrorFlag = TRUE;
}
VOID Mirror::draw()
{	
	//鏡用に描画
	Mir.drawMirror(ML);
}
