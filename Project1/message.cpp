//�A�C�e��
const TCHAR *Item_Light::name(){return _T("Item");}	
Item_Light::Item_Light()
{
	Msh.push_back(&Box);
	Box.Type(x_cube);
	Box.HitMode(CT_OBB,CB_NONE);
	Box.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f);
	gt.init(this);
	gt.s(_T("�A�C�e��Get!!"));
}
VOID Item_Light::Update()
{
	if(P->FM.iGetFlag(ITEM_LIGHT))
	{
		Box.drawSkip = TRUE;
		return;
	}
	if(Box.HitObj.Reaction == 1)	//�C�x���g�ɐG��Ă���ꍇ
	if(P->Mode != Personal::MODE_EVENT)	//�C�x���g���[�h����Ȃ��ꍇ
	if(P->Check)//�`�F�b�N�����ꍇ
	{
		gt.StartText(P);
	}
	if(gt.Update(P,ML) == 1)
	{
		P->FM.iGet(ITEM_LIGHT);
		P->FM.iGet(ITEM_DARTS);
		P->FM.iGet(ITEM_MASUI);

	}

}
//���b�Z�[�W
const TCHAR *Message::name(){return _T("Message");}
Message::Message()
{
	
	Msh.push_back(&Box);
	Box.Type(x_cube);
	Box.HitMode(CT_OBB,CB_PLUS);
	//�c�����̏ꍇ
	Snd.push_back(&mSnd);
	mSnd.Set(wav_ooo);
	mSnd.m_b3DSound = TRUE;
	mSnd.m_bLoop = TRUE;

	gt.init(this);
	gt.s(_T("��������"));
	gt.s(_T("�F��ς���H\n �ɂ���\n �Ԃɂ���"),2,3);
	gt.s(_T("���Ȃ���"),4);
	gt.s(_T("�Ԃ��Ȃ���"));

}


VOID Message::Update()
{

	if(Box.HitObj.Reaction == 1)//�����蔻�肪����
	if(P->Mode != Personal::MODE_EVENT)//�C�x���g���[�h����Ȃ��ꍇ
	if(P->Check)	//�`�F�b�N�����ꍇ
	{
		gt.StartText(P);
	}		
	int On = gt.Update(P,ML);

	if(On == 2)
	{
		Box.BloomColor=D3DXVECTOR4(0.0f,0.0f,20.0f,1.0f);
		mSnd.Stop(ML,0.0f);
	}
	if(On == 3)
	{
		Box.BloomColor=D3DXVECTOR4(20.0f,0.0f,0.0f,1.0f);
		mSnd.Start(ML);
	}
	mSnd.Emi.Position = Box.objPos;
	
}

VOID Message::DebugText(TCHAR* dt,int Len)
{

	gt.DebugText(dt,Len);
	_stprintf_s(dt,Len,
	_T("%s\ntxt\n")
	,dt

	
	);

}

