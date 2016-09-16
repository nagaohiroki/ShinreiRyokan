LiSPSM::LiSPSM()
{
	size_t i;
	for(i=0; i < PN; i++)
	{
		Point[i]=D3DXVECTOR3(0.0f,0.0f,0.0f);
		Point2[i]=D3DXVECTOR3(0.0f,0.0f,0.0f);
	}
	D3DXMatrixIdentity(&mView);
	D3DXMatrixIdentity(&mProj);
}

//上方ベクトルを求める
VOID LiSPSM::UpVec(D3DXVECTOR3* pUp,const D3DXVECTOR3* pView,const D3DXVECTOR3* pLight)
{
	D3DXVECTOR3 Left;
	D3DXVec3Cross(&Left,pView,pLight);
	D3DXVec3Cross(pUp,pLight,&Left);
	D3DXVec3Normalize(pUp,pUp);
}

//行列を(-1,-1,-1)~(1,1,1)の範囲にあわせる
VOID LiSPSM::MatrixFit(D3DXMATRIX *pOut,const D3DXVECTOR3 *pMax,const D3DXVECTOR3 *pMin)
{
	pOut->_11 = 2.0f / (pMax->x - pMin->x);
	pOut->_21 = 0.0f;
	pOut->_31 = 0.0f;
	pOut->_41 = -(pMax->x + pMin->x) / (pMax->x - pMin->x);

	pOut->_12 = 0.0f;
	pOut->_22 = 2.0f / (pMax->y - pMin->y);
	pOut->_32 = 0.0f;
	pOut->_42 = -(pMax->y + pMin->y) / (pMax->y - pMin->y);

	pOut->_13 = 0.0f;
	pOut->_23 = 0.0f;
	pOut->_33 = 1.0f / (pMax->z - pMin->z);
	pOut->_43 = -pMin->z / (pMax->z - pMin->z);

	pOut->_14 = 0.0f;
	pOut->_24 = 0.0f;
	pOut->_34 = 0.0f;
	pOut->_44 = 1.0f;
}

//ポイント変換
VOID LiSPSM::PointTransform(const D3DXMATRIX *pMat)
{
	size_t i;
	D3DXVECTOR3 vec;
	for(i=0;i<PN;i++)
	{
		vec=Point[i];
		D3DXVec3TransformCoord(&vec,&vec,pMat);
		Point[i]=vec;
	}
}

//AABBを取得する
VOID LiSPSM::GetAABB(D3DXVECTOR3* pMax,D3DXVECTOR3* pMin)
{
	size_t i;
	*pMax = *pMin = Point[0];
	for(i = 0; i < PN; i++)
	{
		if(     pMax->x < Point[i].x){pMax->x=Point[i].x;}
		else if(pMin->x > Point[i].x){pMin->x=Point[i].x;}
		if(     pMax->y < Point[i].y){pMax->y=Point[i].y;}
		else if(pMin->y > Point[i].y){pMin->y=Point[i].y;}
		if(     pMax->z < Point[i].z){pMax->z=Point[i].z;}
		else if(pMin->z > Point[i].z){pMin->z=Point[i].z;}
	}
}

VOID LiSPSM::StandPoint(const D3DXMATRIX* matV,					  
					   const float		  angle,
					   const float		  aspect,
					   const float		  Near,
					   const float		  Far  )
{
	//視錐台のボリュームを求める
	const float t		= tanf(angle / 2.0f);
	const float NLen = t * Near;
	const float FLen = t * Far;
	D3DXVECTOR3 pos;
	size_t i;
	//ニアプレーンの点を求める
	pos.x=NLen * aspect;
	pos.y=NLen;
	pos.z=Near;
	for(i=0;i<4;i++)
	{
		Point[i]=pos;
	}
	Point[1].x=-pos.x;
	Point[2].y=-pos.y;
	Point[3].x=-pos.x;

	//ファープレーンを求める
	pos.x=FLen * aspect;
	pos.y=FLen;
	pos.z=Far;
	for(i=4; i < PN;i++)
	{
		Point[i]=pos;
	}
	Point[5].x=-pos.x;
	Point[6].y=-pos.y;
	Point[7].x=-pos.x;
	//ビュー行列の逆行列で変換する
	D3DXMATRIX matInvView;
	D3DXMatrixInverse(&matInvView,NULL,matV);
	PointTransform(&matInvView);
}

VOID LiSPSM::MatLiSPSM(		 D3DXMATRIX  *Out,
					   const D3DXMATRIX  *matV,
					  D3DXVECTOR3 *LightVec,
					    D3DXVECTOR3 *EyeVec,
					   D3DXVECTOR3 *EyePos,
					   const float		  angle,
					   const float		  aspect,
					   const float		  Near,
					   const float		  Far)
{
	StandPoint(matV,angle,aspect,Near, Far  );
	//LiSPSMの変換行列を求める
	D3DXVECTOR3 min,max,up;
	D3DXMATRIX  matLVP;
	D3DXMATRIX  matLisp;
	D3DXMatrixIdentity(&matLisp);	
	//アップベクトルを求める
	UpVec(&up,EyeVec,LightVec);
	//カメラの視点,ライトベクトル,アップベクトルからビュー行列を求める
	D3DXMatrixLookAtLH(&mView,EyePos,&(*EyePos + *LightVec),&up);
	//ポイントを変換
	PointTransform(&mView);
	//変換したポイントを内包するAABBを作成する
	GetAABB(&max,&min);
	const float cosGamma = D3DXVec3Dot(EyeVec,LightVec);
	const float sinGamma = sqrtf(1.0f - cosGamma * cosGamma);
	const float	  factor = 1.0f / sinGamma;
	const float	     z_n = factor * Near;
	const float		   d = max.y - min.y;
	const float		 z_f = z_n + d * sinGamma;
	const float		   n = (z_n + sqrtf(z_f * z_n)) * factor;
	const float	  	   f = n + d;
	const D3DXVECTOR3		Pos = *EyePos - (up * (n - Near));
	D3DXMatrixLookAtLH(&mView, &Pos, &(Pos + *LightVec), &up);
	matLisp._22 = f / (f - n);
	matLisp._42 = -f * n / (f - n);
	matLisp._24 = 1.0f;
	matLisp._44 = 0.0f;
	D3DXMatrixMultiply(&matLVP, &mView, &matLisp);
	StandPoint(matV,angle,aspect,Near, Far  );
	//この行列でポイント変換
	PointTransform(&matLVP);
	//変換したポイントを内包するAABBを作成する
	GetAABB(&max,&min);
	//AABB範囲を収める
	MatrixFit(&mProj,&max,&min);
	//最終的な透視変換行列を求める
	D3DXMatrixMultiply(&mProj,&matLisp,&mProj);
	//行列結果
	D3DXMatrixMultiply(Out,&mView,&mProj);

}
	