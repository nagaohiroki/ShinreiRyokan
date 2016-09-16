//==========================================================
//メニューページ基底オブジェクト
//==========================================================
MenuPage::MenuPage(){}
MenuPage::~MenuPage(){}
int MenuPage::Update(MenuMtrl*){	return 1;}
int MenuPage::MainUpdate(MenuMtrl* mm)
{
	if(mm->UpdateMenu() == 1){return 1;}
	//ページの更新
	return Update(mm);
}
VOID MenuPage::draw(MenuMtrl*){}

//==========================================================
//メインメニュー
//==========================================================
MainPage::MainPage(){}
int MainPage::Update(MenuMtrl* mm)
{
	mm->Title.SetText(_T("メニュー"));
	mm->Cell.SetText(_T("持ち物\nセーブ\n設定変更\nタイトルに戻る"));
	mm->info.SetText(_T(""));
	mm->tSelect.SetText(_T("タイトルに戻る?\n     はい\n     いいえ"));	

	mm->CtrlOpe.SetText(
		_T("方向キーかマウスで選択   ")
		_T("Zか左クリックで決定   ")
		_T("Xか右クリックかSpaceでメニューを閉じる"));
	//選択肢を選んでタイトルに戻る
	if(mm->GetSelect(0))
	{
		mm->Sp = 0;	
		return -1;
	}
	
	//キャンセルを押すとメニューを閉じる
	if(mm->Cansel)
	{
		mm->Sp = 0;
		return 0;
	}	
	//チェックボタンを押すと各ページに移る
	if(mm->Check)
	{
		
		//アイテム
		if(mm->Sp == 0){mm->Sp = 0;mm->Page = MP_ITEM;}
		//セーブ
		if(mm->Sp == -1)
		{
			//敵がいるとセーブできない
			if(mm->FM->enemy.mode == Enemy::MODE_CLEAR)
			{
		
				mm->Sp = 0;
				mm->Page = MP_SAVE;
			}
		}
		//設定
		if(mm->Sp == -2){mm->Sp = 0;mm->Page = MP_OPTION;}
		//タイトル選択肢モードにする
		if(mm->Sp == -3){	mm->SetSelect();	}	
		
		mm->ML->C.getkey.k0m1 = 0;//マウスの位置にカーソルを置かないように
	}
	//敵がいるとセーブできない
	if(mm->Sp == 0)
	{
		mm->info.SetText(_T("持ち物を確認する\nメニューから持ち物を使用することはできない"));
	}
	else if(mm->Sp == -1)
	{
		if(mm->FM->enemy.mode != Enemy::MODE_CLEAR)
		{
			mm->info.SetText(_T("セーブできない"));
	
		}
		else
		{
			mm->info.SetText(_T("今の状態を記録する\nつづきから再開できる"));
		}
	}
	else if(mm->Sp == -2)
	{		
		mm->info.SetText(_T("音量、輝度、解像度を変更できる"));
	}
	else if(mm->Sp == -3)
	{
		mm->info.SetText(_T("タイトルに戻る。セーブをお忘れなく"));

	}

	return 1;
}
//==========================================================
//アイテムメニュー
//==========================================================
ItemPage::ItemPage()
{
	_stprintf_s(t,ITEMMAX,_T(""));
}
int ItemPage::Update(MenuMtrl* mm)
{
	mm->Title.SetText(_T("持ち物"));
	mm->CtrlOpe.SetText(
		_T("方向キーかマウスで選択   ")
		_T("Xか右クリックで戻る   ")
		_T("Spaceでメニューを閉じる"));


	
	int index[ITEM_MAX] = {0};
	int in = 0;
	//セル文字
	_stprintf_s(t,ITEMMAX,_T("ノート"));
	for(int i = 0; i < ITEM_MAX; i++)
	{
		if(mm->FM->iGetFlag((ITEM)i))
		{			
			_stprintf_s(t,ITEMMAX,_T("%s\n%s"),t,mm->ML->itemList.item[i].name);
			index[in] = i;
			in++;
		}
	}
	//info
	if(mm->Sp == 0){mm->info.SetText(_T("記録や持ち物をメモするノート"));}
	else
	{
		//アイテム情報
		int n =  index[-mm->Sp-1];
		mm->info.SetText(mm->ML->itemList.item[n].info);
	}
	mm->Cell.SetText(t);
	//キャンセルボタンで戻る
	if(mm->Cansel)
	{
		mm->ML->C.getkey.k0m1 = 0;
		mm->Sp = 0;
		mm->Page = MP_MAIN;
	}
	return 1;
}
//==========================================================
//セーブメニュー
//==========================================================
SavePage::SavePage()
{	
	InfoClear = FALSE;
	LoadNum = -1;
	_stprintf_s(t,FMMAX,_T(""));
	for( int i = 0; i < GameSave::MAX_SAVE; i++ )
	{
		LoadSuc[i] = GameSave().Load(&Fm[i],i);
	}
}
int SavePage::Update(MenuMtrl* mm)
{
	//キャンセルボタンで戻る
	if(mm->Cansel || mm->FM->enemy.mode != Enemy::MODE_CLEAR)
	{		
		mm->ML->C.getkey.k0m1 = 0;
 		mm->Sp = -1;
		mm->Page = MP_MAIN;		
	}
	//テキストのセット
	mm->Title.SetText(_T("セーブ"));
	mm->Cell.SetText(_T("セーブデータ1\nセーブデータ2\nセーブデータ3"));	
	mm->CtrlOpe.SetText(
		_T("方向キーかマウスで選択   ")
		_T("Zか左クリックで決定   ")
		_T("Xか右クリックで戻る   ")
		_T("Spaceでメニューを閉じる"));
	//選択肢の結果が出たらセーブ
	if(mm->GetSelect(0))
	{
		//セーブする
		if(GameSave().Save(mm->FM,-mm->Sp))
		{
			//ロード情報更新
			LoadSuc[-mm->Sp] = GameSave().Load(&Fm[-mm->Sp],-mm->Sp);
			mm->info.SetText(_T("セーブしました"));	
		}
		else{	mm->info.SetText(_T("セーブに失敗しました"));}
		//入力待ちを呼び出し、セーブしましたの文字を消す
		mm->SetWait();
		InfoClear = TRUE;
	}
	//セーブしましたの文字を消す
	if(InfoClear)
	{
		if(!mm->Wait)
		{
			mm->info.SetText(_T(""));
			InfoClear = FALSE;
		}
	}

	if(mm->Check)
	{		
		//選択肢を呼び出す
		mm->SetSelect();
		mm->tSelect.SetText(_T("セーブしますか?\n     はい\n     いいえ"));
	}
	//セーブデータの情報を表示
	if(!mm->Wait)
	{
		if(LoadSuc[-mm->Sp])
		{
			Fm[-mm->Sp].ShowData(t,FMMAX);
			mm->info.SetText(t);
		}
		else{mm->info.SetText(_T("データがありません"));	}
	}
	
	return 1;
}
//==========================================================
//設定変更のシークバー
//==========================================================
SeekBer::SeekBer()
{
	Hold = FALSE;
	mater.objScal = D3DXVECTOR3(20.0f,20.0f,0.0f);
	ber.objScal = D3DXVECTOR3(20.0f,20.0f,0.0f);
	ber.MeshCol = D3DXVECTOR4(0.5f,0.5f,0.5f,1.0f);
}
//2D当たり判定
BOOL SeekBer::Hit2D(D3DXVECTOR2* m,D3DXVECTOR2* mx,D3DXVECTOR2* mn)
{
	return !(m->x > mx->x || m->x < mn->x || m->y > mx->y || m->y < mn->y);
}
//シークの更新(ml,変更する値,位置,バーのサイズ,最小値,最大値) 
VOID SeekBer::update(MyLibrary* ml,float* now,D3DXVECTOR2* pos,float size,float mn,float mx)
{
	mater.MeshCol.w = 1.0f;
	if(Hold)
	{	
		if(ml->C.getkey.k0m1 == 0)
		{
			//キーボード
			if(ml->C.RIGHT.T()|| ml->C.RIGHT.time() > 20){*now += 0.01f; }
			if(ml->C.LEFT.T() || ml->C.LEFT.time()  > 20){*now -= 0.01f;}
		}
		else{	*now = (mx - mn) * ( ml->GV.mPos.x - pos->x ) / size + mn;	}
		mater.MeshCol.w = 0.2f;

	}
	if(*now > mx){*now = mx;}
	if(*now < mn){*now = mn;}
	//トグルのステータス
	mater.objPos = D3DXVECTOR3(pos->x + ((*now - mn) / (mx - mn)) * size,pos->y,0.0f);
	//バーのステータス
	ber.objPos.y = pos->y;
	ber.objPos.x = pos->x + size * 0.5f ;
	ber.objScal.x= 100.0f+ mater.objScal.x ;
}
//トグルの当たり判定
BOOL SeekBer::Hit(MyLibrary* ml)
{	
	D3DXVECTOR2 mx(mater.objPos.x + mater.objScal.x*0.5f,mater.objPos.y + mater.objScal.y*0.5f);
	D3DXVECTOR2 mn(mater.objPos.x - mater.objScal.x*0.5f,mater.objPos.y - mater.objScal.y*0.5f);
	return Hit2D(&ml->GV.mPos,&mx,&mn);
}
//描画
VOID SeekBer::draw(MyLibrary* ml)
{
	ber.draw(ml);
	mater.draw(ml);
}
//==========================================================
//設定変更
//==========================================================
OptionPage::OptionPage()
{
	HoldPix = FALSE;
	_stprintf_s(t,tn,_T(""));
	k = 0;
	PixelSize.SetText(_T("1024x768 1280x720"));
	PixelSize.objPos = D3DXVECTOR3(-200.0f,80.0f,0.0f);
	ber.objScal.x = 120.0f;
	ber.MeshCol.w = 0.5f;
	ber.objPos.y = 80.0f;

	PrePix = 0;

	Key = 0;
	alpha.SetKey(0,0.0f);
	alpha.SetKey(50,0.5f);
	alpha.SetKey(100,0.0f);
}
int OptionPage::Update(MenuMtrl* mm)
{	
	if(HoldPix){mm->Sp = -3;}
	//テキストのセット
	mm->Title.SetText(_T("設定変更"));
	_stprintf_s(t,tn,_T("設定を初期に戻す\n音量 %.2f\n輝度 %.2f\n解像度")	,mm->ML->Sd.Volume	,mm->ML->Sd.Lum	);
	//項目
	mm->Cell.SetText(t);
	//操作方法
	mm->CtrlOpe.SetText(
		_T("方向キーかマウスで選択   ")
		_T("Zか左クリックで決定   ")
		_T("Xか右クリックで戻る   ")
		_T("Spaceでメニューを閉じる"));


	//変化を反映させる
	mm->ML->UpdateSys();
	//キャンセルボタンで戻る
	if(mm->Cansel)
	{
		mm->ML->C.getkey.k0m1 = 0;
		mm->Page = MP_MAIN;	
		SystemSave().Save(&mm->ML->Sd);
		mm->Sp = -2;
	}
	if(mm->Close){SystemSave().Save(&mm->ML->Sd);}
	//初期化
	if( mm->Sp == 0 )
	{
		if(mm->Check){	mm->ML->Sd.InitOption();	}
	}
	//マウス操作
	if(mm->ML->C.getkey.k0m1 == 1)
	{
		if(mm->ML->C.Z.K())
		{
			if(k == 0)
			{
				if(volume.Hit(mm->ML)){k = 1;}
				if(lum.Hit(mm->ML)){k = 2;}
			}	
		}
		else
		{
			k = 0;
			lum.Hold = FALSE;
			volume.Hold = FALSE;
		}	
		if(k == 1){		volume.Hold = TRUE;}
		if(k == 2){		lum.Hold = TRUE;}
		//段落
		if(volume.Hold){mm->Sp = -1;}
		if(lum.Hold){mm->Sp = -2;}
		mm->Choice.objPos.y = 200.0f + (float)mm->ML->CSMin.FontSize * mm->Cell.intrval.y * (float)mm->Sp;
	}
	//キーボード操作
	else
	{		
		k = 0;
		lum.Hold = FALSE;
		volume.Hold = FALSE;
		if(mm->Sp == -1){volume.Hold = TRUE;}
		if(mm->Sp == -2){lum.Hold = TRUE;}
	}
	//エディタ
	float inv = (float)mm->ML->CSMin.FontSize* mm->Cell.intrval.y;//段落
	volume.update(mm->ML,&mm->ML->Sd.Volume,&D3DXVECTOR2(100.0f,mm->Cell.objPos.y -inv*1.0f),100.0f,0.0f,4.0f);
	lum.update(mm->ML,&mm->ML->Sd.Lum,&D3DXVECTOR2(100.0f,mm->Cell.objPos.y -inv*2.0f),100.0f,0.0f,4.0f);
	if(mm->Sp == 0)
	{
		mm->info.SetText(_T(""));
	}
	if(mm->Sp == -1)
	{
		mm->info.SetText(_T("右のスライダーを動かす\nもしくは←→キーで音量調整\n大きくすると音割れする可能性があります"));
	}
	if(mm->Sp == -2)
	{
		mm->info.SetText(_T("右のスライダーを動かす\nもしくは←→キーで輝度調整"));
	}
	if(mm->Sp == -3)
	{
		mm->info.SetText(_T("解像度の変更\n次回起動時に反映されます"));	
		if(HoldPix)
		{
			//アルファ固定
			mm->Key = 25; 
			//点滅
			Key++;
			if(Key > alpha.MaxKey()){Key = 0;}
			ber.MeshCol.w = alpha.Val(Key);
			//効果音
			if(	PrePix != mm->ML->Sd.PixelMode ){mm->SelectSE();}
			PrePix = mm->ML->Sd.PixelMode;
			//マウス操作
			if(mm->ML->C.getkey.k0m1 == 1)
			{
				if( mm->ML->GV.mPos.x < -85.0f ){mm->ML->Sd.PixelMode = 0;}
				if( mm->ML->GV.mPos.x > -85.0f ){mm->ML->Sd.PixelMode = 1;}
				
			}
			else
			{
				//キーボード操作
				if(mm->ML->C.LEFT.T()){	mm->ML->Sd.PixelMode--;	}
				else if(mm->ML->C.RIGHT.T()){mm->ML->Sd.PixelMode++;}
				if( mm->ML->Sd.PixelMode < 0 ){ mm->ML->Sd.PixelMode = 1; }
				if( mm->ML->Sd.PixelMode > 1 ){ mm->ML->Sd.PixelMode = 0; }
			}
		}
		if(mm->Check)
		{
			if(HoldPix){HoldPix = FALSE;}
			else{HoldPix = TRUE;}
		}
		
	}
	else{ber.MeshCol.w = 0.5f;} 
	
	//カーソル位置
	ber.objScal.y = (float)mm->ML->CSMin.FontSize * PixelSize.objScal.y * PixelSize.intrval.y;
	switch( mm->ML->Sd.PixelMode )
	{
	case 0:ber.objPos.x = -145.0f;break;
	case 1:ber.objPos.x = -25.0f;break;
	default:ber.objPos.x = -145.0f;break;
	}
	return 1;
}
VOID OptionPage::draw(MenuMtrl* mm)
{
	volume.draw(mm->ML);
	lum.draw(mm->ML);

	ber.draw(mm->ML);
	PixelSize.draw(mm->ML);
}
//==========================================================
//メインメニュー
//==========================================================
Menu::Menu()
{
	drawFlag = FALSE;

}
VOID Menu::Set(MyLibrary* ml,FlagManager* fm)
{
	vecPage.push_back(&PgMain);
	vecPage.push_back(&PgItem);
	vecPage.push_back(&PgSave);
	vecPage.push_back(&PgOption);
	mm.Set(ml,fm);
}
int Menu::Update(BOOL Check,BOOL Cansel,BOOL Close)
{	
	mm.ML->C.MouseLock(TRUE,mm.ML->hW);

	drawFlag = TRUE;
	mm.Update(Check,Cansel,Close);
	//選択の位置
	//ページの更新
	//戻り値0メニューを閉じる,1通常更新,-1タイトルに戻る
	return vecPage[mm.Page]->MainUpdate(&mm);
}
VOID Menu::draw()
{
	if(drawFlag == FALSE){return;}
	mm.draw();
	vecPage[mm.Page]->draw(&mm);
}
VOID Menu::CloseMenu()
{
	mm.ML->C.MouseLock(FALSE,mm.ML->hW);
	drawFlag = FALSE;
	mm.Select = 0;
	mm.SelectMode = 0;
	mm.Wait = FALSE;
	mm.Page = MP_MAIN;
	mm.Sp = 0;
}
VOID Menu::DebugText(TCHAR* t,int l)
{
	//*
	_stprintf_s(t,l,
		_T("%s\n")
		_T("Page = %d\n")
		_T("select = %d\n")
		_T("selectflag = %d\n")
		_T("Sp = %d\n")
		,t
		,mm.Page
		,mm.Select
		,mm.SelectMode
		,mm.Sp 	
		
		);
	//	*/
	//mm.Debug(t,l);
}
