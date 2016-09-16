#pragma once
//�����蔻��̎��
enum COLLISION_TYPE
{
	CT_NONE,
	CT_SPHERE,
	CT_OBB,
	CT_PLANE,
	CT_SEGMET,

	CT_MAX,
};
//�����蔽��
enum COLLISION_BACK
{
	CB_NONE,
	CB_PLUS,
	CB_ENEMY,
	CB_MAX,
};
//�����蔻��I�u�W�F�N�g�x�[�X
class CollObj
{
protected:
public:
	int Reaction;//�����蔽��1���v���C���[2���e
	COLLISION_TYPE cType;//�����蔻��̌`
	COLLISION_BACK cBack;//���˕Ԃ�^�C�v
	D3DXVECTOR3 vBack;//�����߂���
	CollObj();

	virtual float *Len();
	virtual D3DXVECTOR3 *Pos();
	virtual D3DXVECTOR3 *Vec();
	virtual D3DXVECTOR3 *vX();
	virtual D3DXVECTOR3 *vY();
	virtual D3DXVECTOR3 *vZ();
};
//����
class Plane : public CollObj
{
private:
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Vec;
public:
	Plane();
	D3DXVECTOR3 *Pos();
	D3DXVECTOR3 *Vec();	

};

//����
class Shpere : public CollObj
{
private:
	float m_Len;
	D3DXVECTOR3 m_Pos;
public:
	Shpere();
	float *Len();
	D3DXVECTOR3 *Pos();
};
//OBB
class OBB : public CollObj
{
private:
	float m_Len;
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Vec;
	D3DXVECTOR3 m_vX;
	D3DXVECTOR3 m_vY;
	D3DXVECTOR3 m_vZ;
public:
	OBB();
	float *Len();
	D3DXVECTOR3 *Pos();
	D3DXVECTOR3 *Vec();
	D3DXVECTOR3 *vX();
	D3DXVECTOR3 *vY();
	D3DXVECTOR3 *vZ();
};

//����
class Segmet :  public CollObj
{
	float m_Len;
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Vec;
public:
	Segmet();
	float *Len();
	D3DXVECTOR3 *Pos();
	D3DXVECTOR3 *Vec();
};