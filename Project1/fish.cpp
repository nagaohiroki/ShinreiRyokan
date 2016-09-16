//====================================
//モーション原型
//====================================
fish_anim::fish_anim(){}
//キーをセット(キー,body2pos,body2,body,head,L_nino,R_nino,L_hand,R_hand,L_asi,R_asi)
VOID fish_anim::s(int k,v* v0,v* v1,v* v2,v* v3,v* v4,v* v5,v* v6,v* v7,v* v8,v* v9)
{
	v* pv[FA_MAX] = {v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,};
	for(int i = 0; i < FA_MAX; i ++){anim[i].SetKey(k,*pv[i]);}
}
//キーの最終位置
int fish_anim::MaxKey()
{
	return anim[0].MaxKey();
}
//====================================
//待機モーション
//====================================
fish_wait::fish_wait()
{
	s(0,&v(0.0f,4.5f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,-75.6f),&v(0.0f,180.0f,-75.6f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
	s(50,&v(0.0f,4.5f,0.0f),&v(0.0f,0.0f,0.0f),&v(-4.2f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,-68.4f),&v(0.0f,180.0f,-68.4f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
	s(100,&v(0.0f,4.5f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,-75.6f),	&v(0.0f,180.0f,-75.6f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
}
//====================================
//歩行モーション
//====================================
fish_walk::fish_walk()
{
	//直立
	s(0,&v(0.0f,4.7f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,-75.0f),&v(0.0f,180.0f,-75.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
	//踏み込み
	s(25,&v(0.0f,4.3f,0.0f),&v(0.0f,0.0f,0.0f),	&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(-25.0f,0.0f,-75.0f),&v(-25.0f,180.0f,-75.0f),&v(0.0f,-20.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(18.0f,0.0f,0.0f),&v(-10.0f,0.0f,0.0f));
	//直立
	s(50,&v(0.0f,4.7f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,-75.0f),&v(0.0f,180.0f,-75.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
	//踏み込み(逆)
	s(75,&v(0.0f,4.3f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(25.0f,0.0f,-75.0f),&v(25.0f,180.0f,-75.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,20.0f,0.0f),&v(-10.0f,0.0f,0.0f),&v(18.0f,0.0f,0.0f));
	//直立
	s(100,&v(0.0f,4.7f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,-75.0f),&v(0.0f,180.0f,-75.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));	
}

//====================================
//攻撃モーション
//====================================
fish_attack::fish_attack()
{
s(0,&v(0.0f,4.7f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,-75.0f),	&v(0.0f,180.0f,-75.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));	
s(10,&v(0.0f,4.3f,0.0f),&v(0.0f,0.0f,0.0f),&v(18.0f,0.0f,5.0f),&v(-10.0f,0.0f,0.0f),&v(-100.0f,0.0f,-70.0f),&v(100.0f,180.0f,-70.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(20.0f,0.0f,0.0f),&v(-5.0f,0.0f,0.0f));
s(20,&v(0.0f,4.7f,0.0f),&v(0.0f,0.0f,0.0f),&v(18.0f,0.0f,0.0f),&v(-10.0f,0.0f,0.0f),&v(-100.0f,0.0f,-70.0f),&v(100.0f,180.0f,-70.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
//フォロースルー
s(30,&v(0.0f,4.3f,0.0f),&v(0.0f,0.0f,0.0f),&v(33.7f,0.0f,5.0f),&v(-35.2f,0.0f,0.0f),&v(-100.0f,0.3f,-70.0f),&v(100.0f,180.0f,-70.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(-5.0f,0.0f,0.0f),&v(20.0f,-0.1f,0.0f));
s(40,&v(0.0f,4.3f,0.0f),&v(0.0f,0.0f,0.0f),&v(62.5f,0.0f,5.0f),&v(-35.2f,0.0f,0.0f),&v(-100.0f,0.3f,-70.0f),&v(100.0f,180.0f,-70.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(9.0f,0.0f,0.0f),&v(-20.0f,-0.1f,0.0f));
s(50,&v(0.0f,4.3f,0.0f),&v(0.0f,0.0f,0.0f),&v(66.1f,0.0f,5.0f),&v(-6.4f,0.0f,0.0f),&v(-100.0f,0.3f,-70.0f),&v(100.0f,180.0f,-70.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(-9.0f,0.0f,0.0f),&v(-2.0f,-0.1f,0.0f));
s(90,&v(0.0f,4.7f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,-75.0f),	&v(0.0f,180.0f,-75.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));	
s(100,&v(0.0f,4.5f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,-75.0f),	&v(0.0f,180.0f,-75.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));	
}
//====================================
//殺害モーション
//====================================
fish_death::fish_death()
{
s(0,&v(0.0f,4.3f,0.0f),&v(0.0f,0.0f,0.0f),&v(18.0f,0.0f,5.0f),&v(-10.0f,0.0f,0.0f),&v(-100.0f,0.0f,-70.0f),&v(100.0f,180.0f,-70.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(20.0f,0.0f,0.0f),&v(-5.0f,0.0f,0.0f));
s(40,&v(0.0f,4.7f,0.0f),&v(0.0f,0.0f,0.0f),&v(18.0f,0.0f,0.0f),&v(-10.0f,0.0f,0.0f),&v(-100.0f,0.0f,-70.0f),&v(100.0f,180.0f,-70.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
s(80,&v(0.0f,4.3f,0.0f),&v(0.0f,0.0f,0.0f),&v(18.0f,0.0f,5.0f),&v(-10.0f,0.0f,0.0f),&v(-100.0f,0.0f,-70.0f),&v(100.0f,180.0f,-70.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(20.0f,0.0f,0.0f),&v(-5.0f,0.0f,0.0f));
s(120,&v(0.0f,4.7f,0.0f),&v(0.0f,0.0f,0.0f),&v(18.0f,0.0f,0.0f),&v(-10.0f,0.0f,0.0f),&v(-100.0f,0.0f,-70.0f),&v(100.0f,180.0f,-70.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
}
//====================================
//モデル
//====================================
//コンストラクタ
Fish::Fish()
{
	drawSkip = FALSE;
	Stop = FALSE;
	MotType = 0;
	frame = 0;
	speed = 1;
	slow = 0;
	//NULLが基点で次にbody2が基点になる
	//配列化
	all.push_back(&Null);
	all.push_back(&body2);
	all.push_back(&body);
	all.push_back(&head);
	all.push_back(&L_nino);
	all.push_back(&R_nino);
	all.push_back(&L_hand);
	all.push_back(&R_hand);
	all.push_back(&L_asi);
	all.push_back(&R_asi);
	//モデルをセット
	Null.Type(x_cube);
	head.Type(x_fishface);
	body.Type(x_fishuebody);
	body2.Type(x_fishkosi);
	L_nino.Type(x_fishnino);
	R_nino.Type(x_fishnino);
	L_hand.Type(x_fishhand);
	R_hand.Type(x_fishhand);
	L_asi.Type(x_fishasi);
	R_asi.Type(x_fishasi);
	//親子付け	
	body2.SetPare(&Null.mWorld);
	body.SetPare(&body2.mWorld);
	head.SetPare(&body.mWorld);
	L_nino.SetPare(&body.mWorld);
	R_nino.SetPare(&body.mWorld);
	L_hand.SetPare(&L_nino.mWorld);
	R_hand.SetPare(&R_nino.mWorld);
	L_asi.SetPare(&body2.mWorld);
	R_asi.SetPare(&body2.mWorld);
	//全体設定
	unsigned int  size = all.size();
	for( unsigned int i = 0;i < size; i++ )
	{
		all[i]->SpCol=D3DXVECTOR4(1.0f,1.0f,1.0f,10.0f);
		all[i]->SpColm=0.0f;
		
	}
	//個別設定
	Null.drawSkip = TRUE;
	Null.MeshCol.w = 0.5f;
	Null.objScal  = D3DXVECTOR3(1.0f,1.0f,1.0f)*0.08f;
	body2.objPos  = D3DXVECTOR3(0.0f,4.5f,0.0f);
	head.objPos   = D3DXVECTOR3(0.0f,2.7f,0.0f);
	head.Bias = 1.0f;
	L_nino.objPos = D3DXVECTOR3(1.1f,2.0f,0.0f);
	R_nino.objPos = D3DXVECTOR3(-1.1f,2.0f,0.0f);
	R_nino.YPR.y = 180.0f;
	L_hand.objPos = D3DXVECTOR3(1.3f,0.0f,0.0f);
	R_hand.objPos = D3DXVECTOR3(1.3f,0.0f,0.0f);
	L_asi.objPos = D3DXVECTOR3(0.5f,0.0f,0.0f);
	R_asi.objPos = D3DXVECTOR3(-0.5f,0.0f,0.0f);
	L_asi.Amb=2.0f;
	R_asi.Amb=2.0f;

	aBase.push_back(new fish_wait);
	aBase.push_back(new fish_walk);
	aBase.push_back(new fish_attack);
	aBase.push_back(new fish_death);


	for(int i = 0; i < RING_MAX; i++)
	{
		Ring[i].Type(x_sphere);
		Ring[i].MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
		all.push_back(&Ring[i]);
	}
	Ring[0].SetPare(&head.mWorld);
	Ring[0].objScal = D3DXVECTOR3(1.0f,1.0f,1.0f)* 0.07f;
	Ring[0].objPos = D3DXVECTOR3(-2.05f,-1.6f,-0.4f);
	Ring[0].YPR.x = 15.0f;
//	Ring[0].objPos = D3DXVECTOR3(-2.0f,2.0f,1.0f);
//	Ring[0].YPR.x = 310.0f;
//	Ring[0].YPR.y = 10.0f;
	for(int i = 1; i < RING_MAX; i++)
	{
		Ring[i].objPos = D3DXVECTOR3(0.0f,2.0f * (float)i,0.0f);
		Ring[i].SetPare(&Ring[0].mWorld);
	}
	HP = 5;
}
//デストラクタ
Fish::~Fish()
{
	unsigned int size = aBase.size();
	for(unsigned int i = 0; i < size ; i++)
	{
		SAFE_DELETE(aBase[i]);
	}
}
//アニメーション更新
VOID Fish::AnimUpdate(fish_anim* a,int f)
{
	if(a->anim[0].val.size() == 0){return;}
	body2.objPos = a->anim[fish_anim::FAP_BODY2].Val(f);
	body2.YPR	 = a->anim[fish_anim::FAR_BODY2].Val(f);
	body.YPR	 = a->anim[fish_anim::FAR_BODY].Val(f);
	head.YPR	 = a->anim[fish_anim::FAR_HEAD].Val(f);
	L_nino.YPR	 = a->anim[fish_anim::FAR_L_NINO].Val(f);
	R_nino.YPR	 = a->anim[fish_anim::FAR_R_NINO].Val(f);
	L_hand.YPR	 = a->anim[fish_anim::FAR_L_HAND].Val(f);
	R_hand.YPR	 = a->anim[fish_anim::FAR_R_HAND].Val(f);
	L_asi.YPR	 = a->anim[fish_anim::FAR_L_ASI].Val(f);
	R_asi.YPR	 = a->anim[fish_anim::FAR_R_ASI].Val(f);
}
//更新
VOID Fish::Update(MyLibrary* ml)
{
	//HPを表示
	if(!drawSkip)
	{
		for(int i = 0; i < RING_MAX; i++)
		{
			Ring[i].drawSkip = TRUE;
		}
		for(int i = 0; i < HP; i++)
		{
			Ring[i].drawSkip = FALSE;
		}
	}
	else
	{
		for(int i = 0; i < RING_MAX; i++)
		{
			Ring[i].drawSkip = TRUE;
		}
	}
	//ヌルオブジェクト更新
	Null.SetSize(ml);	
	if(MotType < (int)aBase.size() )
	{
		//スピード調整
		int f = 0;
		if( slow != 0 ){ f = frame / slow; }
		else{ f = frame * speed; }
		//アニメーション
		AnimUpdate(aBase[MotType],f);
		//上限
		if( aBase[MotType]->MaxKey() < f ){ frame = 0;	}
		//フレームの更新
		if( !Stop ){frame++;}
	}
}
//メッシュカラー
VOID Fish::MeshCol(D3DXVECTOR4* c)
{
	unsigned int size = all.size();
	for( unsigned int i = 0; i < size; i++ )
	{
		all[i]->MeshCol = *c;
	}
}
//ブルームカラー
VOID Fish::Bloom(D3DXVECTOR4* c)
{
	unsigned int size = all.size();
	for( unsigned int i = 0; i < size; i++ )
	{
		all[i]->BloomColor = *c;
	}
}
//スペキュラカラー
VOID Fish::Sp(D3DXVECTOR4* c,float p)
{
	unsigned int size = all.size();
	for( unsigned int i = 0; i < size; i++ )
	{
		all[i]->SpCol = *c;
		all[i]->SpColm = p;

	}
}

//描画
VOID Fish::draw(MyLibrary* ml)
{
	if(drawSkip){return;}
	unsigned int  size = all.size();
	for( unsigned int i = 0;i < size; i++ )
	{
		all[i]->draw(ml);
	}
}
//デバッグ
VOID Fish::DebugBtn(DebugButton* db,MyLibrary* ml)
{

	int maxframe = 300;
	if(MotType < (int)aBase.size()){maxframe = aBase[MotType]->MaxKey();}


	db->DB(_T("speed = %d"),&speed,0,10);
	db->DB(_T("slow = %d"),&slow,0,10);
	db->DB(_T("Stop = %d"),&Stop,FALSE,TRUE);
	db->DB(_T("MotType = %d"),&MotType,0,(int)fish_anim::FM_EDIT);
	db->DB(_T("frame= %d"),&frame,0,maxframe);
	db->DB(_T("body2.objPos.x = %f"),&body2.objPos.x,-30.0f,30.0f);
	db->DB(_T("body2.objPos.y = %f"),&body2.objPos.y,-30.0f,30.0f);
	db->DB(_T("body2.objPos.z = %f"),&body2.objPos.z,-30.0f,30.0f);	
	db->DB(_T("body2.YPR.x = %f"),&body2.YPR.x,-180.0f,180.0f);
	db->DB(_T("body2.YPR.y = %f"),&body2.YPR.y,-180.0f,180.0f);
	db->DB(_T("body2.YPR.z = %f"),&body2.YPR.z,-180.0f,180.0f);	
	db->DB(_T("body.YPR.x = %f"),&body.YPR.x,-180.0f,180.0f);
	db->DB(_T("body.YPR.y = %f"),&body.YPR.y,-180.0f,180.0f);
	db->DB(_T("body.YPR.z = %f"),&body.YPR.z,-180.0f,180.0f);	
	db->DB(_T("head.YPR.x = %f"),&head.YPR.x,-180.0f,180.0f);
	db->DB(_T("head.YPR.y = %f"),&head.YPR.y,-180.0f,180.0f);
	db->DB(_T("head.YPR.z = %f"),&head.YPR.z,-180.0f,180.0f);	
	db->DB(_T("L_nino.YPR.x = %f"),&L_nino.YPR.x,-180.0f,180.0f);
	db->DB(_T("L_nino.YPR.y = %f"),&L_nino.YPR.y,-180.0f,180.0f);
	db->DB(_T("L_nino.YPR.z = %f"),&L_nino.YPR.z,-180.0f,180.0f);
	db->DB(_T("R_nino.YPR.x = %f"),&R_nino.YPR.x,-180.0f,180.0f);
	db->DB(_T("R_nino.YPR.y = %f"),&R_nino.YPR.y,-180.0f,180.0f);
	db->DB(_T("R_nino.YPR.z = %f"),&R_nino.YPR.z,-180.0f,180.0f);	
	db->DB(_T("L_hand.YPR.x = %f"),&L_hand.YPR.x,-180.0f,180.0f);
	db->DB(_T("L_hand.YPR.y = %f"),&L_hand.YPR.y,-180.0f,180.0f);
	db->DB(_T("L_hand.YPR.z = %f"),&L_hand.YPR.z,-180.0f,180.0f);
	db->DB(_T("R_hand.YPR.x = %f"),&R_hand.YPR.x,-180.0f,180.0f);
	db->DB(_T("R_hand.YPR.y = %f"),&R_hand.YPR.y,-180.0f,180.0f);
	db->DB(_T("R_hand.YPR.z = %f"),&R_hand.YPR.z,-180.0f,180.0f);	
	db->DB(_T("L_asi.YPR.x = %f"),&L_asi.YPR.x,-180.0f,180.0f);
	db->DB(_T("L_asi.YPR.y = %f"),&L_asi.YPR.y,-180.0f,180.0f);
	db->DB(_T("L_asi.YPR.z = %f"),&L_asi.YPR.z,-180.0f,180.0f);
	db->DB(_T("R_asi.YPR.x = %f"),&R_asi.YPR.x,-180.0f,180.0f);
	db->DB(_T("R_asi.YPR.y = %f"),&R_asi.YPR.y,-180.0f,180.0f);
	db->DB(_T("R_asi.YPR.z = %f"),&R_asi.YPR.z,-180.0f,180.0f);
	//Ctrl+Eで記録
	if(ml->C.Ctrl.K())
	{
		if(ml->C.E.T())
		{
			TCHAR tmp[1000] = _T("");
			TCHAR txtName[100] = _T("");
			_stprintf_s(tmp,1000,
				_T("s(%d,")
				_T("&v(%.1ff,%.1ff,%.1ff),")
				_T("&v(%.1ff,%.1ff,%.1ff),")
				_T("&v(%.1ff,%.1ff,%.1ff),")
				_T("&v(%.1ff,%.1ff,%.1ff),")
				_T("&v(%.1ff,%.1ff,%.1ff),")
				_T("&v(%.1ff,%.1ff,%.1ff),")
				_T("&v(%.1ff,%.1ff,%.1ff),")
				_T("&v(%.1ff,%.1ff,%.1ff),")
				_T("&v(%.1ff,%.1ff,%.1ff),")
				_T("&v(%.1ff,%.1ff,%.1ff));")
				,frame
 				,body2.objPos.x,body2.objPos.y,body2.objPos.z
				,body2.YPR.x,body2.YPR.y,body2.YPR.z
				,body.YPR.x,body.YPR.y,body.YPR.z
 				,head.YPR.x,head.YPR.y,head.YPR.z
				,L_nino.YPR.x,L_nino.YPR.y,L_nino.YPR.z
				,R_nino.YPR.x,R_nino.YPR.y,R_nino.YPR.z
				,L_hand.YPR.x,L_hand.YPR.y,L_hand.YPR.z
				,R_hand.YPR.x,R_hand.YPR.y,R_hand.YPR.z
				,L_asi.YPR.x,L_asi.YPR.y,L_asi.YPR.z
				,R_asi.YPR.x,R_asi.YPR.y,R_asi.YPR.z				
				);
			_stprintf_s(txtName,100,_T("FishMot%d.txt"),frame);
			CFile().txt(txtName,tmp);		
			CFile().Debug(_T("motionSave\n"));	
		}
	}
}