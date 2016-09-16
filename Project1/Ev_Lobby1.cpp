//====================================================
//正面玄関
//====================================================
const TCHAR *LobbyIriguti::name(){return _T("LobbyIriguti");}
LobbyIriguti::LobbyIriguti()
{
	Msh.push_back(&pIri); 
	pIri.Type(x_iriguti);
	pIri.ShadowFlag=FALSE;
	
	Msh.push_back(&pDoor);
	pDoor.Type(x_irigutidoor);
	pDoor.objPos=D3DXVECTOR3(-1.3f,0,3.64f);
	pDoor.SetPare(&pIri.mWorld);
	pDoor.ShadowFlag=FALSE;	
	
	//上
	Msh.push_back(&pGlass);
	pGlass.Type(x_cube);
	pGlass.MeshCol=D3DXVECTOR4(0.5f,0.5f,0.5f,0.9f);
	pGlass.SetPare(&pIri.mWorld);
	pGlass.objScal=D3DXVECTOR3(11.2f,1.00f,0.01f);
	pGlass.objPos=D3DXVECTOR3(0.00f,0.80f,0.0f);
	pGlass.ShadowFlag=FALSE;
	
	//開く側
	Msh.push_back(&pGlass1);
	pGlass1.Type(x_cube);
	pGlass1.MeshCol=D3DXVECTOR4(0.5f,0.5f,0.5f,0.9f);
	pGlass1.SetPare(&pIri.mWorld);
	pGlass1.objScal=D3DXVECTOR3(5.50f,3.20f,0.02f);	
	pGlass1.objPos=D3DXVECTOR3(-1.45f,-0.25f,0);
	pGlass1.ShadowFlag=FALSE;	
	//開かない側
	Msh.push_back(&pGlass2);
	pGlass2.Type(x_cube);
	pGlass2.MeshCol=D3DXVECTOR4(0.5f,0.5f,0.5f,0.9f);
	pGlass2.SetPare(&pIri.mWorld);
	pGlass2.objScal=D3DXVECTOR3(5.5f,3.2f,0.01f);
	pGlass2.objPos=D3DXVECTOR3(1.42f,-0.26f,0.0f);
	pGlass2.ShadowFlag=FALSE;	
	//ドア
	Msh.push_back(&pGlass3);
	pGlass3.Type(x_cube);
	pGlass3.MeshCol=D3DXVECTOR4(0.5f,0.5f,0.5f,0.9f);
	pGlass3.SetPare(&pDoor.mWorld);
	pGlass3.objScal=D3DXVECTOR3(2.60f,3.20f,0.01f);
	pGlass3.objPos=D3DXVECTOR3(0.64f,-0.30f,0.00f);	
	pGlass3.ShadowFlag=FALSE;	

	//当たり判定
	hitbox.Type(x_cube);
	hitbox.objPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	hitbox.objScal = D3DXVECTOR3(5.0f,4.0f,1.0f);
	hitbox.drawSkip = TRUE;
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.SetPare(&pIri.mWorld);
	Msh.push_back(&hitbox);

	//テキスト
	text.init(this);
	text.s(_T("鍵がかかっている"));
	text.s(_T("外に公衆電話があるのが見える"));

	//鍵がかかってるとき
	text1.init(this);
	text1.s(_T("【正面玄関の鍵】を使った"));
	//鍵がかかってる音
	lock.Set(wav_keylock);
	lock.m_b3DSound = TRUE;
	Snd.push_back(&lock);
	//開錠音
	unlock.Set(wav_dooropen);
	unlock.Filter.Type = BandPassFilter;
	unlock.Filter.OneOverQ = 0.1f;
	unlock.m_b3DSound = TRUE;
	Snd.push_back(&unlock);
}

VOID LobbyIriguti::Update()
{
	BOOL b = hitbox.HitObj.Reaction == 1 && P->Check && P->Mode != Personal::MODE_EVENT;
	//鍵を持っていたら
	if(P->FM.iGetedFlag(ITEM_GENKAN_KEY))
	{
		//鍵を使う
		if( P->FM.iGetFlag(ITEM_GENKAN_KEY) )
		{
			if(b)
			{
				unlock.Emi.Position = pIri.objPos;
				unlock.Start(ML);
				text1.StartText(P);
			}
			if( text1.Update(P,ML) == 1 )
			{
				P->FM.iRelease(ITEM_GENKAN_KEY);
			}

		}
		else
		{
			//普通に出入りできる
			if(b)
			{
				P->CheckSE(Personal::SE_OPEN);
				m_pPare->FldChange(new Soto,&D3DXVECTOR3(0,0.7f,37.0f),180.0f);
			}
		}
	}
	else
	{
		//鍵がかかってる
		if(b)
		{
			lock.Emi.Position = pIri.objPos;
			lock.Start(ML);
			text.StartText(P);
		}
		text.Update(P,ML);
	}
	

}


//====================================================
//椅子
//====================================================
const TCHAR *LobbyChair::name(){return _T("LobbyChair");}
LobbyChair::LobbyChair()
{
	//椅子
	chair.Type(x_chair);
	chair.SpColm = 0.0f;
	chair.Bias = 0.5f;
	chair.HitMode(CT_OBB,CB_PLUS);
	Msh.push_back(&chair);
	//左の手すり
	pLhand.Type(x_chair_tesuri);
	pLhand.SetPare(&chair.mWorld);
	pLhand.SpColm=0.0f;
	pLhand.objPos.x=-0.35f;
	pLhand .Bias=0.5f;
	Msh.push_back(&pLhand);	
	//右の手すり
	pRhand.Type(x_chair_tesuri);
	pRhand.SetPare(&chair.mWorld);
	pRhand.SpColm=0.0f;
	pRhand.objPos.x=0.35f;
	pRhand.Bias=0.5f;
	Msh.push_back(&pRhand);
	frame = 0;
	flag = 0;
}
VOID LobbyChair::Set()
{

	pos.SetKey( 0,chair.objPos );
	pos.SetKey( 50,chair.objPos+ D3DXVECTOR3(0.5f,0.0f,0.0));

	rot.SetKey( 0,chair.YPR );
	rot.SetKey( 50,chair.YPR+ D3DXVECTOR3(0.0f,30.0f,0.0f) );
}

VOID LobbyChair::Update()
{
	
	chair.objPos = pos.Val1(frame);
	chair.YPR = rot.Val1(frame);
	if(P->FM.trick.chairMove == 0)
	{
		if( flag == 0 )
		{
			if( D3DXVec3Length(&(P->obj.objPos - chair.objPos)) < 3.0f )
			{
				flag = 1;
			}
		}
		if( flag == 1 )
		{
		
			frame++;
			if( pos.MaxKey() < frame )
			{
				P->FM.trick.chairMove = 1;
			}
		}
	}
	else
	{
		frame = pos.MaxKey(); 
	}

}
VOID LobbyChair::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,
		_T("%s\n")
		_T("flag = %d\n")
		_T("frame = %d\n")
		,t
		,flag
		,frame
		);
}
