#pragma once
//�q�b�g�|�C���g
class HitPoint
{
private:
	//�̗͒l
	int m_iHp;
public:
	//�R���X�g���N�^
	HitPoint();
	//�̗͒l��Ԃ�
	int HP();
	//�̗͂̐ݒ�
	VOID Set(int);
	//��
	VOID Recovery(int);
	//�_���[�W
	VOID Damage(int);
	//���S����
	BOOL Dead();
	//��������
	BOOL ALive();

};