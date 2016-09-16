//�R���X�g���N�^
HitPoint::HitPoint()
{
	m_iHp = 0;
}
//�̗͒l��Ԃ�
int HitPoint::HP()
{
	return m_iHp;
}
//�̗͂̐ݒ�
VOID HitPoint::Set(int hp)
{
	m_iHp = hp;
}
//��
VOID HitPoint::Recovery(int hp)
{
	m_iHp += hp;
}
//�_���[�W
VOID HitPoint::Damage(int hp)
{
	m_iHp -= hp;
}
//���S����
BOOL HitPoint::Dead()
{
	return 0 >= m_iHp;
}
//��������
BOOL HitPoint::ALive()
{
	return 0 < m_iHp; 
}