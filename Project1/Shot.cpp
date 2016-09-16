//�e
CBullet::CBullet()
{
	_stprintf_s(txt,500,_T(""));

	Energy = 0.0f;//�i�s��
	G = 0.0f;//�d��
	Move = FALSE;//�����Ă��邩
	pos = D3DXVECTOR3(0.0f,0.0f,0.0f);//���ˈʒu
	vec = D3DXVECTOR3(0.0f,0.0f,0.0f);//���ˊp�x
	//�e�����蔻��
	Bullet.Type(x_sphere);
	Bullet.drawSkip = TRUE;
	Bullet.HitMode(CT_SPHERE,CB_NONE);
	Bullet.objScal= D3DXVECTOR3(1.0f,1.0f,1.0f)*0.1f;
	Bullet.MeshCol.w = 0.2f; 
	//�\���I�u�W�F�N�g
	dobj.Type(x_darts);
	dobj.SetPare(&Bullet.mWorld);
	dobj.objPos = D3DXVECTOR3(0.0f,0.0f,-0.5f);
	dobj.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 1.5f;
	dobj.SpCol.w = 8.0f;
	dobj.BloomColor.w = 5.0f;
	//������
	D3DXMatrixIdentity(&mC);
	//�q�b�gSE
	SEHit.Set(wav_step2);
	SEHit.m_b3DSound = TRUE;
	SEHit.m_fVol = 1.0f;
	SEHit.Emi.DopplerScaler = 1.0f;
	SEHit.Filter.Frequency = 0.36f;
	SEHit.Filter.OneOverQ = 0.7252f;
	SEHit.Filter.Type = HighPassFilter;
}
//�e�̏���
VOID CBullet::Init(D3DXVECTOR3* v,D3DXVECTOR3* p)
{	
	if(Move == FALSE)
	{
		D3DXVec3Normalize(&vec,&(*v - *p));
		pos = *p + D3DXVECTOR3(0.0f,0.0f,0.0f);
		Bullet.SetPare(NULL);
		Bullet.YPR.x =  180.0f - D3DXToDegree(atan2f(vec.y, fabsf(vec.x)+fabsf(vec.z)));
		Bullet.YPR.y = D3DXToDegree(atan2f(vec.x,vec.z));
		Bullet.YPR.z= 0.0f;
		Bullet.objPos = pos;
		dobj.drawSkip = FALSE;
		Energy = 0.0f;	
		G = 0.0f;
		Move = TRUE; 
		Bullet.mCustom = NULL;		
	}	
}
//��\��
VOID CBullet::Reset()
{
	//�t��]�A�e����
	Bullet.mCustom = NULL;
	Bullet.Pare = NULL;
	dobj.drawSkip = TRUE;

	Move = FALSE;
}
//�����蔻��
VOID CBullet::HitEvent(std::vector<CollObj*>* c,MyLibrary* ml)
{	
	if(Move == FALSE){	return;	}	
	UINT i;
	UINT j;
	UINT size = c->size();
	UINT m_iAccuracy = 3;//�����蔻���
	if(Energy > 100.0)
	{
		dobj.drawSkip = TRUE;
		Move = FALSE;
		return;
	}
	G -= 0.0001f;	
	for(j = 0; j < m_iAccuracy; j++)
	{
		Energy += 0.2f;	
		Bullet.objPos =  pos + vec * Energy;
		vec.y += G;
		Bullet.SetHit(ml);
		for(i = 0;i <  size; i++)
		{
			if(ml->Col.Hit(&Bullet.HitObj,c->at(i)))
			{
				c->at(i)->Reaction = 2;
				if(c->at(i)->cBack == CB_PLUS || c->at(i)->cBack == CB_ENEMY)
				{

					//�T�E���h
					SEHit.Emi.Velocity = Bullet.objPos;
					SEHit.Emi.Position = Bullet.objPos;
					SEHit.Start(ml);

					//��~���ďI��
					Bullet.objPos += Bullet.HitObj.vBack;
					Move = FALSE;
					return;
				}
			}
		}
	}
}

//���̃I�u�W�F�N�g�ɂ�����
VOID CBullet::Attach(D3DXMATRIX* mat)
{	
	Bullet.SetPare(mat);	
	D3DXMATRIX invMat;
	D3DXMatrixInverse(&invMat,0,mat);
	D3DXMatrixMultiply(&mC,&Bullet.mWorld,&invMat);
	Bullet.mCustom = &mC;
}
//�`��
VOID CBullet::draw(MyLibrary* ml)
{	
	Bullet.SetSize(ml);
	dobj.draw(ml);
	Bullet.draw(ml);	
}
//�f�o�b�O
VOID CBullet::Debug(int len,TCHAR* t)
{
	_stprintf_s(t,len,
		_T("%s%s\n")
		,t,txt
		);
}
