#pragma once
//�ǔ��A���J�[
class Anchor
{
public:
	BOOL use;
	D3DXVECTOR3 Pos;
	Anchor* pNextAnc;
	Anchor();
};
//�G
class Enemy : public Scene
{
private:
	int flow;
	float speed;
	//��̌���
	float neck;
	float body;
	//�����̓����蔻��
	BOOL Line;
	//�p�[�e�B�N��
	CObjParticl part;
	//BGM
	CObjSound bgm;
	//se
	CObjSound voice;
	//�U���J�E���g
	BOOL AtFlag;
	int AtCount;
	D3DXVECTOR3 Atvec;
	//��e���t���O
	int Muteki;
	//��
	Fish fish;
	//�f�o�b�O�\���p�I�u�W�F�N�g
	int annum;
	CObjMesh an;
	//�G���ǂ�������A���J�[
	Anchor* stalkAnc;
	//�����̒[
	Anchor* EyeAnc;
	//�������n�_�̃A���J�[
	std::vector<Anchor*> pAnc;
	//�����蔻��p�I�u�W�F�N�g(�t�B�[���h)
	CObjMesh EriaHit;
	//�e�����蔻��
	CObjMesh BulletHit;
	//����
	VOID Strength(int);
	//��U��
	VOID AngleNeck(float);
	//�����ƃG���A�̓����蔻��
	BOOL EyeHit(Segmet*);
	//�G��ǂ�
	VOID ModeStalking();
	//�G��T��
	VOID ModeSearch();
	//���S��
	VOID ModeDead();
	//�����蔻��
	VOID ModeGameOver();
	//������
	VOID ModeHit();
	//�U��
	VOID ModeAttack();
	//���s
	VOID ModeManual();
	
public:
	enum MODE
	{
		MODE_CLEAR,
		MODE_SEARCH,
		MODE_STALK_ATTACK,
		MODE_STALK,
		MODE_GAMEOVER,
		MODE_DEAD,
		MODE_REMOVE,
		MODE_MANUAL,


	};
	Enemy();
	virtual ~Enemy();
	const TCHAR* name();
	VOID Set();
	VOID Update();
	VOID draw();
	VOID DebugText(TCHAR* ,int);
	VOID DebugBtn(DebugButton*);
};