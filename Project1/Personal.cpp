//�p�[�\�i���f�[�^
//�R���X�g���N�^
Personal::Personal()
{
	TrgRelease = FALSE;
	//���ׂ�t���O
	Check = FALSE;
	//�L�����Z���t���O
	CanselCount = 0;
	Cansel = FALSE;
	m_iPage = 0;	
	//�J�����x�N�g���ɐi�s
	tes = D3DXVECTOR3(0,0,0);
	//�L�����N�^�̃��[�h
	Mode = MODE_ACTIVE;
	//�L�[�L��
	MoveKey = 0;
	//���n����
	HitVec = D3DXVECTOR3(0,0,0);
	//�i�s
	NextPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�f�o�b�O
	EyeRot=D3DXVECTOR2(0,0);
	//�L�����̒����_
	AtPos=D3DXVECTOR3(0,0,0);		
	//�����蔻��I�u�W�F�N�g
	obj.MeshCol=D3DXVECTOR4(1.0f,0,0,0.5f);
	obj.objScal=D3DXVECTOR3(1.0f,1.0f,1.0f)*0.35f;
	obj.Type(x_sphere);
	obj.HitMode(CT_SPHERE,CB_PLUS);
	//����
	Step.Set(wav_step2);
	Step.m_b3DSound = TRUE;
	Step.m_fVol =1.0f;
	Step.Filter.Frequency =0.1f;//������  0.0f~1.0f
    Step.Filter.OneOverQ =0.1f;//�s�� 0.0f~1.5f	XAUDIO2_MAX_FILTER_ONEOVERQ;
    Step.Filter.Type = LowPassFilter;//���x?		
	//���j���[���J����
	MenuOpen.Set(wav_step2);
	MenuOpen.m_fVol =1.0f;
	MenuOpen.Filter.Frequency =0.08f;//������  0.0f~1.0f
    MenuOpen.Filter.OneOverQ =0.0845f;//�s�� 0.0f~1.5f	XAUDIO2_MAX_FILTER_ONEOVERQ;
    MenuOpen.Filter.Type = LowPassFilter;//���x?		
	//�A�C�e���擾��
	ItemGet.Set(wav_dooropen);
	//�I����
	for(int i = 0; i < SMAX ; i++)
	{
		slct[i].Set(wav_step2);
	}
	//�e
	m_iDelay = 0;
	m_iCount = 0;
	int i;
	for(i = 0; i < 5; i++)
	{
		Blt.push_back(new CBullet);
	}
	//FPS�t���O
	FPSFlag = FALSE;
	//�ă��[�h
	ReLoad = 0;
	BGM = NULL;

	//�Ə�
	sight.SetTex(png_sight);
	sight.objScal = D3DXVECTOR3(10.0f,10.0f,0.0f);
	sight.MeshCol.w = 0.5f;
}
Personal::~Personal()
{
	//BGM�j��
	SAFE_DELETE(BGM);
	//�e�j��
	for(std::vector<CBullet*>::iterator it = Blt.begin(); it != Blt.end(); ++it)
	{
		SAFE_DELETE(*it);
	}
	
}
//���ʉ�
VOID Personal::CheckSE(Player_SE n)
{
	switch(n)
	{
	case SE_CANSEL://�L�����Z����
		MenuOpen.m_b3DSound = FALSE;
		MenuOpen.m_fVol = 1.0f;
		MenuOpen.Filter.Frequency =0.04f;//������  0.0f~1.0f
		MenuOpen.Filter.OneOverQ =0.1143f;//�s�� 0.0f~1.5f	XAUDIO2_MAX_FILTER_ONEOVERQ;
		MenuOpen.Filter.Type = LowPassFilter;//���x?
		MenuOpen.Start(ML);
		break;
	case SE_CHECK://���艹
		MenuOpen.m_b3DSound = FALSE;
		MenuOpen.m_fVol = 1.0f;
		MenuOpen.Filter.Frequency =0.08f;//������  0.0f~1.0f
	    MenuOpen.Filter.OneOverQ =0.0845f;//�s�� 0.0f~1.5f	XAUDIO2_MAX_FILTER_ONEOVERQ;
	    MenuOpen.Filter.Type = LowPassFilter;//���x?		
		MenuOpen.Start(ML);
		break;
	case SE_STEP://����
		Step.m_b3DSound = TRUE;
		Step.Emi.Position = obj.objPos;
		Step.Start(ML);
		break;
	case SE_ITEM://�A�C�e���擾��
		ItemGet.m_b3DSound = FALSE;
		ItemGet.Filter.Frequency = 0.05f;
		ItemGet.Filter.OneOverQ = 0.05f;
		ItemGet.Filter.Type = LowPassFilter;
		ItemGet.m_fVol = 0.3f;
		ItemGet.Start(ML);
		break;
	case SE_OPEN://�h�A�I�[�v��
		ItemGet.m_b3DSound = TRUE;
		ItemGet.Emi.Position = obj.objPos;
		ItemGet.Filter.Frequency = 1.0f;
		ItemGet.Filter.OneOverQ = 1.0f;
		ItemGet.Filter.Type = LowPassFilter;
		ItemGet.m_fVol = 1.0f;
		ItemGet.Start(ML);
		break;
	case SE_SLIDE://�h�A�I�[�v��1
		ItemGet.m_b3DSound = TRUE;
		ItemGet.Emi.Position = obj.objPos;
		ItemGet.Filter.Frequency = 0.5f;
		ItemGet.Filter.OneOverQ = 1.0f;
		ItemGet.Filter.Type = HighPassFilter;
		ItemGet.m_fVol = 1.0f;
		ItemGet.Start(ML);
	
		break;
	
	case SE_SELECT://�I����
		for(int i = 0; i < SMAX ; i++)
		{
			if(!slct[i].Sv(ML)->Idol())
			{
				slct[i].m_fVol = 0.5f;
				slct[i].Filter.Frequency = 0.1f;
				slct[i].Start(ML);
				return;
			}		
		}		
		break;
	default:break;
	}
}
//�錾��̃Z�b�g
VOID Personal::Set(MyLibrary* ml)
{
	ML = ml;
	obj.YPR.y = FM.RotY;
	obj.objPos= FM.Pos;
	AtPos	  = FM.Pos;	
	gt.Null.objPos = FM.Pos + D3DXVECTOR3(0.0f,-0.34f,0.0f);;	

	if(Mode == MODE_ACTIVE)
	{
		gt.drawSkip = FALSE;
	}
	obj.SetHit(ML);
	//�e�e�̃A�^�b�`�����Z�b�g
	ResetBullet();
	menu.Set(ML,&FM);
}
//FPS���[�h
VOID Personal::FPSMode()
{	
	//FPS���_
	gt.MotionType = gt_Anim::Motion_Wait;
	float xL = 1.0f;
	float yL = 1.0f;

	if( ML->C.getkey.MouseFlag == 1 )
	{
		float speed = 0.13f;
		float spdX = fabsf((float)ML->C.getkey.speed.x);
		float spdY = fabsf((float)ML->C.getkey.speed.y);
		if(spdX > 100.0f){spdX = 100.0f;}
		if(spdY > 100.0f){spdY = 100.0f;}
		xL = spdX * speed;
		yL = spdY * speed;
	}
	if(ML->C.getkey.k0m1 == 0)
	{
		xL = 1.0f;
		yL = 1.0f;
	}


	if(ML->C.UP.K()){		 MoveKey  = 1;   EyeRot.x -= yL;}
	else if(ML->C.DOWN.K()){ MoveKey  = 10;  EyeRot.x += yL;}
	if(ML->C.RIGHT.K()){	 MoveKey  = 100; EyeRot.y += xL;}
	else if(ML->C.LEFT.K()){ MoveKey  = 1000;EyeRot.y -= xL;}
	D3DXVECTOR3 Ez;
	D3DXMATRIX  mZ;	
	D3DXMatrixRotationYawPitchRoll(&mZ,D3DXToRadian(EyeRot.y +obj.YPR.y  ),D3DXToRadian(EyeRot.x),D3DXToRadian(0.0f));
	D3DXVec3TransformCoord(&Ez,&D3DXVECTOR3(0,0,0.1f),&mZ);		
	ML->E.cam.Eye = obj.objPos +D3DXVECTOR3(0,0.5f,0);
	ML->E.cam.At  = obj.objPos + Ez + D3DXVECTOR3(0,0.5f,0);
	if(EyeRot.x <= -80.0f){EyeRot.x =-80.0f;}
	if(EyeRot.x >=  80.0f){EyeRot.x = 80.0f;}
	if(EyeRot.y >=  360.0f){EyeRot.y = 0.0f;}
	else if(EyeRot.y <=  0.0f){EyeRot.y =360.0f;}
	//�L�����̃A���O��
	D3DXVECTOR3 N(ML->E.cam.At - ML->E.cam.Eye);
	D3DXVec3Normalize(&N,&N);
	AtPos	= obj.objPos+ D3DXVECTOR3(N.x,0.0f,N.z)*0.04f;
	gt.Null.YPR.y= D3DXToDegree(atan2(N.x,N.z));
	//�����d��
	if(FM.iGetedFlag(ITEM_LIGHT))
	{
		ML->E.PSL.Pos = ML->E.cam.Eye;
		ML->E.PSL.Vec = ML->E.cam.At;
	}
	//�e������
	if(m_iDelay >= 50)
	{
		if(ML->C.Z.K())
		{			
			if(TrgRelease == FALSE)
			{
				gt.KeyFrame = 0;
				if( m_iCount > Blt.size() - 1 ){m_iCount = 0;}
				Blt[m_iCount]->Init(&ML->E.cam.At,&ML->E.cam.Eye);
				m_iCount++;			
				m_iDelay = 0;
				TrgRelease = TRUE;
			}
		}
		else{TrgRelease = FALSE;}
	}
	if(m_iDelay < 50)
	{
		gt.MotionType = gt_Anim::Motion_Throw;
	}
	
}
//�C�x���g���[�h
VOID Personal::EventMode()
{
	gt.Null.objPos = obj.objPos + D3DXVECTOR3(0.0f,-0.34f,0.0f);;	
	gt.Null.YPR = obj.YPR;
	AtPos	  = obj.objPos;	
	//�񑀍쎞
	//�C�x���g���ׂ�
	Check = ML->C.Z.T();
	//�L�����Z������
	Cansel = FALSE;
	if(ML->C.X.K()){ CanselCount = 1; }
	else
	{
		if(CanselCount == 1){	Cansel = TRUE;	}
		CanselCount = 0;
	}
	
}
//�q�b�g�C�x���g
VOID Personal::HitEvent(std::vector<CollObj*>* obb)
{
	UINT i;
	UINT size = obb->size();
	//����x�N�g��0.7�����Ȃ�d�͔���
	D3DXVec3Normalize(&HitVec,&HitVec);
	if(HitVec.y > 0.7f){ NextPos.y = 0.0f; }	
	else
	{
		if(!FPSFlag){NextPos.y = -0.06f; }
	}
	HitVec = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�v���C���[�ƃt�B�[���h�̓����蔻��
	//�ʒu���X�V
	obj.objPos += NextPos;
	obj.SetHit(ML);
	//�t�B�[���h�I�u�W�F�N�g�Ƃ̓����蔻��
	for( i = 0; i < size; i++)
	{
		obb->at(i)->Reaction = 0;
	}
	for( i = 0; i < size; i++)
	{		
		if(ML->Col.Hit(&obj.HitObj,obb->at(i))) 
		{
			obb->at(i)->Reaction = 1;
			if(obb->at(i)->cBack == CB_PLUS)
			{
				obj.objPos += obj.HitObj.vBack; 
				HitVec += obj.HitObj.vBack;
			}
		}		
	}	
	//�X�V�l�����Z�b�g
	NextPos = D3DXVECTOR3(0.0f,0.0f,0.0f);	
	//�e�ƃt�B�[���h�̓����蔻��
	size = Blt.size();
	for( i = 0; i < size; i++){		Blt[i]->HitEvent(obb,ML);	}
	//���̋��܂ł̍d��
	if(m_iDelay < 50){	m_iDelay ++;	}
}
//�A�N�e�B�u���[�h
VOID Personal::ActiveMode()
{	
	//FPS���[�h
	if(ML->C.X.K() && FM.iGetedFlag(ITEM_DARTS))
	{
		FPSFlag = TRUE;	
		return;
	}
	else{FPSFlag = FALSE;}
	//���̂𒲂ׂ�
	Check = ML->C.Z.T();	
	Cansel = FALSE;//�L�����Z��������
	//���j���[���[�h
	if(ML->C.Space.T())
	{
		CheckSE(Personal::SE_CHECK);
		//���j���[���[�h�ɂ���
		Mode = MODE_MENU; 
	}	
	D3DXVECTOR3 UpdatePos(0.0f,0.0f,0.0f);
	D3DXVECTOR3 tes2;
	D3DXVec3Cross(&tes2,&D3DXVECTOR3(0.0f,1.0f,0.0f),&tes);
	gt.MotionType = gt_Anim::Motion_Wait;
	int MKey=0;
	if(ML->C.UP.K())
	{
		gt.MotionType = gt_Anim::Motion_Run;
		UpdatePos += tes;
		MKey += 1;
	}
	else if(ML->C.DOWN.K())
	{	
		gt.MotionType = gt_Anim::Motion_Run;
		UpdatePos -= tes;
		MKey += 10;
	}
	if(ML->C.RIGHT.K())
	{	
		gt.MotionType = gt_Anim::Motion_Run;
		UpdatePos += tes2;
		MKey += 100;
	}
	else if(ML->C.LEFT.K())
	{	
		gt.MotionType = gt_Anim::Motion_Run;	
		UpdatePos -= tes2;
		MKey += 1000;
	}	
	//�ړ��x�N�g�����X�V(�L�[����͂��Ȃ������Ƃ�)	
	if(MKey != MoveKey)
	{
		D3DXVECTOR2 v2(ML->E.cam.At.x - ML->E.cam.Eye.x,ML->E.cam.At.z - ML->E.cam.Eye.z);
		D3DXVec2Normalize(&v2,&v2);
		tes = D3DXVECTOR3(v2.x,0.0f,v2.y);
	}
	MoveKey = MKey;		
	//�����_�̍X�V
	float Speed = 0.15f;	
	D3DXVec3Normalize(&UpdatePos,&UpdatePos);			
	AtPos += UpdatePos * Speed;		
	//���_�ƃL�����ʒu�̔����ϕ�
	D3DXVECTOR2 N(AtPos.x - obj.objPos.x,AtPos.z - obj.objPos.z);			
	float Len = D3DXVec2LengthSq(&D3DXVECTOR2(N.x,N.y));
	D3DXVec2Normalize(&N,&N);			
	//Y�������̎Z�o	
	//�����_�����ȏ㗣��Ȃ��Ɖ�]����Ȃ�
	if(Len > 0.001f){
	obj.YPR.y = D3DXToDegree(atan2(N.x,N.y));		
	}
	//�S���̋��x
	N *= Len * 0.05f;
	gt.Null.objPos = obj.objPos + D3DXVECTOR3(0.0f,-0.34f,0.0f);
	gt.Null.YPR = obj.YPR;
	//�i�s�ʒu
	AtPos	   += -D3DXVECTOR3(N.x,0.0f,N.y);
	//�I�u�W�F�N�g�ʒu�̍X�V�l/�����蔻�蕪����
	NextPos = D3DXVECTOR3(N.x,0.0f,N.y);
	//����
	if(gt.MotionType == gt_Anim::Motion_Run)
	{	
		CheckSE(SE_STEP);
	}	
	//�L������\��
	gt.drawSkip = FALSE;
	//FPS�p�����[�^�̕ۑ�
	EyeRot = D3DXVECTOR2(0,0);
}
//���j���[���[�h
VOID Personal::MenuMode()
{
	//����
	Check = ML->C.Z.T();
	if(!Check){
	//�L�����Z��
	Cansel = FALSE;
	if(Check == FALSE)
	{
		if(ML->C.X.K()){ CanselCount = 1; }
		else
		{
			if(CanselCount == 1){Cansel = TRUE;	}
			CanselCount = 0;
		}
	}
	}
	//���j���[�̍X�V
	BOOL Close = ML->C.Space.T();
	FM.StaticPos(&obj.objPos,obj.YPR.y);
	int MenuFlag = menu.Update(Check,Cansel,Close);
	if(Check) {CheckSE(SE_CHECK);}
	else if(Close || Cansel) {CheckSE(SE_CANSEL);}
	//���j���[�����
	if(	 MenuFlag == 0 || Close)
	{
		Check = FALSE;
		menu.CloseMenu();
		Mode = MODE_ACTIVE; 
	}
	//�t�B�[���h�`�F���W
	if(MenuFlag == -1)
	{
		Check = FALSE;
		ReLoad = 1;
		menu.CloseMenu();
	}
	
}
//�_���[�W���󂯂�
VOID Personal::DamageMode()
{	
	gt.drawSkip = FALSE;
	gt.MotionType = gt_Anim::Motion_Wait;
	FPSFlag = FALSE;
}

//���쎞�X�V
VOID Personal::Update()
{	

#ifdef MY_DEBUG 
	//���f����ҏW
	if(m_iPage == 1)
	{
		gt.Update(ML);
		return;
	}
	//�㉺�f�o�b�O�p
	if(Mode == MODE_ACTIVE)
	{
		if(ML->C.V.K()){obj.objPos.y += 0.1f;}
	}	
#endif
//	if( )
//	{
		gt.SoltFlag = FM.iGetFlag(ITEM_MASUI);
//	}

	//�����d��
	gt.FlashFlag = FALSE;
	if(FM.iGetedFlag(ITEM_LIGHT) )
	{

		gt.FlashFlag = TRUE;

		if(!FPSFlag)
		{
			gt.FlashLock = TRUE;
		}
		else
		{
			gt.FlashLock = FALSE;
		}
		
	}
	//�v���C���[�̏��
	switch(Mode)
	{
	case MODE_EVENT: EventMode(); break;//�񑀍�
	case MODE_ACTIVE:ActiveMode();break;//�ړ�
	case MODE_MENU:	 MenuMode();  break;//�Q�[�����j���[
	case MODE_DAMAGE:DamageMode();break;//�G�C�x���g���[�h
	default: break;
	}		
	
	
	//���f�����X�V
	gt.Update(ML);
}

//Ui�e�L�X�g
VOID Personal::Ui()
{
	//�Ə�
	if(FPSFlag){sight.draw(ML);	}
	//���j���[
	menu.draw();
}
//�`��
VOID Personal::draw()
{	
	//��σt���O�������Ă���ꍇ�J��������ς�
	if(ML->E.ShadowPassNum == 1)
	{
		if(Mode == MODE_ACTIVE)
		{
			if(FPSFlag){FPSMode();	}
		}
	}
	//FPS���[�h�̏ꍇ�͋��̂݉f��悤��
	if(FPSFlag)
	{
		if(ML->E.MirrorPass == 1 ){gt.draw(ML);}
		else{gt.Set(ML);}
	}
	else{gt.draw(ML);	}

	for(std::vector<CBullet*>::iterator it = Blt.begin(); it != Blt.end(); ++it )
	{
		(*it)->draw(ML);
	}
	
/*
	obj.draw(ML);//�����蔻��	
	//�����_�I�u�W�F�N�g
	At.Type(x_sphere);
	At.objScal=D3DXVECTOR3(0.2f,0.2f,0.2f);
	At.ShadowFlag =FALSE;
	At.objPos = AtPos;
	At.objPos.y = obj.objPos.y;
	At.draw(ML);//�����_
//*/
}
//==========================================
//�O���Ƃ̃A�N�Z�X
//==========================================
//�G�ɒe��������
VOID Personal::AtcBullet(D3DXMATRIX* mat)
{
	Blt[m_iCount - 1]->Attach(mat);
}
//�e�e�̃A�^�b�`�����Z�b�g
VOID Personal::ResetBullet()
{
	for(std::vector<CBullet*>::iterator it = Blt.begin(); it != Blt.end(); ++it)
	{
		(*it)->Reset();
	}
}
//debug�{�^��
VOID Personal::DButton(DebugButton* db)
{
	db->DB(_T("m_iPage = %d"),&m_iPage,0,1);
	if(m_iPage == 0)
	{

		db->DB(_T("gt.head.Bias = %f"),&gt.head.Bias,0.0f,1.0f);

		
	}
	if(m_iPage == 1)
	{
		//���[�V�����f�o�b�O�p		
		gt.MotionCreate(db,ML);
	}

}
//�f�o�b�O�p�t�H���g
VOID Personal::DebugText(TCHAR* txt,int n)
{	
	/**/
	_stprintf_s(txt,n,
		_T("%s")
		_T("PlayPos x: %f y: %f z: %f\n")	
		_T("RotY:%f\n")	
		_T("FM.EventFlag = %d\n")
		_T("FM.FldType = %d\n")
		_T("Enemy.HP = %d\n")

		,txt
		,obj.objPos.x,obj.objPos.y,obj.objPos.z
		,gt.Null.YPR.y
		,FM.EventFlag
		,FM.FldType
		,FM.enemy.HP
		);
	
//	for(std::vector<CBullet*>::iterator it = Blt.begin(); it != Blt.end(); ++it )
//	{
//		(*it)->Debug(n,txt);
//	}
//	menu.DebugText(txt,n);
//	gt.DebugText(txt,n);
}
