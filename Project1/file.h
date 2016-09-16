#pragma once
//================================
//�O���t�@�C���Ƃ̃A�N�Z�X
//================================
class CFile
{
private:	
public:
	CFile();
	VOID txt(const TCHAR*,const TCHAR*);//�e�L�X�g�t�@�C��(�t�@�C����,�e�L�X�g);
	VOID atxt(const TCHAR*,const TCHAR*);//�e�L�X�g�t�@�C��(�t�@�C����,�e�L�X�g);(�e�L�X�g�ɏ�������)
	VOID Debug(TCHAR*);	

};

//Vec3�Z�p
class vec3Ari
{
public:
	vec3Ari(){}
	//VEC3��xyz���Ƃ̏�
	D3DXVECTOR3 D3DXVec3Multi(D3DXVECTOR3* v1,D3DXVECTOR3* v2)
	{
		return D3DXVECTOR3(
			v1->x * v2->x,
			v1->y * v2->y,
			v1->z * v2->z);
	}
	//Vec3�̏�
	D3DXVECTOR3 D3DXVec3Div(D3DXVECTOR3* v1,D3DXVECTOR3* v2)
	{
		return D3DXVECTOR3(
			v1->x / v2->x,
			v1->y / v2->y,
			v1->z / v2->z);
	}
	//�����(0,0)���[���h���W����X�N���[�����W�ɕϊ�(�o��,���[���h�ʒu,�ˉe�s��,�X�N���[�����T�C�Y,�X�N���[���c�T�C�Y)
	D3DXVECTOR3 D3DXVec3WtoS(D3DXVECTOR3* Out,D3DXVECTOR3 *Pos,D3DXMATRIX* mat,UINT w,UINT h)
	{
		//�L�����̃X�N���[�����W
 		D3DXVECTOR4 out;
		D3DXVec4Transform(&out,&D3DXVECTOR4(Pos->x,Pos->y,Pos->z,1.0f),mat);
		out/=out.w;
		Out->x=(out.x+1.0f) * (w/2);
		Out->y=-(out.y-1.0f) * (h/2);
		Out->z=out.z;
		return *Out;
	}
	//���S��(0,0)���[���h���W����X�N���[�����W�ɕϊ�(�o��,���[���h�ʒu,�ˉe�s��,�X�N���[�����T�C�Y,�X�N���[���c�T�C�Y)
	D3DXVECTOR3 D3DXVec3WtoSCent(D3DXVECTOR3* Out,D3DXVECTOR3 *Pos,D3DXMATRIX* mat,UINT w,UINT h)
	{
		//�L�����̃X�N���[�����W
 		D3DXVECTOR4 out;
		D3DXVec4Transform(&out,&D3DXVECTOR4(Pos->x,Pos->y,Pos->z,1.0f),mat);
		out /= out.w;
		Out->x = out.x * (w / 2);
		Out->y = out.y * (h / 2);
		Out->z = 0.0f;//out.z;
		return *Out;
	}
	//3�x�N�g���̂����Ƃ������l��Ԃ�
	float D3DXVec3Top(D3DXVECTOR3 *v)
	{
		if(v->x >= v->y)
		{
			if(v->x >= v->z){return v->x;}
		}
		else
		{
			if(v->y >= v->z){return v->y;}
		}
		return v->z;
	}

	//�x�N�g�����Ȃ��p�ŕԂ�(�o��,�ʒu,�����_)
	D3DXVECTOR3 AtLookYpr(D3DXVECTOR3* out,D3DXVECTOR3* Eye,D3DXVECTOR3* At)
	{
		
		D3DXVECTOR3 vec(*At - *Eye);
		D3DXVECTOR3 vZ,vY;
		D3DXMATRIX mR;
		D3DXVec3Normalize(&vec,&vec);
		D3DXMatrixRotationY(&mR,atan2(vec.x,vec.z));
		D3DXVec3TransformCoord(&vY,&D3DXVECTOR3(0.0f,1.0f,0.0f),&mR);
		D3DXVec3TransformCoord(&vZ,&D3DXVECTOR3(0.0f,0.0f,1.0f),&mR);

		out->y=D3DXToDegree(atan2(vec.x,vec.z));
		out->x=D3DXToDegree(atan2(
			D3DXVec3Dot(&vZ,&vec),
			D3DXVec3Dot(&vY,&vec)));
		return *out;
	}
	//�x�N�g�����Ȃ��p�ŕԂ�(�o��,�x�N�g��)
	D3DXVECTOR3 AtLookYpr(D3DXVECTOR3* out,D3DXVECTOR3* vec)
	{
		D3DXVECTOR3 vZ,vY;
		D3DXMATRIX mR;
		D3DXMatrixRotationY(&mR,atan2(vec->x,vec->z));
		D3DXVec3TransformCoord(&vY,&D3DXVECTOR3(0.0f,1.0f,0.0f),&mR);
		D3DXVec3TransformCoord(&vZ,&D3DXVECTOR3(0.0f,0.0f,1.0f),&mR);

		out->y=D3DXToDegree(atan2(vec->x,vec->z));
		out->x=D3DXToDegree(atan2(
			D3DXVec3Dot(&vZ,vec),
			D3DXVec3Dot(&vY,vec)));
		return *out;
	}


};
//===================================================
//�A�j���[�V�����L�[
//===================================================
template<class T>
class AKey
{
private:
	typedef std::map<int,T> MapT;
	typedef std::pair<int,T> pT;
	//�l��Ԃ�
	T ValA( int key )
	{
		//��v����L�[������Β��ڏo��
		MapT::iterator it = val.find(key);
		if( it != val.end() ){	return (*it).second;}
		//������ΑO��̃L�[���v�Z����
		MapT::iterator low = val.lower_bound(key);
		MapT::iterator high = low;
		--low;
		return (*low).second + ((*high).second - (*low).second) *
			   (float)(key - (*low).first) / (float)((*high).first - (*low).first);
	}	
public:	
	MapT val;
	AKey(){}
	//�ŏI�L�[
	int MaxKey()
	{
		return val.rbegin()->first; 
	}	
	VOID DeleteKey(int k)
	{
		val.erase(k);
	}
	VOID DeleteAll()
	{
		val.clear();
	}
	//�L�[���Z�b�g
	VOID SetKey( int k,T v )
	{	
		val.insert(pT(k,v));
	}		
	//���[�v
	T Val( int key )
	{
		return ValA(key % MaxKey());	
	}
	//�������[�v
	T Val1( int key )
	{
		if(key <= MaxKey() ){return ValA(key); }
		return ValA(MaxKey()); 
	}

};