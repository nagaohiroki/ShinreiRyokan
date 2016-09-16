LineSegmet::LineSegmet(){}
//線分と点(球)
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
//線と点(球)
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
//線分とOBB
BOOL LineSegmet::LinevsOBB(D3DXVECTOR3* s,D3DXVECTOR3* v,float r,CollObj* Obb)
{
	//OBB各方位ベクトルの長さ+線分の太さ
	D3DXVECTOR3 vVol(*Obb->Vec() + D3DXVECTOR3(r,r,r)); 
	//線分の中間地点(ワールド座標)
	D3DXVECTOR3 mdl = ( *s + *v ) * 0.5f;
	//中間地点から終点までの距離(線分の半分の長さ)
	D3DXVECTOR3 Dis = *v - mdl;
	//線分の中間地点とOBBの距離
	mdl = mdl - *Obb->Pos();
	//各方位ベクトルとInvの距離の内積	
	mdl = D3DXVECTOR3(D3DXVec3Dot(Obb->vX(),&mdl),D3DXVec3Dot(Obb->vY(),&mdl),D3DXVec3Dot(Obb->vZ(),&mdl));
	//各方位ベクトルと線分半分ベクトルの内積	
	Dis = D3DXVECTOR3(D3DXVec3Dot(Obb->vX(),&Dis),D3DXVec3Dot(Obb->vY(),&Dis),D3DXVec3Dot(Obb->vZ(),&Dis));
	//2つのベクトルの各絶対値
	D3DXVECTOR3 InvDotf(fabsf(mdl.x),fabsf(mdl.y),fabsf(mdl.z));
	D3DXVECTOR3 DisDotf(fabsf(Dis.x),fabsf(Dis.y),fabsf(Dis.z));
	//OBBと線分の中間点がOBBの各半径と線分の半分の長さ以上に離れていた場合接触する可能性はない
	if(InvDotf.x > vVol.x + DisDotf.x){return FALSE;}
	if(InvDotf.y > vVol.y + DisDotf.y){return FALSE;}
	if(InvDotf.z > vVol.z + DisDotf.z){return FALSE;}
	//線分の半径ベクトルと、線分の中間とOBBの距離ベクトルの外積の絶対値
	D3DXVECTOR3 crs;
	D3DXVec3Cross(&crs,&mdl,&Dis);
	crs = D3DXVECTOR3(fabsf(crs.x),fabsf(crs.y),fabsf(crs.z));
	//外積ベクトルと比較するベクトル(ここが良くわからない)
	if(crs.x > vVol.y * DisDotf.z + vVol.z * DisDotf.y) {return FALSE;}
	if(crs.y > vVol.x * DisDotf.z + vVol.z * DisDotf.x) {return FALSE;}
	if(crs.z > vVol.x * DisDotf.y + vVol.y * DisDotf.x) {return FALSE;}
	return TRUE;
}

//線分と球体(点)
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
//球体(点)と線分
SvsSeg::SvsSeg(){}
BOOL SvsSeg::Hit(CollObj* s,CollObj* seg)
{
	return SegvsS().Hit(seg,s);
}
//線分とOBB
SegvsOBB::SegvsOBB(){}
BOOL SegvsOBB::Hit(CollObj* seg,CollObj* Obb)
{
		//OBB各方位ベクトルの長さ+線分の太さ
	D3DXVECTOR3 vVol(*Obb->Vec() + D3DXVECTOR3(*seg->Len(),*seg->Len(),*seg->Len())); 
	//線分の中間地点(ワールド座標)
	D3DXVECTOR3 mdl = ( *seg->Pos() + *seg->Vec()) * 0.5f;
	//中間地点から終点までの距離(線分の半分の長さ)
	D3DXVECTOR3 Dis = *seg->Vec() - mdl;
	//線分の中間地点とOBBの距離
	mdl = mdl - *Obb->Pos();
	//各方位ベクトルとInvの距離の内積	
	mdl = D3DXVECTOR3(D3DXVec3Dot(Obb->vX(),&mdl),D3DXVec3Dot(Obb->vY(),&mdl),D3DXVec3Dot(Obb->vZ(),&mdl));
	//各方位ベクトルと線分半分ベクトルの内積	
	Dis = D3DXVECTOR3(D3DXVec3Dot(Obb->vX(),&Dis),D3DXVec3Dot(Obb->vY(),&Dis),D3DXVec3Dot(Obb->vZ(),&Dis));
	//2つのベクトルの各絶対値
	D3DXVECTOR3 InvDotf(fabsf(mdl.x),fabsf(mdl.y),fabsf(mdl.z));
	D3DXVECTOR3 DisDotf(fabsf(Dis.x),fabsf(Dis.y),fabsf(Dis.z));
	//OBBと線分の中間点がOBBの各半径と線分の半分の長さ以上に離れていた場合接触する可能性はない
	if(InvDotf.x > vVol.x + DisDotf.x){return FALSE;}
	if(InvDotf.y > vVol.y + DisDotf.y){return FALSE;}
	if(InvDotf.z > vVol.z + DisDotf.z){return FALSE;}
	//線分の半径ベクトルと、線分の中間とOBBの距離ベクトルの外積の絶対値
	D3DXVECTOR3 crs;
	D3DXVec3Cross(&crs,&mdl,&Dis);
	crs = D3DXVECTOR3(fabsf(crs.x),fabsf(crs.y),fabsf(crs.z));
	//外積ベクトルと比較するベクトル(ここが良くわからない)
	if(crs.x > vVol.y * DisDotf.z + vVol.z * DisDotf.y) {return FALSE;}
	if(crs.y > vVol.x * DisDotf.z + vVol.z * DisDotf.x) {return FALSE;}
	if(crs.z > vVol.x * DisDotf.y + vVol.y * DisDotf.x) {return FALSE;}
	return TRUE;
}
//OBBと線分
OBBvsSeg::OBBvsSeg(){}
BOOL OBBvsSeg::Hit(CollObj* obb,CollObj* seg)
{
	return SegvsOBB().Hit(seg,obb);
}