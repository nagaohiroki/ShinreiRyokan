//============================================
//食堂扉
//============================================
const TCHAR* Dining_Door_In::name(){return _T("Dining_Door_In");}
Dining_Door_In::Dining_Door_In()
{
	//当たり判定
	Msh.push_back(&pBox);
	pBox.Type(x_cube);
	pBox.drawSkip=TRUE;
	pBox.HitMode(CT_OBB,CB_NONE);
	//ドア枠
	Msh.push_back(&pWaku);
	pWaku.Type(x_wood_door_waku);
	pWaku.objScal=D3DXVECTOR3(0.8f,0.9f,1.0f);
	pWaku.ShadowFlag=FALSE;
	pWaku.SetPare(&pBox.mWorld);
	//ドア
	Msh.push_back(&pDoor);
	pDoor.Type(x_wood_door);
	pDoor.SetPare(&pWaku.mWorld);
	pDoor.objPos.x=-0.47f;
	pDoor.ShadowFlag=FALSE;
	//ノブ1
	Msh.push_back(&pNobu);
	pNobu.Type(x_doornobu);
	pNobu.SetPare(&pDoor.mWorld);
	pNobu.objPos=D3DXVECTOR3(0.82f,0.75f,0);
	pNobu.ShadowFlag=FALSE;
	//SE
	se.Set(wav_dooropen);
	se.Filter.Type = BandPassFilter;
	se.Filter.OneOverQ = 0.1f;
	se.m_b3DSound = TRUE;
	//テキスト
	text.init(this);
	text.s(_T("鍵を開けた"));
}
VOID Dining_Door_In::Update()
{
	if( pBox.HitObj.Reaction == 1 )
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	{
		if(	P->FM.trick.dinigDoor == 1)
		{
			P->CheckSE(Personal::SE_OPEN);
			m_pPare->FldChange(new Lobby,&D3DXVECTOR3(2.3f,0.0f,41.7f),270.0f);
		}
		else
		{
			text.StartText(P);
			se.Start(ML);
			se.Emi.Position = pBox.objPos;	
		}
	}
	if(text.Update(P,ML) == 1)
	{
		P->FM.trick.dinigDoor = 1;
	}
}
//===========================================
//ダイニングセット
//===========================================
const TCHAR *DiningSet::name(){return _T("DiningSet");}
DiningSet::DiningSet()
{
	Msh.push_back(&pTable);
	pTable.Type(x_dining_table);	
	pTable.HitMode(CT_OBB,CB_PLUS);
	Msh.push_back(&pChair);
	pChair.Type(x_dining_chair);
	pChair.SetPare(&pTable.mWorld);
	pChair.MeshCol=D3DXVECTOR4(1.50f,1.50f,1.50f,1.00f);
	pChair.SpColm=0.00f;
	pChair.HitMode(CT_OBB,CB_PLUS);
	pChair.objPos=D3DXVECTOR3(0.40f,0.00f,0.40f);
	pChair.YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);

	Msh.push_back(&pChair1);
	pChair1.Type(x_dining_chair);
	pChair1.SetPare(&pTable.mWorld);
	pChair1.MeshCol=D3DXVECTOR4(1.50f,1.50f,1.50f,1.00f);
	pChair1.SpColm=0.00f;
	pChair1.HitMode(CT_OBB,CB_PLUS);
	pChair1.objPos=D3DXVECTOR3(0.40f,0.00f,-0.40f);
	pChair1.YPR=D3DXVECTOR3(0.00f,90.00f,0.00f);

	Msh.push_back(&pChair2);
	pChair2.Type(x_dining_chair);
	pChair2.SetPare(&pTable.mWorld);
	pChair2.MeshCol=D3DXVECTOR4(1.50f,1.50f,1.50f,1.00f);
	pChair2.SpColm=0.00f;
	pChair2.HitMode(CT_OBB,CB_PLUS);
	pChair2.objPos=D3DXVECTOR3(-0.40f,0.00f,0.40f);
	pChair2.YPR=D3DXVECTOR3(0.00f,-90.00f,0.00f);

	Msh.push_back(&pChair3);
	pChair3.Type(x_dining_chair);
	pChair3.SetPare(&pTable.mWorld);
	pChair3.MeshCol=D3DXVECTOR4(1.50f,1.50f,1.50f,1.00f);
	pChair3.SpColm=0.00f;
	pChair3.HitMode(CT_OBB,CB_PLUS);
	pChair3.objPos=D3DXVECTOR3(-0.40f,0.00f,-0.40f);
	pChair3.YPR=D3DXVECTOR3(0.00f,-90.00f,0.00f);
}
//===========================================
//蛍光灯
//===========================================
const TCHAR *Keikou::name(){return _T("Keikou");}
Keikou::Keikou()
{
	Msh.push_back(&pKeikou);
	pKeikou.Type(x_keikou);
	pKeikou.Type(x_keikou);
	pKeikou.ShadowFlag=FALSE;

	Msh.push_back(&pLight);
	pLight.Type(x_cylin);
	pLight.ShadowFlag=FALSE;
	pLight.SetPare(&pKeikou.mWorld);
	pLight.objPos=D3DXVECTOR3(0.03f,-0.04f,-0.90f);
	pLight.YPR=D3DXVECTOR3(90.00f,0.00f,0.00f);
	pLight.objScal=D3DXVECTOR3(0.02f,1.80f,0.02f);
	pLight.SpCol=D3DXVECTOR4(1.00f,1.00f,1.00f,1.00f);
	
	pLight.BloomColor=D3DXVECTOR4(1.00f,1.00f,1.00f,1.00f);
	pLight.objPos=D3DXVECTOR3(0.03f,-0.04f,-0.90f);
		
	Msh.push_back(&pLight1);
	pLight1.Type(x_cylin);
	pLight1.ShadowFlag=FALSE;
	pLight1.SetPare(&pKeikou.mWorld);
	pLight1.objPos=D3DXVECTOR3(0.03f,-0.04f,-0.90f);
	pLight1.YPR=D3DXVECTOR3(90.00f,0.00f,0.00f);
	pLight1.objScal=D3DXVECTOR3(0.02f,1.80f,0.02f);
	pLight1.SpCol=D3DXVECTOR4(1.00f,1.00f,1.00f,1.00f);
	pLight1.BloomColor=D3DXVECTOR4(1.00f,1.00f,1.00f,1.00f);
	pLight1.objPos=D3DXVECTOR3(-0.03f,-0.04f,-0.90f);

	pLight1.SpColm=1.0f;
	pLight.SpColm=1.0f;
}
VOID Keikou::Update()
{
	float p = ML->E.Ls.Col.x * 10.0f; 
	pLight1.SpColm = p;
	pLight.SpColm  = p;
}
//===========================================
//木椅子
//===========================================
const TCHAR *Wood_Chair::name(){return _T("Wood_Chair");}
Wood_Chair::Wood_Chair()
{
	//椅子
	chair.Type(x_dining_chair);
	chair.HitMode(CT_OBB,CB_PLUS);
	chair.Bias = 0.1f;
	chair.MeshCol = D3DXVECTOR4(2.0f,2.0f,2.0f,1.0f);
	chair.SpColm = 0.0f;
	Msh.push_back(&chair);
	//鍵
	Key.Type(x_key);
	Key.SetPare(&chair.mWorld);
	Key.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 0.2f;
	Key.objPos = D3DXVECTOR3(0.0f,0.4f,0.0f);
	Key.YPR = D3DXVECTOR3(0.0f,45.0f,0.0f);
	Key.MeshCol = D3DXVECTOR4(5.0f,5.0f,5.0f,1.0f);
	Msh.push_back(&Key);
	frame = 0;

	//text
	text.init(this);
	text.s(_T("【従業員室の鍵】を手に入れた"));

	se.Set(wav_sa);
	se.Filter.OneOverQ = 0.3f;
	se.Filter.Type = BandPassFilter;
	se.m_fVol = 0.1f;
	Snd.push_back(&se);
	flag = 0;


}
VOID Wood_Chair::Set()
{
	
}

VOID Wood_Chair::Update()
{
	frame++;
	if(frame > 250){frame = 0;}
	float f = 0.6f;
	if( frame >  10 && frame <  20 ||	frame >  50 && frame <  60 ||  frame > 130 && frame < 140 )
	{
		se.Start(ML);
		f  = 0.1f;
	}
	ML->E.Ls.Col = D3DXVECTOR4(f,f,f,1.0); 
	if(!P->FM.iGetedFlag(ITEM_STAFF_KEY))
	{
		//フラグ0
		if(flag == 0)
		{
			if(chair.HitObj.Reaction == 1 )
			if( P->Check )
			if(P->Mode != Personal::MODE_EVENT)
			{
			
				text.StartText(P);
				P->CheckSE(Personal::SE_ITEM);
			}
		
			int t = text.Update(P,ML);
			if(t == 1)
			{
				flag = 1;
				frame = 0;
				P->FM.iGet(ITEM_STAFF_KEY);
			}
		}
	}
	else
	{
		Key.drawSkip = TRUE;
		if(flag == 1)
		{
			if( frame >=  20 &&	frame <= 50)
			{
				
				P->FM.enemy.pos = D3DXVECTOR3(0.0f,0.35f,2.0f);
				P->FM.enemy.rot = 90.0f;
				P->FM.enemy.mode = Enemy::MODE_SEARCH;
			}
			else
			{			
				P->FM.enemy.mode = Enemy::MODE_CLEAR;
			}
			if(frame > 200)
			{
				flag = 0;
				P->FM.enemy.mode = Enemy::MODE_CLEAR;
			}
	
		}
	}
	

}

VOID Wood_Chair::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,
		_T("%s\n")
		_T("frame = %d\n")
		_T("flag = %d\n")
		,t
		,frame
		,flag
		);
}
