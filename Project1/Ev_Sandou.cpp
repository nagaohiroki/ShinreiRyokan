//==============================================
//山道イベント
//==============================================
const TCHAR* SandouEvent::name(){return _T("SandouEvent");}
SandouEvent::SandouEvent()
{}
VOID SandouEvent::Set()
{
	//BGM
	if(P->BGM == NULL)
	{
		P->BGM = new CObjSound;
		P->BGM->Set(wav_suzumusi);
		P->BGM->m_fVol = 0.8f;
		P->BGM->m_bLoop = TRUE;
	}
}

VOID SandouEvent::Update()
{
	if(P->BGM)
	{
		P->BGM->Start(ML);
	}
	/*
	//BGM
	if(P->BGM == NULL)
	{
		P->BGM = new CObjSound;
		P->BGM->Set(wav_suzumusi);
		P->BGM->m_fVol = 0.8f;
		P->BGM->m_bLoop = TRUE;
	}
	else
	{
		P->BGM->Start(ML);
	}
	*/
	//エリア移動
	if( P->obj.objPos.z >  14.0f )
	{
		m_pPare->FldChange(new Fld::Soto,&D3DXVECTOR3(0.0f,0.35f,2.0f),0.0f);
	}
	else if( P->obj.objPos.z < -14.0f )
	{
		m_pPare->FldChange(new Fld::Sandou,&D3DXVECTOR3(0.0f,0.35f,13.0f),180.0f);
	}
}