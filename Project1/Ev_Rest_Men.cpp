//=========================================
//トイレメモ
//=========================================
const TCHAR *ToileMemo::name(){return _T("ToileMemo");}
ToileMemo::ToileMemo(int r)
{
	//当たり判定box
	Msh.push_back(&hitbox);
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.drawSkip = TRUE;
	//メモ
	for(int i = 0; i < MEMO_MAX; i ++)
	{
		Fvf.push_back(&memo[i]);
		memo[i].objScal = D3DXVECTOR3( 0.2f,0.2f,1.0f);
		memo[i].MeshCol = D3DXVECTOR4(0.8f,0.8f,0.8f,1.0f);
		memo[i].SetPare(&hitbox.mWorld);
	}
	memo[0].objPos = D3DXVECTOR3(-0.1f,-0.1f,0.0f);
	memo[1].objPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	memo[2].objPos = D3DXVECTOR3(0.05f,-0.05f,0.0f);
	memo[3].objPos = D3DXVECTOR3(0.5f,0.0f,0.0f);

	//テキスト
	text.init(this);
	text.s(_T("メモがたくさんはってある"));
	text.s(_T("メモにはこう書かれている"));
	text.s(_T("7/10\n個室のトイレが全て壊れているようです"));
	if(r == 0)
	{
		//テキスト正解は手前	
		text.s(_T("7/11\n知り合いの業者に直してもらいましたが、\n予算が足りず奥のトイレはそのままです"));
		text.s(_T("7/12\n壊れているトイレの隣のトイレが壊れたようです"));
	}
	if(r == 1)
	{
		//テキスト正解は真ん中		
		text.s(_T("7/11\n知り合いの業者に直してもらいましたが、\n予算が足りず奥のトイレはそのままです"));
		text.s(_T("7/12\n壊れているトイレの隣じゃない方のトイレが壊れたようです"));
	}
	if(r == 2)
	{
		//テキスト正解は奥
		text.s(_T("7/11\n知り合いの業者に直してもらいましたが、\n予算が足りず手前のトイレはそのままです"));
		text.s(_T("7/12\n壊れているトイレの隣のトイレが壊れたようです"));
	}
	text.s(_T("7/15\n202号室のお客様がルームキーをトイレに落としたようです\n使えるトイレに落ちていると思うので回収お願いします"));
}
VOID ToileMemo::Update()
{
	if(P->Mode != Personal::MODE_EVENT)
	if(hitbox.HitObj.Reaction == 1)
	if(P->Check)
	{
		text.StartText(P);
	}
	text.Update(P,ML);
}
//=========================================
//男子トイレドア
//=========================================
const TCHAR *Rest_Men_door::name(){return _T("Rest_Men_door");}
//鍵青
Rest_Men_door::Rest_Men_door()
{
	//ドア
	Msh.push_back(&pDoor);
	pDoor.Type(x_rest_door);
	pDoor.ShadowFlag=FALSE;
	pDoor.HitMode(CT_OBB,CB_PLUS);
	//鍵
	Msh.push_back(&pGreen);
	pGreen.Type(x_cube);
	pGreen.SetPare(&pDoor.mWorld);
	pGreen.objPos=D3DXVECTOR3(0.02f,0.775f,-0.764f);//青
	pGreen.objScal=D3DXVECTOR3(0.10f,0.05f,0.04f);
	pGreen.MeshCol=D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f);
	pGreen.ShadowFlag=FALSE;
	Msh.push_back(&pRed);
	pRed.Type(x_cube);
	pRed.ShadowFlag=FALSE;
	pRed.SetPare(&pGreen.mWorld);
	pRed.objPos=D3DXVECTOR3(-0.00f,0.00f,0.50f);
	pRed.MeshCol=D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f);
	pGreen.objPos.z=-0.764f;
	//アニメーション
	frame = 0;
	flag = 0;
	door.SetKey(0,0.0f);
	door.SetKey(50,90.0f);
	//Se
	gan.Set(wav_keylock);
	gan.m_b3DSound = TRUE;
}
VOID Rest_Men_door::Update()
{
	//SE
	gan.Emi.Position = pDoor.objPos;
	//あいてるときは当たり判定を消す
	if(flag == 0)
	{
		pDoor.HitMode(CT_OBB,CB_PLUS);
	}
	else
	{
		pDoor.HitMode(CT_OBB,CB_NONE);
	}
	//当たり判定
	if(pDoor.HitObj.Reaction == 1)
	{
		if(P->Check)
		{
			if(flag == 0){flag = 1;}
			if(flag == 2){flag = 3;}
		}
	}
	//ドアの当たり判定
	if(pDoor.HitObj.Reaction == 2)
	{
		P->AtcBullet(&pDoor.mWorld);
	}
	if(flag == 1)
	{
		frame++;
		if(frame > 48){flag = 2;}
	}
	if(flag == 3)
	{
		frame--;
		if(frame < 1)
		{
			gan.Start(ML);
			flag = 0;
		}
	}
	pDoor.YPR.y = door.Val(frame);
}
//=========================================
//トイレ	
//=========================================
const TCHAR *name(){return _T("Rest_Men_Toile");}
Rest_Men_Toile::Rest_Men_Toile(int f)
{
	//トイレ
	Msh.push_back(&pToile);
	pToile.Type(x_toile);
	pToile.HitMode(CT_OBB,CB_PLUS);
	pToile.Bias = 0.1f;
	//当たり判定
	Msh.push_back(&hitbox);
	hitbox.Type(x_cube);
	hitbox.SetPare(&pToile.mWorld);
	hitbox.objScal = D3DXVECTOR3(1.0f,1.0f,3.0f);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.drawSkip = TRUE;
	//ふた
	Msh.push_back(&pHuta);
	pHuta.Type(x_tcover);
	pHuta.SetPare(&pToile.mWorld);
	pHuta.objPos.y=0.35f;
	pHuta.MeshCol=D3DXVECTOR4(2.5f,2.5f,2.5f,1.0f);
	pHuta.SpColm=0.0f;
	//テキスト
	text.init(this);
	text.s(_T("トイレを開けますか？\n開ける\n開けない"),1,2);
	//トイレを調べる
	text1.init(this);
	text1.s(_T("トイレの中に何か落ちている"));
	text1.s(_T("【202号室の鍵】を手に入れた"));
	//便座アニメーション
	flag = 0;
	hutaframe = 0;
	rot.SetKey(0,0.0f);
	rot.SetKey(10,-90.0f);
	//gt
	gtframe = 0;
	prot.SetKey(0,0.0f);
	prot.SetKey(10,190.0f);
	//ゲームオーバーか鍵取得
	GOFlag = f;

	//SE
	//ふたのしまる音
	gan.Set(wav_keylock);
	gan.m_b3DSound = TRUE;
	Snd.push_back(&gan);
	//びっくり音
	oop.Set(wav_oop);
	Snd.push_back(&oop);
	//水音
	water.Set(wav_water);
	Snd.push_back(&water);
	
}
VOID Rest_Men_Toile::Set()
{
	//吸い込まれるアニメーション
	pos.SetKey(10,pToile.objPos + D3DXVECTOR3(-0.2f,1.0f,0.0f));
	pos.SetKey(50,pToile.objPos + D3DXVECTOR3(-0.2f,0.6f,0.0f));
	//SE
	gan.Emi.Position =	pToile.objPos;
}

VOID Rest_Men_Toile::Update()
{
	//調べる
	if(P->Mode != Personal::MODE_EVENT)
	if(hitbox.HitObj.Reaction == 1)
	if(P->Check)
	{
		//テキストを進める
		if(flag == 0)
		{
			text.StartText(P);
			pos.SetKey(0,P->obj.objPos);

			D3DXVECTOR3 N(pToile.objPos - P->obj.objPos);
			D3DXVec3Normalize(&N,&N);
			P->obj.YPR.y = D3DXToDegree(atan2f(N.x,N.z));
		}
		//アイテム取得パターン
		if( GOFlag == 0 )
		{
			//鍵を持ってないと
			if(flag == 2)
			{
				if(!P->FM.iGetedFlag(ITEM_202_KEY)){text1.StartText(P);}
				else{flag = 3;}
			}
		}		
	}
	//テキスト
	int t = text.Update(P,ML);
	//鍵の取得
	if( text1.Update(P,ML) == 1 )
	{
		if(!P->FM.iGetedFlag(ITEM_202_KEY))
		{
			P->FM.iGet(ITEM_202_KEY);
			P->CheckSE(Personal::SE_ITEM);
		}
	}
	//ふた開く
	if(t == 1){flag = 1;}
	//アニメーション
	if(flag == 1)
	{
		//ふた開く
		hutaframe++;
		if(hutaframe > 8)
		{
			gan.Start(ML);
			if(GOFlag != 0 ){oop.Start(ML);}
			flag = 2;
		}
	}
	//ふたを閉じる
	if(GOFlag == 0 )
	{
		if(P->FM.iGetedFlag(ITEM_202_KEY))
		{
			if(flag == 3)
			{		
				hutaframe--;
				if(hutaframe < 1)
				{
					gan.Start(ML);
					flag = 0;
				}
			}
		}
	}
	//死亡パターン
	else
	{
		if(flag == 2)
		{
			//水音
			water.Start(ML);
			//トイレの当たり判定を消滅
			pToile.HitMode(CT_OBB,CB_NONE);
			P->Mode = Personal::MODE_EVENT;
			P->gt.MotionType = gt_Anim::Motion_Wait;
			//gtひっくり返って落っこちる
			gtframe++;
			P->obj.objPos = pos.Val(gtframe);
			P->obj.YPR.x = prot.Val(gtframe);
			if( gtframe> 8 ){flag = 3;}
		}
		if(flag == 3)
		{
			//回転ながら落ちる
			gtframe++;
			//音
			if(gtframe== 145){	gan.Start(ML);	}
			//ふたを閉める
			if(gtframe> 150){flag = 4;}
			P->obj.objPos = pos.Val1(gtframe);
			P->obj.YPR.y += 10.0f;
		}
		if(flag == 4)
		{
			//ふた閉まる
			hutaframe--;
			if(hutaframe < 1){flag = 5;}
		}
		if(flag == 5)
		{
			//ゲームオーバー
			P->obj.YPR =D3DXVECTOR3(0.0f,0.0f,0.0f); 
			m_pPare->FldChange(new Gameover,&D3DXVECTOR3(0.0f,0.0f,0.0f),0.0f);
		}
	}
	//ふたのアニメ
	pHuta.YPR.x = rot.Val(hutaframe);
}
VOID Rest_Men_Toile::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,
		_T("%s")
		_T("GOFlag = %d\n")
		,t
		,GOFlag
		);
}
