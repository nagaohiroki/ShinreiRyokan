#pragma once//ヘッダーの重複防止

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
//当たり判定基盤
class BaseColl
{
protected:
	float Ln(D3DXVECTOR3*,D3DXVECTOR3*,D3DXVECTOR3*,D3DXVECTOR3*);
	float Ln(D3DXVECTOR3*,D3DXVECTOR3*,D3DXVECTOR3*);
public:
	BaseColl();
	virtual BOOL Hit(CollObj*,CollObj*);
}; 
//球対球
class SvsS : public BaseColl
{
public:
	SvsS();
	BOOL Hit(CollObj*,CollObj*);
};
//球対平面
class SvsP : public BaseColl
{
public:
	SvsP();
	BOOL Hit(CollObj*,CollObj*);
};

//平面対球
class PvsS : public BaseColl
{
public:
	PvsS();
	BOOL Hit(CollObj*,CollObj*);
};
//球対立方体
class SvsOBB : public BaseColl
{
	std::vector<HitVector> v;
public:
	SvsOBB();
	BOOL Hit(CollObj*,CollObj*);
};
//立方体対球
class OBBvsS : public BaseColl
{
	SvsOBB so;
public:
	OBBvsS();
	BOOL Hit(CollObj*,CollObj*);
};
//立方体対平面
class OBBvsP : public BaseColl
{
public:
	OBBvsP();
	BOOL Hit(CollObj*,CollObj*);
};
//平面対立方体
class PvsOBB : public BaseColl
{
public:
	PvsOBB();
	BOOL Hit(CollObj*,CollObj*);
};
//立方体対立方体
class OBBvsOBB : public BaseColl
{
public:
	OBBvsOBB();
	BOOL Hit(CollObj*,CollObj*);
};