//コンストラクタ
GameText::GameText()
{
	Page = 0;
	Flag = 0;
	Count = 0;
	txt.drawSkip = TRUE;//描画許可
	txt.StrLen=0;//描画文字数
	txt.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 1.0f;
	select.drawSkip = TRUE;
	select.MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f);
	bg.drawSkip = TRUE;
	feed.SetKey(0,0.0f);
	feed.SetKey(50,0.5f);
	feed.SetKey(100,0.0f);

}
//各オブジェクトをシーンにセット
VOID GameText::init(Scene* S)
{

	S->Ui.push_back(&bg);
	S->Ui.push_back(&select);
	S->UiTxt.push_back(&txt);
}
//テキストを入力
VOID GameText::s(TCHAR* t)
{
	tp tP;
	tP.first= t;
	str.push_back(tP);
}


VOID GameText::s(TCHAR* t,int i1)
{
	tp tP;
	tP.second.push_back(i1);
	tP.first = t;
	str.push_back(tP);

}

VOID GameText::s(TCHAR* t,int i1,int i2)
{
	tp tP;
	tP.second.push_back(i1);
	tP.second.push_back(i2);
	tP.first = t;
	str.push_back(tP);

}
//テキストスタート
VOID GameText::StartText(Personal* P)
{
	
	bg.drawSkip = FALSE;
	txt.drawSkip = FALSE;
	P->Mode = Personal::MODE_EVENT;//非操作モード
	P->gt.MotionType = gt_Anim::Motion_Wait;
	Page = 0;//テキストのページ数
	txt.drawSkip = FALSE;//描画許可
	txt.StrLen=0;//描画文字数
	
}
//更新
int GameText::Update(Personal* P,MyLibrary* ML)
{	
	if(txt.drawSkip){return 0;}
	bg.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,0.8f);
	bg.objScal.x = (float)ML->GV.ClientWidth;
	bg.objScal.y = 110.0f;
	bg.objScal.z = 1.0f;	
	bg.objPos.x = 0.0f;
	bg.objPos.y = bg.objScal.y/2.0f - (float)(ML->GV.ClientHeight/2);
	bg.objPos.z = 0.2f;

	float x = (float)ML->CSMin.FontSize * txt.objScal.x * txt.intrval.x;
	float y = (float)ML->CSMin.FontSize * txt.objScal.y * txt.intrval.y;
	txt.intrval.y = 1.3f;
	txt.objPos.x = -450.0f;
	txt.objPos.y = bg.objPos.y + y; 
	txt.objPos.z = 0.0f;
	select.objScal = D3DXVECTOR3(x*10.0f,y,0.0f);
	select.objPos.x = txt.objPos.x + select.objScal.x * 0.5f; 
	select.objPos.z = 0.1f;
	select.drawSkip = TRUE;
	
	//指定ページのテキストを表示
	txt.SetText(str[Page].first);
	int size = str[Page].second.size();
	switch(size)
	{
	case 0:break;
	case 1:Flag = 0;break;
	default:
		if(txt.StrLen >= txt.Max())
		{
			select.MeshCol.w = feed.Val(Count);
			select.drawSkip = FALSE;
		}
		//選択肢
		if(ML->C.UP.T() || ML->C.DOWN.T())
		{
			Flag = 1 - Flag;
			//選択肢音
			P->CheckSE(Personal::SE_SELECT);
		}
		break;
	}
	//選択
	select.objPos.y =  txt.objPos.y - y * (float)Flag - y;	
	//文字の送り
	if(txt.Max() > txt.StrLen){	txt.StrLen++;}
	Count++;
	if(Count > 100){Count = 0;}
	//調べるボタンを押すとページを送る
	if( P->Check )
	{
		if(txt.StrLen >= txt.Max())
		{		
			//文字送りをリセット
			txt.StrLen = 0;
			//指定の番号が無い場合ページを1つ送る
			if(size == 0){	Page++;	}
			else{Page = str[Page].second[Flag];	}
		}			
			
	}	
	//ページが最大に達したらメッセージ終了
	if((int)str.size() <= Page)
	{
		Flag = 0;
		select.drawSkip = TRUE;

		bg.drawSkip = TRUE;
		txt.drawSkip = TRUE;//描画中止
		P->Mode      = Personal::MODE_ACTIVE;//移動モード
		P->Check     = FALSE;//二度目がないように
	}
	return Page;
	
}
//テキストページ数
int GameText::Max()
{
	return (int)str.size();
}
//デバッグ
VOID GameText::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,_T("%s")
		_T("%f,%f\n")
		,t
		,txt.vol.x
		,txt.vol.y
		);
}
