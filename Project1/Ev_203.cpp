//===============================================
//203��������o���
//===============================================
const TCHAR* Door203Exit::name(){return _T("Door203Exit");}
Door203Exit::Door203Exit()
{
	Msh.push_back(&pBox);
	pBox.Type(x_cube);
	pBox.drawSkip=TRUE;
	pBox.HitMode(CT_OBB,CB_NONE);

	Msh.push_back(&pWaku);
	pWaku.Type(x_wood_door_waku);
	pWaku.objScal=D3DXVECTOR3(0.8f,0.9f,1.0f);
	pWaku.ShadowFlag=FALSE;
	pWaku.SetPare(&pBox.mWorld);

	Msh.push_back(&pDoor);
	pDoor.Type(x_wood_door);
	pDoor.SetPare(&pWaku.mWorld);
	pDoor.objPos.x=-0.47f;
	pDoor.ShadowFlag=FALSE;

	Msh.push_back(&pNobu);
	pNobu.Type(x_doornobu);
	pNobu.SetPare(&pDoor.mWorld);
	pNobu.objPos=D3DXVECTOR3(0.82f,0.75f,0);
	pNobu.ShadowFlag=FALSE;
	//�A���t�@�}�X�N
	Msh.push_back(&pMask);
	pMask.Type(x_cube);
	pMask.SetPare(&pBox.mWorld);
	pMask.MeshCol.w = 0.0f;
	pMask.SpColm = 0.0f;
	pMask.ShadowFlag = FALSE;
	pMask.Amb = 0.0f;
	pMask.objPos = D3DXVECTOR3(0.0f,0.67f,0.0f);
	pMask.objScal = D3DXVECTOR3(1.52f,3.212f,0.1f);

	flag = 0;
	//�A�j���[�V����
	frame = 0;
	rot.SetKey(0,130.0f);
	rot.SetKey(20,0.0f);
	//se
	//�߂鉹
	close.Set(wav_doorclose);
	close.m_b3DSound = TRUE;
	close.m_fVol = 2.0f;
	Snd.push_back(&close);
	//���܂��Ă�
	lock.Set(wav_keylock);
	lock.m_b3DSound = TRUE;
	Snd.push_back(&lock);
	//�����J���鉹
	unlock.Set(wav_dooropen);
	unlock.Filter.Type = BandPassFilter;
	unlock.Filter.OneOverQ = 0.1f;
	unlock.m_b3DSound = TRUE;
	Snd.push_back(&unlock);

	//�e�L�X�g
	text.init(this);
	text.s(_T("�����������Ă���"));
	text.s(_T("�y203�����̌��z���g����"));
	//�e�L�X�g
	text1.init(this);
	text1.s(_T("�����Ȃ�"));
	//�T�E���h�I���̍��}
	soundEnd = 0;
}
VOID Door203Exit::Set()
{
	if(P->FM.iGetedFlag(ITEM_GENKAN_KEY))
	{
		flag = 1;
		frame = rot.MaxKey();
	}
	
}

VOID Door203Exit::Update()
{
	pDoor.YPR.y = rot.Val1(frame);
	if(flag == 0)
	{
		if(!P->FM.iGetedFlag(ITEM_GENKAN_KEY))
		{
			if( pBox.HitObj.Reaction == 1 )
			{
				if( P->Check )
				{
					m_pPare->FldChange(new F3,&D3DXVECTOR3(-4.00f,2.55f,30.5f),0.0f);
				}
			}

		}
		else
		{
			frame++;
			if(frame > rot.MaxKey())
			{
				close.Emi.Position = pBox.objPos;
				close.Start(ML);
				flag = 1;
			}
		
		}
	}
	else if(flag == 1)
	{
		if(P->FM.iGetFlag(ITEM_203_KEY))
		{
			//�����g��
			if( pBox.HitObj.Reaction == 1 )
			if( P->Check )
			if( P->Mode != Personal::MODE_EVENT )
			{
				text.StartText(P);
				lock.Start(ML);
				lock.Emi.Position = pBox.objPos;
			}
			const int t = text.Update(P,ML);
			if( t == 1 )
			{
				if(soundEnd == 0)
				{
					soundEnd = 1;
					unlock.Start(ML);
					unlock.Emi.Position = pBox.objPos;
				}
			}
			if( t == 2 )
			{
				P->FM.iRelease(ITEM_203_KEY);
			}
		}
		else
		{
			//�^�C�����C�����i�߂ΊJ��
			if(P->FM.EventFlag < TL_203_EXIT )
			{
				//�����Ȃ�
				if( pBox.HitObj.Reaction == 1 )
				if( P->Check )
				if( P->Mode != Personal::MODE_EVENT )
				{
				
					text1.StartText(P);
					lock.Start(ML);
					lock.Emi.Position = pBox.objPos;
				}
				text1.Update(P,ML);
			}
			else
			{
				//�O�ɏo����
				if( pBox.HitObj.Reaction == 1  )
				if( P->Check )
				{
					P->CheckSE(Personal::SE_OPEN);
					m_pPare->FldChange(new F3,&D3DXVECTOR3(-4.00f,2.55f,30.5f),0.0f);

				}
			}
		}
	}
}
//===============================================
//���ʌ��ւ̌�
//===============================================
const TCHAR* GenkanKey::name(){return _T("GenkanKey");}
GenkanKey::GenkanKey()
{
	
	Time = 0;

	key.Type(x_key);
	key.objScal = D3DXVECTOR3(0.15f,0.15f,0.15f);
	key.MeshCol = D3DXVECTOR4(3.0f,3.0f,3.0f,1.0f);
	key.HitMode(CT_OBB,CB_NONE);
	Msh.push_back(&key);
	text.init(this);
	text.s(_T("�y���ʌ��ւ̌��z����ɓ��ꂽ"));

}
VOID GenkanKey::Update()
{
	if( P->FM.iGetedFlag(ITEM_GENKAN_KEY ))
	{
		key.drawSkip = TRUE;
//		P->FM.enemy.pos.y = 0.5f;
		//�G���S
		if(	P->FM.enemy.mode == Enemy::MODE_REMOVE)
		{
			P->FM.enemy.mode = Enemy::MODE_CLEAR;
			P->FM.EventFlag = TL_203_EXIT; 
		
		}
		//�G�o��
		if( P->FM.enemy.mode == Enemy::MODE_CLEAR )
		{	
			if( P->FM.EventFlag < TL_203_EXIT )
			{			
				P->FM.enemy.mode = Enemy::MODE_STALK_ATTACK;
				
			}
		}
		return;
	}

	
	if( key.HitObj.Reaction == 1 )
	if( P->Check )
	if( P->Mode != Personal::MODE_EVENT )
	{
		P->CheckSE(Personal::SE_ITEM);
		text.StartText(P);
	}
	if( text.Update(P,ML) == 1 )
	{
		P->FM.iGet(ITEM_GENKAN_KEY);
	}	
}

VOID GenkanKey::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,
		_T("%s\n")
		_T("Time = %d\n")
		,t
		,Time
		);
}
