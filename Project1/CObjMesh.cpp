//===========================================================================
//���b�V���I�u�W�F�N�g
//===========================================================================
CObjMesh::CObjMesh()
{
	ML = NULL;	
	//�ϐ��̏�����
	D3DXMatrixIdentity(&mWorld);	
	objPos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	objScal=D3DXVECTOR3(1.0f,1.0f,1.0f);
	YPR=D3DXVECTOR3(0.0f,0.0f,0.0f);
	Pare=NULL;
	MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
	drawSkip=FALSE;
	//�`����
	MdlType=0;// �I�u�W�F�N�g�̃��f���̎��
	MeshCol=D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);//�炢�Ƃ̐F(w�̓A���t�@)
	SpCol=D3DXVECTOR4(1.0f,1.0f,1.0f,10.0f);//�X�y�L����(w�̓p���[)
	SpColm=0.5f;//�X�y�L�����̑���
	ShadowFlag=TRUE;//�e�����邩	
	Amb=1.0f;//�A�r�G���g�̖��邳
	Shadow=0.8f;//�e�̔���
	Bias=0.035f;//�e�̃o�C�A�X
	BloomColor=D3DXVECTOR4(1.0f,1.0f,1.0f,0.0f);//���C�g�u���[��
	Height=0.016f;
	mCustom = NULL;

}
CObjMesh::~CObjMesh()
{
	if(ML != NULL)
	{
		DWORD i;
		for(i = 0; i < itMod->second->m_dwMatNum; i++)
		{
			ML->T.Release(itMod->second->m_pCMtrl[i].m_iTex);
			ML->T.Release(itMod->second->m_pCMtrl[i].m_iNTex);	
		}
		ML->M.Release(MdlType);
	}
}
//�e�I�u�W�F�N�g���擾	
VOID CObjMesh::SetPare(const D3DXMATRIX* p)
{
	Pare = p;	
}

//�I�u�W�F�N�g�̍s��ϊ�
VOID CObjMesh::UpdateMat()
{
	if(mCustom)
	{
		//�s��������Őݒ肷��ꍇ
		mWorld = *mCustom;
	}
	else
	{	//��]
		D3DXMatrixRotationYawPitchRoll(&mWorld,D3DXToRadian(YPR.y),D3DXToRadian(YPR.x),D3DXToRadian(YPR.z));
		//�傫��
		mWorld._11 *= objScal.x; 
		mWorld._12 *= objScal.x; 
		mWorld._13 *= objScal.x; 
		mWorld._21 *= objScal.y; 
		mWorld._22 *= objScal.y; 
		mWorld._23 *= objScal.y; 
		mWorld._31 *= objScal.z; 
		mWorld._32 *= objScal.z; 
		mWorld._33 *= objScal.z; 
		//�ʒu
		mWorld._41 = objPos.x;
		mWorld._42 = objPos.y;
		mWorld._43 = objPos.z;
	}
	
	//�e������ꍇ
	if(Pare)
	{
		D3DXMatrixMultiply(&mWorld,&mWorld,Pare);
	}
	
}
VOID CObjMesh::SetSp()
{
	//�s�񂩂�X�P�[��
	D3DXVECTOR3 MatScl(
	D3DXVec3Length(&D3DXVECTOR3(mWorld._11,mWorld._12,mWorld._13)),
	D3DXVec3Length(&D3DXVECTOR3(mWorld._21,mWorld._22,mWorld._23)),
	D3DXVec3Length(&D3DXVECTOR3(mWorld._31,mWorld._32,mWorld._33)));
	//����̔��a
	*HitObj.Len() =itMod->second->Sren * vec3Ari().D3DXVec3Top(&MatScl);
	//���S�ʒu
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	mat._41 = itMod->second->Center.x;
	mat._42 = itMod->second->Center.y;
	mat._43 = itMod->second->Center.z;
	D3DXMatrixMultiply(&mat,&mat,&mWorld);
	HitObj.Pos()->x = mat._41;
	HitObj.Pos()->y = mat._42;
	HitObj.Pos()->z = mat._43;
}
VOID CObjMesh::SetObb()
{
	//�s�񂩂�X�P�[��
	D3DXVECTOR3 MatScl(
	D3DXVec3Length(&D3DXVECTOR3(mWorld._11,mWorld._12,mWorld._13)),
	D3DXVec3Length(&D3DXVECTOR3(mWorld._21,mWorld._22,mWorld._23)),
	D3DXVec3Length(&D3DXVECTOR3(mWorld._31,mWorld._32,mWorld._33)));
	//���S�ʒu	
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	mat._41 = itMod->second->Center.x;
	mat._42 =itMod->second->Center.y;
	mat._43 = itMod->second->Center.z;
	D3DXMatrixMultiply(&mat,&mat,&mWorld);
	HitObj.Pos()->x = mat._41;
	HitObj.Pos()->y = mat._42;
	HitObj.Pos()->z = mat._43;

	//�e������
	D3DXVec3Normalize(HitObj.vX(),&D3DXVECTOR3(mWorld._11,mWorld._12,mWorld._13));
	D3DXVec3Normalize(HitObj.vY(),&D3DXVECTOR3(mWorld._21,mWorld._22,mWorld._23));
	D3DXVec3Normalize(HitObj.vZ(),&D3DXVECTOR3(mWorld._31,mWorld._32,mWorld._33));	
	//����̔��a
	*HitObj.Len() = itMod->second->Sren * vec3Ari().D3DXVec3Top(&MatScl);
	//�e�ӂ̔��a
	HitObj.Vec()->x = itMod->second->ren.x * MatScl.x;
	HitObj.Vec()->y = itMod->second->ren.y * MatScl.y;
	HitObj.Vec()->z = itMod->second->ren.z * MatScl.z;		
}



VOID CObjMesh::Type(arc xmod)
{
	if(ML == NULL)
	{
		MdlType = xmod;
	}
}
VOID CObjMesh::SetSize(MyLibrary* ml)
{
	if(ML == NULL)
	{
		ML = ml;
		itMod = ML->M.Load(MdlType,ML->D,&ML->af,ML->fp);
		for(DWORD i = 0; i < itMod->second->m_dwMatNum; i++)
		{
	
			itT.push_back( ML->T.load(itMod->second->m_pCMtrl[i].m_iTex, ML->D,&ML->af,ML->fp));
			itNT.push_back(ML->T.load(itMod->second->m_pCMtrl[i].m_iNTex,ML->D,&ML->af,ML->fp));
		}
	}
	UpdateMat();
}
VOID CObjMesh::SetHit(MyLibrary* ml) 
{
	SetSize(ml);

	switch(HitObj.cType)
	{
	case CT_OBB:	SetObb();	break;
	case CT_SPHERE:	SetSp();	break;
	default:break;
	}
	
}
VOID CObjMesh::HitMode(COLLISION_TYPE ct,COLLISION_BACK cb)
{
	HitObj.cType = ct;
	HitObj.cBack = cb;
}

//�ʏ�`��
VOID CObjMesh::MeshDraw()
{
	//�I�u�W�F�N�g�ŗL�̑傫��
	//�e�I�u�W�F�N�g
	//������J�����O
	SetSp();//���E���̃Z�b�g
	if(ML->E.Culling(HitObj.Pos(),*HitObj.Len())){return;}
	DWORD j0;	
	ML->E.mWVP(&mWorld);//���[���h�g�����X	
	//�|�C���g�X�|�b�g���C�g�̔���
	ML->E.LightLamSpc(&mWorld,Amb);
	D3DXVECTOR3 Lc(ML->E.LightCol());
	//���ʔ��˂̐F
	ML->E.SpCol(&D3DXVECTOR4(
		SpCol.x * SpColm * Lc.x,
		SpCol.y * SpColm * Lc.y,
		SpCol.z * SpColm * Lc.z,
		SpCol.w));	//�p���[
	//���C�g�u���[���J���[
	ML->E.BloomColor(&D3DXVECTOR4(
		BloomColor.x * BloomColor.w,
		BloomColor.y * BloomColor.w,
		BloomColor.z * BloomColor.w,
		1.0f));
		
	//�e�̔Z���ƃo�C�A�X
	ML->E.ShadowBias(Bias,Shadow);
	//�X�|�b�g���C�g
	ML->E.SetPLCol(&MeshCol);		
	D3DXVECTOR3 v(  MeshCol.x * Lc.x,
					MeshCol.y * Lc.y,
					MeshCol.z * Lc.z);
	ML->E.BeginPass( itMod->second->TexPass);
	for(j0 = 0; j0 < itMod->second->m_dwMatNum; j0++ )
	{	
		//���b�V���̃J���[
		ML->E.vCol(&D3DXVECTOR4(
			itMod->second->m_pCMtrl[j0].m_Mtrl.Diffuse.r * v.x,
			itMod->second->m_pCMtrl[j0].m_Mtrl.Diffuse.g * v.y,
			itMod->second->m_pCMtrl[j0].m_Mtrl.Diffuse.b * v.z,
			MeshCol.w));
		
		//�e�N�X�`�����Z�b�g
		if(itT[j0] != ML->T.tex.end())
		{
			ML->E.Tex(itT[j0]->second->m_pTex);
		}

		if(itNT[j0] != ML->T.tex.end())
		{
			ML->E.MTex(itNT[j0]->second->m_pTex);
		}

		ML->E.CommitChange();	
		//���b�V���E�T�u�Z�b�g�̕`��
		itMod->second->m_pMesh->DrawSubset( j0 );
	}
}
VOID CObjMesh::ShadowDraw()
{
	//�V���h�E�}�b�v	
	if(!ShadowFlag){return;}	
	ML->E.mWVP(&mWorld);//���[���h�g�����X
	//������J�����O
	if(ML->E.Culling(HitObj.Pos(),*HitObj.Len())){return;}
	DWORD j0;
	ML->E.vCol(&D3DXVECTOR4(0.1f,0.1f,0.1f,0.1f));
	switch(itMod->second->TexPass)
	{
	case fx::Mesh_AlphaTex:
		//���b�V��(�e�N�X�`�����胿�e�N�X�`���p)
		ML->E.BeginPass(fx::ShadowAlphaMap);
		for(j0=0; j0 < itMod->second->m_dwMatNum ; j0++ )
		{
			//�e�N�X�`�����Z�b�g
			if(itT[j0] != ML->T.tex.end())
			{
				ML->E.Tex(itT[j0]->second->m_pTex);
			}
			ML->E.CommitChange();
			itMod->second->m_pMesh->DrawSubset(j0);
		}			
		break;
	default:
		//���b�V���݂̂ŕ`��
		ML->E.BeginPass(fx::ShadowMap);
		for(j0=0; j0 < itMod->second->m_dwMatNum; j0++ )
		{
			ML->E.CommitChange();
			itMod->second->m_pMesh->DrawSubset(j0);
		}
		break;		
	}	
}

VOID CObjMesh::draw(MyLibrary* ml)
{
	if(drawSkip == TRUE){return;}
	if(ml->E.ShadowPassNum == 0)
	{
		MeshDraw();
	}
	else
	{
		SetSize(ml);//�V���h�E�}�b�v���ɌĂяo���̂Ő�Ɏ擾	
		ShadowDraw();
	}
}