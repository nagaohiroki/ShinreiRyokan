const TCHAR* Ending::name(){return _T("Ending");}
Ending::Ending()
{
	
	black.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f);
	Ui.push_back(&black);
	text.init(this);

	text.s(_T("あれからしばらくたった。"));
	text.s(_T("あのあと、警察に説明したり、取材を受けたりと\n慌しい日々が続いた。"));
	text.s(_T("アルバイトのことはすっかり忘れていたが、"));
	text.s(_T("ちゃんと家にバイト代を送ってくれていた"));
	text.s(_T("女の子は元気に回復したらしい"));
	text.s(_T("退院まではもう少しかかるようだ"));
	text.s(_T("面会に行ったら驚くだろうか"));	
	text.s(_T("・・・・"));	
	text.s(_T("いや驚くのはこっちかもしれない"));
	osimai.SetText(_T("おしまい"));
	osimai.MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,0.0f);
	UiTxt.push_back(&osimai);
	//アルファ
	alpha.SetKey(0,0.0f);
	alpha.SetKey(100,1.0f);

	eye.SetKey(0,D3DXVECTOR3(0.0f,1.0f,5.0f));
	eye.SetKey(300,D3DXVECTOR3(0.0f,1.0f,4.0f));

	fade.SetKey(0,0.0f);
	fade.SetKey(250,0.0f);
	fade.SetKey(300,1.0f);

	flag = 0;
	frame = 0;
}
VOID Ending::Set()
{
	black.objScal.x = (float)ML->GV.ClientWidth;
	black.objScal.y = (float)ML->GV.ClientHeight;

}

VOID Ending::Update()
{

	P->gt.drawSkip = TRUE;
	P->Mode = Personal::MODE_EVENT;
	if(flag == 0)
	{
		black.MeshCol.w = fade.Val1(frame);
		ML->E.cam.At =D3DXVECTOR3(0.0f,0.0f,30.0f);
		ML->E.cam.Eye =eye.Val1(frame);
		frame++;
		if(frame > eye.MaxKey())
		{
			text.StartText(P);
			flag = 1;
		}
	}
	if(flag == 2)
	{

		frame++;
		if(frame > alpha.MaxKey()){flag = 3;}
		osimai.objPos = D3DXVECTOR3(-osimai.vol.x / 2.0f,0.0f,0.0f);
		osimai.MeshCol.w = alpha.Val1(frame);
	}
	if(flag == 3)
	{
		if( P->Check )
		{
			//プレイ時間を記録
			P->FM.SaveTime();
			//最初の時間
			if( ML->Sd.First == 0 )
			{
				ML->Sd.First = P->FM.PlayTime;
				ML->Sd.Best = P->FM.PlayTime;	
			}
			//ベストタイム
			if( ML->Sd.Best > P->FM.PlayTime)
			{
				ML->Sd.Best = P->FM.PlayTime;	
			}
			SystemSave().Save(&ML->Sd);
			//タイトルに戻る
			m_pPare->FldChange(new Fld::Title,&D3DXVECTOR3(0.0f,0.0f,0.0f),0.0f);
		}
	}
	if(text.Update(P,ML) == text.Max())
	{
		flag = 2;
		frame = 0;
	} 
}

VOID Ending::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,
		_T("%s\nflag = %d frame = %d\n")
		,t,flag,frame
		);
}
