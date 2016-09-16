LineSegmet::LineSegmet(){}
//�����Ɠ_(��)
BOOL LineSegmet::LineSegHit(D3DXVECTOR3* s,D3DXVECTOR3* v,D3DXVECTOR3* p,float r)
{
	D3DXVECTOR3 vs = *v - *s;
	float dotvs = D3DXVec3Dot(&vs,&vs);
	if( dotvs == 0.0f){ return FALSE;} 
	float dotvp = D3DXVec3Dot(&vs,&(*v - *p));
	float Linein = dotvp / dotvs;
	if(Linein > 1.0f){Linein = 1.0f;}
	if(Linein < 0.0f){Linein = 0.0f;}
	D3DXVECTOR3 root = *v - vs * Linein;  
	if( D3DXVec3LengthSq(&(root - *p)) < r * r ){return TRUE;}
	return FALSE;
}
//���Ɠ_(��)
BOOL LineSegmet::LineHit(D3DXVECTOR3* s,D3DXVECTOR3* v,D3DXVECTOR3* p,float r)
{
	D3DXVECTOR3 vs = *v - *s;
	float dotvs = D3DXVec3Dot(&vs,&vs);
	if( dotvs == 0.0f){ return FALSE;} 
	float dotvp = D3DXVec3Dot(&vs,&(*v - *p));
	float Linein = dotvp / dotvs;
	D3DXVECTOR3 root = *v - vs * Linein;  
	if( D3DXVec3LengthSq(&(root - *p)) < r * r ){return TRUE;}
	return FALSE;
}
//������OBB
BOOL LineSegmet::LinevsOBB(D3DXVECTOR3* s,D3DXVECTOR3* v,float r,CollObj* Obb)
{
	//OBB�e���ʃx�N�g���̒���+�����̑���
	D3DXVECTOR3 vVol(*Obb->Vec() + D3DXVECTOR3(r,r,r)); 
	//�����̒��Ԓn�_(���[���h���W)
	D3DXVECTOR3 mdl = ( *s + *v ) * 0.5f;
	//���Ԓn�_����I�_�܂ł̋���(�����̔����̒���)
	D3DXVECTOR3 Dis = *v - mdl;
	//�����̒��Ԓn�_��OBB�̋���
	mdl = mdl - *Obb->Pos();
	//�e���ʃx�N�g����Inv�̋����̓���	
	mdl = D3DXVECTOR3(D3DXVec3Dot(Obb->vX(),&mdl),D3DXVec3Dot(Obb->vY(),&mdl),D3DXVec3Dot(Obb->vZ(),&mdl));
	//�e���ʃx�N�g���Ɛ��������x�N�g���̓���	
	Dis = D3DXVECTOR3(D3DXVec3Dot(Obb->vX(),&Dis),D3DXVec3Dot(Obb->vY(),&Dis),D3DXVec3Dot(Obb->vZ(),&Dis));
	//2�̃x�N�g���̊e��Βl
	D3DXVECTOR3 InvDotf(fabsf(mdl.x),fabsf(mdl.y),fabsf(mdl.z));
	D3DXVECTOR3 DisDotf(fabsf(Dis.x),fabsf(Dis.y),fabsf(Dis.z));
	//OBB�Ɛ����̒��ԓ_��OBB�̊e���a�Ɛ����̔����̒����ȏ�ɗ���Ă����ꍇ�ڐG����\���͂Ȃ�
	if(InvDotf.x > vVol.x + DisDotf.x){return FALSE;}
	if(InvDotf.y > vVol.y + DisDotf.y){return FALSE;}
	if(InvDotf.z > vVol.z + DisDotf.z){return FALSE;}
	//�����̔��a�x�N�g���ƁA�����̒��Ԃ�OBB�̋����x�N�g���̊O�ς̐�Βl
	D3DXVECTOR3 crs;
	D3DXVec3Cross(&crs,&mdl,&Dis);
	crs = D3DXVECTOR3(fabsf(crs.x),fabsf(crs.y),fabsf(crs.z));
	//�O�σx�N�g���Ɣ�r����x�N�g��(�������ǂ��킩��Ȃ�)
	if(crs.x > vVol.y * DisDotf.z + vVol.z * DisDotf.y) {return FALSE;}
	if(crs.y > vVol.x * DisDotf.z + vVol.z * DisDotf.x) {return FALSE;}
	if(crs.z > vVol.x * DisDotf.y + vVol.y * DisDotf.x) {return FALSE;}
	return TRUE;
}

//�����Ƌ���(�_)
SegvsS::SegvsS(){}
BOOL SegvsS::Hit(CollObj* seg,CollObj* s)
{
	D3DXVECTOR3 vs = *seg->Vec() - *seg->Pos();
	float dotvs = D3DXVec3Dot(&vs,&vs);
	if( dotvs == 0.0f){ return FALSE;} 
	float dotvp = D3DXVec3Dot(&vs,&(*seg->Vec() - *s->Pos()));
	float Linein = dotvp / dotvs;
	if(Linein > 1.0f){Linein = 1.0f;}
	if(Linein < 0.0f){Linein = 0.0f;}
	D3DXVECTOR3 root = *seg->Vec() - vs * Linein;
	float r = *s->Len() + *seg->Len();
	if( D3DXVec3LengthSq(&(root - *s->Pos())) < r * r ){return TRUE;}
	return FALSE;
}
//����(�_)�Ɛ���
SvsSeg::SvsSeg(){}
BOOL SvsSeg::Hit(CollObj* s,CollObj* seg)
{
	return SegvsS().Hit(seg,s);
}
//������OBB
SegvsOBB::SegvsOBB(){}
BOOL SegvsOBB::Hit(CollObj* seg,CollObj* Obb)
{
		//OBB�e���ʃx�N�g���̒���+�����̑���
	D3DXVECTOR3 vVol(*Obb->Vec() + D3DXVECTOR3(*seg->Len(),*seg->Len(),*seg->Len())); 
	//�����̒��Ԓn�_(���[���h���W)
	D3DXVECTOR3 mdl = ( *seg->Pos() + *seg->Vec()) * 0.5f;
	//���Ԓn�_����I�_�܂ł̋���(�����̔����̒���)
	D3DXVECTOR3 Dis = *seg->Vec() - mdl;
	//�����̒��Ԓn�_��OBB�̋���
	mdl = mdl - *Obb->Pos();
	//�e���ʃx�N�g����Inv�̋����̓���	
	mdl = D3DXVECTOR3(D3DXVec3Dot(Obb->vX(),&mdl),D3DXVec3Dot(Obb->vY(),&mdl),D3DXVec3Dot(Obb->vZ(),&mdl));
	//�e���ʃx�N�g���Ɛ��������x�N�g���̓���	
	Dis = D3DXVECTOR3(D3DXVec3Dot(Obb->vX(),&Dis),D3DXVec3Dot(Obb->vY(),&Dis),D3DXVec3Dot(Obb->vZ(),&Dis));
	//2�̃x�N�g���̊e��Βl
	D3DXVECTOR3 InvDotf(fabsf(mdl.x),fabsf(mdl.y),fabsf(mdl.z));
	D3DXVECTOR3 DisDotf(fabsf(Dis.x),fabsf(Dis.y),fabsf(Dis.z));
	//OBB�Ɛ����̒��ԓ_��OBB�̊e���a�Ɛ����̔����̒����ȏ�ɗ���Ă����ꍇ�ڐG����\���͂Ȃ�
	if(InvDotf.x > vVol.x + DisDotf.x){return FALSE;}
	if(InvDotf.y > vVol.y + DisDotf.y){return FALSE;}
	if(InvDotf.z > vVol.z + DisDotf.z){return FALSE;}
	//�����̔��a�x�N�g���ƁA�����̒��Ԃ�OBB�̋����x�N�g���̊O�ς̐�Βl
	D3DXVECTOR3 crs;
	D3DXVec3Cross(&crs,&mdl,&Dis);
	crs = D3DXVECTOR3(fabsf(crs.x),fabsf(crs.y),fabsf(crs.z));
	//�O�σx�N�g���Ɣ�r����x�N�g��(�������ǂ��킩��Ȃ�)
	if(crs.x > vVol.y * DisDotf.z + vVol.z * DisDotf.y) {return FALSE;}
	if(crs.y > vVol.x * DisDotf.z + vVol.z * DisDotf.x) {return FALSE;}
	if(crs.z > vVol.x * DisDotf.y + vVol.y * DisDotf.x) {return FALSE;}
	return TRUE;
}
//OBB�Ɛ���
OBBvsSeg::OBBvsSeg(){}
BOOL OBBvsSeg::Hit(CollObj* obb,CollObj* seg)
{
	return SegvsOBB().Hit(seg,obb);
}