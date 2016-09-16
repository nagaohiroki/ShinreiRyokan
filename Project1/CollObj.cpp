//�����蔻��I�u�W�F�N�g
CollObj::CollObj()
{
	Reaction = 0;
	cType = CT_NONE;
	cBack = CB_NONE;
	vBack = D3DXVECTOR3(0.0f,0.0f,0.0f);
}
float* CollObj::Len(){		return NULL; }
D3DXVECTOR3* CollObj::Pos(){return NULL; }
D3DXVECTOR3* CollObj::Vec(){return NULL; }
D3DXVECTOR3* CollObj::vX(){ return NULL; }
D3DXVECTOR3* CollObj::vY(){ return NULL; }
D3DXVECTOR3* CollObj::vZ(){ return NULL; }

//�����蔻��I�u�W�F�N�g
//���ʃI�u�W�F�N�g
Plane::Plane()
{
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Vec = D3DXVECTOR3(0.0f,0.0f,0.0f);
}
D3DXVECTOR3* Plane::Pos(){return &m_Pos;}
D3DXVECTOR3* Plane::Vec(){return &m_Vec;}
//���̃I�u�W�F�N�g
Shpere::Shpere()
{
	m_Len = 0.0f;
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
}	
float* Shpere::Len(){return &m_Len;}
D3DXVECTOR3* Shpere::Pos(){return &m_Pos;}


//OBB�I�u�W�F�N�g
OBB::OBB()
{
	m_Len = 0.0f;
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Vec = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_vX  = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_vY  = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_vZ  = D3DXVECTOR3(0.0f,0.0f,0.0f);
}
float *OBB::Len(){return &m_Len;}
D3DXVECTOR3* OBB::Pos(){ return &m_Pos;}
D3DXVECTOR3* OBB::Vec(){ return &m_Vec;}
D3DXVECTOR3* OBB::vX(){  return &m_vX; }
D3DXVECTOR3* OBB::vY(){  return &m_vY; }
D3DXVECTOR3* OBB::vZ(){  return &m_vZ; }

//����
Segmet::Segmet()
{
	m_Len = 0.0f;
	m_Pos =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Vec =D3DXVECTOR3(0.0f,0.0f,0.0f);

}
float* Segmet::Len(){return &m_Len;}
D3DXVECTOR3* Segmet::Pos(){return &m_Pos;}
D3DXVECTOR3* Segmet::Vec(){return &m_Vec;}