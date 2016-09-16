//コンストラクタ
HitPoint::HitPoint()
{
	m_iHp = 0;
}
//体力値を返す
int HitPoint::HP()
{
	return m_iHp;
}
//体力の設定
VOID HitPoint::Set(int hp)
{
	m_iHp = hp;
}
//回復
VOID HitPoint::Recovery(int hp)
{
	m_iHp += hp;
}
//ダメージ
VOID HitPoint::Damage(int hp)
{
	m_iHp -= hp;
}
//死亡判定
BOOL HitPoint::Dead()
{
	return 0 >= m_iHp;
}
//生存判定
BOOL HitPoint::ALive()
{
	return 0 < m_iHp; 
}