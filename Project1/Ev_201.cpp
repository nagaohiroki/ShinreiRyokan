const TCHAR *Key201::name(){return _T("Key201");}
Key201::Key201()
{
	//�����蔻�蔠
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.drawSkip = TRUE;
	Msh.push_back(&hitbox);
	//�J����
	unlock.Set(wav_dooropen);
	unlock.Filter.Type = BandPassFilter;
	unlock.Filter.OneOverQ = 0.1f;
	unlock.m_b3DSound = TRUE;
	Snd.push_back(&unlock);
	//�e�L�X�g
	text.init(this);
	text.s(_T("�����J����"));
}
VOID Key201::Update()
{
	unlock.Emi.Position = hitbox.objPos;
	if(hitbox.HitObj.Reaction == 1)
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	{
		if(P->FM.EventFlag >= TL_201_OPEN)
		{
			//���ʉ�
			P->CheckSE(Personal::SE_OPEN);
			m_pPare->FldChange(new F3, &D3DXVECTOR3(0.5f,2.55f,7.00f),90.0f);
		}
		else
		{
			unlock.Start(ML);
			text.StartText(P);
			P->FM.EventFlag = TL_201_OPEN;
		}

	}
	text.Update(P,ML);
}


//=======================================
//�Ύ�
//=======================================
const TCHAR *Fire::name(){return _T("Fire");}
Fire::Fire()
{
	//��
	fire.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 5.0f;
	fire.PrtTime = 0.8f;
	fire.Speed = 0.01f;
	fire.Height = 2.5f;
	fire.SetTex(bmp_fire);
	Prt.push_back(&fire);
	//��
	smoke.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 3.0f;
	smoke.PrtTime = 0.5f;
	smoke.Speed = 0.02f;
	smoke.Height = 2.5f;
	smoke.SetTex(bmp_smoke);
	Prt.push_back(&smoke);
	//�e�[�u��
	table.Type(x_table);
	table.HitMode(CT_OBB,CB_PLUS);
	table.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 1.5f;
	table.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	Msh.push_back(&table);
	//�d�C
	denki.Type(x_denki);
	denki.HitMode(CT_OBB,CB_PLUS);
	denki.SetPare(&table.mWorld);
	denki.objPos = D3DXVECTOR3(0.0f,0.35f,0.2f);
	denki.YPR = D3DXVECTOR3(0.0f,60.0f,0.0f);
	denki.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) / 1.5f;
	denki.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	Msh.push_back(&denki);
	//���Ί�
	syoukaki.Type(x_syoukaki);
	syoukaki.drawSkip = TRUE;
	syoukaki.objScal= D3DXVECTOR3(1.0f,1.0f,1.0f) * 10.0f;
	syoukaki.objPos = D3DXVECTOR3(2.0f,1.0f,1.5f); 
	Msh.push_back(&syoukaki); 
	//SE
	pati.Set(wav_fire);
	pati.m_b3DSound = TRUE;
	Snd.push_back(&pati);
	//���ˉ�
	syouka.Set(wav_water);
	syouka.m_b3DSound = TRUE;
	syouka.Filter.OneOverQ = 0.1f;
	Snd.push_back(&syouka);
	//�t���O
	flag = 0;
	frame = 0;
	//���΃e�L�X�g
	textFire.init(this);
	textFire.s(_T("�y���Ί�z��������"));

	textNoFire.init(this);
	textNoFire.s(_T("�R���Ă���"));

	//����
	gush.SetTex(bmp_smoke);
	gush.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 3.0f;
	gush.YPR = D3DXVECTOR3(0.0f,0.0f,270.0f);
	gush.Ext = 0.0f;
	gush.Height = 3.0f;
	gush.Speed = 0.05f;
	gush.drawSkip = TRUE;
	Prt.push_back(&gush);
}
VOID Fire::Set()
{
	syoukaki.SetPare(&P->gt.Null.mWorld);

	ML->E.Fs.Far = 10.0f;
	ML->E.Fs.Near = 1.5f;
	if(P->FM.iGetedFlag(ITEM_SYOUKAKI))
	{
		if(!P->FM.iGetFlag(ITEM_SYOUKAKI))
		{
			ML->E.Fs.Far = 30.0f;
			ML->E.Fs.Near = 0.0f;

			
		}
	}
}
VOID Fire::Update()
{
	if(P->FM.iGetedFlag(ITEM_SYOUKAKI))
	{
		if(!P->FM.iGetFlag(ITEM_SYOUKAKI))
		{
			if(ML->E.Fs.Far <= 30.0f){ML->E.Fs.Far  += 0.01f;}
			if(ML->E.Fs.Near>=  0.0f){ML->E.Fs.Near -= 0.005f;}
			fire.drawSkip = TRUE;
			smoke.drawSkip = TRUE;
			return;
		}
		else
		{
	
			if(flag == 0)
			{
				pati.Start(ML);
				pati.Emi.Position = table.objPos;
				//���ׂ�
				if(table.HitObj.Reaction == 1)
				if(P->Check)
				if(P->Mode != Personal::MODE_EVENT)
				{
					//�e�L�X�g�X�^�[�g
					textFire.StartText(P);		
				}
			}
			//�e�L�X�g�i�߂�
			if(textFire.Update(P,ML) == 1)
			{
				flag = 1;
			}
			if(flag == 1)
			{
				//���o�̃A���O��
				D3DXVECTOR3 v(table.objPos - P->obj.objPos);
				D3DXVec3Normalize(&v,&v);
				float angle = D3DXToDegree(atan2f(v.x,v.z));
				gush.objPos = D3DXVECTOR3(syoukaki.mWorld._41,syoukaki.mWorld._42 + 0.5f,syoukaki.mWorld._43);
				gush.YPR.y = angle - 90.0f;
				gush.drawSkip = FALSE; 
				//�v���C���[�̃A���O��
				P->Mode = Personal::MODE_EVENT;
				P->obj.YPR.y = angle;
				//���Ί�o��
				syoukaki.drawSkip = FALSE;	
				//���Ί퉹
				syouka.Emi.Position = syoukaki.objPos;
				syouka.Start(ML);
				//�t���[����i�߂ď���
				frame++;
				int time = 200;
				if(frame >= time){	flag = 2;}

				//�i�X�������Ȃ�
				float scl = (float)(time - frame) / (float)time;
				fire.objScal  = D3DXVECTOR3(1.0f,1.0f,1.0f) * 5.0f * scl;
				smoke.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 3.0f * scl;
				gush.objScal  = D3DXVECTOR3(1.0f,1.0f,1.0f) * 3.0f * scl;
			}
			if(flag == 2)
			{
				P->Mode = Personal::MODE_ACTIVE;
				//SE����
				syouka.Stop(ML,0.0f);
				pati.Stop(ML,0.0f);		
				//�I�u�W�F�N�g����
				syoukaki.drawSkip = TRUE;
				//�e�p�[�e�B�N������
				gush.drawSkip = TRUE;
				fire.drawSkip = TRUE;
				smoke.drawSkip = TRUE;
				flag = 3;
			}
			if(flag == 3)
			{
				P->FM.iRelease(ITEM_SYOUKAKI);
			}
		}
		
	}
	else
	{
		if(flag == 0)
		{
				pati.Start(ML);
				pati.Emi.Position = table.objPos;
				//���ׂ�
				if(table.HitObj.Reaction == 1)
				if(P->Check)
				if(P->Mode != Personal::MODE_EVENT)
				{
					//�e�L�X�g�X�^�[�g
					textNoFire.StartText(P);		
				}
		}
		//�e�L�X�g�i�߂�
		textNoFire.Update(P,ML);
	}
}
