#pragma once

//�����蔻��̑�
class CollSell
{
public:	
	BaseColl* coll[CT_MAX];
	CollSell();
};
//3��I�u�W�F�N�g�̓����蔻��
class CollParfect
{
private:
	BaseColl  base;
	SvsS	  svss;
	SvsP	  svsp;
	SvsOBB	  svso;
	SvsSeg    svsg;    

	OBBvsS	  ovss;
	OBBvsP	  ovsp;
	OBBvsOBB  ovso;
	OBBvsSeg  ovsg;    

	PvsS      pvss;
	PvsOBB    pvso;

	SegvsS    gvss;    
	SegvsOBB  gvso;    
	
	CollSell coll[CT_MAX];
public:
	CollParfect();
	BOOL Hit(CollObj*,CollObj*);
};
