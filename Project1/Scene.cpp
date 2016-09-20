//=============================================
//�t�B�[���h�̃x�[�X
//=============================================
//�R���X�g���N�^
Scene::Scene()
{
	//�f�o�b�O�p
	m_iHir = 0;
	m_iEvent= 0;
	m_iSelect = 0;
	m_iObjType = 0;
	m_iObjNum = 0;
	int i;
	for(i = 0; i < 6;i++)
	{
		HitEriaObj[i].Type(x_cube);
		HitEriaObj[i].drawSkip = TRUE;
	}

	//�I�u�W�F�N�g
	m_pPare = NULL;
	ML = NULL;
	P = NULL;
}
//�f�X�g���N�^
Scene::~Scene()
{
	//�q�̔j��
	for(std::vector<Scene*>::iterator it = m_pChild.begin(); it != m_pChild.end(); ++it)
	{
		SAFE_DELETE(*it);
	}
}
//���z�֐�==========================================================
VOID Scene::Set(){}
VOID Scene::Update(){}
VOID Scene::draw(){}
VOID Scene::UI(){}
//�f�o�b�O�p�e�L�X�g(���z)
VOID Scene::DebugText(TCHAR* t,int len)
{
	_stprintf_s(t,len,_T("%s"),t);
} 
//�N���X�̖��O
const TCHAR* Scene::name()
{
	return _T("noname");
}
//�f�o�b�O�{�^��
VOID Scene::DebugBtn(DebugButton*){}
//�h���N���X�Ŏg���֐�==========================================================
//�G���A�̓����蔻��(��`�ŏ��l�A�ő�l)
VOID Scene::EriaHit(D3DXVECTOR3* Min,D3DXVECTOR3* Max)
{
	if(Pl.size() < 6)
	{
		int i;
		for(i = 0; i < 6; i++)
		{
			Plane p;
			p.cBack= CB_PLUS;
			p.cType= CT_PLANE;
			Pl.push_back(p);
		}
	}
	//+X�̕�
	*Pl[0].Pos() = D3DXVECTOR3( Max->x,0.0f,0.0f);
	*Pl[0].Vec() = D3DXVECTOR3(-1.0f,0.0f,0.0f);
	//-X�̕�
	*Pl[1].Pos() = D3DXVECTOR3( Min->x,0.0f,0.0f);
	*Pl[1].Vec() = D3DXVECTOR3( 1.0f,0.0f,0.0f);
	//+Y
	*Pl[3].Pos() = D3DXVECTOR3(0.0f,Max->y,0.0f);
	*Pl[3].Vec() = D3DXVECTOR3(0.0f,-1.0f,0.0f);
	//-Y
	*Pl[2].Pos() = D3DXVECTOR3(0.0f,Min->y,0.0f);
	*Pl[2].Vec() = D3DXVECTOR3(0.0f, 1.0f,0.0f);
	//+Z�̕�
	*Pl[4].Pos() = D3DXVECTOR3(0.0f,0.0f,Max->z);
	*Pl[4].Vec() = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	//-Z�̕�
	*Pl[5].Pos() = D3DXVECTOR3(0.0f,0.0f,Min->z);
	*Pl[5].Vec() = D3DXVECTOR3(0.0f,0.0f, 1.0f);


}
//�t�B�[���h�J��
VOID Scene::FldChange(Scene* Bf,D3DXVECTOR3 *Pos,float RotY)
{
	P->FM.StaticPos(Pos,RotY);//�L�����̎p��
	//�Z����쐬
	m_pPare->AddField(Bf);
}
//�C�x���g���擾
Scene* Scene::NewObj(Scene* bo)
{
	m_pChild.push_back(bo);
	m_pChild.back()->m_pPare = this;
	return m_pChild.back();
}
//�����Ŏg�p����֐�==============================================================
//�g��Ȃ��t�B�[���h���폜
VOID Scene::DeleteField()
{
	for(std::vector<Scene*>::iterator it = m_pChild.begin(); it != m_pChild.end(); ++it)
	{
		//m_iSelect�ȊO���폜
		if( it - m_pChild.begin() != m_iSelect )
		{
			SAFE_DELETE(*it);
		}
	}
}
//�I�u�W�F�N�g�ƊO���I�u�W�F�N�g���Z�b�g
VOID Scene::Main_Set(Personal* p,MyLibrary* ml)
{
	P  = p;
	ML = ml;
	//�G�t�F�N�g�̏�����
	ML->E.InitEffect();
	//�t�B�[���h�̃Z�b�g
	//�O�g�̓����蔻��
	EriaHit(&D3DXVECTOR3(-10.0f,0.0f,-10.0f),&D3DXVECTOR3(10.0f,10.0f,10.0f));
	//�����f�[�^���폜
	ML->CSMin.Reset();
	//�v���C���[�Z�b�g
	P->Set(ML);
	//�t�B�[���h�̃Z�b�g
	Obj_Set(P,ML);	
	//�Ǐ��̓����蔻��
	for(std::vector<Plane>::iterator it = Pl.begin(); it != Pl.end(); ++it)
	{
		HitObj.push_back(&(*it));
	}	
	//�q�̃��b�V���I�u�W�F�N�g���瓖���蔻��𒊏o
	for(std::vector<Scene*>::iterator it = m_pChild.begin(); it != m_pChild.end(); ++it)
	{
		if((*it))
		{
			//�����蔻��I�u�W�F�N�g���쐬
			(*it)->Obj_Set(p,ml);
			for(std::vector<CObjMesh*>::iterator it2 = (*it)->Msh.begin(); it2 != (*it)->Msh.end(); ++it2)
			{
				if((*it2)->HitObj.cType != CT_NONE)
				{
					HitObj.push_back(&(*it2)->HitObj);
				}
			}
		}
	}
	
}	
//�X�V
VOID Scene::Main_Update()
{
	//�v���C���[�̍X�V
	P->Update();	
	//���j���[���J���ꍇ�t�B�[���h���X�V���Ȃ�
	if(P->Mode == Personal::MODE_MENU)
	{
		if(P->ReLoad != 0)
		{
			//�^�C�g���ɖ߂�
			if(P->ReLoad == 1)
			{
				FldChange(new Fld::Title,&D3DXVECTOR3(0.0f,0.0f,0.0),0.0f);
			}
			P->ReLoad = 0;
		}
		return;
	}
	//�v���C���[�ƃI�u�W�F�N�g�����蔻��
	P->HitEvent(&HitObj);
	//�t�B�[���h�̍X�V
	Obj_Update();
	//�C�x���g�̍X�V	
	for(std::vector<Scene*>::iterator it = m_pChild.begin(); it != m_pChild.end(); ++it)
	{
		if((*it))
		{
			(*it)->Obj_Update();	
		}
	}
}
//�`��
VOID Scene::Mat_draw()
{
	//���j���[���J���Ă���Ƃ��͕`�悵�Ȃ�
	if(P->Mode == Personal::MODE_MENU){return;}
	P->draw();
	//�t�B�[���h
	Obj_Draw();
	//�C�x���g
	for(std::vector<Scene*>::iterator it = m_pChild.begin(); it != m_pChild.end(); ++it)
	{
		if((*it))
		{
			(*it)->Obj_Draw();
		}
	}
	//�f�o�b�O�p�I�u�W�F�N�g
	for(int i = 0; i < 6;i++)
	{
		HitEriaObj[i].draw(ML);
	}
}
//�e�L�X�g�̕`��
VOID Scene::UI_draw()
{
	P->Ui();
	if(P->Mode == Personal::MODE_MENU)
	{	
		return;
	}

	//�t�B�[���h
	Obj_UI();
	//�C�x���g
	for(std::vector<Scene*>::iterator it = m_pChild.begin(); it != m_pChild.end(); ++it)
	{
		if((*it))
		{
			(*it)->Obj_UI();	
		}
	}
}
//�`��
VOID Scene::Main_draw()
{
	//�o�b�N�o�b�t�@�p
	CObjFVF Back;
	D3DXVECTOR3 WindowSize = D3DXVECTOR3((float)ML->GV.ClientWidth,(float)ML->GV.ClientHeight,0.0f);
	Back.objPos.z = 1.0f;
	Back.objScal = WindowSize;
	//�}���`�����_�����O�T�[�t�F�C�X���J�n================================================================	
	ML->E.begin();		
	//�V���h�E�}�b�v-------------------------------------------
	ML->E.BeginSh();//�V���h�E�}�b�v���N��
	ML->Sf.Begin(SU_SHADOWMAP,ML->D);
	//�S�ĕ`��(�V���h�E�}�b�v�ɏ�������)
	if(ML->E.ShadowFlag == TRUE){	Mat_draw();	}
	ML->E.ShadowMapSet(ML->Sf.Retex(SU_SHADOWMAP));//�V���h�E�}�b�v���Z�b�g�V���h�E�}�b�v�I��	
	
	//��
	if(ML->E.MirrorFlag == TRUE)
	{
		ML->E.MirrorPass = 1;
		Cam c;
		c.Cast(&ML->E.cam);
		ML->E.cam.Cast(&ML->E.Mirrorcam);
		ML->E.UpdateCam();
		ML->Sf.Begin(SU_MIRROR,ML->D);
		Mat_draw();	
		ML->E.cam.Cast(&c);
		ML->E.UpdateCam();
		ML->E.MirrorPass = 0;
	}

	//�S�ĕ`��
	ML->Sf.Begin(SU_HDR,ML->D);
	ML->Sf.Begin(SU_TONE,ML->D);
	Mat_draw();
	ML->D->SetRenderTarget(1,NULL);//�p�X1������

	//�|�X�g�G�t�F�N�g----------------------------------------
	//�X�N���[���`��
	//�E�B���h�E�T�C�Y	
	ML->E.ScreenView(ML->D,ML->GV.ClientWidth,ML->GV.ClientHeight);	
	//�K�E�X�t�B���^	
	//�K�E�X�̃}�b�v���w��
	ML->E.SetGaussMap((float)ML->GV.ClientWidth/4,(float)ML->GV.ClientHeight/4);
	//�P�x�o�b�t�@���ڂ���
	//��
	ML->Sf.Begin(SU_GAUSSX,ML->D);
	Back.draw(ML,ML->Sf.Retex(SU_GAUSSX),fx::GaussX);
	//�c
	ML->Sf.Begin(SU_GAUSSY,ML->D);
	Back.draw(ML,ML->Sf.Retex(SU_GAUSSY),fx::GaussY);

	//�T�[�t�F�C�X���I��
	ML->Sf.End(ML->D);
	//�}���`�����_�����O�T�[�t�F�C�X���I��================================================================
	Back.draw(ML,ML->Sf.Retex(SU_TONE),fx::Tone);
	//���C�g�u���[��
	Back.draw(ML,ML->Sf.Retex(SU_HDR),fx::FVF_Tex_One);
	//UI��\��
	UI_draw();

	//�t�F�[�h
	Back.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,ML->E.Fade);
	Back.draw(ML);

}
//�f�o�b�O
VOID Scene::Main_Debug(DebugButton* db)
{	
	TCHAR HirName[100] = _T("Hir = %d;");
	enum DebugMode
	{
		dmNone,
		dmEvent,
		dmHit,
		dmLightPos,
		dmAudio,
		dmPlay,
		dmOther,
		dmMax,
	};
	switch(m_iHir)
	{
	case dmHit:			_stprintf_s(HirName,100,_T("%sHitandCam"),HirName);break;
	case dmLightPos:	_stprintf_s(HirName,100,_T("%sLightState"),HirName);break;
	case dmAudio:	    _stprintf_s(HirName,100,_T("%sAudio"),HirName);break;
	case dmPlay:	    _stprintf_s(HirName,100,_T("%sPlay"),HirName);break;
	case dmEvent:		_stprintf_s(HirName,100,_T("%sEvent"),HirName);break;
	case dmOther:		_stprintf_s(HirName,100,_T("%sOther"),HirName);break;
	default:break;
	}
	db->DB( HirName,&m_iHir,(int)dmNone,(int)dmMax-1);
	const int TMAX = 1500;
	TCHAR txt[TMAX] = _T("");
	DebugText(txt,TMAX);
	P->DebugText(txt,TMAX);
	for(std::vector<Scene*>::iterator it = m_pChild.begin(); it != m_pChild.end(); ++it)
	{
		if((*it))
		{
			(*it)->DebugText(txt,TMAX);
		}
	}

	ML->Tx.draw(txt,600,100);
	//�f�o�b�O�e�L�X�g	
	if(m_iHir == dmHit)
	{
		
		db->DB(_T("Max->x = %f") ,&Pl[0].Pos()->x,-100.0f,100.0f);
		db->DB(_T("Min->x = %f"),&Pl[1].Pos()->x,-100.0f,100.0f);
		db->DB(_T("Max->y = %f") ,&Pl[2].Pos()->y,-100.0f,100.0f);
		db->DB(_T("Min->y = %f"),&Pl[3].Pos()->y,-100.0f,100.0f);
		db->DB(_T("Max->z = %f") ,&Pl[4].Pos()->z,-100.0f,100.0f);
		db->DB(_T("Min->z = %f") ,&Pl[5].Pos()->z,-100.0f,100.0f);
		db->DB(_T("ML->E.cam.Eye.x = %f"),&ML->E.cam.Eye.x,-100.0f,100.0f);
		db->DB(_T("ML->E.cam.Eye.y = %f"),&ML->E.cam.Eye.y,-100.0f,100.0f);
		db->DB(_T("ML->E.cam.Eye.z = %f"),&ML->E.cam.Eye.z,-100.0f,100.0f);
		db->DB(_T("ML->E.cam.At.x = %f"),&ML->E.cam.At.x,-100.0f,100.0f);
		db->DB(_T("ML->E.cam.At.y = %f"),&ML->E.cam.At.y,-100.0f,100.0f);
		db->DB(_T("ML->E.cam.At.z = %f"),&ML->E.cam.At.z,-100.0f,100.0f);
		db->DB(_T("ML->E.cam.Up.x = %f"),&ML->E.cam.Up.x,-100.0f,100.0f);
		db->DB(_T("ML->E.cam.Up.y = %f"),&ML->E.cam.Up.y,-100.0f,100.0f);
		db->DB(_T("ML->E.cam.Up.z = %f"),&ML->E.cam.Up.z,-100.0f,100.0f);
		db->DB(_T("ML->E.cam.Pars = %f"),&ML->E.cam.Pars,0.0f,180.0f);
		//�f�o�b�O�p�\��
		HitEriaObj[0].SetHit(ML);
		float sh = 0.25f;
		D3DXVECTOR3 shift[6] =
		{
			D3DXVECTOR3(sh,0.0f,0.0f),D3DXVECTOR3(-sh,0.0f,0.0f),
			D3DXVECTOR3(0.0f,-sh,0.0f),D3DXVECTOR3(0.0f,sh,0.0f),
			D3DXVECTOR3(0.0f,0.0f,sh),D3DXVECTOR3(0.0f,0.0f,-sh),

		};
		for(int i = 0; i < 6;i++)
		{
			HitEriaObj[i].drawSkip = FALSE;
			HitEriaObj[i].objPos =  *Pl[i].Pos() + shift[i];
		}
	}
	else
	{
		//�f�o�b�O�p��\��
		for(int i = 0; i < 6;i++)
		{
			HitEriaObj[i].drawSkip = TRUE;
		}
	}
	if(m_iHir == dmLightPos)
	{
		CObjFVF ShadowMap;
		ShadowMap.objScal=D3DXVECTOR3(200.0f,200.0f,0.0f);
		ShadowMap.objPos=D3DXVECTOR3(ML->GV.ClientWidth/2.0f - 100.0f ,ML->GV.ClientHeight/2.0f - 100.0f,0.0f);
		ShadowMap.draw(ML,ML->Sf.Retex(SU_SHADOWMAP),fx::FVF_Tex);
		db->DB(_T("ML->E.Ls.Pos.x = %f"),&ML->E.Ls.Pos.x,-100.0f,100.0f);
		db->DB(_T("ML->E.Ls.Pos.y = %f"),&ML->E.Ls.Pos.y,-100.0f,100.0f);
		db->DB(_T("ML->E.Ls.Pos.z = %f"),&ML->E.Ls.Pos.z,-100.0f,100.0f);
		db->DB(_T("ML->E.Ls.At.x = %f"),&ML->E.Ls.At.x,-100.0f,100.0f);
		db->DB(_T("ML->E.Ls.At.y = %f"),&ML->E.Ls.At.y,-100.0f,100.0f);
		db->DB(_T("ML->E.Ls.At.z = %f"),&ML->E.Ls.At.z,-100.0f,100.0f);
		db->DB(_T("ML->E.Ls.EyePlus.x = %f"),&ML->E.Ls.EyePlus.x,-100.0f,100.0f);
		db->DB(_T("ML->E.Ls.EyePlus.y = %f"),&ML->E.Ls.EyePlus.y,-100.0f,100.0f);
		db->DB(_T("ML->E.Ls.EyePlus.z = %f"),&ML->E.Ls.EyePlus.z,-100.0f,100.0f);
		db->DB(_T("ML->E.Ls.Pars = %f"),&ML->E.Ls.Pars,0.0f,180.0f);
		db->DB(_T("ML->E.Ls.Near = %f"),&ML->E.Ls.Near,-150.0f,150.0f);
		db->DB(_T("ML->E.Ls.Far = %f"),&ML->E.Ls.Far,-150.0f,150.0f);
		db->DB(_T("ML->E.Ls.Col.x = %f"),&ML->E.Ls.Col.x,0.0f,1.0f);
		db->DB(_T("ML->E.Ls.Col.y = %f"),&ML->E.Ls.Col.y,0.0f,1.0f);
		db->DB(_T("ML->E.Ls.Col.z = %f"),&ML->E.Ls.Col.z,0.0f,1.0f);
		db->DB(_T("ML->E.Ls.Col.w = %f"),&ML->E.Ls.Col.w,0.0f,1.0f);
		db->DB(_T("ML->E.Ls.Shadow = %f"),&ML->E.Ls.Shadow,0.0f,1.0f);
		db->DB(_T("ML->E.Ls.Bias = %f"),&ML->E.Ls.Bias,-1.0f,1.0f);
		db->DB(_T("ML->E.Tone.x = %f"),&ML->E.Tone.x,-10.0f,10.0f);
		db->DB(_T("ML->E.Tone.y = %f"),&ML->E.Tone.y,-10.0f,10.0f);
		db->DB(_T("ML->E.Tone.z = %f"),&ML->E.Tone.z,-10.0f,10.0f);
		db->DB(_T("ML->E.Tone.w = %f"),&ML->E.Tone.w,-10.0f,10.0f);		
		db->DB(_T("ML->E.PSL.Pos.x = %f"),&ML->E.PSL.Pos.x,-100.0f,100.0f);
		db->DB(_T("ML->E.PSL.Pos.y = %f"),&ML->E.PSL.Pos.y,-100.0f,100.0f);
		db->DB(_T("ML->E.PSL.Pos.z = %f"),&ML->E.PSL.Pos.z,-100.0f,100.0f);
		db->DB(_T("ML->E.PSL.Vec.x = %f"),&ML->E.PSL.Vec.x,-100.0f,100.0f);
		db->DB(_T("ML->E.PSL.Vec.y = %f"),&ML->E.PSL.Vec.y,-100.0f,100.0f);
		db->DB(_T("ML->E.PSL.Vec.z = %f"),&ML->E.PSL.Vec.z,-100.0f,100.0f);
		db->DB(_T("ML->E.PSL.dis = %f"),&ML->E.PSL.dis,-10.0f,10.0f);
		db->DB(_T("ML->E.PSL.Lcos = %f"),&ML->E.PSL.Lcos,-2.0f,2.0f);
		db->DB(_T("ML->E.PSL.Col.x = %f"),&ML->E.PSL.Col.x,0.0f,1.0f);
		db->DB(_T("ML->E.PSL.Col.y = %f"),&ML->E.PSL.Col.y,0.0f,1.0f);
		db->DB(_T("ML->E.PSL.Col.z = %f"),&ML->E.PSL.Col.z,0.0f,1.0f);
		db->DB(_T("ML->E.PSL.Col.w = %f"),&ML->E.PSL.Col.w,0.0f,1.0f);
		db->DB(_T("ML->E.Fs.Col.x = %f"),&ML->E.Fs.Col.x,0.0f,1.0f);
		db->DB(_T("ML->E.Fs.Col.y = %f"),&ML->E.Fs.Col.y,0.0f,1.0f);
		db->DB(_T("ML->E.Fs.Col.z = %f"),&ML->E.Fs.Col.z,0.0f,1.0f);
		db->DB(_T("ML->E.Fs.Far = %f"),&ML->E.Fs.Far,-150.0f,150.0f);
		db->DB(_T("ML->E.Fs.Near = %f"),&ML->E.Fs.Near,-150.0f,150.0f);		
		db->DB(_T("ML->E.Fs.use = %d"),&ML->E.Fs.use,FALSE,TRUE);
	}
	
	//�I�[�f�B�I
	if(m_iHir == dmAudio)
	{
		//�I�[�f�B�I
		db->DB(_T("ML->Audio.Audio.Volume = %f"),&ML->Audio.Audio.Volume,0.0f,10.0f);
		db->DB(_T("ML->Audio.Audio.Effect = %d"),&ML->Audio.Audio.Effect,(int)AE_DEFAULT,(int)AE_PLATE);
		//���X�i�[�R�[��
		db->DB(_T("ML->Audio.Audio.x3dCone.InnerAngle = %f"),&ML->Audio.Audio.x3dCone.InnerAngle,0.0f,X3DAUDIO_2PI);
		db->DB(_T("ML->Audio.Audio.x3dCone.InnerLPF = %f"),&ML->Audio.Audio.x3dCone.InnerLPF,0.0f,1.0f);
		db->DB(_T("ML->Audio.Audio.x3dCone.InnerReverb = %f"),&ML->Audio.Audio.x3dCone.InnerReverb,0.0f,2.0f);
		db->DB(_T("ML->Audio.Audio.x3dCone.InnerVolume = %f"),&ML->Audio.Audio.x3dCone.InnerVolume,0.0f,2.0f);
		db->DB(_T("ML->Audio.Audio.x3dCone.OuterAngle = %f"),&ML->Audio.Audio.x3dCone.OuterAngle,ML->Audio.Audio.x3dCone.InnerAngle,X3DAUDIO_2PI);
		db->DB(_T("ML->Audio.Audio.x3dCone.OuterLPF = %f"),&ML->Audio.Audio.x3dCone.OuterLPF,0.0f,1.0f);
		db->DB(_T("ML->Audio.Audio.x3dCone.OuterReverb = %f"),&ML->Audio.Audio.x3dCone.OuterReverb,0.0f,2.0f);
		db->DB(_T("ML->Audio.Audio.x3dCone.OuterVolume = %f"),&ML->Audio.Audio.x3dCone.OuterVolume,0.0f,2.0f);
		//���X�i�[
		db->DB(_T("ML->Audio.Audio.x3dLis.Position.x = %f"),&ML->Audio.Audio.x3dLis.Position.x,-100.0f,100.0f);
		db->DB(_T("ML->Audio.Audio.x3dLis.Position.y = %f"),&ML->Audio.Audio.x3dLis.Position.y,-100.0f,100.0f);
		db->DB(_T("ML->Audio.Audio.x3dLis.Position.z = %f"),&ML->Audio.Audio.x3dLis.Position.z,-100.0f,100.0f);

		db->DB(_T("ML->Audio.Audio.x3dLis.OrientFront.x = %f"),&ML->Audio.Audio.x3dLis.OrientFront.x,-1.0f,1.0f);
		db->DB(_T("ML->Audio.Audio.x3dLis.OrientFront.y = %f"),&ML->Audio.Audio.x3dLis.OrientFront.y,-1.0f,1.0f);
		db->DB(_T("ML->Audio.Audio.x3dLis.OrientFront.z = %f"),&ML->Audio.Audio.x3dLis.OrientFront.z,-1.0f,1.0f);
		
		db->DB(_T("ML->Audio.Audio.x3dLis.OrientTop.x = %f"),&ML->Audio.Audio.x3dLis.OrientTop.x,-1.0f,1.0f);
		db->DB(_T("ML->Audio.Audio.x3dLis.OrientTop.y = %f"),&ML->Audio.Audio.x3dLis.OrientTop.y,-1.0f,1.0f);
		db->DB(_T("ML->Audio.Audio.x3dLis.OrientTop.z = %f"),&ML->Audio.Audio.x3dLis.OrientTop.z,-1.0f,1.0f);

		db->DB(_T("ML->Audio.Audio.x3dLis.Velocity.x = %f"),&ML->Audio.Audio.x3dLis.Velocity.x,-100.0f,100.0f);
		db->DB(_T("ML->Audio.Audio.x3dLis.Velocity.y = %f"),&ML->Audio.Audio.x3dLis.Velocity.y,-100.0f,100.0f);
		db->DB(_T("ML->Audio.Audio.x3dLis.Velocity.z = %f"),&ML->Audio.Audio.x3dLis.Velocity.z,-100.0f,100.0f);
		
	}
	if(m_iHir == dmEvent)
	{
		//�C�x���g�̑I��
		int Size = m_pChild.size();
		TCHAR Name[100] = _T("m_iEvent = %d;//");
		_stprintf_s(Name,100,_T("%s%s"),Name,m_pChild[m_iEvent]->name());
		db->DB(Name,&m_iEvent,0,Size - 1);
		//�I�������C�x���g�̃f�o�b�O
		m_pChild[m_iEvent]->Obj_Debug(db);		
	}	
	if(m_iHir == dmPlay)
	{
		P->DButton(db);
	}
	if(m_iHir == dmOther)
	{
		DebugBtn(db);
	}
	db->draw();
}
#ifdef MY_DEBUG 

//���C�����[�v
VOID Scene::Main_Loop(DebugButton* Db)
{
	Main_Update();
	Main_draw();
	Main_Debug(Db);
}
#else
//���C�����[�v
VOID Scene::Main_Loop(DebugButton*)
{
	Main_Update();
	Main_draw();
}
#endif

//�t�B�[���h�X�V
VOID Scene::Main(Personal* p,MyLibrary* ml,DebugButton* Db)
{
	if(ML == NULL)
	{
		//���񃋁[�v
		Main_Set(p,ml);
		Main_Loop(Db);
		//�e�I�u�W�F�N�g�̎g��Ȃ��v�f��j��
		m_pPare->DeleteField();	
	}
	else
	{
		Main_Loop(Db);
	}
}
//�O���Ŏg���֐�=========================================================================
//�����Ă���v�f�Ɏq��ǉ��󂫂������ꍇpush
VOID Scene::AddField(Scene* Bf)
{
	//��̗v�f��T���Ă����ɐV�����t�B�[���h��ǉ�����
	for(std::vector<Scene*>::iterator it = m_pChild.begin(); it != m_pChild.end(); ++it)
	{
		if((*it) == NULL)
		{
			(*it)  = Bf;
			(*it) ->m_pPare = this;
			m_iSelect = it - m_pChild.begin();
			return;	
		}
	}
	//���������ꍇ�V���ɒǉ�
	m_pChild.push_back(Bf);
	m_pChild.back()->m_pPare = this;
	m_iSelect = m_pChild.size() - 1;
}
//����X�V
VOID Scene::Begin(Personal* p,MyLibrary* ml,DebugButton* Db)
{
	m_pChild[m_iSelect]->Main(p,ml,Db);
}
//===================================================================================
//�C�x���g�p
//===================================================================================
//���C�u�����ƃv���C���[�̃Z�b�g
VOID Scene::Obj_Set(Personal* p,MyLibrary *ml)
{	
	P  = p;	
	ML = ml;	
	Set();
	//�I�u�W�F�N�g�̓����蔻��Z�b�g
	for(std::vector<CObjMesh*>::iterator it = Msh.begin(); it != Msh.end(); ++it)
	{	
		(*it)->SetHit(ML);
	}
}
//�X�V
VOID Scene::Obj_Update(){Update();}
//Ui�̕`��
VOID Scene::Obj_UI()
{	
	for(std::vector<CObjFVF*>::iterator it = Ui.begin(); it != Ui.end(); ++it)
	{
		(*it)->draw(ML);
	}
	for(std::vector<CObjText*>::iterator it = UiTxt.begin(); it != UiTxt.end(); ++it)
	{
		(*it)->draw(ML);
	}
	UI();
}
//���ʂ̕`��
VOID Scene::Obj_Draw()
{
	for(std::vector<CObjMesh*>::iterator it = Msh.begin(); it != Msh.end(); ++it)
	{		
		(*it)->draw(ML);
	}
	for(std::vector<CObjFVF*>::iterator it = Fvf.begin(); it != Fvf.end(); ++it)
	{
		(*it)->draw(ML);
	}
	for(std::vector<CObjText*>::iterator it = Txt.begin(); it != Txt.end(); ++it)
	{
		(*it)->draw(ML);
	}
	draw();
	for(std::vector<CObjParticl*>::iterator it = Prt.begin(); it != Prt.end(); ++it)
	{
		(*it)->draw(ML);
	}
}
//�f�o�b�O
VOID Scene::Obj_Debug(DebugButton* db)
{
	enum debugobj
	{
		do_Msh,
		do_Fvf,
		do_Prt,
		do_Txt,
		do_Snd,
		do_Ui,
		do_UiTxt,
		do_Other,
		do_Max,

	};
	//�I�������I�u�W�F�N�g��\������
	CObjFVF Slct;
	Slct.objScal = D3DXVECTOR3(100.0f,100.0f,0.0f);
	Slct.MeshCol = D3DXVECTOR4(1.0f,1.0f,1.0f,0.2f);
	//�e�I�u�W�F�N�g��I��
	int ObjSize = 0;
	TCHAR ObjName[100] = _T("m_iObjType = %d;//");
	if(m_iObjType == do_Msh)
	{
		//Mesh
		_stprintf_s(ObjName,100,_T("%sMsh"),ObjName);
		ObjSize = Msh.size() - 1;
	}
	if(m_iObjType == do_Fvf)
	{
		//Fvf
		_stprintf_s(ObjName,100,_T("%sFvf"),ObjName);
		ObjSize = Fvf.size() - 1;
	}
	if(m_iObjType == do_Prt)
	{
		//Prt
		_stprintf_s(ObjName,100,_T("%sPrt"),ObjName);
		ObjSize = Prt.size() - 1;

	}
	if(m_iObjType == do_Snd)
	{
		//Snd
		_stprintf_s(ObjName,100,_T("%sSnd"),ObjName);
		ObjSize = Snd.size() - 1;
	}
	if(m_iObjType == do_Ui)
	{
		//Ui
		_stprintf_s(ObjName,100,_T("%sUi"),ObjName);
		ObjSize = Ui.size() - 1;
	}
	if(m_iObjType == do_UiTxt)
	{
		//UiTxt
		_stprintf_s(ObjName,100,_T("%sUiTxt"),ObjName);
		ObjSize = UiTxt.size() - 1;
	}
	if(m_iObjType == do_Txt)
	{
		//Txt
		_stprintf_s(ObjName,100,_T("%sTxt"),ObjName);
		ObjSize = Txt.size() - 1;
	}

	if(m_iObjType == do_Other)
	{
		//Txt
		_stprintf_s(ObjName,100,_T("%sOther"),ObjName);
	}

	//�I�u�W�F�N�g�̎��
	db->DB(ObjName,&m_iObjType,0,do_Max - 1);
	//�I�������I�u�W�F�N�g
	db->DB(_T("m_iObjNum = %d"),&m_iObjNum,0,ObjSize);
	//���b�V��
	if(m_iObjType == do_Msh)
	if(Msh.size() != 0)
	{
		if((int)Msh.size() <= m_iObjNum ){m_iObjNum = 0; }
		CObjMesh* tm = Msh[m_iObjNum];	
		vec3Ari().D3DXVec3WtoSCent(&Slct.objPos,&tm->objPos,&ML->E.matPxV,ML->GV.ClientWidth,ML->GV.ClientHeight);

		//�X�V
		tm->SetHit(ML);
		db->DB(_T("Ob()->objPos.x = %f"),&tm->objPos.x,-100.0f,100.0f);
		db->DB(_T("Ob()->objPos.y = %f"),&tm->objPos.y,-100.0f,100.0f);
		db->DB(_T("Ob()->objPos.z = %f"),&tm->objPos.z,-100.0f,100.0f);

		db->DB(_T("Ob()->objScal.x = %f"),&tm->objScal.x,0.0f,200.0f);
		db->DB(_T("Ob()->objScal.y = %f"),&tm->objScal.y,0.0f,200.0f);
		db->DB(_T("Ob()->objScal.z = %f"),&tm->objScal.z,0.0f,200.0f);
	
		db->DB(_T("Ob()->YPR.x = %f"),&tm->YPR.x,0.0f,360.0f);
		db->DB(_T("Ob()->YPR.y = %f"),&tm->YPR.y,0.0f,360.0f);
		db->DB(_T("Ob()->YPR.z = %f"),&tm->YPR.z,0.0f,360.0f);			
	
		db->DB(_T("Ob()->MeshCol.x = %f"),&tm->MeshCol.x,0.0f,1.0f);
		db->DB(_T("Ob()->MeshCol.y = %f"),&tm->MeshCol.y,0.0f,1.0f);
		db->DB(_T("Ob()->MeshCol.z = %f"),&tm->MeshCol.z,0.0f,1.0f);
		db->DB(_T("Ob()->MeshCol.w = %f"),&tm->MeshCol.w,0.0f,1.0f);

		db->DB(_T("Ob()->SpCol.x = %f"),&tm->SpCol.x,0.0f,1.0f);
		db->DB(_T("Ob()->SpCol.y = %f"),&tm->SpCol.y,0.0f,1.0f);
		db->DB(_T("Ob()->SpCol.z = %f"),&tm->SpCol.z,0.0f,1.0f);
		db->DB(_T("Ob()->SpCol.w = %f"),&tm->SpCol.w,0.0f,20.0f);
		db->DB(_T("Ob()->SpColm = %f"),&tm->SpColm,0.0f,1.0f);
	
		db->DB(_T("Ob()->drawSkip = %d"),&tm->drawSkip,FALSE,TRUE);
		db->DB(_T("Ob()->ShadowFlag = %d"),&tm->ShadowFlag,FALSE,TRUE);
		db->DB(_T("Ob()->Shadow = %f"),&tm->Shadow,0.0f,1.0f);
		db->DB(_T("Ob()->Bias = %f"),&tm->Bias,0.0f,1.0f);
		db->DB(_T("Ob()->Amb = %f"),&tm->Amb,0.0f,1.0f);
		db->DB(_T("Ob()->BloomColor.x = %f"),&tm->BloomColor.x,-10.0f,10.0f);
		db->DB(_T("Ob()->BloomColor.y = %f"),&tm->BloomColor.y,-10.0f,10.0f);
		db->DB(_T("Ob()->BloomColor.z = %f"),&tm->BloomColor.z,-10.0f,10.0f);
		db->DB(_T("Ob()->BloomColor.w = %f"),&tm->BloomColor.w,-10.0f,10.0f);
		
	}
	//Fvf
	if(m_iObjType == do_Fvf)
	if(Fvf.size() != 0)
	{
		if((int)Fvf.size() <= m_iObjNum ){m_iObjNum = 0; }
		CObjFVF* tf = Fvf[m_iObjNum];
		vec3Ari().D3DXVec3WtoSCent(&Slct.objPos,&tf->objPos,&ML->E.matPxV,ML->GV.ClientWidth,ML->GV.ClientHeight);
				
		db->DB(_T("Ob()->objPos.x = %f"),&tf->objPos.x,-100.0f,100.0f);
		db->DB(_T("Ob()->objPos.y = %f"),&tf->objPos.y,-100.0f,100.0f);
		db->DB(_T("Ob()->objPos.z = %f"),&tf->objPos.z,-100.0f,100.0f);
		db->DB(_T("Ob()->objScal.x = %f"),&tf->objScal.x,-50.0f,50.0f);
		db->DB(_T("Ob()->objScal.y = %f"),&tf->objScal.y,-50.0f,50.0f);
		db->DB(_T("Ob()->YPR.x = %f"),&tf->YPR.x,0.0f,360.0f);
		db->DB(_T("Ob()->YPR.y = %f"),&tf->YPR.y,0.0f,360.0f);
		db->DB(_T("Ob()->YPR.z = %f"),&tf->YPR.z,0.0f,360.0f);
		
		db->DB(_T("Ob()->MeshCol.x = %f"),&tf->MeshCol.x,0.0f,1.0f);
		db->DB(_T("Ob()->MeshCol.y = %f"),&tf->MeshCol.y,0.0f,1.0f);
		db->DB(_T("Ob()->MeshCol.z = %f"),&tf->MeshCol.z,0.0f,1.0f);
		db->DB(_T("Ob()->MeshCol.w = %f"),&tf->MeshCol.w,0.0f,1.0f);
		db->DB(_T("Ob()->drawSkip = %d"),&tf->drawSkip,FALSE,TRUE);			
		
	}
	//Prt
	if(m_iObjType == do_Prt)
	if(Prt.size() != 0)
	{
		if((int)Prt.size() <= m_iObjNum ){m_iObjNum = 0; }
		CObjParticl* tp = Prt[m_iObjNum];
		vec3Ari().D3DXVec3WtoSCent(&Slct.objPos,&tp->objPos,&ML->E.matPxV,ML->GV.ClientWidth,ML->GV.ClientHeight);
	
		
		db->DB(_T("Ob()->objPos.x = %f"),&tp->objPos.x,-100.0f,100.0f);
		db->DB(_T("Ob()->objPos.y = %f"),&tp->objPos.y,-100.0f,100.0f);
		db->DB(_T("Ob()->objPos.z = %f"),&tp->objPos.z,-100.0f,100.0f);

		db->DB(_T("Ob()->objScal.x = %f"),&tp->objScal.x,0.0f,200.0f);
		db->DB(_T("Ob()->objScal.y = %f"),&tp->objScal.y,0.0f,200.0f);
		db->DB(_T("Ob()->objScal.z = %f"),&tp->objScal.z,0.0f,200.0f);
	
		db->DB(_T("Ob()->YPR.x = %f"),&tp->YPR.x,0.0f,360.0f);
		db->DB(_T("Ob()->YPR.y = %f"),&tp->YPR.y,0.0f,360.0f);
		db->DB(_T("Ob()->YPR.z = %f"),&tp->YPR.z,0.0f,360.0f);

		db->DB(_T("Ob()->drawSkip = %d"),&tp->drawSkip,FALSE,TRUE);
		db->DB(_T("Ob()->MeshCol.x = %f"),&tp->MeshCol.x,-10.0f,10.0f);
		db->DB(_T("Ob()->MeshCol.y = %f"),&tp->MeshCol.y,-10.0f,10.0f);
		db->DB(_T("Ob()->MeshCol.z = %f"),&tp->MeshCol.z,-10.0f,10.0f);
		db->DB(_T("Ob()->MeshCol.w = %f"),&tp->MeshCol.w,-10.0f,10.0f);
		db->DB(_T("Ob()->BloomColor.x = %f"),&tp->BloomColor.x,-10.0f,10.0f);
		db->DB(_T("Ob()->BloomColor.y = %f"),&tp->BloomColor.y,-10.0f,10.0f);
		db->DB(_T("Ob()->BloomColor.z = %f"),&tp->BloomColor.z,-10.0f,10.0f);
		db->DB(_T("Ob()->BloomColor.w = %f"),&tp->BloomColor.w,-10.0f,10.0f);
	
		db->DB(_T("Ob()->Ext = %f"),&tp->Ext,0.0f,10.0f);
		db->DB(_T("Ob()->Height = %f"),&tp->Height,0.0f,10.0f);
		db->DB(_T("Ob()->Speed = %f"),&tp->Speed,0.0f,1.0f);
		db->DB(_T("Ob()->PrtTime = %f"),&tp->PrtTime,0.0f,1.0f);
		
	}
	//�T�E���h
	if(m_iObjType == do_Snd)
	if(Snd.size() != 0)
	{
		if((int)Snd.size() <= m_iObjNum ){m_iObjNum = 0; }
		CObjSound* ts = Snd[m_iObjNum];	
		D3DXVECTOR3 Pos = ts->Emi.Position; 
		vec3Ari().D3DXVec3WtoSCent(&Slct.objPos,&Pos,&ML->E.matPxV,ML->GV.ClientWidth,ML->GV.ClientHeight);
		db->DB(_T("ts->m_fNoise = %f"),&ts->m_fNoise,0.0f,10.0f);	
		db->DB(_T("ts->m_fVol = %f"),&ts->m_fVol,0.0f,10.0f);
		db->DB(_T("ts->m_b3DSound = %d"),&ts->m_b3DSound,FALSE,TRUE);
		db->DB(_T("ts->m_bLoop = %d"),&ts->m_bLoop,FALSE,TRUE);
		db->DB(_T("ts->Filter.Frequency = %f"),&ts->Filter.Frequency,0.0f,1.0f);
		db->DB(_T("ts->Filter.OneOverQ = %f"),&ts->Filter.OneOverQ,0.01f,1.5f);
		db->DB(_T("ts->Filter.Type = %d"),&ts->Type,0,2);		
		db->DB(_T("ts->Cone.InnerAngle = %f"),&ts->Cone.InnerAngle,0.0f,X3DAUDIO_2PI);
		db->DB(_T("ts->Cone.InnerLPF = %f"),&ts->Cone.InnerLPF,0.0f,1.0f);
		db->DB(_T("ts->Cone.InnerReverb = %f"),&ts->Cone.InnerReverb,0.0f,2.0f);
		db->DB(_T("ts->Cone.InnerVolume = %f"),&ts->Cone.InnerVolume,0.0f,2.0f);
		db->DB(_T("ts->Cone.OuterAngle = %f"),&ts->Cone.OuterAngle,ts->Cone.InnerAngle,X3DAUDIO_2PI);
		db->DB(_T("ts->Cone.OuterLPF = %f"),&ts->Cone.OuterLPF,0.0f,1.0f);
		db->DB(_T("ts->Cone.OuterReverb = %f"),&ts->Cone.OuterReverb,0.0f,2.0f);
		db->DB(_T("ts->Cone.OuterVolume = %f"),&ts->Cone.OuterVolume,0.0f,2.0f);		
		db->DB(_T("ts->Emi.Position.x = %f"),&ts->Emi.Position.x,-100.0f,100.0f);
		db->DB(_T("ts->Emi.Position.y = %f"),&ts->Emi.Position.y,-100.0f,100.0f);
		db->DB(_T("ts->Emi.Position.z = %f"),&ts->Emi.Position.z,-100.0f,100.0f);
		db->DB(_T("ts->Emi.OrientFront.x = %f"),&ts->Emi.OrientFront.x,-1.0f,1.0f);
		db->DB(_T("ts->Emi.OrientFront.y = %f"),&ts->Emi.OrientFront.y,-1.0f,1.0f);
		db->DB(_T("ts->Emi.OrientFront.z = %f"),&ts->Emi.OrientFront.z,-1.0f,1.0f);			
		db->DB(_T("ts->Emi.OrientTop.x = %f"),&ts->Emi.OrientTop.x,-1.0f,1.0f);
		db->DB(_T("ts->Emi.OrientTop.y = %f"),&ts->Emi.OrientTop.y,-1.0f,1.0f);
		db->DB(_T("ts->Emi.OrientTop.z = %f"),&ts->Emi.OrientTop.z,-1.0f,1.0f);			
		db->DB(_T("ts->Emi.Velocity.x = %f"),&ts->Emi.Velocity.x,-100.0f,100.0f);
		db->DB(_T("ts->Emi.Velocity.y = %f"),&ts->Emi.Velocity.y,-100.0f,100.0f);
		db->DB(_T("ts->Emi.Velocity.z = %f"),&ts->Emi.Velocity.z,-100.0f,100.0f);		
		db->DB(_T("ts->Emi.DopplerScaler = %f"),&ts->Emi.DopplerScaler,0.0f,100.0f);			
		db->DB(_T("ts->Emi.InnerRadius = %f"),&ts->Emi.InnerRadius,0.0f,100.0f);			
		db->DB(_T("ts->Emi.InnerRadiusAngle = %f"),&ts->Emi.InnerRadiusAngle,0.0f,X3DAUDIO_PI/4.0f);			
		db->DB(_T("ts->Emi.CurveDistanceScaler = %f"),&ts->Emi.CurveDistanceScaler,0.0f,50.0f);		
		
	}
	//Ui
	if(m_iObjType == do_Ui)
	if(Ui.size() != 0)
	{
		if((int)Ui.size() <= m_iObjNum ){m_iObjNum = 0; }
		CObjFVF* tf = Ui[m_iObjNum];
		float w = (float)ML->GV.ClientWidth;
		float h = (float)ML->GV.ClientHeight;
		db->DB(_T("Ob()->objPos.x = %f"),&tf->objPos.x,-w/2,w/2);
		db->DB(_T("Ob()->objPos.y = %f"),&tf->objPos.y,-h/2,h/2);
		db->DB(_T("Ob()->objScal.x = %f"),&tf->objScal.x,0.0f,w);
		db->DB(_T("Ob()->objScal.y = %f"),&tf->objScal.y,0.0f,h);
		db->DB(_T("Ob()->YPR.z = %f"),&tf->YPR.z,0.0f,360.0f);
		db->DB(_T("Ob()->MeshCol.x = %f"),&tf->MeshCol.x,0.0f,1.0f);
		db->DB(_T("Ob()->MeshCol.y = %f"),&tf->MeshCol.y,0.0f,1.0f);
		db->DB(_T("Ob()->MeshCol.z = %f"),&tf->MeshCol.z,0.0f,1.0f);
		db->DB(_T("Ob()->MeshCol.w = %f"),&tf->MeshCol.w,0.0f,1.0f);
		db->DB(_T("Ob()->drawSkip = %d"),&tf->drawSkip,FALSE,TRUE);		
	}
	//UiTxt
	if(m_iObjType == do_UiTxt)
	if(UiTxt.size() != 0)
	{
		if((int)UiTxt.size() <= m_iObjNum ){m_iObjNum = 0; }
		float w = (float)ML->GV.ClientWidth;
		float h = (float)ML->GV.ClientHeight;
		CObjText* tt = UiTxt[m_iObjNum];	
		db->DB(_T("Ob()->objPos.x = %f"),&tt->objPos.x,-w/2,w/2);
		db->DB(_T("Ob()->objPos.y = %f"),&tt->objPos.y,-h/2,h/2);
		db->DB(_T("Ob()->objScal.x = %f"),&tt->objScal.x,0.0f,w);
		db->DB(_T("Ob()->objScal.y = %f"),&tt->objScal.y,0.0f,h);
		db->DB(_T("Ob()->YPR.z = %f"),&tt->YPR.z,0.0f,360.0f);
		db->DB(_T("Ob()->MeshCol.x = %f"),&tt->MeshCol.x,0.0f,1.0f);
		db->DB(_T("Ob()->MeshCol.y = %f"),&tt->MeshCol.y,0.0f,1.0f);
		db->DB(_T("Ob()->MeshCol.z = %f"),&tt->MeshCol.z,0.0f,1.0f);
		db->DB(_T("Ob()->MeshCol.w = %f"),&tt->MeshCol.w,0.0f,1.0f);		
		db->DB(_T("Ob()->drawSkip = %d"),&tt->drawSkip,FALSE,TRUE);		
		db->DB(_T("Ob()->Length = %d"),&tt->Length,FALSE,TRUE);	
		db->DB(_T("Ob()->StrLen = %d"),&tt->StrLen,-1,tt->Max());		
		db->DB(_T("Ob()->intrval.x = %f"),&tt->intrval.x,-10.0f,10.0f);		
		db->DB(_T("Ob()->intrval.y = %f"),&tt->intrval.y,-10.0f,10.0f);
				
	}
	//Txt
	if(m_iObjType == do_Txt)
	if(Txt.size() != 0)
	{
		if((int)Txt.size() <= m_iObjNum ){m_iObjNum = 0; }
		CObjText* tt = Txt[m_iObjNum];
		vec3Ari().D3DXVec3WtoSCent(&Slct.objPos,&tt->objPos,&ML->E.matPxV,ML->GV.ClientWidth,ML->GV.ClientHeight);
	
		db->DB(_T("Ob()->objPos.x = %f"),&tt->objPos.x,-100.0f,100.0f);
		db->DB(_T("Ob()->objPos.y = %f"),&tt->objPos.y,-100.0f,100.0f);
		db->DB(_T("Ob()->objPos.z = %f"),&tt->objPos.z,-100.0f,100.0f);
		db->DB(_T("Ob()->objScal.x = %f"),&tt->objScal.x,0.0f,200.0f);
		db->DB(_T("Ob()->objScal.y = %f"),&tt->objScal.y,0.0f,200.0f);
		db->DB(_T("Ob()->YPR.x = %f"),&tt->YPR.x,0.0f,360.0f);
		db->DB(_T("Ob()->YPR.y = %f"),&tt->YPR.y,0.0f,360.0f);
		db->DB(_T("Ob()->YPR.z = %f"),&tt->YPR.z,0.0f,360.0f);		
		db->DB(_T("Ob()->MeshCol.x = %f"),&tt->MeshCol.x,0.0f,1.0f);
		db->DB(_T("Ob()->MeshCol.y = %f"),&tt->MeshCol.y,0.0f,1.0f);
		db->DB(_T("Ob()->MeshCol.z = %f"),&tt->MeshCol.z,0.0f,1.0f);
		db->DB(_T("Ob()->MeshCol.w = %f"),&tt->MeshCol.w,0.0f,1.0f);
		db->DB(_T("Ob()->drawSkip = %d"),&tt->drawSkip,FALSE,TRUE);	
		db->DB(_T("Ob()->Length = %d"),&tt->Length,FALSE,TRUE);		
		db->DB(_T("Ob()->StrLen = %d"),&tt->StrLen,-1,tt->Max());			
		db->DB(_T("Ob()->intrval.x = %f"),&tt->intrval.x,-10.0f,10.0f);		
		db->DB(_T("Ob()->intrval.y = %f"),&tt->intrval.y,-10.0f,10.0f);		
		
	}
	//���z�֐��p�f�o�b�O�{�^��
	if(m_iObjType == do_Other)
	{
		DebugBtn(db);
	}
	//�I�����Ă���I�u�W�F�N�g�̈ʒu��FVF��\��
	Slct.draw(ML);
}
//�����蔻��======================================================================
//�����蔻��(�ڐG�̐���)

BOOL Scene::HitObjFlag(size_t num)
{
	if(Msh[num]->HitObj.Reaction == 1){return TRUE;}
	return FALSE;
}

//�擪�̃I�u�W�F�N�g��Ԃ�
CObjMesh* Scene::Ob(){	return Msh[0];}
//�ŏ��̃I�u�W�F�N�g��Ԃ�	
CObjMesh* Scene::Ob(int num){return Msh[num];}
 
