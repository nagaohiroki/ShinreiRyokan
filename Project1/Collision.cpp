HitVector::HitVector()
{
	val = 0.0f;
	back = 0.0f;
	v = D3DXVECTOR3(0.0f,0.0f,0.0f);
}
VOID HitVector::Set(float Val,float Back,D3DXVECTOR3* V)
{
	val = Val;
	back = Back;
	v = *V;
}

//当たり判定
BaseColl::BaseColl(){}
float BaseColl::Ln(D3DXVECTOR3* v,D3DXVECTOR3* x,D3DXVECTOR3* y,D3DXVECTOR3* z)
{
	return fabs(D3DXVec3Dot(v,x)) + fabs(D3DXVec3Dot(v,y)) + fabs(D3DXVec3Dot(v,z));
}
float BaseColl::Ln(D3DXVECTOR3* v,D3DXVECTOR3* x,D3DXVECTOR3* y)
{
	return fabs(D3DXVec3Dot(v,x)) + fabs(D3DXVec3Dot(v,y));
}
//基底は押し戻しを0にするだけ
BOOL BaseColl::Hit(CollObj* c1,CollObj* c2)
{
	c1->vBack =
	c2->vBack = D3DXVECTOR3(0.0f,0.0f,0.0f);
	return FALSE;
}
//球対球
SvsS::SvsS(){}
BOOL SvsS::Hit(CollObj* s1,CollObj* s2)
{
	D3DXVECTOR3 vec(*s1->Pos() - *s2->Pos());
	float Len = D3DXVec3LengthSq(&vec); 
	float S  = *s1->Len() + *s2->Len();
	if(S * S > Len)
	{
		s1->vBack = vec * (S - sqrtf(Len));
		s2->vBack = -s1->vBack;
		return TRUE;
	}
	s1->vBack = D3DXVECTOR3(0.0f,0.0f,0.0f);
	s2->vBack = D3DXVECTOR3(0.0f,0.0f,0.0f);
	return FALSE;
}
//球対平面
SvsP::SvsP(){}
BOOL SvsP::Hit(CollObj* s,CollObj* p)
{
	float Len = *s->Len() - D3DXVec3Dot(p->Vec(),&(*s->Pos() - *p->Pos()));
	if(Len > 0.0f)
	{
		s->vBack  = *p->Vec() * Len;
		p->vBack = -s->vBack;
		return TRUE;
	}
	s->vBack = D3DXVECTOR3(0.0f,0.0f,0.0f);
	p->vBack = D3DXVECTOR3(0.0f,0.0f,0.0f);
	
	return FALSE;
}

//平面対球(上のを逆にしただけ)
PvsS::PvsS(){}
BOOL PvsS::Hit(CollObj* p,CollObj* s)
{
	if(SvsP().Hit(s,p))
	{
		s->vBack  = p->vBack;
		p->vBack = -s->vBack;
		return TRUE;
	}
	return FALSE;

}


//球対立方体
SvsOBB::SvsOBB(){	v.resize(3);}
BOOL SvsOBB::Hit(CollObj* s,CollObj* obb)
{
	D3DXVECTOR3 Inv(*s->Pos() - *obb->Pos());
	s->vBack   = D3DXVECTOR3(0.0f,0.0f,0.0f);
	obb->vBack = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//各方向ベクトルと対象ベクトルを比べる
	float DotX = D3DXVec3Dot(&Inv,obb->vX());
	float sX = (obb->Vec()->x + *s->Len() ) - fabs(DotX);
	if(sX < 0.0f){return FALSE;}
	float DotY = D3DXVec3Dot(&Inv,obb->vY());
	float sY = (obb->Vec()->y + *s->Len() ) - fabs(DotY);
	if(sY < 0.0f){return FALSE;}
	float DotZ = D3DXVec3Dot(&Inv,obb->vZ());
	float sZ = (obb->Vec()->z + *s->Len() ) - fabs(DotZ);
	if(sZ < 0.0f){return FALSE;}	
	//はみ出し部分が一番短いオブジェクトが接触しているベクトル
	v[0].Set(sX,DotX,obb->vX());
	v[1].Set(sY,DotY,obb->vY());
	v[2].Set(sZ,DotZ,obb->vZ());
	std::sort(v.begin(),v.end(),HitVector());
	if(v[0].back > 0.0f){s->vBack= v[0].v * v[0].val;}
	else{			s->vBack = -v[0].v * v[0].val;}		
	obb->vBack = -s->vBack ;
	return TRUE;
}
//立方体対球(上のを逆にしただけ)
OBBvsS::OBBvsS(){}
BOOL OBBvsS::Hit(CollObj* obb,CollObj* s)
{	
	if(so.Hit(s,obb))
	{
		s->vBack = obb->vBack;
		obb->vBack = -s->vBack;
		return TRUE;

	}
	return FALSE;
}
//立方体と平面
OBBvsP::OBBvsP(){}
BOOL OBBvsP::Hit(CollObj* obb,CollObj* p)
{
	float L = D3DXVec3Dot(&(*obb->Pos() - *p->Pos()),p->Vec()) - 
	Ln(p->Vec(),&(*obb->vX() * obb->Vec()->x),&(*obb->vY() * obb->Vec()->y),&(*obb->vZ() * obb->Vec()->z));
	if(L < 0.0f)
	{
		obb->vBack = *p->Vec() * -L;
		p->vBack = -obb->vBack;

		return TRUE;
	}
	obb->vBack = D3DXVECTOR3(0.0f,0.0f,0.0f);
	p->vBack = D3DXVECTOR3(0.0f,0.0f,0.0f);

	return FALSE;
}

//平面と立方体(上のを逆にしただけ)
PvsOBB::PvsOBB(){}
BOOL PvsOBB::Hit(CollObj* p ,CollObj*obb)
{
	if(OBBvsP().Hit(obb,p))
	{
		p->vBack = obb->vBack;
		obb->vBack = -p->vBack;
		return TRUE;
	}
	return FALSE;
}
//立方体と立方体
OBBvsOBB::OBBvsOBB(){}
BOOL OBBvsOBB::Hit(CollObj* obb1,CollObj* obb2)
{
	obb1->vBack = D3DXVECTOR3(0.0f,0.0f,0.0f);
	obb2->vBack = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 Inv(*obb1->Pos() - *obb2->Pos());
	D3DXVECTOR3 X1 = *obb1->vX() * obb1->Vec()->x;
	D3DXVECTOR3 Y1 = *obb1->vY() * obb1->Vec()->y;
	D3DXVECTOR3 Z1 = *obb1->vZ() * obb1->Vec()->z;
	D3DXVECTOR3 X2 = *obb2->vX() * obb2->Vec()->x;
	D3DXVECTOR3 Y2 = *obb2->vY() * obb2->Vec()->y;
	D3DXVECTOR3 Z2 = *obb2->vZ() * obb2->Vec()->z;
	//obb1の3軸
	float I1x = D3DXVec3Dot(&Inv,obb1->vX());
	float x1  = (Ln(obb1->vX(),&X2,&Y2,&Z2) + obb1->Vec()->x) - fabs(I1x);
	if( 0.0f > x1 ){return FALSE;}

	float I1y = D3DXVec3Dot(&Inv,obb1->vY());
	float y1  = (Ln(obb1->vY(),&X2,&Y2,&Z2) + obb1->Vec()->y) - fabs(I1y);
	if( 0.0f > y1 ){return FALSE;}

	float I1z = D3DXVec3Dot(&Inv,obb1->vZ());
	float z1  = (Ln(obb1->vZ(),&X2,&Y2,&Z2) + obb1->Vec()->z) - fabs(I1z);
	if( 0.0f > z1 ){return FALSE;}
	//obb2の3軸
	float I2x = D3DXVec3Dot(&Inv,obb2->vX());
	float x2  = (Ln(obb2->vX(),&X1,&Y1,&Z1) + obb2->Vec()->x) - fabs(I2x);
	if( 0.0f > x2 ){return FALSE;}

	float I2y = D3DXVec3Dot(&Inv,obb2->vY());
	float y2  = (Ln(obb2->vY(),&X1,&Y1,&Z1) + obb2->Vec()->y) - fabs(I2y);
	if( 0.0f > y2 ){return FALSE;}

	float I2z = D3DXVec3Dot(&Inv,obb2->vZ());
	float z2  = (Ln(obb2->vZ(),&X1,&Y1,&Z1) + obb2->Vec()->z) - fabs(I2z);
	if( 0.0f > z2 ){return FALSE;}
	//C11
	D3DXVECTOR3 C11;
	D3DXVec3Cross(&C11,obb1->vX(),obb2->vX());
	D3DXVec3Normalize(&C11,&C11);
	float IC11=D3DXVec3Dot(&Inv,&C11);
	float c11 = (Ln(&C11,&X1,&Y1,&Z1) + Ln(&C11,&X2,&Y2,&Z2)) - fabs(IC11);
	if(0.0f > c11){return FALSE; }

	//C12
	D3DXVECTOR3 C12;
	D3DXVec3Cross(&C12,obb1->vX(),obb2->vY());
	D3DXVec3Normalize(&C12,&C12);
	float IC12=D3DXVec3Dot(&Inv,&C12);
	float c12= (Ln(&C12,&X1,&Y1,&Z1) + Ln(&C12,&X2,&Y2,&Z2)) - fabs(IC12);
	if(0.0f > c12){return FALSE;}
	
	//C13
	D3DXVECTOR3 C13;
	D3DXVec3Cross(&C13,obb1->vX(),obb2->vZ());
	D3DXVec3Normalize(&C13,&C13);
	float IC13=D3DXVec3Dot(&Inv,&C13);
	float c13= (Ln(&C13,&X1,&Y1,&Z1) + Ln(&C13,&X2,&Y2,&Z2)) - fabs(IC13);
	if(0.0f > c13){return FALSE;}
	
	//C21
	D3DXVECTOR3 C21;
	D3DXVec3Cross(&C21,obb1->vY(),obb2->vX());
	D3DXVec3Normalize(&C21,&C21);
	float IC21=D3DXVec3Dot(&Inv,&C21);
	float c21= (Ln(&C21,&X1,&Y1,&Z1) + Ln(&C21,&X2,&Y2,&Z2)) - fabs(IC21);
	if(0.0f > c21){return FALSE;}
	
	//C22
	D3DXVECTOR3 C22;
	D3DXVec3Cross(&C22,obb1->vY(),obb2->vY());
	D3DXVec3Normalize(&C22,&C22);
	float IC22=D3DXVec3Dot(&Inv,&C22);
	float c22 = (Ln(&C22,&X1,&Y1,&Z1) + Ln(&C22,&X2,&Y2,&Z2)) - fabs(IC22);
	if(0.0f > c22){return FALSE;}
	
	//C23
	D3DXVECTOR3 C23;
	D3DXVec3Cross(&C23,obb1->vY(),obb2->vZ());
	D3DXVec3Normalize(&C23,&C23);
	float IC23=D3DXVec3Dot(&Inv,&C23);
	float c23 = (Ln(&C23,&X1,&Y1,&Z1) + Ln(&C23,&X2,&Y2,&Z2)) - fabs(IC23);
	if(0.0f > c23){return FALSE;}
	
	//C31
	D3DXVECTOR3 C31;
	D3DXVec3Cross(&C31,obb1->vZ(),obb2->vX());
	D3DXVec3Normalize(&C31,&C31);
	float IC31=D3DXVec3Dot(&Inv,&C31);
	float c31= (Ln(&C31,&X1,&Y1,&Z1)+Ln(&C31,&X2,&Y2,&Z2)) - fabs(IC31);
	if(0.0f > c31){return FALSE;}


	//C32
	D3DXVECTOR3 C32;
	D3DXVec3Cross(&C32,obb1->vZ(),obb2->vY());
	D3DXVec3Normalize(&C32,&C32);
	float IC32=D3DXVec3Dot(&Inv,&C32);
	float c32 = (Ln(&C32,&X1,&Y1,&Z1) + Ln(&C32,&X2,&Y2,&Z2)) - fabs(IC32);
	if(0.0f > c32){return FALSE;}


	//C33
	D3DXVECTOR3 C33;
	D3DXVec3Cross(&C33,obb1->vZ(),obb2->vZ());
	D3DXVec3Normalize(&C33,&C33);
	float IC33 = D3DXVec3Dot(&Inv,&C33);
	float c33= (Ln(&C33,&X1,&Y1,&Z1) + Ln(&C33,&X2,&Y2,&Z2)) - fabs(IC33);
	if(0.0f > c33){return FALSE;}
	float tes = 50.0f;
	if(c11 > 0.0f)
	{
		if(IC11 > 0.0f){ obb1->vBack  = C11 * c11; }
		else{			 obb1->vBack  =-C11 * c11;}
		tes=c11;
	}

	if(c12 > 0.0f)
	{
		if(tes > c12)
		{
			if(IC12 > 0.0f){ obb1->vBack  = C12 * c12; }
			else{			 obb1->vBack  =-C12 * c12;}
			tes=c12;
		}
	}

	if(c13 > 0.0f)
	{
		if(tes > c13)
		{
			if(IC13 > 0.0f){ obb1->vBack  = C13 * c13; }
			else{			 obb1->vBack  =-C13 * c13;}
			tes=c13;
		}
	}

	if(c21 > 0.0f)
	{
		if(tes > c21)
		{
			if(IC21 > 0.0f){ obb1->vBack  = C21 * c21; }
			else{			 obb1->vBack  =-C21 * c21;}
			tes=c21;
		}
	}

	if(c22 > 0.0f)
	{
		if(tes > c22)
		{
			if(IC22 > 0.0f){ obb1->vBack  = C22 * c22; }
			else{			 obb1->vBack  =-C22 * c22;}
			tes=c22;
		}
	}

	if(c23 > 0.0f)
	{
		if(tes > c23)
		{
			if(IC23 > 0.0f){ obb1->vBack  = C23 * c23; }
			else{			 obb1->vBack  =-C23 * c23;}
			tes=c23;
		}
	}

	if(c31 > 0.0f)
	{
		if(tes > c31)
		{
			if(IC31 > 0.0f){ obb1->vBack  = C31 * c31; }
			else{			 obb1->vBack  =-C31 * c31;}
			tes=c31;
		}
	}

	if(c32 > 0.0f)
	{
		if(tes > c32)
		{
			if(IC32 > 0.0f){ obb1->vBack  = C32 * c32; }
			else{			 obb1->vBack  =-C32 * c32;}
			tes=c32;
		}
	}

	if(c33 > 0.0f)
	{
		if(tes > c33)
		{
			if(IC33 > 0.0f){ obb1->vBack  = C33 * c33; }
			else{			 obb1->vBack  =-C33 * c33;}
			tes=c33;
		}
	}
	if(x1 > 0.0f)
	{
		if(tes > x1)
		{
			if(I1x > 0.0f){ obb1->vBack  = *obb1->vX() * x1;}
			else{			obb1->vBack  =-*obb1->vX() * x1;}
			tes=x1;	
		
		}
	}

	if(y1 > 0.0f)
	{
		if(tes > y1)
		{
			if(I1y > 0.0f){ obb1->vBack  = *obb1->vY() * y1;}
			else{			obb1->vBack  =-*obb1->vY() * y1;}
			tes=y1;
		}
	}
	if(z1 > 0.0f)
	{
		if(tes > z1)
		{
			if(I1z > 0.0f){ obb1->vBack  = *obb1->vZ() * z1;}
			else{			obb1->vBack  =-*obb1->vZ() * z1;}
			tes=z1;
		
		}
	}

	if(x2 > 0.0f)
	{
		if(tes > x2)
		{
			if(I2x > 0.0f){ obb1->vBack  = *obb2->vX() * x2;}
			else{			obb1->vBack  =-*obb2->vX() * x2;}
			tes=x2;
		
		}
	}	
	if(y2 > 0.0f)
	{
		if(tes > y2)
		{
			if(I2y > 0.0f){ obb1->vBack  = *obb2->vY() * y2;}
			else{			obb1->vBack  =-*obb2->vY() * y2;}
			tes=y2;
		
		}
	}
	if(z2 > 0.0f)
	{
		if(tes > z2)
		{
			if(I2z > 0.0f){ obb1->vBack  = *obb2->vZ() * z2;}
			else{			obb1->vBack  =-*obb2->vZ() * z2;}
			tes=z2;		
		}
	}
	//微調整
	obb1->vBack  = obb1->vBack  * 1.01f; 
	obb2->vBack  = -obb1->vBack;
	return TRUE;
}