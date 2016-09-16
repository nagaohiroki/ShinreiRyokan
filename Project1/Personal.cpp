//パーソナルデータ
//コンストラクタ
Personal::Personal()
{
	TrgRelease = FALSE;
	//調べるフラグ
	Check = FALSE;
	//キャンセルフラグ
	CanselCount = 0;
	Cansel = FALSE;
	m_iPage = 0;	
	//カメラベクトルに進行
	tes = D3DXVECTOR3(0,0,0);
	//キャラクタのモード
	Mode = MODE_ACTIVE;
	//キー記憶
	MoveKey = 0;
	//着地判定
	HitVec = D3DXVECTOR3(0,0,0);
	//進行
	NextPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//デバッグ
	EyeRot=D3DXVECTOR2(0,0);
	//キャラの注視点
	AtPos=D3DXVECTOR3(0,0,0);		
	//当たり判定オブジェクト
	obj.MeshCol=D3DXVECTOR4(1.0f,0,0,0.5f);
	obj.objScal=D3DXVECTOR3(1.0f,1.0f,1.0f)*0.35f;
	obj.Type(x_sphere);
	obj.HitMode(CT_SPHERE,CB_PLUS);
	//足音
	Step.Set(wav_step2);
	Step.m_b3DSound = TRUE;
	Step.m_fVol =1.0f;
	Step.Filter.Frequency =0.1f;//こもり具合  0.0f~1.0f
    Step.Filter.OneOverQ =0.1f;//鋭さ 0.0f~1.5f	XAUDIO2_MAX_FILTER_ONEOVERQ;
    Step.Filter.Type = LowPassFilter;//湿度?		
	//メニューを開く音
	MenuOpen.Set(wav_step2);
	MenuOpen.m_fVol =1.0f;
	MenuOpen.Filter.Frequency =0.08f;//こもり具合  0.0f~1.0f
    MenuOpen.Filter.OneOverQ =0.0845f;//鋭さ 0.0f~1.5f	XAUDIO2_MAX_FILTER_ONEOVERQ;
    MenuOpen.Filter.Type = LowPassFilter;//湿度?		
	//アイテム取得音
	ItemGet.Set(wav_dooropen);
	//選択音
	for(int i = 0; i < SMAX ; i++)
	{
		slct[i].Set(wav_step2);
	}
	//弾
	m_iDelay = 0;
	m_iCount = 0;
	int i;
	for(i = 0; i < 5; i++)
	{
		Blt.push_back(new CBullet);
	}
	//FPSフラグ
	FPSFlag = FALSE;
	//再ロード
	ReLoad = 0;
	BGM = NULL;

	//照準
	sight.SetTex(png_sight);
	sight.objScal = D3DXVECTOR3(10.0f,10.0f,0.0f);
	sight.MeshCol.w = 0.5f;
}
Personal::~Personal()
{
	//BGM破棄
	SAFE_DELETE(BGM);
	//弾破棄
	for(std::vector<CBullet*>::iterator it = Blt.begin(); it != Blt.end(); ++it)
	{
		SAFE_DELETE(*it);
	}
	
}
//効果音
VOID Personal::CheckSE(Player_SE n)
{
	switch(n)
	{
	case SE_CANSEL://キャンセル音
		MenuOpen.m_b3DSound = FALSE;
		MenuOpen.m_fVol = 1.0f;
		MenuOpen.Filter.Frequency =0.04f;//こもり具合  0.0f~1.0f
		MenuOpen.Filter.OneOverQ =0.1143f;//鋭さ 0.0f~1.5f	XAUDIO2_MAX_FILTER_ONEOVERQ;
		MenuOpen.Filter.Type = LowPassFilter;//湿度?
		MenuOpen.Start(ML);
		break;
	case SE_CHECK://決定音
		MenuOpen.m_b3DSound = FALSE;
		MenuOpen.m_fVol = 1.0f;
		MenuOpen.Filter.Frequency =0.08f;//こもり具合  0.0f~1.0f
	    MenuOpen.Filter.OneOverQ =0.0845f;//鋭さ 0.0f~1.5f	XAUDIO2_MAX_FILTER_ONEOVERQ;
	    MenuOpen.Filter.Type = LowPassFilter;//湿度?		
		MenuOpen.Start(ML);
		break;
	case SE_STEP://足音
		Step.m_b3DSound = TRUE;
		Step.Emi.Position = obj.objPos;
		Step.Start(ML);
		break;
	case SE_ITEM://アイテム取得音
		ItemGet.m_b3DSound = FALSE;
		ItemGet.Filter.Frequency = 0.05f;
		ItemGet.Filter.OneOverQ = 0.05f;
		ItemGet.Filter.Type = LowPassFilter;
		ItemGet.m_fVol = 0.3f;
		ItemGet.Start(ML);
		break;
	case SE_OPEN://ドアオープン
		ItemGet.m_b3DSound = TRUE;
		ItemGet.Emi.Position = obj.objPos;
		ItemGet.Filter.Frequency = 1.0f;
		ItemGet.Filter.OneOverQ = 1.0f;
		ItemGet.Filter.Type = LowPassFilter;
		ItemGet.m_fVol = 1.0f;
		ItemGet.Start(ML);
		break;
	case SE_SLIDE://ドアオープン1
		ItemGet.m_b3DSound = TRUE;
		ItemGet.Emi.Position = obj.objPos;
		ItemGet.Filter.Frequency = 0.5f;
		ItemGet.Filter.OneOverQ = 1.0f;
		ItemGet.Filter.Type = HighPassFilter;
		ItemGet.m_fVol = 1.0f;
		ItemGet.Start(ML);
	
		break;
	
	case SE_SELECT://選択音
		for(int i = 0; i < SMAX ; i++)
		{
			if(!slct[i].Sv(ML)->Idol())
			{
				slct[i].m_fVol = 0.5f;
				slct[i].Filter.Frequency = 0.1f;
				slct[i].Start(ML);
				return;
			}		
		}		
		break;
	default:break;
	}
}
//宣言後のセット
VOID Personal::Set(MyLibrary* ml)
{
	ML = ml;
	obj.YPR.y = FM.RotY;
	obj.objPos= FM.Pos;
	AtPos	  = FM.Pos;	
	gt.Null.objPos = FM.Pos + D3DXVECTOR3(0.0f,-0.34f,0.0f);;	

	if(Mode == MODE_ACTIVE)
	{
		gt.drawSkip = FALSE;
	}
	obj.SetHit(ML);
	//銃弾のアタッチをリセット
	ResetBullet();
	menu.Set(ML,&FM);
}
//FPSモード
VOID Personal::FPSMode()
{	
	//FPS視点
	gt.MotionType = gt_Anim::Motion_Wait;
	float xL = 1.0f;
	float yL = 1.0f;

	if( ML->C.getkey.MouseFlag == 1 )
	{
		float speed = 0.13f;
		float spdX = fabsf((float)ML->C.getkey.speed.x);
		float spdY = fabsf((float)ML->C.getkey.speed.y);
		if(spdX > 100.0f){spdX = 100.0f;}
		if(spdY > 100.0f){spdY = 100.0f;}
		xL = spdX * speed;
		yL = spdY * speed;
	}
	if(ML->C.getkey.k0m1 == 0)
	{
		xL = 1.0f;
		yL = 1.0f;
	}


	if(ML->C.UP.K()){		 MoveKey  = 1;   EyeRot.x -= yL;}
	else if(ML->C.DOWN.K()){ MoveKey  = 10;  EyeRot.x += yL;}
	if(ML->C.RIGHT.K()){	 MoveKey  = 100; EyeRot.y += xL;}
	else if(ML->C.LEFT.K()){ MoveKey  = 1000;EyeRot.y -= xL;}
	D3DXVECTOR3 Ez;
	D3DXMATRIX  mZ;	
	D3DXMatrixRotationYawPitchRoll(&mZ,D3DXToRadian(EyeRot.y +obj.YPR.y  ),D3DXToRadian(EyeRot.x),D3DXToRadian(0.0f));
	D3DXVec3TransformCoord(&Ez,&D3DXVECTOR3(0,0,0.1f),&mZ);		
	ML->E.cam.Eye = obj.objPos +D3DXVECTOR3(0,0.5f,0);
	ML->E.cam.At  = obj.objPos + Ez + D3DXVECTOR3(0,0.5f,0);
	if(EyeRot.x <= -80.0f){EyeRot.x =-80.0f;}
	if(EyeRot.x >=  80.0f){EyeRot.x = 80.0f;}
	if(EyeRot.y >=  360.0f){EyeRot.y = 0.0f;}
	else if(EyeRot.y <=  0.0f){EyeRot.y =360.0f;}
	//キャラのアングル
	D3DXVECTOR3 N(ML->E.cam.At - ML->E.cam.Eye);
	D3DXVec3Normalize(&N,&N);
	AtPos	= obj.objPos+ D3DXVECTOR3(N.x,0.0f,N.z)*0.04f;
	gt.Null.YPR.y= D3DXToDegree(atan2(N.x,N.z));
	//懐中電灯
	if(FM.iGetedFlag(ITEM_LIGHT))
	{
		ML->E.PSL.Pos = ML->E.cam.Eye;
		ML->E.PSL.Vec = ML->E.cam.At;
	}
	//弾を撃つ
	if(m_iDelay >= 50)
	{
		if(ML->C.Z.K())
		{			
			if(TrgRelease == FALSE)
			{
				gt.KeyFrame = 0;
				if( m_iCount > Blt.size() - 1 ){m_iCount = 0;}
				Blt[m_iCount]->Init(&ML->E.cam.At,&ML->E.cam.Eye);
				m_iCount++;			
				m_iDelay = 0;
				TrgRelease = TRUE;
			}
		}
		else{TrgRelease = FALSE;}
	}
	if(m_iDelay < 50)
	{
		gt.MotionType = gt_Anim::Motion_Throw;
	}
	
}
//イベントモード
VOID Personal::EventMode()
{
	gt.Null.objPos = obj.objPos + D3DXVECTOR3(0.0f,-0.34f,0.0f);;	
	gt.Null.YPR = obj.YPR;
	AtPos	  = obj.objPos;	
	//非操作時
	//イベント調べる
	Check = ML->C.Z.T();
	//キャンセルする
	Cansel = FALSE;
	if(ML->C.X.K()){ CanselCount = 1; }
	else
	{
		if(CanselCount == 1){	Cansel = TRUE;	}
		CanselCount = 0;
	}
	
}
//ヒットイベント
VOID Personal::HitEvent(std::vector<CollObj*>* obb)
{
	UINT i;
	UINT size = obb->size();
	//上方ベクトル0.7未満なら重力発生
	D3DXVec3Normalize(&HitVec,&HitVec);
	if(HitVec.y > 0.7f){ NextPos.y = 0.0f; }	
	else
	{
		if(!FPSFlag){NextPos.y = -0.06f; }
	}
	HitVec = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//プレイヤーとフィールドの当たり判定
	//位置を更新
	obj.objPos += NextPos;
	obj.SetHit(ML);
	//フィールドオブジェクトとの当たり判定
	for( i = 0; i < size; i++)
	{
		obb->at(i)->Reaction = 0;
	}
	for( i = 0; i < size; i++)
	{		
		if(ML->Col.Hit(&obj.HitObj,obb->at(i))) 
		{
			obb->at(i)->Reaction = 1;
			if(obb->at(i)->cBack == CB_PLUS)
			{
				obj.objPos += obj.HitObj.vBack; 
				HitVec += obj.HitObj.vBack;
			}
		}		
	}	
	//更新値をリセット
	NextPos = D3DXVECTOR3(0.0f,0.0f,0.0f);	
	//弾とフィールドの当たり判定
	size = Blt.size();
	for( i = 0; i < size; i++){		Blt[i]->HitEvent(obb,ML);	}
	//次の球までの硬直
	if(m_iDelay < 50){	m_iDelay ++;	}
}
//アクティブモード
VOID Personal::ActiveMode()
{	
	//FPSモード
	if(ML->C.X.K() && FM.iGetedFlag(ITEM_DARTS))
	{
		FPSFlag = TRUE;	
		return;
	}
	else{FPSFlag = FALSE;}
	//ものを調べる
	Check = ML->C.Z.T();	
	Cansel = FALSE;//キャンセルを解除
	//メニューモード
	if(ML->C.Space.T())
	{
		CheckSE(Personal::SE_CHECK);
		//メニューモードにする
		Mode = MODE_MENU; 
	}	
	D3DXVECTOR3 UpdatePos(0.0f,0.0f,0.0f);
	D3DXVECTOR3 tes2;
	D3DXVec3Cross(&tes2,&D3DXVECTOR3(0.0f,1.0f,0.0f),&tes);
	gt.MotionType = gt_Anim::Motion_Wait;
	int MKey=0;
	if(ML->C.UP.K())
	{
		gt.MotionType = gt_Anim::Motion_Run;
		UpdatePos += tes;
		MKey += 1;
	}
	else if(ML->C.DOWN.K())
	{	
		gt.MotionType = gt_Anim::Motion_Run;
		UpdatePos -= tes;
		MKey += 10;
	}
	if(ML->C.RIGHT.K())
	{	
		gt.MotionType = gt_Anim::Motion_Run;
		UpdatePos += tes2;
		MKey += 100;
	}
	else if(ML->C.LEFT.K())
	{	
		gt.MotionType = gt_Anim::Motion_Run;	
		UpdatePos -= tes2;
		MKey += 1000;
	}	
	//移動ベクトルを更新(キーを入力しなおしたとき)	
	if(MKey != MoveKey)
	{
		D3DXVECTOR2 v2(ML->E.cam.At.x - ML->E.cam.Eye.x,ML->E.cam.At.z - ML->E.cam.Eye.z);
		D3DXVec2Normalize(&v2,&v2);
		tes = D3DXVECTOR3(v2.x,0.0f,v2.y);
	}
	MoveKey = MKey;		
	//注視点の更新
	float Speed = 0.15f;	
	D3DXVec3Normalize(&UpdatePos,&UpdatePos);			
	AtPos += UpdatePos * Speed;		
	//視点とキャラ位置の微分積分
	D3DXVECTOR2 N(AtPos.x - obj.objPos.x,AtPos.z - obj.objPos.z);			
	float Len = D3DXVec2LengthSq(&D3DXVECTOR2(N.x,N.y));
	D3DXVec2Normalize(&N,&N);			
	//Y軸方向の算出	
	//注視点が一定以上離れないと回転されない
	if(Len > 0.001f){
	obj.YPR.y = D3DXToDegree(atan2(N.x,N.y));		
	}
	//ゴムの強度
	N *= Len * 0.05f;
	gt.Null.objPos = obj.objPos + D3DXVECTOR3(0.0f,-0.34f,0.0f);
	gt.Null.YPR = obj.YPR;
	//進行位置
	AtPos	   += -D3DXVECTOR3(N.x,0.0f,N.y);
	//オブジェクト位置の更新値/当たり判定分割数
	NextPos = D3DXVECTOR3(N.x,0.0f,N.y);
	//足音
	if(gt.MotionType == gt_Anim::Motion_Run)
	{	
		CheckSE(SE_STEP);
	}	
	//キャラを表示
	gt.drawSkip = FALSE;
	//FPSパラメータの保存
	EyeRot = D3DXVECTOR2(0,0);
}
//メニューモード
VOID Personal::MenuMode()
{
	//決定
	Check = ML->C.Z.T();
	if(!Check){
	//キャンセル
	Cansel = FALSE;
	if(Check == FALSE)
	{
		if(ML->C.X.K()){ CanselCount = 1; }
		else
		{
			if(CanselCount == 1){Cansel = TRUE;	}
			CanselCount = 0;
		}
	}
	}
	//メニューの更新
	BOOL Close = ML->C.Space.T();
	FM.StaticPos(&obj.objPos,obj.YPR.y);
	int MenuFlag = menu.Update(Check,Cansel,Close);
	if(Check) {CheckSE(SE_CHECK);}
	else if(Close || Cansel) {CheckSE(SE_CANSEL);}
	//メニューを閉じる
	if(	 MenuFlag == 0 || Close)
	{
		Check = FALSE;
		menu.CloseMenu();
		Mode = MODE_ACTIVE; 
	}
	//フィールドチェンジ
	if(MenuFlag == -1)
	{
		Check = FALSE;
		ReLoad = 1;
		menu.CloseMenu();
	}
	
}
//ダメージを受ける
VOID Personal::DamageMode()
{	
	gt.drawSkip = FALSE;
	gt.MotionType = gt_Anim::Motion_Wait;
	FPSFlag = FALSE;
}

//操作時更新
VOID Personal::Update()
{	

#ifdef MY_DEBUG 
	//モデルを編集
	if(m_iPage == 1)
	{
		gt.Update(ML);
		return;
	}
	//上下デバッグ用
	if(Mode == MODE_ACTIVE)
	{
		if(ML->C.V.K()){obj.objPos.y += 0.1f;}
	}	
#endif
//	if( )
//	{
		gt.SoltFlag = FM.iGetFlag(ITEM_MASUI);
//	}

	//懐中電灯
	gt.FlashFlag = FALSE;
	if(FM.iGetedFlag(ITEM_LIGHT) )
	{

		gt.FlashFlag = TRUE;

		if(!FPSFlag)
		{
			gt.FlashLock = TRUE;
		}
		else
		{
			gt.FlashLock = FALSE;
		}
		
	}
	//プレイヤーの状態
	switch(Mode)
	{
	case MODE_EVENT: EventMode(); break;//非操作
	case MODE_ACTIVE:ActiveMode();break;//移動
	case MODE_MENU:	 MenuMode();  break;//ゲームメニュー
	case MODE_DAMAGE:DamageMode();break;//敵イベントモード
	default: break;
	}		
	
	
	//モデルを更新
	gt.Update(ML);
}

//Uiテキスト
VOID Personal::Ui()
{
	//照準
	if(FPSFlag){sight.draw(ML);	}
	//メニュー
	menu.draw();
}
//描画
VOID Personal::draw()
{	
	//主観フラグが発っている場合カメラを主観に
	if(ML->E.ShadowPassNum == 1)
	{
		if(Mode == MODE_ACTIVE)
		{
			if(FPSFlag){FPSMode();	}
		}
	}
	//FPSモードの場合は鏡のみ映るように
	if(FPSFlag)
	{
		if(ML->E.MirrorPass == 1 ){gt.draw(ML);}
		else{gt.Set(ML);}
	}
	else{gt.draw(ML);	}

	for(std::vector<CBullet*>::iterator it = Blt.begin(); it != Blt.end(); ++it )
	{
		(*it)->draw(ML);
	}
	
/*
	obj.draw(ML);//当たり判定	
	//注視点オブジェクト
	At.Type(x_sphere);
	At.objScal=D3DXVECTOR3(0.2f,0.2f,0.2f);
	At.ShadowFlag =FALSE;
	At.objPos = AtPos;
	At.objPos.y = obj.objPos.y;
	At.draw(ML);//注視点
//*/
}
//==========================================
//外部とのアクセス
//==========================================
//敵に弾がくっつく
VOID Personal::AtcBullet(D3DXMATRIX* mat)
{
	Blt[m_iCount - 1]->Attach(mat);
}
//銃弾のアタッチをリセット
VOID Personal::ResetBullet()
{
	for(std::vector<CBullet*>::iterator it = Blt.begin(); it != Blt.end(); ++it)
	{
		(*it)->Reset();
	}
}
//debugボタン
VOID Personal::DButton(DebugButton* db)
{
	db->DB(_T("m_iPage = %d"),&m_iPage,0,1);
	if(m_iPage == 0)
	{

		db->DB(_T("gt.head.Bias = %f"),&gt.head.Bias,0.0f,1.0f);

		
	}
	if(m_iPage == 1)
	{
		//モーションデバッグ用		
		gt.MotionCreate(db,ML);
	}

}
//デバッグ用フォント
VOID Personal::DebugText(TCHAR* txt,int n)
{	
	/**/
	_stprintf_s(txt,n,
		_T("%s")
		_T("PlayPos x: %f y: %f z: %f\n")	
		_T("RotY:%f\n")	
		_T("FM.EventFlag = %d\n")
		_T("FM.FldType = %d\n")
		_T("Enemy.HP = %d\n")

		,txt
		,obj.objPos.x,obj.objPos.y,obj.objPos.z
		,gt.Null.YPR.y
		,FM.EventFlag
		,FM.FldType
		,FM.enemy.HP
		);
	
//	for(std::vector<CBullet*>::iterator it = Blt.begin(); it != Blt.end(); ++it )
//	{
//		(*it)->Debug(n,txt);
//	}
//	menu.DebugText(txt,n);
//	gt.DebugText(txt,n);
}
