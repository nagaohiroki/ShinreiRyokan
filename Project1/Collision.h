#pragma once//�w�b�_�[�̏d���h�~

class HitVector
{
public:
	float val;
	float back;
	D3DXVECTOR3 v;
	HitVector();
	VOID Set(float,float,D3DXVECTOR3*);
	bool operator ()(const HitVector& a, const HitVector& b) const
	{
		return a.val < b.val;
	}
};
//�����蔻����
class BaseColl
{
protected:
	float Ln(D3DXVECTOR3*,D3DXVECTOR3*,D3DXVECTOR3*,D3DXVECTOR3*);
	float Ln(D3DXVECTOR3*,D3DXVECTOR3*,D3DXVECTOR3*);
public:
	BaseColl();
	virtual BOOL Hit(CollObj*,CollObj*);
}; 
//���΋�
class SvsS : public BaseColl
{
public:
	SvsS();
	BOOL Hit(CollObj*,CollObj*);
};
//���Ε���
class SvsP : public BaseColl
{
public:
	SvsP();
	BOOL Hit(CollObj*,CollObj*);
};

//���ʑ΋�
class PvsS : public BaseColl
{
public:
	PvsS();
	BOOL Hit(CollObj*,CollObj*);
};
//���Η�����
class SvsOBB : public BaseColl
{
	std::vector<HitVector> v;
public:
	SvsOBB();
	BOOL Hit(CollObj*,CollObj*);
};
//�����̑΋�
class OBBvsS : public BaseColl
{
	SvsOBB so;
public:
	OBBvsS();
	BOOL Hit(CollObj*,CollObj*);
};
//�����̑Ε���
class OBBvsP : public BaseColl
{
public:
	OBBvsP();
	BOOL Hit(CollObj*,CollObj*);
};
//���ʑΗ�����
class PvsOBB : public BaseColl
{
public:
	PvsOBB();
	BOOL Hit(CollObj*,CollObj*);
};
//�����̑Η�����
class OBBvsOBB : public BaseColl
{
public:
	OBBvsOBB();
	BOOL Hit(CollObj*,CollObj*);
};