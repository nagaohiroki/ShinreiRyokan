//============================================
//BGM
//============================================
const TCHAR* SotoEvent::name(){return _T("SotoEvent");}
SotoEvent::SotoEvent()
{
}
VOID SotoEvent::Set()
{
	//BGM
	if(P->BGM == NULL)
	{
		P->BGM = new CObjSound;
		P->BGM->Set(wav_suzumusi);
		P->BGM->m_fVol = 0.8f;
		P->BGM->m_bLoop = TRUE;
	}
}
VOID SotoEvent::Update()
{
	if( P->BGM )
	{
		P->BGM->Start(ML);
	}
	/*
	if( P->FM.EventFlag >= TL_ENDING )
	{
		if( P->BGM )
		{
			P->BGM->Stop(ML,0.0f);
			SAFE_DELETE(P->BGM);
		}
		return;
	}
	//BGM
	if(P->BGM == NULL)
	{
		P->BGM = new CObjSound;
		P->BGM->Set(wav_suzumusi);
		P->BGM->m_fVol = 0.8f;
		P->BGM->m_bLoop = TRUE;
	}
	else
	{
		P->BGM->Start(ML);
	}
	*/
	if(P->obj.objPos.z < 0.5f)
	{
		m_pPare->FldChange(new Sandou,&D3DXVECTOR3(0.0f,0.35f,13.0f),180.0f);
	}
}


//============================================
//10円
//============================================
const TCHAR* TenYen::name(){return _T("TenYen");}
TenYen::TenYen()
{
	//基点
	box.Type(x_cube);
	box.drawSkip = TRUE;
	Msh.push_back(&box);



	//モーション
	fish.Null.SetPare(&box.mWorld);
	neck = 0.0f;
	body = 0.0f;

	frame = 0; 
	flag = 0;
	
	posz.SetKey(0,0.0f);
	posz.SetKey(100,0.0f);
	posz.SetKey(300,2.0f);

	alpha.SetKey(0,0.0f);
	alpha.SetKey(10,1.0f);
	alpha.SetKey(100,1.0f);
	alpha.SetKey(300,0.0f);

	angle.SetKey(0,180.0f);
	angle.SetKey(100,360.0f);

	nangle.SetKey(0,0.0f);
	nangle.SetKey(50,1.0f);

	for(std::vector<CObjMesh*>::iterator it = fish.all.begin(); it != fish.all.end();++it )
	{
		(*it)->ShadowFlag = FALSE;
	}
}
VOID TenYen::NeckAngle(D3DXVECTOR3* p,float r)
{
	D3DXMATRIX m;
	D3DXVECTOR3 mp(fish.Null.mWorld._41,fish.Null.mWorld._42,fish.Null.mWorld._43);
	D3DXMatrixRotationY(&m,-D3DXToRadian(fish.Null.YPR.y));
	D3DXVECTOR3 v,N(*p - mp );
	D3DXVec3Normalize(&N,&N);
	D3DXVec3TransformCoord(&v,&N,&m);
	float y = D3DXToDegree(atan2(v.x,v.z));
	float fy = fabsf(y);
	float by = 0.0f;
	if(fy > 50.0f)
	{
		by = fy - 50.0f; 
		if(by > 30.0f){by = 30.0f;}
		if(y > 0.0f)
		{
			by *= 1.0f; 
			y= 50.0f;
		}
		else
		{
			by *= -1.0f; 
			y= -50.0f;
		}
	}
	neck = y * r;
	body = by * r;
}
VOID TenYen::Set()
{
	if(P->FM.EventFlag >= TL_GOOD_BYE)
	{
		flag = 2; 
	}
	if(P->FM.iGetedFlag(ITEM_TENYEN))
	{
		flag = 3;
	}
}

VOID TenYen::Update()
{

	if( flag == 0 )
	{
		fish.drawSkip = TRUE;
	
		if( P->obj.objPos.z < 28.0f )
		{
			P->FM.EventFlag = TL_GOOD_BYE;
			fish.drawSkip = FALSE;
			flag = 1;
		}
	}
	else if( flag == 1 )
	{
	

		frame++;
		if(frame > alpha.MaxKey())
		{
			flag = 2; 
		}
		//首ふり
		D3DXVECTOR3 mp = D3DXVECTOR3(fish.Null.mWorld._41,fish.Null.mWorld._42,fish.Null.mWorld._43)+
		D3DXVECTOR3(-0.2f,0.0f,2.0f);
	
		NeckAngle(&mp,nangle.Val1(frame));
		fish.Null.YPR.y = angle.Val1(frame);
		fish.Null.objPos.z = posz.Val1(frame);
		fish.MeshCol(&D3DXVECTOR4(1.0f,1.0f,1.0f,alpha.Val1(frame)));

		if(frame > 100)
		{
			fish.MotType = fish_anim::FM_WALK;
	
		}
		else
		{
			fish.MotType = fish_anim::FM_WAIT;
		}


		fish.Update(ML);
		fish.body.YPR.y += body;
		fish.head.YPR.y += neck;
	}	
	else if( flag == 2 )
	{		
		//魚けし
		fish.drawSkip = TRUE;
	}
}
VOID TenYen::draw()
{
	fish.draw(ML);
}

//======================================
//本館
//======================================
Honkan::cMado::cMado(){}
const TCHAR *Honkan::name(){return _T("Honkan");}
Honkan::Honkan()
{	
	//建物
	Msh.push_back(&m_pRyokan);
	m_pRyokan.Type(x_ryokan);
	m_pRyokan .ShadowFlag=FALSE;

	Msh.push_back(&m_pIriGuti);
	m_pIriGuti.Type(x_iriguti);
	Msh.push_back(&m_pDoor);  
	m_pDoor.Type(x_irigutidoor);		
	//入り口
	m_pIriGuti.SetPare(&m_pRyokan.mWorld);
	m_pIriGuti.objPos= D3DXVECTOR3(0,1.5f,-10.0f);
	m_pIriGuti.ShadowFlag=FALSE;

	m_pDoor.objPos=D3DXVECTOR3(-1.3f,0,3.64f);
	m_pDoor.SetPare(&m_pIriGuti.mWorld);
	m_pDoor.ShadowFlag=FALSE;
		
	Mad(&m_cMado[0],&D3DXVECTOR3(8.0f,3.0f,-10.0f));
	Mad(&m_cMado[1],&D3DXVECTOR3(8.0f,8.0f,-10.0f));
	Mad(&m_cMado[2],&D3DXVECTOR3(8.0f,13.0f,-10.0f));
	Mad(&m_cMado[3],&D3DXVECTOR3(15.0f,8.0f,-10.0f));
	Mad(&m_cMado[4],&D3DXVECTOR3(15.0f,13.0f,-10.0f));
	Mad(&m_cMado[5],&D3DXVECTOR3(-8.0f,8.0f,-10.0f));
	Mad(&m_cMado[6],&D3DXVECTOR3(-8.0f,13.0f,-10.0f));
	Mad(&m_cMado[7],&D3DXVECTOR3(-15.0f,8.0f,-10.0f));
	Mad(&m_cMado[8],&D3DXVECTOR3(-15.0f,13.0f,-10.0f));
}	
VOID Honkan::Mad(cMado* mado,D3DXVECTOR3* Pos)
{
	//窓枠
	Msh.push_back(&mado->m_pMado);
	mado->m_pMado.Type(x_mado);
	mado->m_pMado.SetPare(&m_pRyokan.mWorld);
	mado->m_pMado.objPos = *Pos;
	mado->m_pMado.ShadowFlag=FALSE;
	//窓ガラス

	Msh.push_back(&mado->m_pCube);
	mado->m_pCube.Type(x_cube);
	mado->m_pCube.SetPare(&mado->m_pMado.mWorld);
	mado->m_pCube.ShadowFlag=FALSE;		
	mado->m_pCube.objScal=D3DXVECTOR3(6.0f,4.8f,0.1f);
	mado->m_pCube.MeshCol=D3DXVECTOR4(0.5f,0.5f,0.5f,0.1f);		
}
//======================================
//窓ガラス
//======================================
const TCHAR *GenGlass::name(){return _T("GenGlass");}
GenGlass::GenGlass()
{
	Msh.push_back(&glass);
	glass.Type(x_cube);
	glass.MeshCol = D3DXVECTOR4(0.8f,0.8f,1.0f,0.5f);
	glass.objScal=D3DXVECTOR3(11.3f,4.3f,0.1f);
	glass.ShadowFlag = FALSE;
}
//======================================
//月
//======================================
const TCHAR *Moon::name(){return _T("Moon");}
Moon::Moon()
{
	moon.Type(x_sphere);
	moon.ShadowFlag = FALSE;
	moon.BloomColor = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
//	moon.objPos = D3DXVECTOR3(0.0f,36.0f,26.0f);
	moon.SpCol.w = 0.0f;
	moon.SpColm = 1.0f;	
	moon.HitMode(CT_SPHERE,CB_PLUS);
	Msh.push_back(&moon);

	flag = 0;
}
VOID Moon::Update()
{

	if( moon.HitObj.Reaction == 2 )
	{
		flag = 1;
	}
	if(flag == 1)
	{

		if(moon.objPos.y > -2.0f)
		{
			moon.objPos.y -= 0.1f;
		}
	}

}

//======================================
//???
//======================================
const TCHAR *Case::name(){return _T("Case");}
Case::Case()
{
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.drawSkip = TRUE;
	Msh.push_back(&hitbox);

	paper.SetPare(&hitbox.mWorld);
	paper.YPR = D3DXVECTOR3(90.0f,20.0f,0.0f);
	paper.objScal =  D3DXVECTOR3(0.3f,0.5f,0.2f);
	paper.objPos =  D3DXVECTOR3(0.0f,0.01f,0.0f);
	paper.MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
	Fvf.push_back(&paper);

	text.init(this);
	text.s(_T("新聞紙が落ちている"));
	text.s(_T("新聞を読んだ"));
	text.s(_T("[女児誘拐監禁事件犯人死亡]"));
	text.s(_T("女児誘拐事件の犯人とされる建築業の男が\n犯行自供後死亡した。"));
	text.s(_T("死因は高度のストレスによる心不全。"));
	text.s(_T("なお監禁場所は供述せず"));
	text.s(_T("犯人拘束から長く経過しており\n誘拐された女児の安否は絶望視されている"));
	text.s(_T("写真の女の子はあの幽霊に似ている"));
	text.s(_T("・・・・・"));
	text.s(_T("もう一度旅館内を調べてみるか？"));



}

VOID Case::Update()
{
	if(P->FM.EventFlag >= TL_GOOD_BYE)
	if(hitbox.HitObj.Reaction == 1)
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	{
		if(P->FM.EventFlag == TL_GOOD_BYE)
		{
			P->FM.EventFlag = TL_READ_TIPS;
		}
		text.StartText(P);
	}
	text.Update(P,ML);
}
