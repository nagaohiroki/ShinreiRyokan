#pragma once
//当たり判定の種類
enum COLLISION_TYPE
{
	CT_NONE,
	CT_SPHERE,
	CT_OBB,
	CT_PLANE,
	CT_SEGMET,

	CT_MAX,
};
//当たり反応
enum COLLISION_BACK
{
	CB_NONE,
	CB_PLUS,
	CB_ENEMY,
	CB_MAX,
};
//当たり判定オブジェクトベース
class CollObj
{
protected:
public:
	int Reaction;//当たり反応1がプレイヤー2が弾
	COLLISION_TYPE cType;//当たり判定の形
	COLLISION_BACK cBack;//跳ね返りタイプ
	D3DXVECTOR3 vBack;//押し戻し量
	CollObj();

	virtual float *Len();
	virtual D3DXVECTOR3 *Pos();
	virtual D3DXVECTOR3 *Vec();
	virtual D3DXVECTOR3 *vX();
	virtual D3DXVECTOR3 *vY();
	virtual D3DXVECTOR3 *vZ();
};
//平面
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

//球体
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

//線分
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