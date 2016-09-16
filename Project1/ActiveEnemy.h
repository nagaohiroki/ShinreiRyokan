#pragma once 
namespace Ev
{
//====================================
//エリアをまたいだときの敵の挙動
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
//敵イベント
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