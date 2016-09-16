//====================================
//エリアをまたいだときの敵の挙動
//====================================
const TCHAR* ActiveEnemy::name(){return _T("ActiveEnemy");}
ActiveEnemy::ActiveEnemy(){}
VOID ActiveEnemy::Set()
{
	count = 0;
	//攻撃モードだった場合出てくるまで少し待機
	if(P->FM.enemy.mode == Enemy::MODE_STALK_ATTACK)
	{
		P->FM.enemy.mode = Enemy::MODE_STALK;
	}
	//非攻撃モードだった場合定位置でまつ
	else if(P->FM.enemy.mode == Enemy::MODE_STALK)
	{
		P->FM.enemy.mode = Enemy::MODE_STALK_ATTACK;
	}
}
VOID ActiveEnemy::Update()
{
	if(!(P->FM.enemy.mode == Enemy::MODE_STALK_ATTACK || P->FM.enemy.mode == Enemy::MODE_STALK)){return;}
	if(count < 100){count++;}
	if(count == 90)
	{
		P->FM.enemy.mode = Enemy::MODE_STALK_ATTACK;
	}
}

VOID ActiveEnemy::DebugText(TCHAR* t,int l)
{
	_stprintf_s(t,l,
		_T("%s\n")
		_T("count = %d\n")
		,t,count
		);
}
//=========================================
//バスルーム敵イベント
//=========================================
const TCHAR* EnemyGuestBath::name(){return _T("EnemyGuestBath");}
EnemyGuestBath::EnemyGuestBath()
{

	oop.Set(wav_oop);
	Snd.push_back(&oop);
}	
VOID EnemyGuestBath::Update()
{
	if(P->FM.EventFlag != TL_GUEST_ENEMY_START){return;}
	switch(P->FM.enemy.mode)
	{
		//出現------------------------------------------------
	case Enemy::MODE_CLEAR:	
		if(P->FM.EventFlag == TL_GUEST_ENEMY_START)
		{
			P->FM.enemy.mode = Enemy::MODE_SEARCH;
		}
		break;
		//発見------------------------------------------------
	case Enemy::MODE_SEARCH:
		//近づくもしくは攻撃を受けると気づく
		if( D3DXVec3LengthSq(&(P->obj.objPos - P->FM.enemy.pos)) < 2.0f * 2.0f )
		{
			oop.Start(ML);
			P->FM.enemy.mode = Enemy::MODE_STALK_ATTACK;
		}
		break;
		//死亡------------------------------------------------
	case Enemy::MODE_REMOVE:
		//フラグを進める
		P->FM.EventFlag = TL_GUEST_ENEMY_END;
		//モードをクリア
		P->FM.enemy.mode  = Enemy::MODE_CLEAR;
		break;
	default:break;
	}
}
