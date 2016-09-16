//アンカーオブジェクト
Anchor::Anchor()
{
	Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pNextAnc = NULL;	
	use = TRUE;
}
//敵オブジェクト
const TCHAR* Enemy::name(){return _T("Enemy");}
//コンストラクタ
Enemy::Enemy()
{
	//エリアの当たり判定オブジェクト
	Msh.push_back(&EriaHit);
	EriaHit.Type(x_sphere);
	EriaHit.HitMode(CT_SPHERE,CB_NONE);
	EriaHit.objScal= D3DXVECTOR3(0.2f,0.2f,0.2f);
	EriaHit.objPos = D3DXVECTOR3(0.0f,0.35f,0.0f);
	EriaHit.YPR.y = 0.0f;
	EriaHit.drawSkip = TRUE;
	//弾当たり判定オブジェクト
	Msh.push_back(&BulletHit);
	BulletHit.Type(x_cube);
	BulletHit.objPos = D3DXVECTOR3(0.0f,0.3f,0.0f);
	BulletHit.objScal= D3DXVECTOR3(1.0f,7.0f,1.0f);
	BulletHit.SetPare(&EriaHit.mWorld);
	BulletHit.MeshCol = D3DXVECTOR4(0.5f,0.5f,0.5f,0.5f);
	BulletHit.HitMode(CT_OBB,CB_NONE);
	BulletHit.drawSkip = TRUE;
	//追跡アンカー
	pAnc.push_back(new Anchor);
	pAnc.push_back(new Anchor);
	stalkAnc = pAnc[0];
	EyeAnc = pAnc[0];
	pAnc[0]->pNextAnc = pAnc[1];
	pAnc[0]->Pos = EriaHit.objPos;
	//アンカーデバッグ表示
	an.Type(x_cube);
	an.drawSkip = TRUE;
	Msh.push_back(&an);
	annum = 0;	
	//被弾しないように
	Muteki = 0;
	//攻撃開始中
	AtCount = 0;
	//攻撃中フラグ
	AtFlag = FALSE;
	Atvec = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//BGM
	bgm.Set(wav_fish);
	bgm.m_bLoop = TRUE;
	//voice
	voice.Set(wav_voice);
	voice.m_b3DSound = TRUE;
	voice.m_bLoop = TRUE;
	//パーティクル
	Prt.push_back(&part);
	part.objScal = D3DXVECTOR3(0.5f,1.0f,1.0f);
	part.MeshCol = D3DXVECTOR4(0.0f,0.0f,10.0f,10.0f);
	part.BloomColor = D3DXVECTOR4(0.0f,0.0f,10.0f,10.0f);
	part.Ext = 0.5f;
	part.Height = 1.0f;
	part.Speed = 0.02f;
	part.PrtTime = 1.0f;
	part.SetTex(bmp_fire);
	//首振り
	neck = 0.0f;
	body = 0.0f;

	Line = FALSE;

	//速度
	speed = 2.0f;
	//待機時間
	flow = 50;
}
//デストラクタ
Enemy::~Enemy()
{
	//プレイヤーの銃弾アタッチをリセットする
	P->ResetBullet();
	//アンカーの破棄
	for(std::vector<Anchor*>::iterator it = pAnc.begin();it != pAnc.end(); ++it)
	{
		SAFE_DELETE(*it);
	}
}
//強さ
VOID Enemy::Strength( int Level )
{
	switch( Level )
	{
	case 0:
		speed = 1.0f;
		flow = 100;
		break;
	case 1:
		speed = 2.0f;
		flow = 10;
		break;
	default:
		speed = 1.0f;
		flow = 100;
		break;
	}
}
//セット
VOID Enemy::Set()
{
	EriaHit.objPos = P->FM.enemy.pos;	
	EriaHit.YPR.y = P->FM.enemy.rot;
	pAnc[0]->Pos  = P->FM.enemy.pos;
}
//視線のあたり判定
BOOL Enemy::EyeHit(Segmet* sgm)
{
	//敵とプレイヤーの間に障害物があるか
	for(std::vector<CollObj*>::iterator it = m_pPare->HitObj.begin(); it != m_pPare->HitObj.end(); ++it)
	{
		if((*it)->cBack == CB_PLUS)
		{
			if(ML->Col.Hit(sgm,(*it))){return TRUE;}
		}
	}	
	return FALSE;
}
//首回し
VOID Enemy::AngleNeck(float t)
{
	D3DXMATRIX m;
	D3DXMatrixRotationY(&m,-D3DXToRadian(P->FM.enemy.rot));
	D3DXVECTOR3 v,N(P->obj.objPos - P->FM.enemy.pos );
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
	neck = y * t;
	body = by * t;
}
//プレイヤーを探す
VOID Enemy::ModeSearch()
{	
	AngleNeck(1.0f);
	fish.drawSkip = FALSE;
	//攻撃されると攻撃モードに
	if(BulletHit.HitObj.Reaction == 2)
	{
		P->FM.enemy.mode = Enemy::MODE_STALK_ATTACK;
	}
}

//細かな操作
VOID Enemy::ModeManual()
{
	fish.MotType = fish_anim::FM_WALK;
}

//プレイヤーを追跡
VOID Enemy::ModeStalking()
{	
	bgm.Start(ML);
	voice.Start(ML);
	//敵とプレイヤーをつなぐ線分
	Segmet seg;
	seg.cType = CT_SEGMET;
	*seg.Len() = *EriaHit.HitObj.Len();
	*seg.Vec() = P->obj.objPos;
	*seg.Pos() = EriaHit.objPos;
	//遮断していない場合
	Line = EyeHit(&seg);
	if(!Line)
	{
		if(pAnc.size() != 2)
		{
			for(std::vector<Anchor*>::iterator it = pAnc.begin();it != pAnc.end(); ++it)
			{
				SAFE_DELETE(*it);
			}
			pAnc.clear();
			pAnc.push_back(new Anchor);
			pAnc.push_back(new Anchor);
		}
		//アンカー0にプレイヤーの位置に
		stalkAnc = pAnc[0];
		EyeAnc = pAnc[0];
		pAnc[0]->pNextAnc = pAnc[1];
		pAnc[0]->Pos = P->obj.objPos;		
	}
	else
	{
		//アンカーが限界数を超えたら停止
		if(pAnc.size() < 100 )
		{
			//遮断されたとき新たなアンカーをセット
			*seg.Pos() = EyeAnc->Pos;	
			EyeAnc->pNextAnc->Pos = P->obj.objPos;
			//さらに遮断されたとき、使ってない要素を探し
			if(EyeHit(&seg))
			{
				EyeAnc = EyeAnc->pNextAnc;
				//使われていない要素を探し
				BOOL Flag = FALSE;
				for(std::vector<Anchor*>::iterator it = pAnc.begin();it != pAnc.end(); ++it)
				{
					if(!(*it)->use)
					{
						EyeAnc->pNextAnc = (*it);
						(*it)->use = TRUE;
						Flag = TRUE;
						break;
					}
				}
				//空きがなかった場合、新たに生成
				if(!Flag)
				{
					pAnc.push_back(new Anchor);
					EyeAnc->pNextAnc = pAnc[pAnc.size() - 1];
				}
			}
		}
		else
		{
			//見失う
			fish.MotType = fish_anim::FM_WAIT;
			EyeAnc->pNextAnc = NULL;
			D3DXVECTOR3 v(stalkAnc->Pos - P->FM.enemy.pos);
			D3DXVec3Normalize(&v,&v);
			P->FM.enemy.rot = D3DXToDegree(atan2f(v.x,v.z));

		}
		//アンカーに追いついた場合次の目標を追う(アンカーと重なる)
		if( D3DXVec3LengthSq(&(stalkAnc->Pos - EriaHit.objPos)) < 0.0001f )
		{
			if(stalkAnc->use == TRUE)
			{
				if(stalkAnc->pNextAnc != NULL)
				{
					stalkAnc->use = FALSE;
					stalkAnc = stalkAnc->pNextAnc; 	
				}
				//つぎのアンカーが存在しない場合見失う
				else{P->FM.enemy.mode = MODE_SEARCH;}
			} 
		}
	}	
}
//攻撃
VOID Enemy::ModeAttack()
{
	//カウントが0以下なら待機
	if(AtCount < 0)
	{
		
		//待機中
		AtCount++; 
		//首回し
		float a = (100.0f + (float)AtCount)/100.0f;
		AngleNeck(a);
		//アニメーション
		fish.MotType = fish_anim::FM_WAIT;
	}
	else
	{
		//首を元に戻す
		neck = 0.0f;
		body = 0.0f;
		//攻撃
		if(AtFlag)
		{
			//攻撃態勢
			fish.MotType = fish_anim::FM_ATTACK;
			AtCount--;
			//攻撃終了
			if(AtCount <= 0 )
			{
				//待機させる
				AtCount = -flow;
				AtFlag = FALSE;	
			}
			//攻撃
			else if( AtCount > 60)
			{
				//進む
				P->FM.enemy.pos+= Atvec * 0.02f * speed;
				//デバッグ
				EriaHit.MeshCol  = D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f);
				//攻撃ヒット
				if(EriaHit.HitObj.Reaction == 1)
				{		
					AtCount = 0;
					P->FM.enemy.mode = MODE_GAMEOVER;	
					fish.frame = 0; 
					AtFlag = FALSE;
					bgm.Stop(ML,0.0f);
				}
			}
		}
		else
		{
			//プレイヤーもしくはアンカーを追う	
			D3DXVECTOR3 v(stalkAnc->Pos - P->FM.enemy.pos);
			D3DXVec3Normalize(&v,&v);
			P->FM.enemy.pos+= v * 0.01f * speed;
			P->FM.enemy.rot = D3DXToDegree(atan2f(v.x,v.z));
			//アニメーション
			fish.MotType = fish_anim::FM_WALK;
			//遮断物がなく、近い場合攻撃に入る
			if(!Line)
			{
				if(1.2f > D3DXVec3LengthSq(&(P->obj.objPos - P->FM.enemy.pos)))
				{
					Atvec = v;
					AtFlag = TRUE;
					AtCount = 100;
					fish.frame = 0;
				}
			}
		}
	}
}

//死亡処理
VOID Enemy::ModeDead()
{
	//消滅まで停止
	P->Mode = Personal::MODE_DAMAGE;	
	//消滅演出
	float a = (100.0f - (float)AtCount)/100.0f;
	bgm.m_fVol = a;
	bgm.Filter.Frequency = a;
	bgm.Start(ML);
	voice.m_fVol = a;
	voice.Filter.Frequency = a;
	voice.Start(ML);
	fish.MeshCol(&D3DXVECTOR4(1.0f,1.0f,1.0f,a));
	//首回し
	AngleNeck(1.0f);
	//アニメーション
	fish.MotType = fish_anim::FM_WAIT;
	AtCount++;
	if(AtCount > 100)
	{
		bgm.Stop(ML,0.0f);
		voice.Stop(ML,0.0f);
		P->FM.enemy.mode = MODE_REMOVE;
		P->Mode = Personal::MODE_ACTIVE;	
		a = 0.0f;
		bgm.m_fVol = a;
		bgm.Filter.Frequency = a;
		voice.m_fVol = a;
		voice.Filter.Frequency = a;
	}
}
//当たり判定
VOID Enemy::ModeHit()
{	
	if(P->FM.enemy.mode == MODE_CLEAR)
	{
		fish.drawSkip = TRUE;
	}
	if(P->FM.enemy.mode == MODE_DEAD || P->FM.enemy.mode == MODE_CLEAR || P->FM.enemy.mode == MODE_REMOVE)
	{
		return; 
	}
	//当たり判定更新
	EriaHit.SetHit(ML);
	BulletHit.SetHit(ML);
	
	//弾との判定
	if(BulletHit.HitObj.Reaction == 2)
	{
		//食塩つきダーツを持っていた場合
	 	if(P->FM.iGetedFlag(ITEM_MASUI_DARTS))
		{
			
			if( P->FM.enemy.mode != MODE_GAMEOVER )
			{
				//連続HITしないように調整
				if(Muteki <= 0 )
				{
					Muteki = 50;
					EriaHit.MeshCol.y = 0.0f;
					if( P->FM.enemy.HP > 0 )
					{
						P->FM.enemy.HP -= 1;
					}
				}
			}
		}
	}
	//無敵時間&被ダメージ演出
	if(Muteki > 0 )
	{
		//パーティクル
		part.drawSkip = FALSE;
		part.objPos = P->FM.enemy.pos - D3DXVECTOR3(0.0f,0.4f,0.0f);

		//半透明
		float a = 0.0f;
		if(Muteki > 25){	a = ((float)Muteki - 25.0f) / 25.0f;}
		else{a = (25.0f - (float)Muteki) / 25.0f;}
		voice.Filter.Frequency = a;
		fish.MeshCol(&D3DXVECTOR4(1.0f,1.0f,1.0f,a));
		Muteki--;
	}
	else
	{
		fish.MeshCol(&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f));
		part.drawSkip = TRUE;
	}
	//死亡
	//HP0になると消滅モードになる
	if(	P->FM.enemy.HP <= 0)
	{
		AtCount = 0;
		P->FM.enemy.mode = MODE_DEAD;
		fish.MeshCol(&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f));
		bgm.Stop(ML,0.0f);
		voice.Stop(ML,0.0f);
	}
	
	/*
	//プレイヤーとの判定
	if(EriaHit.HitObj.Reaction == 1)
	{
		//押し戻し
		P->FM.enemy.pos.x += EriaHit.HitObj.vBack.x;
		P->FM.enemy.pos.z += EriaHit.HitObj.vBack.z;
	}
	//*/

	//フィールドの判定
	D3DXVECTOR3 LandVec(0.0f,0.0f,0.0f);
	for(std::vector<CollObj*>::iterator it = m_pPare->HitObj.begin(); it != m_pPare->HitObj.end(); ++it)
	{
		if((*it)->cBack == CB_PLUS)
		{
			if(ML->Col.Hit(&EriaHit.HitObj,*it))
			{
				P->FM.enemy.pos += EriaHit.HitObj.vBack;
				LandVec += EriaHit.HitObj.vBack;
			}
		}
	}
	
}
//攻撃処理
VOID Enemy::ModeGameOver()
{
	P->Mode = Personal::MODE_DAMAGE;	
	fish.MotType = fish_anim::FM_DEATH;	
	//プレイヤーの色を変える
	float c = (float)AtCount / 100.0f;
	ML->E.Tone.x = -2.0f - c * 3.0f;
	//シュー
	bgm.Filter.Frequency = 1.0f - c; 
	AtCount++;
	if(AtCount > 100)
	{

		//待機させる
		AtCount = -100;
		//プレイヤーが攻撃を受ける
		P->FM.enemy.mode = MODE_CLEAR; 
		//ゲームオーバー
		m_pPare->FldChange(new Gameover,&D3DXVECTOR3(0.0f,0.0f,0.0f),0.0f);
		ML->E.Tone.x = 1.0f;
	}
}
//更新
VOID Enemy::Update()
{	
	fish.HP = P->FM.enemy.HP;
	Strength( P->FM.enemy.Level );
	//クリアモード
	if(P->FM.enemy.mode == MODE_CLEAR || P->FM.enemy.mode == MODE_REMOVE)
	{
		
		part.drawSkip = TRUE;
		fish.drawSkip = TRUE;
		return;
	}
	//サウンド
	if(P->FM.enemy.mode == MODE_STALK_ATTACK || P->FM.enemy.mode == MODE_GAMEOVER )
	{
		bgm.Start(ML);
		voice.Start(ML);
		voice.Emi.Position = P->FM.enemy.pos;
	}	
	//プレイヤーがアクションと被ダメージでは無い時は終了
	if(!(P->Mode == Personal::MODE_ACTIVE || P->Mode == Personal::MODE_DAMAGE)){return ;}
	//モード
	switch(P->FM.enemy.mode)
	{
	case MODE_SEARCH:ModeSearch();break;
	case MODE_STALK_ATTACK:
		fish.drawSkip = FALSE;
		ModeStalking();
		ModeAttack();
		break;
	case MODE_STALK:
		fish.drawSkip = TRUE;
		ModeStalking();	
		break;
	case MODE_GAMEOVER:ModeGameOver();break;
	case MODE_DEAD:ModeDead();break;
	case MODE_MANUAL:ModeManual();break;
	
	default:break;
	}
	//当たり判定
	ModeHit();

	EriaHit.objPos  = P->FM.enemy.pos ;
	fish.Null.objPos = P->FM.enemy.pos + D3DXVECTOR3(0.0f,-0.35f,0.0f);
	fish.Null.YPR.y = P->FM.enemy.rot;
	fish.Update(ML);		
	fish.body.YPR.y += body;
	fish.head.YPR.y += neck;
/*
	//アンカーの位置デバッグ
	annum++;
	an.drawSkip = FALSE;
	an.objPos = 	pAnc[ annum % (int)pAnc.size()]->Pos;
//*/

}
//描画
VOID Enemy::draw()
{
	fish.draw(ML);
}
VOID Enemy::DebugBtn(DebugButton* db)
{
	fish.DebugBtn(db,ML);
}
VOID Enemy::DebugText(TCHAR* tt,int len)
{
	float y = 100.0f + (float)AtCount/100.0f;
	_stprintf_s(tt,len,
		_T("%s\n")
		_T("HitPoint = %d\n")
		_T("EnemyMode = %d\n")
		_T("pAnc.size = %d\n")
		_T("Muteki = %d\n")
		_T("AtFlag = %d\n")
		_T("AtCount = %d\n")
		_T("y = %f\n")
		,tt
		,P->FM.enemy.HP		
		,P->FM.enemy.mode
		,pAnc.size()
		,Muteki
		,AtFlag
		,AtCount
		,y
		);
}