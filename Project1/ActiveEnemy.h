#pragma once 
namespace Ev
{
//====================================
//�G���A���܂������Ƃ��̓G�̋���
//====================================
class ActiveEnemy : public Scene
{
	int count;
public:
	
	const TCHAR *name();
	ActiveEnemy();
	VOID Set();
	VOID Update();
	VOID DebugText(TCHAR*,int);
};
//====================================
//�G�C�x���g
//====================================
class EnemyGuestBath : public Scene 
{	
	CObjSound oop;
public:
	const TCHAR *name();
	EnemyGuestBath();
	VOID Update();
};

};