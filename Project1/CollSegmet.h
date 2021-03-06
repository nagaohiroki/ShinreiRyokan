#pragma once
//線分の当たり判定
class LineSegmet
{
public:
	LineSegmet();
	//線分と点(球)
	BOOL LineSegHit(D3DXVECTOR3*,D3DXVECTOR3*,D3DXVECTOR3*,float);
	//線と点(球)
	BOOL LineHit(D3DXVECTOR3*,D3DXVECTOR3*,D3DXVECTOR3*,float);
	//線分とOBB
	BOOL LinevsOBB(D3DXVECTOR3*,D3DXVECTOR3*,float,CollObj*);

};
//線分と点(球)
class SegvsS :public BaseColl
{
public:
	SegvsS();
	BOOL Hit(CollObj*,CollObj*);

};
//球体と線分
class SvsSeg:public BaseColl
{
public:
	SvsSeg();
	BOOL Hit(CollObj*,CollObj*);

};
//線分とOBB
class SegvsOBB :public BaseColl
{
public:
	SegvsOBB();
	BOOL Hit(CollObj*,CollObj*);

};
//OBBと線分
class OBBvsSeg :public BaseColl
{
public:
	OBBvsSeg();
	BOOL Hit(CollObj*,CollObj*);

};