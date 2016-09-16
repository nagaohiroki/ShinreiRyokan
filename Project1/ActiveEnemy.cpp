//====================================
//�G���A���܂������Ƃ��̓G�̋���
//====================================
const TCHAR* ActiveEnemy::name(){return _T("ActiveEnemy");}
ActiveEnemy::ActiveEnemy(){}
VOID ActiveEnemy::Set()
{
	count = 0;
	//�U�����[�h�������ꍇ�o�Ă���܂ŏ����ҋ@
	if(P->FM.enemy.mode == Enemy::MODE_STALK_ATTACK)
	{
		P->FM.enemy.mode = Enemy::MODE_STALK;
	}
	//��U�����[�h�������ꍇ��ʒu�ł܂�
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
//�o�X���[���G�C�x���g
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
		//�o��------------------------------------------------
	case Enemy::MODE_CLEAR:	
		if(P->FM.EventFlag == TL_GUEST_ENEMY_START)
		{
			P->FM.enemy.mode = Enemy::MODE_SEARCH;
		}
		break;
		//����------------------------------------------------
	case Enemy::MODE_SEARCH:
		//�߂Â��������͍U�����󂯂�ƋC�Â�
		if( D3DXVec3LengthSq(&(P->obj.objPos - P->FM.enemy.pos)) < 2.0f * 2.0f )
		{
			oop.Start(ML);
			P->FM.enemy.mode = Enemy::MODE_STALK_ATTACK;
		}
		break;
		//���S------------------------------------------------
	case Enemy::MODE_REMOVE:
		//�t���O��i�߂�
		P->FM.EventFlag = TL_GUEST_ENEMY_END;
		//���[�h���N���A
		P->FM.enemy.mode  = Enemy::MODE_CLEAR;
		break;
	default:break;
	}
}
