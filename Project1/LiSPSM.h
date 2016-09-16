#pragma once
//-================================================================
//LiSPSM(���C�g�X�y�[�X�p�[�X�y�N�e�B�u�V���h�E�}�b�v)
//-================================================================
class LiSPSM
{
private:
	enum{PN=8};
	D3DXVECTOR3 Point[PN];
	D3DXVECTOR3 Point2[PN];
	D3DXMATRIX mView;
	D3DXMATRIX mProj;
	//UP�x�N�g�������߂�
	VOID UpVec(D3DXVECTOR3*,const D3DXVECTOR3*,const D3DXVECTOR3*);
	//�s���(-1,-1,-1)~(1,1,1)�͈̔͂ɂ��킹��
	VOID MatrixFit(D3DXMATRIX*,const D3DXVECTOR3*,const D3DXVECTOR3*);
	//�|�C���g�֘A
	//�s�񂩂�ϊ�
	VOID PointTransform(const D3DXMATRIX*);
	//AABB���擾����
	VOID GetAABB(D3DXVECTOR3*,D3DXVECTOR3*);
	VOID StandPoint(const D3DXMATRIX*,const float,const float,const float,const float);
public:
	LiSPSM();
	VOID MatLiSPSM(D3DXMATRIX*,const D3DXMATRIX*,D3DXVECTOR3*,D3DXVECTOR3*,D3DXVECTOR3*,const float,const float,const float,const float);

};