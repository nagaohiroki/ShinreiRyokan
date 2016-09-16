//�A���J�[�I�u�W�F�N�g
Anchor::Anchor()
{
	Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pNextAnc = NULL;	
	use = TRUE;
}
//�G�I�u�W�F�N�g
const TCHAR* Enemy::name(){return _T("Enemy");}
//�R���X�g���N�^
Enemy::Enemy()
{
	//�G���A�̓����蔻��I�u�W�F�N�g
	Msh.push_back(&EriaHit);
	EriaHit.Type(x_sphere);
	EriaHit.HitMode(CT_SPHERE,CB_NONE);
	EriaHit.objScal= D3DXVECTOR3(0.2f,0.2f,0.2f);
	EriaHit.objPos = D3DXVECTOR3(0.0f,0.35f,0.0f);
	EriaHit.YPR.y = 0.0f;
	EriaHit.drawSkip = TRUE;
	//�e�����蔻��I�u�W�F�N�g
	Msh.push_back(&BulletHit);
	BulletHit.Type(x_cube);
	BulletHit.objPos = D3DXVECTOR3(0.0f,0.3f,0.0f);
	BulletHit.objScal= D3DXVECTOR3(1.0f,7.0f,1.0f);
	BulletHit.SetPare(&EriaHit.mWorld);
	BulletHit.MeshCol = D3DXVECTOR4(0.5f,0.5f,0.5f,0.5f);
	BulletHit.HitMode(CT_OBB,CB_NONE);
	BulletHit.drawSkip = TRUE;
	//�ǐՃA���J�[
	pAnc.push_back(new Anchor);
	pAnc.push_back(new Anchor);
	stalkAnc = pAnc[0];
	EyeAnc = pAnc[0];
	pAnc[0]->pNextAnc = pAnc[1];
	pAnc[0]->Pos = EriaHit.objPos;
	//�A���J�[�f�o�b�O�\��
	an.Type(x_cube);
	an.drawSkip = TRUE;
	Msh.push_back(&an);
	annum = 0;	
	//��e���Ȃ��悤��
	Muteki = 0;
	//�U���J�n��
	AtCount = 0;
	//�U�����t���O
	AtFlag = FALSE;
	Atvec = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//BGM
	bgm.Set(wav_fish);
	bgm.m_bLoop = TRUE;
	//voice
	voice.Set(wav_voice);
	voice.m_b3DSound = TRUE;
	voice.m_bLoop = TRUE;
	//�p�[�e�B�N��
	Prt.push_back(&part);
	part.objScal = D3DXVECTOR3(0.5f,1.0f,1.0f);
	part.MeshCol = D3DXVECTOR4(0.0f,0.0f,10.0f,10.0f);
	part.BloomColor = D3DXVECTOR4(0.0f,0.0f,10.0f,10.0f);
	part.Ext = 0.5f;
	part.Height = 1.0f;
	part.Speed = 0.02f;
	part.PrtTime = 1.0f;
	part.SetTex(bmp_fire);
	//��U��
	neck = 0.0f;
	body = 0.0f;

	Line = FALSE;

	//���x
	speed = 2.0f;
	//�ҋ@����
	flow = 50;
}
//�f�X�g���N�^
Enemy::~Enemy()
{
	//�v���C���[�̏e�e�A�^�b�`�����Z�b�g����
	P->ResetBullet();
	//�A���J�[�̔j��
	for(std::vector<Anchor*>::iterator it = pAnc.begin();it != pAnc.end(); ++it)
	{
		SAFE_DELETE(*it);
	}
}
//����
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
//�Z�b�g
VOID Enemy::Set()
{
	EriaHit.objPos = P->FM.enemy.pos;	
	EriaHit.YPR.y = P->FM.enemy.rot;
	pAnc[0]->Pos  = P->FM.enemy.pos;
}
//�����̂����蔻��
BOOL Enemy::EyeHit(Segmet* sgm)
{
	//�G�ƃv���C���[�̊Ԃɏ�Q�������邩
	for(std::vector<CollObj*>::iterator it = m_pPare->HitObj.begin(); it != m_pPare->HitObj.end(); ++it)
	{
		if((*it)->cBack == CB_PLUS)
		{
			if(ML->Col.Hit(sgm,(*it))){return TRUE;}
		}
	}	
	return FALSE;
}
//���
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
//�v���C���[��T��
VOID Enemy::ModeSearch()
{	
	AngleNeck(1.0f);
	fish.drawSkip = FALSE;
	//�U�������ƍU�����[�h��
	if(BulletHit.HitObj.Reaction == 2)
	{
		P->FM.enemy.mode = Enemy::MODE_STALK_ATTACK;
	}
}

//�ׂ��ȑ���
VOID Enemy::ModeManual()
{
	fish.MotType = fish_anim::FM_WALK;
}

//�v���C���[��ǐ�
VOID Enemy::ModeStalking()
{	
	bgm.Start(ML);
	voice.Start(ML);
	//�G�ƃv���C���[���Ȃ�����
	Segmet seg;
	seg.cType = CT_SEGMET;
	*seg.Len() = *EriaHit.HitObj.Len();
	*seg.Vec() = P->obj.objPos;
	*seg.Pos() = EriaHit.objPos;
	//�Ւf���Ă��Ȃ��ꍇ
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
		//�A���J�[0�Ƀv���C���[�̈ʒu��
		stalkAnc = pAnc[0];
		EyeAnc = pAnc[0];
		pAnc[0]->pNextAnc = pAnc[1];
		pAnc[0]->Pos = P->obj.objPos;		
	}
	else
	{
		//�A���J�[�����E���𒴂������~
		if(pAnc.size() < 100 )
		{
			//�Ւf���ꂽ�Ƃ��V���ȃA���J�[���Z�b�g
			*seg.Pos() = EyeAnc->Pos;	
			EyeAnc->pNextAnc->Pos = P->obj.objPos;
			//����ɎՒf���ꂽ�Ƃ��A�g���ĂȂ��v�f��T��
			if(EyeHit(&seg))
			{
				EyeAnc = EyeAnc->pNextAnc;
				//�g���Ă��Ȃ��v�f��T��
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
				//�󂫂��Ȃ������ꍇ�A�V���ɐ���
				if(!Flag)
				{
					pAnc.push_back(new Anchor);
					EyeAnc->pNextAnc = pAnc[pAnc.size() - 1];
				}
			}
		}
		else
		{
			//������
			fish.MotType = fish_anim::FM_WAIT;
			EyeAnc->pNextAnc = NULL;
			D3DXVECTOR3 v(stalkAnc->Pos - P->FM.enemy.pos);
			D3DXVec3Normalize(&v,&v);
			P->FM.enemy.rot = D3DXToDegree(atan2f(v.x,v.z));

		}
		//�A���J�[�ɒǂ������ꍇ���̖ڕW��ǂ�(�A���J�[�Əd�Ȃ�)
		if( D3DXVec3LengthSq(&(stalkAnc->Pos - EriaHit.objPos)) < 0.0001f )
		{
			if(stalkAnc->use == TRUE)
			{
				if(stalkAnc->pNextAnc != NULL)
				{
					stalkAnc->use = FALSE;
					stalkAnc = stalkAnc->pNextAnc; 	
				}
				//���̃A���J�[�����݂��Ȃ��ꍇ������
				else{P->FM.enemy.mode = MODE_SEARCH;}
			} 
		}
	}	
}
//�U��
VOID Enemy::ModeAttack()
{
	//�J�E���g��0�ȉ��Ȃ�ҋ@
	if(AtCount < 0)
	{
		
		//�ҋ@��
		AtCount++; 
		//���
		float a = (100.0f + (float)AtCount)/100.0f;
		AngleNeck(a);
		//�A�j���[�V����
		fish.MotType = fish_anim::FM_WAIT;
	}
	else
	{
		//������ɖ߂�
		neck = 0.0f;
		body = 0.0f;
		//�U��
		if(AtFlag)
		{
			//�U���Ԑ�
			fish.MotType = fish_anim::FM_ATTACK;
			AtCount--;
			//�U���I��
			if(AtCount <= 0 )
			{
				//�ҋ@������
				AtCount = -flow;
				AtFlag = FALSE;	
			}
			//�U��
			else if( AtCount > 60)
			{
				//�i��
				P->FM.enemy.pos+= Atvec * 0.02f * speed;
				//�f�o�b�O
				EriaHit.MeshCol  = D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f);
				//�U���q�b�g
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
			//�v���C���[�������̓A���J�[��ǂ�	
			D3DXVECTOR3 v(stalkAnc->Pos - P->FM.enemy.pos);
			D3DXVec3Normalize(&v,&v);
			P->FM.enemy.pos+= v * 0.01f * speed;
			P->FM.enemy.rot = D3DXToDegree(atan2f(v.x,v.z));
			//�A�j���[�V����
			fish.MotType = fish_anim::FM_WALK;
			//�Ւf�����Ȃ��A�߂��ꍇ�U���ɓ���
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

//���S����
VOID Enemy::ModeDead()
{
	//���ł܂Œ�~
	P->Mode = Personal::MODE_DAMAGE;	
	//���ŉ��o
	float a = (100.0f - (float)AtCount)/100.0f;
	bgm.m_fVol = a;
	bgm.Filter.Frequency = a;
	bgm.Start(ML);
	voice.m_fVol = a;
	voice.Filter.Frequency = a;
	voice.Start(ML);
	fish.MeshCol(&D3DXVECTOR4(1.0f,1.0f,1.0f,a));
	//���
	AngleNeck(1.0f);
	//�A�j���[�V����
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
//�����蔻��
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
	//�����蔻��X�V
	EriaHit.SetHit(ML);
	BulletHit.SetHit(ML);
	
	//�e�Ƃ̔���
	if(BulletHit.HitObj.Reaction == 2)
	{
		//�H�����_�[�c�������Ă����ꍇ
	 	if(P->FM.iGetedFlag(ITEM_MASUI_DARTS))
		{
			
			if( P->FM.enemy.mode != MODE_GAMEOVER )
			{
				//�A��HIT���Ȃ��悤�ɒ���
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
	//���G����&��_���[�W���o
	if(Muteki > 0 )
	{
		//�p�[�e�B�N��
		part.drawSkip = FALSE;
		part.objPos = P->FM.enemy.pos - D3DXVECTOR3(0.0f,0.4f,0.0f);

		//������
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
	//���S
	//HP0�ɂȂ�Ə��Ń��[�h�ɂȂ�
	if(	P->FM.enemy.HP <= 0)
	{
		AtCount = 0;
		P->FM.enemy.mode = MODE_DEAD;
		fish.MeshCol(&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f));
		bgm.Stop(ML,0.0f);
		voice.Stop(ML,0.0f);
	}
	
	/*
	//�v���C���[�Ƃ̔���
	if(EriaHit.HitObj.Reaction == 1)
	{
		//�����߂�
		P->FM.enemy.pos.x += EriaHit.HitObj.vBack.x;
		P->FM.enemy.pos.z += EriaHit.HitObj.vBack.z;
	}
	//*/

	//�t�B�[���h�̔���
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
//�U������
VOID Enemy::ModeGameOver()
{
	P->Mode = Personal::MODE_DAMAGE;	
	fish.MotType = fish_anim::FM_DEATH;	
	//�v���C���[�̐F��ς���
	float c = (float)AtCount / 100.0f;
	ML->E.Tone.x = -2.0f - c * 3.0f;
	//�V���[
	bgm.Filter.Frequency = 1.0f - c; 
	AtCount++;
	if(AtCount > 100)
	{

		//�ҋ@������
		AtCount = -100;
		//�v���C���[���U�����󂯂�
		P->FM.enemy.mode = MODE_CLEAR; 
		//�Q�[���I�[�o�[
		m_pPare->FldChange(new Gameover,&D3DXVECTOR3(0.0f,0.0f,0.0f),0.0f);
		ML->E.Tone.x = 1.0f;
	}
}
//�X�V
VOID Enemy::Update()
{	
	fish.HP = P->FM.enemy.HP;
	Strength( P->FM.enemy.Level );
	//�N���A���[�h
	if(P->FM.enemy.mode == MODE_CLEAR || P->FM.enemy.mode == MODE_REMOVE)
	{
		
		part.drawSkip = TRUE;
		fish.drawSkip = TRUE;
		return;
	}
	//�T�E���h
	if(P->FM.enemy.mode == MODE_STALK_ATTACK || P->FM.enemy.mode == MODE_GAMEOVER )
	{
		bgm.Start(ML);
		voice.Start(ML);
		voice.Emi.Position = P->FM.enemy.pos;
	}	
	//�v���C���[���A�N�V�����Ɣ�_���[�W�ł͖������͏I��
	if(!(P->Mode == Personal::MODE_ACTIVE || P->Mode == Personal::MODE_DAMAGE)){return ;}
	//���[�h
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
	//�����蔻��
	ModeHit();

	EriaHit.objPos  = P->FM.enemy.pos ;
	fish.Null.objPos = P->FM.enemy.pos + D3DXVECTOR3(0.0f,-0.35f,0.0f);
	fish.Null.YPR.y = P->FM.enemy.rot;
	fish.Update(ML);		
	fish.body.YPR.y += body;
	fish.head.YPR.y += neck;
/*
	//�A���J�[�̈ʒu�f�o�b�O
	annum++;
	an.drawSkip = FALSE;
	an.objPos = 	pAnc[ annum % (int)pAnc.size()]->Pos;
//*/

}
//�`��
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