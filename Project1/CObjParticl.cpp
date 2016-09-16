
//===========================================================================
//�p�[�e�B�N��
//===========================================================================
CParticl::CParticl()
{
	OverTime = 0.0f;
	timeLine = 0.0f;
	randVec	 = D3DXVECTOR3(0.0f,0.0f,0.0f);
	objPos   = D3DXVECTOR3(0.0f,0.0f,0.0f);
	objScal  = D3DXVECTOR3(1.0f,1.0f,1.0f);
	alpha = 1.0f;
}
CObjParticl::CObjParticl()
{
	Height = 1.0f;//����
	Ext    = 1.0f;//�L����
	Speed  = 0.01f;//���x
	PrtTime= 1.0f;//�p������
	Height = 4.0f;//����
	Ext    = 0.5f;//�L����
	Speed  = 0.01f;//���x
	PrtTime= 1.0f;//�p������
	BloomColor= D3DXVECTOR4(1.0f,1.0f,1.0f,10.0f);//���C�g�u���[��
	objScal   = D3DXVECTOR3(8.0f,8.0f,8.0f);//���q�̑傫��
	TexType = 0;
	ML = NULL;

	int i;
	CParticl pt;
	for(i = 0;i < 4;i++)
	{
		prt.push_back(pt);
	}

	//�ϐ��̏�����
	D3DXMatrixIdentity(&mWorld);
	D3DXMatrixIdentity(&mR);	
	objPos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	YPR=D3DXVECTOR3(0.0f,0.0f,0.0f);
	Pare=NULL;
	MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
	drawSkip=FALSE;
	
}
CObjParticl::~CObjParticl()
{
	if(ML != NULL)
	{
		ML->T.Release(TexType);
	}
}
//������Ԃ������͗����͈̔�(�ŏ��͈�,�ő�͈�)
float CObjParticl::randf(float min,float max)
{
	return ((float)rand() * ( max -min)/ (float)RAND_MAX) + min;
}

//�e�I�u�W�F�N�g���擾	
VOID CObjParticl::SetPare(const D3DXMATRIX* p)
{
	Pare = p;	
}
VOID CObjParticl::Update(CParticl* p)
{
	//�^�C�����C����i�߂�
	p->timeLine += Speed;
	//�^�C�����C�����p�����Ԃ��z������
	if(p->timeLine > p->OverTime)
	{
		p->timeLine = 0.0f;
		//���q�̍L����
		p->randVec.x = randf(-Ext,Ext);
		p->randVec.y = Height;
		p->randVec.z = randf(-Ext,Ext);
		//�p������
		p->OverTime  = randf(0.0f,PrtTime);
	}	
	//���q�̓���
	D3DXVECTOR3 out;	
	D3DXVec3TransformCoord(&out,&(p->randVec * p->timeLine),&mR);	
	p->objPos = objPos + out;
	//�A���t�@�𔖂�
	p->alpha= ( -p->timeLine + p->OverTime ) / p->OverTime;
	//���q�̑傫��
	p->objScal = objScal * p->timeLine;

}

VOID CObjParticl::SetTex(arc textype)
{
	if(ML == NULL)
	{
		TexType = textype;
	}
}

VOID CObjParticl::draw(MyLibrary* ml)
{
	if(drawSkip){return;}
	if(ml->E.ShadowPassNum==1){return;}//�V���h�E�p�X�̏ꍇ�̓X���[
	if(ML == NULL)
	{
		ML = ml;
		it = ML->T.load(TexType,ML->D,&ML->af,ML->fp);
	}
	//�J�����̕���������
	D3DXVECTOR3 o(0.0f,0.0f,0.0f);
	D3DXMATRIX  mS;//�X�P�[���̍s��
	
	D3DXMATRIX mR1;
	vec3Ari().AtLookYpr(&o,&ML->E.cam.Eye,&ML->E.cam.At);
	D3DXMatrixRotationYawPitchRoll(&mR1,D3DXToRadian(o.y),D3DXToRadian(o.x - 90.0f),D3DXToRadian(YPR.z));
	D3DXMatrixRotationYawPitchRoll(&mR,D3DXToRadian(YPR.y),D3DXToRadian(YPR.x),D3DXToRadian(YPR.z));	
//	ML->E.Tex(ML->T.Retex(TexType));

	if(it != ML->T.tex.end()){
		ML->E.Tex((*it).second->m_pTex);
	}
	ML->E.BeginPass(fx::FVF_Tex_One);
	int i;	
	int size = prt.size();
	for(i = 0; i < size; i++ )
	{
		Update(&prt[i]);
		D3DXMatrixScaling(&mS,prt[i].objScal.x,prt[i].objScal.y,prt[i].objScal.z);
		D3DXMatrixMultiply(&mWorld,&mS,&mR1);
		mWorld._41 = prt[i].objPos.x;
		mWorld._42 = prt[i].objPos.y;
		mWorld._43 = prt[i].objPos.z;	
		D3DXVECTOR4 Col(MeshCol.x,MeshCol.y,MeshCol.z,MeshCol.w * prt[i].alpha);
		ML->E.vCol(&Col);
		ML->E.BloomColor(&BloomColor);
		ML->E.mWVP(&mWorld);	
		ML->F.SetStream(ML->D);
		ML->E.CommitChange();
		ML->D->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2);	
	}
}