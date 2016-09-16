
//====================================
//�󒲂̃X�C�b�`
//====================================
const TCHAR *AirSwitch::name(){return _T("AirSwitch");}
AirSwitch::AirSwitch()
{
	//�����蔻��
	Msh.push_back(&hitbox);
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.drawSkip = TRUE;
	hitbox.MeshCol.w = 0.5f;
	//���
	Msh.push_back(&pBase);
	pBase.Type(x_cube);
	pBase.SetPare(&hitbox.mWorld);
	pBase.objScal=D3DXVECTOR3(0.2f,0.4f,0.04f);
	pBase.MeshCol=D3DXVECTOR4(0.6f,0.6f,0.6f,1.0f);
	pBase.ShadowFlag=FALSE;
	pBase.SpColm=0.0f;
	//�X�C�b�`����
	Msh.push_back(&pSwitch);
	pSwitch.Type(x_cube);
	pSwitch.SetPare(&pBase.mWorld);
	pSwitch.objScal=D3DXVECTOR3(0.5f,0.15f,0.2f);
	pSwitch.objPos=D3DXVECTOR3(0.0f,0.0f,-0.35f);
	pSwitch.MeshCol=D3DXVECTOR4(0.9f,0.9f,0.9f,1.0f);
	pSwitch.YPR.y=-45.0f;
	pSwitch.ShadowFlag=FALSE;
	//�e�L�X�g
	text.init(this);
	text.s(_T("�󒲂̂ӂ����O�ꂩ�����Ă���"));
	text.s(_T("�󒲂��~�߂�H\n�~�߂�\n���̂܂܂ɂ��Ă���"),2,3);
	text.s(_T("�󒲂��~�߂�"));
}
VOID AirSwitch::Update()
{
	int tt = text.Update(P,ML);
	//�󒲂��~�߂�
	if(P->FM.EventFlag == 5 || P->FM.EventFlag == 6)
	{
		if(tt == 2){P->FM.EventFlag = TL_GUEST_ENEMY_START; }
	
		//�e�L�X�g
		if(hitbox.HitObj.Reaction == 1)
		if(P->Mode != Personal::MODE_EVENT)
		if(P->Check)
		{
			text.StartText(P);
		}
	}
}
//====================================
//��
//====================================
const TCHAR *Air::name(){return _T("Air");}
Air::Air()
{
	//��
	Msh.push_back(&Null);
	Null.Type(x_cube);
	Null.MeshCol.w = 0.5f;
	Null.drawSkip = TRUE;
	//��
	Msh.push_back(&air);
	air.Type(x_tdact);
	air.SetPare(&Null.mWorld);
	air.objPos.y = -0.25f;
	air.Bias = 0.5f;
	//��
	Snd.push_back(&gangan);
	gangan.Set(wav_keylock);
	gangan.m_b3DSound = TRUE;
	//�󒲉�
	Snd.push_back(&airSe);
	airSe.Set(wav_ari);
	airSe.m_b3DSound = TRUE;
	airSe.m_bLoop = TRUE;
	airSe.Filter.Frequency = 0.8f;
	airSe.Filter.OneOverQ= 1.5f;
	//�A�j���[�V����
	frame = 0;
	anim.SetKey(0,0.0f);
	anim.SetKey(60,0.0f);
	anim.SetKey(90,-15.0f);
	anim.SetKey(100,0.0f);
	anim.SetKey(110,-15.0f);
	anim.SetKey(140,0.0f);
	anim.SetKey(200,0.0f);
	anim.SetKey(220,-15.0f);
	anim.SetKey(250,0.0f);
	anim.SetKey(300,0.0f);

}
VOID Air::Update()
{
	if(frame == 100 || frame == 140 || frame == 250  )
	{
		if(frame == 250){gangan.m_fVol = 2.0f;}
		else{gangan.m_fVol = 1.0f;}
		gangan.Emi.Position = air.objPos;
		gangan.Start(ML);
	}
	Null.YPR.x = anim.Val(frame);
	Null.SetHit(ML);
	if(P->FM.EventFlag >= 7)
	{
		airSe.Stop(ML,0.0f);
		frame = 0;
	}
	//������
	if(P->FM.EventFlag == 5 || P->FM.EventFlag == 6)
	{
		airSe.Start(ML);
		frame++;
		if(frame > 300){frame = 0;}
	}
}
VOID Air::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,
		_T("%s")
		_T("frame = %d")
		,t
		,frame
		);
}
