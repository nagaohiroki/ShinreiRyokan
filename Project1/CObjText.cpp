
//===========================================================================
//�e�L�X�g�̕`��
//===========================================================================
CObjText::CObjText()
{
	txt = _T("Hello World");
	MeshCol =D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
	MaxLen = (int)_tcslen(txt);
	Length = FALSE;
	StrLen = -1;
	intrval = D3DXVECTOR2(1.1f,1.1f);
	D3DXMatrixIdentity(&mWorld);
	objPos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	objScal=D3DXVECTOR3(1.0f,1.0f,1.0f);
	YPR=D3DXVECTOR3(0.0f,0.0f,0.0f);
	Pare=NULL;
	MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
	drawSkip=FALSE;
	vol = D3DXVECTOR2(0.0f,0.0f);
} 
//�e�I�u�W�F�N�g���擾	
VOID CObjText::SetPare(const D3DXMATRIX* p)
{
	Pare = p;	
}
//�I�u�W�F�N�g�̍s��ϊ�
VOID CObjText::UpdateMat()
{
	D3DXMATRIX  mS;//�X�P�[���̍s��
	D3DXMATRIX  mR;//��]�̍s��
	//�s���������
	D3DXMatrixIdentity(&mWorld);
	// �g��k���p�̍s���ݒ�
	D3DXMatrixScaling(&mS,objScal.x ,objScal.y ,objScal.z );
	//��]�ݒ�
	D3DXMatrixRotationYawPitchRoll( &mR ,D3DXToRadian(YPR.y),D3DXToRadian(YPR.x),D3DXToRadian(YPR.z));
	//�X�P�[��*��]
	D3DXMatrixMultiply(&mWorld,&mS,&mR);
	//�ʒu�͍Ō��
	mWorld._41=objPos.x;
	mWorld._42=objPos.y;
	mWorld._43=objPos.z;
	//�e������ꍇ
	if(Pare){D3DXMatrixMultiply(&mWorld,&mWorld,Pare);}
}
VOID CObjText::SetText(TCHAR* t)
{
	txt = t;
	MaxLen = (int)_tcslen(txt);
}

int CObjText::Max()
{
	return MaxLen;
}


//���̕�����
int CObjText::wN(MyLibrary*ml)
{
	return (int)vol.x/ml->CSMin.FontSize;
}
//�i����
int CObjText::hN(MyLibrary* ml)
{
	return (int)vol.y/ml->CSMin.FontSize;

}


VOID CObjText::draw(MyLibrary* ML)
{
	if(ML->E.ShadowPassNum==1){return;}//�V���h�E�p�X�̏ꍇ�̓X���[
	if(drawSkip == TRUE){return;}
	//�c�����������ꍇ�I��
	if(Length == TRUE){Ldraw(ML);}
	else{Sdraw(ML);}

}

//������
VOID CObjText::Sdraw(MyLibrary* ML)
{
	
	if(ML->E.ShadowPassNum==1){return;}//�V���h�E�p�X�̏ꍇ�̓X���[
	if(drawSkip == TRUE){return;}
	int Len = MaxLen;
	int i = 0;
//	float x = 0.0f;
//	float y = 0.0f;
	vol = D3DXVECTOR2(0.0f,0.0f);
	float w,h;
	D3DXMATRIX mW;
	CFontTex* ft = NULL; 
	//�`�悷�镶���̐�
	if(StrLen != -1)
	{
		if(MaxLen >= StrLen){	Len = StrLen; 	}
	}
	//�����ŕύX���Ȃ�
	ML->E.vCol(&MeshCol);
	ML->E.BeginPass(fx::FVF_Tex);
	UpdateMat();
	for(i = 0; i < Len; i++)
	{
		ft = ML->CSMin.SetFontTex(ML->D,txt+ i);
		w = (float)(ft->rect.right - ft->rect.left);
		h = (float)(ft->rect.bottom - ft->rect.top);
	
#if _UNICODE
#else
		//�}���`�o�C�g�������ꍇ�J�E���g���ЂƂ���
		if( IsDBCSLeadByte( (BYTE)txt[i] ) ){i++;}
#endif		
		switch(ft->c[0])
		{
		case _T('\n')://���s�R�}���h
			vol.y -= h; 
			vol.x  = 0.0f;
			break;
		default://�ʏ핶��
			D3DXMatrixIdentity(&mW);
			D3DXMatrixScaling(&mW,w,h,1.0f);
			vol.x +=  w * 0.5f;		
			mW._41 = vol.x * intrval.x;
			mW._42 = vol.y * intrval.y;
			mW._43 = 0.0f;
			D3DXMatrixMultiply(&mW,&mW,&mWorld);//�r���{�[�h�I�u�W�F�N�g�̎q�ɂ���
			vol.x +=  w * 0.5f;
			ML->E.mWVP(&mW);
			ML->E.Tex(ft->pTex);	
			ML->F.SetStream(ML->D);	
			ML->E.CommitChange();
			ML->D->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			break;
		}
	}
}
//�c����
VOID CObjText::Ldraw(MyLibrary* ML)
{	
	
	if( ML->E.ShadowPassNum == 1 ){return;}//�V���h�E�p�X�̏ꍇ�̓X���[
	if( drawSkip == TRUE ){return;}
	int Len = MaxLen;
	int i = 0;
	
	vol = D3DXVECTOR2(0.0f,0.0f);
	float w,h;
	CFontTex* ft = NULL; 
	D3DXMATRIX mW;
	//�`�悷�镶���̐�
	if(StrLen != -1)
	{
		if( MaxLen >= StrLen ){	Len = StrLen; 	}
	}
	//�����ŕύX���Ȃ�
	ML->E.vCol(&MeshCol);
	ML->E.BeginPass(fx::FVF_Tex);
	UpdateMat();
	for(i = 0; i < Len; i++)
	{
		ft = ML->CSMin.SetFontTex(ML->D,txt+i);
		w = (float)(ft ->rect.right - ft ->rect.left);
		h = (float)(ft ->rect.bottom - ft ->rect.top);
	
#ifndef _UNICODE
		if(IsDBCSLeadByte((BYTE)txt[i])){i++;}//�}���`�o�C�g�������ꍇ�J�E���g���ЂƂ���
#endif		
		switch(ft ->c[0])
		{
		case _T('\n')://���s�R�}���h
			vol.x -= w * 2.0f; 
			vol.y  = 0.0f;
			break;
		default://�ʏ핶��
			D3DXMatrixIdentity(&mW);
			D3DXMatrixScaling(&mW,w,h,1.0f);
			vol.y -= h * 0.5f;	
			if( ft->c[0] == _T('�B') || ft->c[0] == _T('�A'))
			{
				mW._41 = vol.x * intrval.x  + w * 0.75f;
				mW._42 = vol.y * intrval.y  + h * 0.75f;
			}
			else
			{
				mW._41 = vol.x * intrval.x;
				mW._42 = vol.y * intrval.y;
			}
			mW._43 = 0.0f;
			D3DXMatrixMultiply(&mW,&mW,&mWorld);//�r���{�[�h�I�u�W�F�N�g�̎q�ɂ���
			vol.y -= h * 0.5f;
			ML->E.mWVP(&mW);
			ML->E.Tex(ft->pTex);	
			ML->F.SetStream(ML->D);	
			ML->E.CommitChange();
			ML->D->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			break;
		}
	}
}