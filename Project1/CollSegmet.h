#pragma once
//ü•ª‚Ì“–‚½‚è”»’è
class LineSegmet
{
public:
	LineSegmet();
	//ü•ª‚Æ“_(‹…)
	BOOL LineSegHit(D3DXVECTOR3*,D3DXVECTOR3*,D3DXVECTOR3*,float);
	//ü‚Æ“_(‹…)
	BOOL LineHit(D3DXVECTOR3*,D3DXVECTOR3*,D3DXVECTOR3*,float);
	//ü•ª‚ÆOBB
	BOOL LinevsOBB(D3DXVECTOR3*,D3DXVECTOR3*,float,CollObj*);

};
//ü•ª‚Æ“_(‹…)
class SegvsS :public BaseColl
{
public:
	SegvsS();
	BOOL Hit(CollObj*,CollObj*);

};
//‹…‘Ì‚Æü•ª
class SvsSeg:public BaseColl
{
public:
	SvsSeg();
	BOOL Hit(CollObj*,CollObj*);

};
//ü•ª‚ÆOBB
class SegvsOBB :public BaseColl
{
public:
	SegvsOBB();
	BOOL Hit(CollObj*,CollObj*);

};
//OBB‚Æü•ª
class OBBvsSeg :public BaseColl
{
public:
	OBBvsSeg();
	BOOL Hit(CollObj*,CollObj*);

};