
//=========================
//����
//=========================
const TCHAR *Memo::name(){return _T("Memo");}
Memo::Memo()
{
	flag = 0;
	frame = 0;
	//�J��
	Msh.push_back(&hit);
	hit.Type(x_cube);
	hit.HitMode(CT_OBB,CB_NONE);
	hit.drawSkip = TRUE;
	//��
	Msh.push_back(&hit1);
	hit1.Type(x_cube);
	hit1.HitMode(CT_OBB,CB_NONE);
	hit1.SetPare(&hit.mWorld);
	hit1.objPos = D3DXVECTOR3(-1.0f,0.0f,0.0f);
	hit1.drawSkip = TRUE;
	//�ӂ���
	Msh.push_back(&husuma);
	husuma.Type(x_husuma);
	husuma.SetPare(&hit.mWorld);
	husuma.ShadowFlag = FALSE;
	//�e�L�X�g
	text.init(this);
	text.s(_T("���؂ꂪ�����Ă�"));
	text.s(_T("���ɂ͂���������Ă���"));
	text.s(_T("���D���Ƃ��܂�ǂ��Ȃ������炵���ł�"));
	text.s(_T("�H�����̕������ʂ��������悤�Ȃ̂Ŗ߂��Ă����܂�"));
	text.s(_T("�������̕������q�l���|����Ȃ��Ǝv���̂�"));

	//�X���C�h�A�j���[�V����
	slide.SetKey(0,0.0f);
	slide.SetKey(10,0.0f);
	slide.SetKey(20,-0.85f);
	slide.SetKey(30,-0.85f);
	//SE
	se.Set(wav_sa);
	se.m_b3DSound = TRUE;
}
VOID Memo::Update()
{
	
	husuma.objPos.x = slide.Val(frame);
	//SE
	se.Emi.Position = husuma.objPos;
	if(frame == 15){se.Start(ML);}
//	if(se.Sv(ML)->Time() > 0.5f){se.Stop(ML,0.0f);}
	if(flag == 0)
	{
		frame--;
		if(frame < 0){frame = 0;}

		//�ӂ��܂��J����
		//���ׂ�
		if(P->Check)
		{
			if(hit.HitObj.Reaction == 1){	flag = 1;}
		}
	
	}
	else
	{
		frame++;
		if(frame > 29){frame = 29;}

		if(P->Check)
		{
			//�ӂ��܂����
			if(hit1.HitObj.Reaction == 1)
			{
				flag = 0;
			}
			else if(hit.HitObj.Reaction == 1)
			{
				if(P->Mode != Personal::MODE_EVENT)
				{
					text.StartText(P);

				}
			}
		}
		text.Update(P,ML);
	}

}
VOID Memo::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,
		_T("%s")
		_T("flag = %d\n")
		_T("frame = %d\n")
		,t
		,flag
		,frame
		);
}
//=========================
//������
//=========================
const TCHAR *Memokami::name(){return _T("Memokami");}
Memokami::Memokami()
{
	Fvf.push_back(&kami);
}
//=========================
//�d�b
//=========================
const TCHAR *Tel::name(){return _T("Tel");}
Tel::Tel()
{
	tel.Type(x_tel);
	tel.HitMode(CT_OBB,CB_PLUS);
	Msh.push_back(&tel);

	text.init(this);
	text.s(_T("��̓e�[�u���̏�ɂ���܂�"));
	text.s(_T("�o���邾����������ł�������\n(�e�[�u���ɋ߂Â��AZ�L�[�Œ��ׂ�)"));
	text.s(_T("�����炩�狖���������蕔���̊O�ɏo�鎖�͂ł��܂���"));
	text.s(_T("�Ȃɂ���펖�Ԃ��N�����ۂ͑��}�ɂ��A����������"));

	text1.init(this);
	text1.s(_T("............."));
	text1.s(_T("�����������Ȃ��B���Ă���̂��낤��"));

}
VOID Tel::Update()
{
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	if(tel.HitObj.Reaction == 1)
	{
		//����ޑO
		if(P->FM.EventFlag < 5){text.StartText(P);}
		//���񂾌�
		else{text1.StartText(P);}
	}
	text1.Update(P,ML);
	text.Update(P,ML);
}

//=========================================
//����
//=========================================
const TCHAR *Kinko::name(){return _T("Kinko");}
Kinko::Kinko()
{
	//����
	Msh.push_back(&pKinko);
	pKinko.Type(x_kinko);
	pKinko.Bias=0.05f;
	pKinko.HitMode(CT_OBB,CB_PLUS);
	//���ɂ̃h�A
	Msh.push_back(&pDoor);
	pDoor.Type(x_kinko_door);
	pDoor.Type(x_kinko_door);
	pDoor.SetPare(&pKinko.mWorld);
	pDoor.objPos=D3DXVECTOR3(-0.18f,0.04f,0.18f);
	pDoor.Bias=0.05f;
	//�e�L�X�g
	close.init(this);
	close.s(_T("���ɂ͊J���Ȃ��B�ٗl�ɗ₽��"));

	open.init(this);
	open.s(_T("���Ɍ�������"));
	open.s(_T("�y205�����̌��z����ɓ��ꂽ"));

	//SE
	se.Set(wav_dooropen);
	se.m_b3DSound = TRUE;
	se.Filter.OneOverQ = 0.05f;
	//�h�A�A�j���[�V����
	flag = 0;
	frame = 0;
	rot.SetKey(0,0.0f);
	rot.SetKey(50,-90.0f);

}
VOID Kinko::Update()
{
	//���ׂ�
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	if(pKinko.HitObj.Reaction == 1)
	{
		
		if(P->FM.EventFlag < TL_GUEST_ENEMY_END)
		{
			//���܂��Ă���
			close.StartText(P);
		}
		else
		{
			if(!P->FM.iGetedFlag(ITEM_GUEST_KEY))
			{
				if(flag == 2)
				{
					open.StartText(P);
				}
				if(flag == 0)
				{
					//�I�[�v��
					se.Emi.Position = pKinko.objPos;
					se.Start(ML);
					flag = 1;
				}
			}
	
		}

	}
	//�h�A���J����
	if(flag == 1)
	{
		frame ++;
		if(frame > 45)
		{
			flag = 2;
		}
		pDoor.YPR.y = rot.Val(frame);
	}


	//�e�L�X�g�X�V
	close.Update(P,ML);
	int o = open.Update(P,ML);
	//���擾
	if(o == 1)
	{
	
		if(	!P->FM.iGetedFlag(ITEM_GUEST_KEY))
		{
			P->CheckSE(Personal::SE_ITEM);
			P->FM.iGet(ITEM_GUEST_KEY);
		}
	}

}
//=========================================
//TV
//=========================================
const TCHAR *TV::name(){return _T("TV");}
TV::TV()
{
	//�e���r
	tv.Type(x_tv);
	tv.HitMode(CT_OBB,CB_PLUS);
	tv.Bias = 0.3f;
	Msh.push_back(&tv);
	//�e�L�X�g
	text.init(this);
	text.s(_T("�e���r�͂��Ȃ��B���Ă���悤��"));

}
VOID TV::Update()
{
	//���ׂ�
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	if(tv.HitObj.Reaction == 1)
	{
		text.StartText(P);
	}
	text.Update(P,ML);
}

//=========================================
//�①��
//=========================================
const TCHAR *Reizouko::name(){return _T("Reizouko");}
Reizouko::Reizouko()
{
	Msh.push_back(&pReizou);
	pReizou.Type(x_reizouko);
	pReizou.Bias=0.15f;
	pReizou.HitMode(CT_OBB,CB_PLUS);
	//�①�ɂ̃h�A
	Msh.push_back(&pDoor);
	pDoor.Type(x_reizouko_door);
	pDoor.SetPare(&pReizou.mWorld);
	pDoor.objPos=D3DXVECTOR3(-0.27f,0.05f,0.28f);
	pDoor.Bias=0.5f;
	//�t���O
	flag = 0;
	//�t���[��
	frame = 0;
	anim.SetKey(0,0.0f);
	anim.SetKey(10,-45.0f);
	anim.SetKey(50,-90.0f);
	//�T�E���h
	open.Set(wav_dooropen);
	open.m_b3DSound = TRUE;
	open.Filter.OneOverQ = 0.05f;
	Snd.push_back(&open);

	close.Set(wav_doorclose);
	close.m_b3DSound = TRUE;
	close.Filter.OneOverQ = 0.05f;
	Snd.push_back(&close);

	text.init(this);
	text.s(_T("�①�ɂ̒��ɂ͉����Ȃ�"));
	text.s(_T("���R�A���ɓ��邱�Ƃ͂ł��Ȃ�"));
}	
VOID Reizouko::Update()
{
	if(pReizou.HitObj.Reaction == 1)
	{
		if(P->Check)
		if(P->Mode != Personal::MODE_EVENT)	
		{
			if(flag == 0){flag = 1;}
			if(flag == 2)
			{
				text.StartText(P);
			}
		}
	}
	else
	{
		if(flag == 2){flag = 3;}
	}
	//�A�j���[�V����
	if(flag == 1)
	{
		frame++;
		if(frame > 48){flag = 2;}
		if(frame == 3)
		{
			open.Emi.Position = pReizou.objPos;
			open.Start(ML);
		}
	}
	
	if(flag == 3)
	{
		frame--;
		if(frame < 1){flag = 0;}	
		if(frame == 3)
		{
			close.Emi.Position = pReizou.objPos;
			close.Start(ML);
		}
	}
	text.Update(P,ML);
	pDoor.YPR.y = anim.Val(frame);
}

//=========================================
//�`���[�g���A��
//=========================================
const TCHAR *Tutorial::name(){return _T("Tutorial");}
Tutorial::Tutorial()
{
	//�����蔻�蔠
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.Type(x_cube);
	hitbox.drawSkip= TRUE;
	hitbox.MeshCol.w = 0.5f;
	Msh.push_back(&hitbox);
	//��
	paper.objScal = D3DXVECTOR3( 0.4f,0.3f,1.0f);
	paper.YPR = D3DXVECTOR3( 90.0f,20.0f,0.0f);
	paper.SetPare(&hitbox.mWorld);
	Fvf.push_back(&paper);
	//�e�L�X�g
	text.init(this);
	text.s(_T("[������@]\nZ�����N���b�N������ׂ�BX���������܂܂��ƃ_�[�c�𓊂���\nX���E�N���b�N����_��"));
	text.s(_T("Space������j���[���J��\nC���z�C�[���{�^������}�E�X���[�hON/OFF��؂�ւ���\n(�}�E�X���[�hON���ƃ}�E�X�J�[�\������\���ɂȂ�܂�)"));
	text.s(_T("Alt+Enter������������t���X�N���[���E�E�B���h�E���[�h�ؑ�"));
	text.s(_T("Esc����Q�[���I���E�t���X�N���[���̎��̓E�B���h�E���[�h�ɐؑ�\n(�Q�[���I������ۂ̓Z�[�u�����Y��Ȃ�)"));
}
VOID Tutorial::Update()
{
	if( hitbox.HitObj.Reaction == 1 )
	if( P->Check )
	if( P->Mode != Personal::MODE_EVENT )
	{
		text.StartText(P);
	}
	text.Update(P,ML);
}
