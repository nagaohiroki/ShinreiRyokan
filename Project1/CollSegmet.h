#pragma once
//�����̓����蔻��
class LineSegmet
{
public:
	LineSegmet();
	//�����Ɠ_(��)
	BOOL LineSegHit(D3DXVECTOR3*,D3DXVECTOR3*,D3DXVECTOR3*,float);
	//���Ɠ_(��)
	BOOL LineHit(D3DXVECTOR3*,D3DXVECTOR3*,D3DXVECTOR3*,float);
	//������OBB
	BOOL LinevsOBB(D3DXVECTOR3*,D3DXVECTOR3*,float,CollObj*);

};
//�����Ɠ_(��)
class SegvsS :public BaseColl
{
public:
	SegvsS();
	BOOL Hit(CollObj*,CollObj*);

};
//���̂Ɛ���
class SvsSeg:public BaseColl
{
public:
	SvsSeg();
	BOOL Hit(CollObj*,CollObj*);

};
//������OBB
class SegvsOBB :public BaseColl
{
public:
	SegvsOBB();
	BOOL Hit(CollObj*,CollObj*);

};
//OBB�Ɛ���
class OBBvsSeg :public BaseColl
{
public:
	OBBvsSeg();
	BOOL Hit(CollObj*,CollObj*);

};