//=============================================
//��
//=============================================
const TCHAR *Drug::name(){return _T("Drug");}
Drug::Drug()
{
	//�钎
	Suzumusi.Set(wav_suzumusi);
	Suzumusi.m_bLoop = TRUE;
	Suzumusi.m_fVol = 0.2f;
	Snd.push_back(&Suzumusi);
	//���݉�
	se.Set(wav_step2);
	se.m_b3DSound = TRUE;
	se.Filter.Frequency = 0.050000f;
	se.Filter.OneOverQ = 0.248400f;
	Snd.push_back(&se);
	//���񂪂�
	frame = 0;
	gangan.Set(wav_keylock);
	gangan.m_b3DSound = TRUE;
	gangan.Filter.Frequency = 0.08f;
	Snd.push_back(&gangan);

	//��r
	bottle.Type(x_bottle);
	bottle.objScal = D3DXVECTOR3(0.05f,0.05f,0.05f);
	bottle.objPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	bottle.MeshCol = D3DXVECTOR4(0.1f,0.1f,0.1f,1.0f);
	Msh.push_back(&bottle);
	//�����蔻��
	hitbox.Type(x_cube);
	hitbox.drawSkip = TRUE;
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f);
	hitbox.objPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	Msh.push_back(&hitbox);
	//�e�L�X�g
	text.init(this);
	text.s(_T("�������"));
	flag = 0;
	//���C�g���Â�
	lightframe = 0;
	light.SetKey(0,D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f));
	light.SetKey(200,D3DXVECTOR4(0.8f,0.8f,0.9f,1.0f));
}
VOID Drug::Set()
{
	hitbox.objPos = bottle.objPos;
}
VOID Drug::Update()
{
	if(P->FM.EventFlag == 5)
	{
		ML->E.Ls.Col = light.Val(lightframe);
		lightframe++;
		if(lightframe > 199 ){P->FM.EventFlag = TL_DRUG_GUNGUN; }
	
	}
	if(P->FM.EventFlag == TL_DRUG_GUNGUN || P->FM.EventFlag == TL_DRUG_LIGHT)
	{	
		//���񂪂�
		frame++;
		if(frame > 300){frame = 0;}
		if(frame == 100 || frame == 140 || frame == 250  )
		{
			gangan.Emi.Position = D3DXVECTOR3(0.0f,0.0f,-2.0f);
			gangan.Start(ML);
		}
	}
	if(P->FM.EventFlag >= 4)
	{
		//�{�g������
		bottle.drawSkip = TRUE;
		//bgm�X�g�b�v
		Suzumusi.Pause(ML);		
		return;
	}		
	Suzumusi.Start(ML);
	switch(flag)
	{
	case 0:
		if(hitbox.HitObj.Reaction == 1)
		{
			if(P->Check){flag = 1;	}
		}
		break;
	case 1:
		P->Mode = Personal::MODE_EVENT;
		P->gt.MotionType = gt_Anim::Motion_Drink;
		P->gt.KeyFrame = 0;
		flag = 2;
		bottle.drawSkip = TRUE;
		break;
	case 2:
		if(P->gt.KeyFrame % 40 == 0){se.Start(ML);}
		if(P->gt.MaxKey(gt_Anim::Motion_Drink) < P->gt.KeyFrame)
		{
			P->gt.MotionType = gt_Anim::Motion_Wait;
			flag = 3;
			text.StartText(P);
		}
		break;
	case 3:
		if(text.Update(P,ML) == 1)
		{
			P->Mode = Personal::MODE_ACTIVE;
			P->FM.EventFlag = TL_DRUG_START;
		}
		break;	
	default:break;
	}
}
//=====================================
//�o�X���[���̃h�A
//=====================================
const TCHAR* bathdoor::name(){return _T("bathdoor");}
bathdoor::bathdoor()
{
	Msh.push_back(&	hit);
	Msh.push_back(&	door);
	Msh.push_back(&	waku);

	hit.Type(x_cube);
	hit.drawSkip = TRUE;
	hit.HitMode(CT_OBB,CB_NONE);

	waku.objScal = D3DXVECTOR3(0.9f,0.9f,0.9f);
	waku.Type(x_bathdoorwaku);
	waku.SetPare(&hit.mWorld);
	waku.ShadowFlag = FALSE;
	waku.objPos.x = 0.5f;

	door.ShadowFlag = FALSE;
	door.Type(x_bathdoor);
	door.SetPare(&waku.mWorld);
	door.YPR.y = 0.0f;

	frame = 0;
	aopen.SetKey(0,0.0f);
	aopen.SetKey(90,30.0f);
	aopen.SetKey(95,0.0f);

	//�h�A���J���鉹
	open.m_b3DSound = TRUE;
	open.Set(wav_dooropen);
	Snd.push_back(&open);
	//�h�A��߂鉹
	close.m_b3DSound = TRUE;
	close.Set(wav_doorclose);
	Snd.push_back(&close);

}
VOID bathdoor::Update()
{
	if(P->FM.EventFlag == 4)
	{
		P->gt.MotionType = gt_Anim::Motion_Wait;
		P->Mode = Personal::MODE_EVENT;
		open.Emi.Position = hit.objPos;
		close.Emi.Position = hit.objPos;
		if(frame == 1){open.Start(ML);}
		if(frame == 90){close.Start(ML);}
		ML->Audio.Audio.Effect = AE_BATHROOM;
		door.YPR.y = aopen.Val1(frame);
		frame++;
		if(frame > 150)
		{
			P->Mode = Personal::MODE_ACTIVE;
			ML->Audio.Audio.Effect = AE_LIVINGROOM;
			P->FM.EventFlag = TL_DRUG_LIGHT;
		}
	
	}
}
//=======================
//�V���O���e�L�X�g�o�X���[��
//=======================
const TCHAR *DoorText::name(){return _T("Text");}
DoorText::DoorText()
{
	text.init(this);
	text.s(_T("�J���Ȃ�"));
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.drawSkip = TRUE;
	Msh.push_back(&hitbox);

	//����
	gatya.Set(wav_keylock);
	gatya.m_b3DSound = TRUE;
	Snd.push_back(&gatya);


}
VOID DoorText::Update()
{
	if(P->FM.EventFlag < 5)
	{
		if(P->Mode != Personal::MODE_EVENT)
		if(hitbox.HitObj.Reaction == 1)
		{	
			if(P->Check)
			{
				text.StartText(P);	
				gatya.Emi.Position = hitbox.objPos;
				gatya.Start(ML);
			}
		}
		text.Update(P,ML);
	}	
}

//=====================
//�V���O���e�L�X�gF3���e�L�X�g
//=====================
const TCHAR *F2_DoorText::name(){return _T("F2_DoorText");}
F2_DoorText::F2_DoorText()
{
	//���������Ă�
	text.init(this);
	text.s(_T("�����������Ă���"));
	//�J���e�L�X�g
	text1.init(this);
	text1.s(_T("�y205�����̌��z��������"));
	text1.s(_T("�����ɂ���悤�Ɍ���ꂽ��"));
	text1.s(_T("�O�ɏo�āA���������߂��ق���������������Ȃ�"));

	//�����蔻��BOX
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.drawSkip = TRUE;
	Msh.push_back(&hitbox);
	//����
	gatya.Set(wav_keylock);
	gatya.m_b3DSound = TRUE;
	Snd.push_back(&gatya);
	//�J����
	unlock.Set(wav_dooropen);
	unlock.Filter.Type = BandPassFilter;
	unlock.Filter.OneOverQ = 0.1f;
	unlock.m_b3DSound = TRUE;
	Snd.push_back(&unlock);
}
VOID F2_DoorText::Update()
{
	//�����J���ĂȂ�
	if(!P->FM.iGetedFlag(ITEM_GUEST_KEY))
	{
		if(P->Mode != Personal::MODE_EVENT)
		if(hitbox.HitObj.Reaction == 1)
		{	
			if(P->Check)
			{
				gatya.Filter.Frequency = 1.0f;
				gatya.Filter.OneOverQ = 1.0f;
				gatya.Filter.Type = LowPassFilter;
				gatya.Start(ML);
				text.StartText(P);	
			}
		}
		text.Update(P,ML);
		return;
	}
	else
	{
		//�����g������Ȃ�Ȃɂ��Ȃ�
		if(!P->FM.iGetFlag(ITEM_GUEST_KEY))
		{
			return;
		}
	}
	//���[�������Ă���Ƃ�
	if(P->FM.iGetFlag(ITEM_GUEST_KEY))
	{
		if(P->Mode != Personal::MODE_EVENT)
		if(hitbox.HitObj.Reaction == 1)
		{	
			if(P->Check)
			{
				unlock.Start(ML);
				text1.StartText(P);	
			}
		}
		//�����̂Ă�
		if(text1.Update(P,ML) == 3)
		{
			P->FM.iRelease(ITEM_GUEST_KEY);
		}
	}
	
}

//=====================
//�_�[�c
//=====================
const TCHAR *Darts::name(){return _T("Darts");}
Darts::Darts()
{
	frame = 0;
	//�����蔻��p
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.objPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	hitbox.drawSkip = TRUE;
	Msh.push_back(&hitbox);
	//�`��p
	for(int i = 0; i < MAX;i++)
	{
		darts[i].Type(x_darts);
		darts[i].objScal = D3DXVECTOR3(0.2f,0.2f,0.2f);
		darts[i].SpCol.w = 8.0f;
		darts[i].BloomColor.w = 5.0f;
		darts[i].SetPare(&hitbox.mWorld);
		darts[i].objPos =D3DXVECTOR3(0.0f,0.02f * (float)i,0.0f);
		darts[i].YPR.y = 20.0f * (float)i;
		darts[i].YPR.x = 5.0f * (float)i;
		Msh.push_back(&darts[i]);
	}
	//�e�L�X�g
	text.init(this);
	text.s(_T("�y�_�[�c�z����ɓ��ꂽ\n(X�L�[�������đ_���AX���������܂�Z�L�[�Ń_�[�c�𓊂���)"));
	textmasui.init(this);
	textmasui.s(_T("�y�H�����z���g����"));
	textmsdt.init(this);
	textmsdt.s(_T("�y�H�����t���_�[�c�z����ɓ��ꂽ"));
	//�t
	drip.Type(x_sphere);
	drip.SetPare(&hitbox.mWorld);
	drip.objScal = D3DXVECTOR3(0.0f,0.01f,0.0f);
	drip.drawSkip = TRUE;
	drip.MeshCol = D3DXVECTOR4(1.0f,0.0f,1.0f,0.5f);
	Msh.push_back(&drip);
	//�A�j���[�V����
	adrip.SetKey(0,0.0f);
	adrip.SetKey(150,0.25f);

	//�h���b�v��
	se.Set(wav_step2);
	se.m_b3DSound = TRUE;
	se.Filter.Frequency = 0.055277f;
	se.Filter.OneOverQ = 0.016600f;
	Snd.push_back(&se);

	drug.Type(x_bottle);
	drug.objPos = D3DXVECTOR3(0.0f,0.04f,-0.3f);
	drug.objScal= D3DXVECTOR3(1.0f,1.0f,1.0f)* 0.3f * 0.15f;
	drug.YPR.x = 90.0f;
//	drug.YPR.y = 90.0f;

	drug.SpColm = 1.0f; 
	drug.SpCol.w = 0.0f;
	drug.SetPare(&hitbox.mWorld);
	drug.drawSkip = TRUE;
	Msh.push_back(&drug);

}
VOID Darts::Update()
{
	if(P->FM.iGetedFlag(ITEM_MASUI_DARTS))
	{
		drug.drawSkip = FALSE;
		drip.objScal.x = 0.25f;
		drip.objScal.z = 0.25f;
		drip.drawSkip = FALSE;	
		return;
	}
	//�_�[�c�����
	if(!P->FM.iGetedFlag(ITEM_DARTS))
	{
		if(hitbox.HitObj.Reaction == 1)
		{		
			if(P->Mode != Personal::MODE_EVENT)
			{
	
				if(P->Check)
				{
					P->CheckSE(Personal::SE_ITEM);
					text.StartText(P);	
				}
			}
		}		
		if( text.Update(P,ML) == 1 )
		{
			
			P->FM.iGet(ITEM_DARTS);
		}		
	}
	else
	{
		if(P->FM.iGetedFlag(ITEM_MASUI))
		{
			if(P->FM.iGetFlag(ITEM_MASUI))
			{
				//�e�L�X�g�J�n
				if(hitbox.HitObj.Reaction == 1)
				if(P->Mode != Personal::MODE_EVENT)
				if(P->Check){textmasui.StartText(P);	}
				//�e�L�X�g���I������
				if( textmasui.Update(P,ML) == 1 )
				{
					P->FM.iRelease(ITEM_MASUI);	

				}
			}
			//���т����_�[�c
			else
			{
				drug.drawSkip = FALSE;
				//�h���b�v�A�j���[�V����
				if(P->FM.trick.darts == 0)
				{
				
					if(frame < 150)
					{
						frame++;
						//��
						se.Emi.Position = hitbox.objPos;
						se.Start(ML);
						se.Filter.Frequency =  0.001f * (float)frame;
					}
					else{P->FM.trick.darts = 1; }
				}
				else if(P->FM.trick.darts == 1)
				{
					frame = 150;
					//���ׂ�
					if(hitbox.HitObj.Reaction == 1)
					if(P->Mode != Personal::MODE_EVENT)
					if(P->Check)
					{
						P->CheckSE(Personal::SE_ITEM);
						textmsdt.StartText(P);	
					}
					//���т��t���_�[�c�擾
					if(textmsdt.Update(P,ML) == 1)
					{
						P->FM.iRelease(ITEM_DARTS);
						P->FM.iGet(ITEM_MASUI_DARTS);
					}
				}
				float anim = adrip.Val1(frame);		
				drip.drawSkip = FALSE;
				drip.objScal.x = anim;
				drip.objScal.z = anim;
			}
		
		}
	}
	
}
//=====================
//�I
//=====================
const TCHAR *Dartsbord::name(){return _T("Dartsbord");}
Dartsbord::Dartsbord()
{
	frame = 0;
	//���_�I�u�W�F�N�g
	center.MeshCol.w = 0.5f;
	center.Type(x_cube);
	center.drawSkip = TRUE;
	Msh.push_back(&center);
	//�`��I�u�W�F�N�g
	dartsbord.Type(x_dartsbord);
	dartsbord.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 0.3f;
	dartsbord.objPos.z = -0.3f;
	dartsbord.ShadowFlag = FALSE;
	dartsbord.SetPare(&center.mWorld);
	Msh.push_back(&dartsbord);
	//�����蔻��I�u�W�F�N�g
	hit.Type(x_cube);
	hit.HitMode(CT_OBB,CB_ENEMY);
	hit.SetPare(&dartsbord.mWorld);
	hit.objPos = D3DXVECTOR3(0.0f,0.5f,0.0f);
	hit.objScal = D3DXVECTOR3(2.5f,2.0f,2.5f);
	hit.drawSkip = TRUE;

	hit.MeshCol.w = 0.5f;
	Msh.push_back(&hit);
	//��r
	drug.Type(x_bottle);
	drug.SetPare(&dartsbord.mWorld);
	drug.objPos = D3DXVECTOR3(0.0f,-0.2f,0.0f);
	drug.objScal= D3DXVECTOR3(0.15f,0.15f,0.15f);
	drug.YPR.x = 270.0f;
	drug.SpColm = 1.0f; 
	drug.SpCol.w = 0.0f;
	drug.ShadowFlag = FALSE;
	drug.HitMode(CT_OBB,CB_NONE);
	Msh.push_back(&drug);
	//�T�E���h
	se.Set(wav_step2);
	se.m_b3DSound = TRUE;
	se.Filter.Frequency = 0.110000f;
	se.Filter.OneOverQ = 0.904000f;
	se.Filter.Type = LowPassFilter;
	Snd.push_back(&se);
	//�e�L�X�g
	text.init(this);
	text.s(_T("�_�[�c�{�[�h�̗��ɉ����\��t���Ă���"));
	text.s(_T("�y�H�����z����ɓ��ꂽ"));

	SoundFlag = FALSE;
}
VOID Dartsbord::Set()
{
	//�A�j���[�V����
//	float y = dartsbord.HitObj.Vec()->y; 
	//����
	py.SetKey(0,center.objPos.y);
	py.SetKey(20,0.0f);
	//��]
	rx.SetKey(0,center.YPR.x);
	rx.SetKey(45,center.YPR.x);
	rx.SetKey(60,center.YPR.x + 90.0f);
}
VOID Dartsbord::Update()
{
	if(P->FM.iGetedFlag(ITEM_MASUI))
	{
		drug.drawSkip = TRUE;
		dartsbord.drawSkip = TRUE;
		return;
	}
	center.SetHit(ML);
	se.Emi.Position = center.objPos;
	if( frame == 30 || frame == 60 ){se.Start(ML);}
	int page = 0;
	switch(	P->FM.trick.dartsbord)
	{
	case 0://�_�[�c����������
		if(hit.HitObj.Reaction == 2)
		{
			P->AtcBullet(&dartsbord.mWorld);
			P->FM.trick.dartsbord = 1;
		}
		break;
	case 1: 
		frame++;
		if(frame > 100){	P->FM.trick.dartsbord = 2;}
		break;
	case 2:
		frame = 100;
		//���ׂ�
		if(drug.HitObj.Reaction == 1)
		{
			if(P->Mode != Personal::MODE_EVENT)
			{
				if(P->Check){text.StartText(P);}
			}
		}
		page = text.Update(P,ML);

		if(page  == 1)
		{
			if(!SoundFlag)
			{
				P->CheckSE(Personal::SE_ITEM);
				SoundFlag = TRUE;
			}
		}
		if(page  == 2)
		{
			P->FM.iGet(ITEM_MASUI);
			P->FM.trick.dartsbord = 3;
		}
		break;
	default:break;
	
	}
	center.objPos.y = py.Val1(frame);
	center.YPR.x = rx.Val1(frame);		
}
VOID Dartsbord::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,_T("%s\n")
		_T("Flag = %d\n")
		,t
		,P->FM.trick.dartsbord
		);
}