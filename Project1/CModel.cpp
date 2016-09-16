gt_Model::gt_Model()
{
	Null.Type(x_cube);
	neck.Type(x_cube);

	head.Type(x_gthead);
	body.Type(x_gtbody);
	body2.Type(x_gtbody2);
	L_nino.Type(x_gtnino);
	R_nino.Type(x_gtnino);
	L_hand.Type(x_gthand);
	R_hand.Type(x_gthand);
	L_momo.Type(x_gtmomo);
	R_momo.Type(x_gtmomo);
	L_asi.Type(x_gtasi);
	R_asi.Type(x_gtasi);		
	body2.SetPare(&Null.mWorld);
	body.SetPare(&body2.mWorld);
	neck.SetPare(&body.mWorld);
	head.SetPare(&neck.mWorld);
	L_nino.SetPare(&body.mWorld);
	R_nino.SetPare(&body.mWorld);
	L_hand.SetPare(&L_nino.mWorld);
	R_hand.SetPare(&R_nino.mWorld);
	L_momo.SetPare(&body2.mWorld);
	R_momo.SetPare(&body2.mWorld);
	L_asi.SetPare(&L_momo.mWorld);
	R_asi.SetPare(&R_momo.mWorld);

	//まとめて設定
	all.push_back(&Null);
	all.push_back(&body2);
	all.push_back(&body);
	all.push_back(&neck);
	all.push_back(&head);
	all.push_back(&L_nino);
	all.push_back(&R_nino);
	all.push_back(&L_hand);
	all.push_back(&R_hand);
	all.push_back(&L_momo);
	all.push_back(&R_momo);
	all.push_back(&L_asi);
	all.push_back(&R_asi);
	unsigned int size = all.size();
	for(unsigned int i = 0; i < size; i++)
	{
		all[i]->ShadowFlag = TRUE;
		all[i]->MeshCol=D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
		all[i]->SpCol=D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
		all[i]->SpColm=0.1f;


	}
	//個別設定
	Null.objScal=D3DXVECTOR3(0.1f,0.1f,0.1f);
	Null.objPos=D3DXVECTOR3(0,0,0);
	Null.YPR.y=180.0f;
	Null.drawSkip = TRUE;
	body.objPos.y=-0.5f;
	body2.objPos.y=6.1f;
	neck.objPos.y=2.9f;
	head.objPos.y=1.9f;
	head.Bias = 1.0f;
	L_nino.YPR.y=180.0f;
	L_nino.objPos=D3DXVECTOR3(-1.0f,2.3f,0);
	L_hand.objPos.x=1.9f;

	R_nino.objPos=D3DXVECTOR3(1.0f,2.3f,0);
	R_hand.objPos.x=1.9f;

	L_momo.objPos=D3DXVECTOR3(0.6f,-2.0f,0.0f);
	L_asi.objPos=D3DXVECTOR3(0.0f,-1.4f,0.0f);

	R_momo.objPos=D3DXVECTOR3(-0.6f,-2.0f,0.0f);
	R_asi.objPos=D3DXVECTOR3(0.0f,-1.4f,0.0f);
	//懐中電灯
	FlashFlag = FALSE;
	fl.flash.SetPare(&R_hand.mWorld);
	fl.flash.YPR.x =90.0f;
	fl.flash.YPR.y = 50.0f;
	fl.flash.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 10.0f;
	fl.flash.objPos = D3DXVECTOR3(2.0f,0.0f,0.0f);
	//モーション
	drawSkip = FALSE;
	MotionType = gt_Anim::Motion_Wait;
	KeyFrame=0;
	speed = 1;
	slow = 0;
	Stop = FALSE;
	Anim.push_back(new gt_Wait);
	Anim.push_back(new gt_Walk);
	Anim.push_back(new gt_Run);
	Anim.push_back(new gt_Drink);
	Anim.push_back(new gt_Throw);
	FlashLock = TRUE;

	SoltFlag = FALSE;
	//薬瓶
	drug.Type(x_bottle);
//	drug.objPos = D3DXVECTOR3(0.0f,-0.2f,0.0f);
	drug.objScal= D3DXVECTOR3(0.15f,0.15f,0.15f)*10.0f * 0.3f;
	drug.YPR.x = 90.0f;
	drug.SpColm = 1.0f; 
	drug.SpCol.w = 0.0f;
	drug.objPos.x = 2.5f;
	drug.SetPare(&R_hand.mWorld);
//	drug.ShadowFlag = FALSE;
//	drug.HitMode(CT_OBB,CB_NONE);

}
gt_Model::~gt_Model()
{
	int size = Anim.size();
	for(int i = 0; i < size; i++)
	{
		SAFE_DELETE(Anim[i]);
	}

}
//メッシュの色
VOID gt_Model::MeshCol(D3DXVECTOR4* Col)
{
	unsigned int size = all.size();
	for(unsigned int i = 0; i < size; i++)
	{
		all[i]->MeshCol = *Col;
	}
}
//スペキュラ
VOID gt_Model::SpcCol(D3DXVECTOR4* Col,float m)
{
	unsigned int size = all.size();
	for(unsigned int i = 0; i < size; i++)
	{
		all[i]->SpCol= *Col;
		all[i]->SpColm= m;
	}
}
//アニメーション変数
VOID gt_Model::aSet(gt_Anim* A,int f)
{
	
	neck.YPR	 = A->Ak[gt_Anim::GR_NECK].Val(f);
	body.YPR	 = A->Ak[gt_Anim::GR_BODY].Val(f);
	body2.YPR	 = A->Ak[gt_Anim::GR_BODY2].Val(f);
	L_nino.YPR	 = A->Ak[gt_Anim::GR_L_NINO].Val(f);
	R_nino.YPR	 = A->Ak[gt_Anim::GR_R_NINO].Val(f);
	L_hand.YPR	 = A->Ak[gt_Anim::GR_L_HAND].Val(f);
	R_hand.YPR	 = A->Ak[gt_Anim::GR_R_HAND].Val(f);
	L_momo.YPR	 = A->Ak[gt_Anim::GR_L_MOMO].Val(f);
	R_momo.YPR	 = A->Ak[gt_Anim::GR_R_MOMO].Val(f);
	L_asi.YPR	 = A->Ak[gt_Anim::GR_L_ASI].Val(f);
	R_asi.YPR	 = A->Ak[gt_Anim::GR_R_ASI].Val(f);
	body2.objPos = A->Ak[gt_Anim::GP_BODY2].Val(f);

}

VOID gt_Model::Set(MyLibrary* ML)
{
	
	if(FlashFlag){fl.Set(ML);}
	int size = all.size();
	for(int i = 0; i < size; i++)
	{
		all[i]->SetSize(ML);
	}
}
int gt_Model::MaxKey(gt_Anim::Motion m)
{
	return Anim[m]->MaxKey();
}
//更新
VOID gt_Model::Update(MyLibrary* ML)
{
	//塗るオブジェクトの更新
	Null.SetSize(ML);
	head.SetSize(ML);
	if(MotionType < (int)Anim.size())
	{
		//スピード調整
		int f = 0;
		if( slow != 0 ){ f = KeyFrame / slow; }
		else{ f = KeyFrame * speed; }
		//フレームの更新
		if(KeyFrame > Anim[MotionType]->MaxKey()){KeyFrame = 0;}
		aSet(Anim[MotionType],f);
		if(!Stop){KeyFrame++;}		
	}
	//ライトもち
	if(FlashFlag)
	{
		fl.Update(ML,FlashLock);
		R_hand.YPR = D3DXVECTOR3(0.0f,-50.0f,0.0f);
		R_nino.YPR.x = 0.0f; 
		R_nino.YPR.y = 0.0f; 
		R_nino.YPR.z = -70.0f; 
	}
}
//描画
VOID gt_Model::draw(MyLibrary *ML)
{	
	if(drawSkip){return;}
	if(FlashFlag){fl.draw(ML);}
	if(SoltFlag){drug.draw(ML);}
	int size = all.size();
	for(int i = 0; i < size; i++)
	{
		all[i]->draw(ML);
	}
}
VOID gt_Model::DebugText(TCHAR*,int)
{
}

VOID gt_Model::MotionCreate(DebugButton* db,MyLibrary *ml)
{
	int maxframe = 300;
	if(MotionType < (int)Anim.size()){maxframe = Anim[MotionType]->MaxKey();}

	db->DB(_T("KeyFrame = %d"),&KeyFrame,0,maxframe);
	db->DB(_T("MotionType = %d"),&MotionType,0,(int)gt_Anim::Motion_Edit);
	db->DB(_T("Stop = %d"),&Stop,FALSE,TRUE);
	db->DB(_T("speed = %d"),&speed,0,10);
	db->DB(_T("slow = %d"),&slow,0,10);
	
	db->DB(_T("GR_NECK.x = %f"),&neck.YPR.x,-180.0f,180.0f);
	db->DB(_T("GR_NECK.y = %f"),&neck.YPR.y,-180.0f,180.0f);
	db->DB(_T("GR_NECK.z = %f"),&neck.YPR.z,-180.0f,180.0f);
	db->DB(_T("GR_BODY.x = %f"),&body.YPR.x,-180.0f,180.0f);
	db->DB(_T("GR_BODY.y = %f"),&body.YPR.y,-180.0f,180.0f);
	db->DB(_T("GR_BODY.z = %f"),&body.YPR.z,-180.0f,180.0f);
	db->DB(_T("GR_BODY2.x = %f"),&body2.YPR.x,-180.0f,180.0f);
	db->DB(_T("GR_BODY2.y = %f"),&body2.YPR.y,-180.0f,180.0f);
	db->DB(_T("GR_BODY2.z = %f"),&body2.YPR.z,-180.0f,180.0f);
	db->DB(_T("GP_BODY2.x = %f"),&body2.objPos.x,-10.0f,10.0f);
	db->DB(_T("GP_BODY2.y = %f"),&body2.objPos.y,-10.0f,10.0f);
	db->DB(_T("GP_BODY2.z = %f"),&body2.objPos.z,-10.0f,10.0f);
	db->DB(_T("GR_L_NINO.x = %f"),&L_nino.YPR.x,-180.0f,180.0f);
	db->DB(_T("GR_L_NINO.y = %f"),&L_nino.YPR.y,-180.0f,180.0f);
	db->DB(_T("GR_L_NINO.z = %f"),&L_nino.YPR.z,-180.0f,180.0f);
	db->DB(_T("GR_R_NINO.x = %f"),&R_nino.YPR.x,-180.0f,180.0f);
	db->DB(_T("GR_R_NINO.y = %f"),&R_nino.YPR.y,-180.0f,180.0f);
	db->DB(_T("GR_R_NINO.z = %f"),&R_nino.YPR.z,-180.0f,180.0f);
	db->DB(_T("GR_L_HAND.x = %f"),&L_hand.YPR.x,-180.0f,180.0f);
	db->DB(_T("GR_L_HAND.y = %f"),&L_hand.YPR.y,-180.0f,180.0f);
	db->DB(_T("GR_L_HAND.z = %f"),&L_hand.YPR.z,-180.0f,180.0f);
	db->DB(_T("GR_R_HAND.x = %f"),&R_hand.YPR.x,-180.0f,180.0f);
	db->DB(_T("GR_R_HAND.y = %f"),&R_hand.YPR.y,-180.0f,180.0f);
	db->DB(_T("GR_R_HAND.z = %f"),&R_hand.YPR.z,-180.0f,180.0f);
	db->DB(_T("GR_L_MOMO.x = %f"),&L_momo.YPR.x,-180.0f,180.0f);
	db->DB(_T("GR_L_MOMO.y = %f"),&L_momo.YPR.y,-180.0f,180.0f);
	db->DB(_T("GR_L_MOMO.z = %f"),&L_momo.YPR.z,-180.0f,180.0f);
	db->DB(_T("GR_R_MOMO.x = %f"),&R_momo.YPR.x,-180.0f,180.0f);
	db->DB(_T("GR_R_MOMO.y = %f"),&R_momo.YPR.y,-180.0f,180.0f);
	db->DB(_T("GR_R_MOMO.z = %f"),&R_momo.YPR.z,-180.0f,180.0f);
	db->DB(_T("GR_L_ASI.x = %f"),&L_asi.YPR.x,-180.0f,180.0f);
	db->DB(_T("GR_L_ASI.y = %f"),&L_asi.YPR.y,-180.0f,180.0f);
	db->DB(_T("GR_L_ASI.z = %f"),&L_asi.YPR.z,-180.0f,180.0f);
	db->DB(_T("GR_R_ASI.x = %f"),&R_asi.YPR.x,-180.0f,180.0f);
	db->DB(_T("GR_R_ASI.y = %f"),&R_asi.YPR.y,-180.0f,180.0f);
	db->DB(_T("GR_R_ASI.z = %f"),&R_asi.YPR.z,-180.0f,180.0f);

	//Ctrl+Eで記録
	if(ml->C.Ctrl.K())
	{
		if(ml->C.E.T())
		{
			TCHAR tmp[1000] = _T("");
			_stprintf_s(tmp,1000,
				_T("s(%d,&v(%.1ff,%.1ff,%.1ff),&v(%.1ff,%.1ff,%.1ff),&v(%.1ff,%.1ff,%.1ff),")
				_T("&v(%.1ff,%.1ff,%.1ff),&v(%.1ff,%.1ff,%.1ff),&v(%.1ff,%.1ff,%.1ff),")
				_T("&v(%.1ff,%.1ff,%.1ff),&v(%.1ff,%.1ff,%.1ff),&v(%.1ff,%.1ff,%.1ff),")
				_T("&v(%.1ff,%.1ff,%.1ff),&v(%.1ff,%.1ff,%.1ff),&v(%.1ff,%.1ff,%.1ff));")
				,KeyFrame
				 ,neck.YPR.x,neck.YPR.y,neck.YPR.z
				 ,body.YPR.x,body.YPR.y,body.YPR.z
				 ,body2.YPR.x,body2.YPR.y,body2.YPR.z
				 ,body2.objPos.x,body2.objPos.y,body2.objPos.z
				 ,L_nino.YPR.x,L_nino.YPR.y,L_nino.YPR.z		
				 ,R_nino.YPR.x,R_nino.YPR.y,R_nino.YPR.z
				 ,L_hand.YPR.x,L_hand.YPR.y,L_hand.YPR.z
				 ,R_hand.YPR.x,R_hand.YPR.y,R_hand.YPR.z
				 ,L_momo.YPR.x,L_momo.YPR.y,L_momo.YPR.z
				 ,R_momo.YPR.x,R_momo.YPR.y,R_momo.YPR.z
				 ,L_asi.YPR.x,L_asi.YPR.y,L_asi.YPR.z
				 ,R_asi.YPR.x,R_asi.YPR.y,R_asi.YPR.z				
				);

			TCHAR name[MAX_PATH];
			_stprintf_s(name,MAX_PATH,_T("gt_motion%d.txt"),KeyFrame);
			CFile().txt(name,tmp);		
			CFile().Debug(_T("gt_motionSave\n"));		
		}
	}
}
//アニメーション基底オブジェクト
gt_Anim::gt_Anim(){}
VOID gt_Anim::s(int k,v* v0,v* v1,v* v2,v* v3,v* v4,v* v5,v* v6,v* v7,v* v8,v* v9,v* v10,v* v11)
{
	v* pv[G_END] = {v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11};
	for(int i = 0; i < G_END; i ++){Ak[i].SetKey(k,*pv[i]);}
}
//キーの最大数
int gt_Anim::MaxKey(){return Ak[0].MaxKey();}
//待機アニメーション
gt_Wait::gt_Wait()
{
s(0,&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,6.1f,0.0f),&v(0.0f,180.0f,-75.0f),&v(0.0f,0.0f,-75.0f),&v(0.0f,0.0f,0.0f),&v( 0.0f,0.0f,0.0f),&v(0.0f,10.0f,0.0f),&v(0.0f,-10.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
s(50,&v(0.0f,0.0f,0.0f),&v(-7.5f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,6.1f,0.0f),&v(0.0f,180.0f,-70.0f),&v(0.0f,0.0f,-70.0f),&v(0.0f,0.0f,0.0f),&v( 0.0f,0.0f,0.0f),&v(0.0f,10.0f,0.0f),&v(0.0f,-10.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
s(100,&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,6.1f,0.0f),&v(0.0f,180.0f,-75.0f),&v(0.0f,0.0f,-75.0f),&v(0.0f,0.0f,0.0f),&v( 0.0f,0.0f,0.0f),&v(0.0f,10.0f,0.0f),&v(0.0f,-10.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
}
//歩きモーション
gt_Walk::gt_Walk()
{
s(0,&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,6.1f,0.0f),&v(-20.0f,180.0f,-70.0f),&v(-20.0f,0.0f,-70.0f),	&v(0.0f,20.0f,0.0f),&v( 0.0f,-20.0f,0.0f),&v( 30.0f,6.0f,0.0f),&v(-30.0f,-6.0f,0.0f),&v(30.0f,0.0f,0.0f),&v(30.0f,0.0f,0.0f));
s(5,&v(0.0f,0.0f,0.0f),&v(-7.5f,0.0f,0.0f),&v(0.0f,0.0f,4.0f),&v(0.0f,5.7f,0.0f),&v(-30.0f,180.0f,-70.0f),&v(-30.0f,0.0f,-70.0f),	&v(0.0f, 0.0f,0.0f),&v( 0.0f,-30.0f,0.0f),&v( 30.0f,6.0f,0.0f),&v(-30.0f,-6.0f,0.0f),&v(43.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
s(10,&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,6.1f,0.0f),&v(-10.0f,180.0f,-70.0f),&v(-10.0f,0.0f,-70.0f),	&v(0.0f,20.0f,0.0f),&v( 0.0f,-20.0f,0.0f),&v( -4.0f,6.0f,0.0f),&v(0.5f,-6.0f,0.0f),&v(43.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
s(15,&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,6.1f,0.0f),&v(20.0f,180.0f,-70.0f),&v( 20.0f,0.0f,-70.0f),	&v(0.0f,20.0f,0.0f),&v( 0.0f,-20.0f,0.0f),&v(-30.0f,6.0f,0.0f),&v(30.0f,-6.0f,0.0f),&v(30.0f,0.0f,0.0f),&v(30.0f,0.0f,0.0f));
s(20,&v(0.0f,0.0f,0.0f),&v(-7.5f,0.0f,0.0f),&v(0.0f,0.0f,-4.0f),&v(0.0f,5.7f,0.0f),&v(30.0f,180.0f,-70.0f),	&v( 30.0f,0.0f,-70.0f),	&v(0.0f,30.0f,0.0f),&v( 0.0f,  0.0f,0.0f),&v(-30.0f,6.0f,0.0f),&v(30.0f,-6.0f,0.0f),&v( 0.0f,0.0f,0.0f),&v(43.0f,0.0f,0.0f));
s(25,&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,6.1f,0.0f),&v(10.0f,180.0f,-70.0f),&v( 10.0f,0.0f,-70.0f),	&v(0.0f,20.0f,0.0f),&v( 0.0f,-20.0f,0.0f),&v(  0.5f,6.0f,0.0f),&v(-4.0f,-6.0f,0.0f),&v( 0.0f,0.0f,0.0f),&v(43.0f,0.0f,0.0f));
s(30,&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,6.1f,0.0f),&v(-20.0f,180.0f,-70.0f),&v(-20.0f,0.0f,-70.0f),	&v(0.0f,20.0f,0.0f),&v( 0.0f,-20.0f,0.0f),&v( 30.0f,6.0f,0.0f),&v(30.0f,-6.0f,0.0f),&v(30.0f,0.0f,0.0f),&v(30.0f,0.0f,0.0f));
}
//走りモーション
gt_Run::gt_Run()
{
s(0,&v(-21.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(16.0f,0.0f,0.0f),&v(0.0f,5.8f,0.0f),&v(-37.5f,180.0f,-70.0f),&v( 10.0f,0.0f,-70.0f),&v(0.0f,90.0f,0.0f),&v( 0.0f,-48.0f,0.0f),&v(-47.0f,0.0f,0.0f),&v(-17.0f,0.0f,0.0f),&v(30.0f,0.0f,0.0f),&v(121.5f,0.0f,0.0f));
s(8,&v(-21.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(16.0f,0.0f,0.0f),&v(0.0f,7.5f,0.0f),&v(-74.0f,180.0f,-70.0f),&v(-50.0f,0.0f,-70.0f),&v(0.0f,63.5f,0.0f),&v( 0.0f,-90.0f,0.0f),&v( 20.5f,0.0f,0.0f),&v(-65.0f,0.0f,0.0f),&v(40.0f,0.0f,0.0f),&v(29.0f,0.0f,0.0f));
s(16,&v(-21.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(16.0f,0.0f,0.0f),&v(0.0f,5.8f,0.0f),&v( 10.0f,180.0f,-70.0f),&v( 37.5f,0.0f,-70.0f),&v(0.0f,48.0f,0.0f),&v( 0.0f,-90.0f,0.0f),&v(-17.0f,0.0f,0.0f),&v(-47.0f,0.0f,0.0f),&v(121.5f,0.0f,0.0f),&v(30.0f,0.0f,0.0f));
s(24,&v(-21.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(16.0f,0.0f,0.0f),&v(0.0f,7.5f,0.0f),&v( 50.0f,180.0f,-70.0f),&v( 74.0f,0.0f,-70.0f),&v(0.0f,90.0f,0.0f),&v( 0.0f,-63.5f,0.0f),&v(-65.0f,0.0f,0.0f),&v( 20.5f,0.0f,0.0f),&v(29.0f,0.0f,0.0f),&v(40.0f,0.0f,0.0f));
s(32,&v(-21.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(16.0f,0.0f,0.0f),&v(0.0f,5.8f,0.0f),&v(-37.5f,180.0f,-70.0f),&v( 10.0f,0.0f,-70.0f),&v(0.0f,90.0f,0.0f),&v( 0.0f,-48.0f,0.0f),&v(-47.0f,0.0f,0.0f),&v(-17.0f,0.0f,0.0f),&v(30.0f,0.0f,0.0f),&v(121.5f,0.0f,0.0f));
}
//飲みモーション
gt_Drink::gt_Drink()
{
s(0,&v(0.0f,0.0f,0.0f),&v(-2.8f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,6.1f,0.0f),&v(0.0f,180.0f,-73.1f),&v(0.0f,0.0f,-73.1f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,10.0f,0.0f),&v(0.0f,-10.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
s(20,&v(0.0f,0.0f,0.0f),&v(-1.9f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,6.1f,0.0f),&v(36.0f,180.0f,-78.9f),&v(0.0f,0.0f,-73.7f),&v(0.0f,135.6f,-21.6f),&v(0.0f,0.0f,0.0f),&v(0.0f,10.0f,0.0f),&v(0.0f,-10.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
s(80,&v(0.0f,0.0f,0.0f),&v(-12.7f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,6.1f,0.0f),&v(35.3f,180.0f,-78.8f),&v(0.0f,0.0f,-73.7f),&v(0.0f,132.9f,-21.2f),&v(0.0f,0.0f,0.0f),&v(0.0f,10.0f,0.0f),&v(0.0f,-10.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
s(140,&v(0.0f,0.0f,0.0f),&v(-1.6f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,6.1f,0.0f),&v(35.3f,180.0f,-78.8f),&v(0.0f,0.0f,-73.7f),&v(0.0f,132.9f,-21.2f),&v(0.0f,0.0f,0.0f),&v(0.0f,10.0f,0.0f),&v(0.0f,-10.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
s(160,&v(0.0f,0.0f,0.0f),&v(-2.8f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,6.1f,0.0f),&v(0.0f,180.0f,-73.1f),&v(0.0f,0.0f,-73.1f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,10.0f,0.0f),&v(0.0f,-10.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
}
//投げモーション
gt_Throw::gt_Throw()
{
s(00,&v(0.0f,0.0f,0.0f),&v(-2.8f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,6.1f,0.0f),&v(90.0f,180.0f,-73.1f),&v(0.0f,0.0f,-73.1f),&v(0.0f,57.6f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,10.0f,0.0f),&v(0.0f,-10.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
s(10,&v(0.0f,0.0f,0.0f),&v(-2.8f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,6.1f,0.0f),&v(90.0f,180.0f,-73.1f),&v(0.0f,0.0f,-73.1f),&v(0.0f,18.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,10.0f,0.0f),&v(0.0f,-10.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
s(20,&v(0.0f,0.0f,0.0f),&v(-2.8f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,6.1f,0.0f),&v(90.0f,180.0f,-73.1f),&v(0.0f,0.0f,-73.1f),&v(0.0f,12.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,10.0f,0.0f),&v(0.0f,-10.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));
s(50,&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,6.1f,0.0f),&v(0.0f,180.0f,-75.0f),&v(0.0f,0.0f,-75.0f),&v(0.0f,0.0f,0.0f),&v( 0.0f,0.0f,0.0f),&v(0.0f,10.0f,0.0f),&v(0.0f,-10.0f,0.0f),&v(0.0f,0.0f,0.0f),&v(0.0f,0.0f,0.0f));

}