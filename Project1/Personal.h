#pragma once
//=======================================================
//�p�[�\�i���f�[�^
//=======================================================
class Personal
{
private:
	//�Ə�
	CObjFVF sight;
	//�V���b�g�̃g���K
	BOOL TrgRelease;
	//�L�����Z���J�E���g�p
	int CanselCount;
	Menu menu;
	//�i�s�l
	D3DXVECTOR3 NextPos;
	//�ڐG�x�N�g��
	D3DXVECTOR3 HitVec;	
	//�}�C���C�u����
	MyLibrary* ML;
	//�L�[�ύX�̍X�V
	int MoveKey;
	//�L�����̒����_	
	D3DXVECTOR3 AtPos;
	//�ړ��x�N�g��
	D3DXVECTOR3 tes;
	//����
	CObjSound Step;	
	CObjSound MenuOpen;	
	CObjSound ItemGet;
	enum SLCT_MAX{SMAX = 3};
	CObjSound slct[SMAX];
	//�n�_�f�o�b�O�p
//	CObjMesh At;
	//�V���b�g
	std::vector<CBullet*> Blt;
	int m_iDelay;	
	UINT m_iCount;
	//�y�[�W
	int m_iPage;
	//FPS�J�����ړ���
	D3DXVECTOR2 EyeRot;
	
	//debug�pFPS
	VOID FPSMode();
	//���
	VOID ActiveMode();
	VOID EventMode();
	VOID MenuMode();
	VOID DamageMode();
	VOID DeadMode();
public:
	//FPS���[�h�t���O	
	BOOL FPSFlag;
	//SE
	enum Player_SE
	{
		SE_CANSEL,
		SE_CHECK,
		SE_STEP,
		SE_ITEM,
		SE_OPEN,
		SE_SLIDE,
		SE_SELECT,

	};
	//���	
	enum Player_Mode
	{
		MODE_EVENT,
		MODE_ACTIVE,
		MODE_MENU,
		MODE_DAMAGE,
	};	
	Player_Mode Mode;
	//�O���[�o��BGM
	CObjSound *BGM;	
 	int ReLoad;
	//�t���O�}�l�[�W��
	FlagManager FM;		
	//��l�����f��
	gt_Model  gt;		
	//���ׂ�t���O
	BOOL Check;	
	//�L�����Z���t���O
	BOOL Cansel;
	//�����蔻��p�I�u�W�F�N�g
	CObjMesh obj;	
	//�R���X�g���N�^
	Personal();	
	virtual ~Personal();	
	//����
	VOID Set(MyLibrary*);
	//�X�V
	VOID Update();	
	//�`��
	VOID draw();
	//UI�̕`��
	VOID Ui();
	//�q�b�g�C�x���g
	VOID HitEvent(std::vector<CollObj*>*);
	//�e���G�ɂ�����
	VOID AtcBullet(D3DXMATRIX*);
	//�e�̃��Z�b�g
	VOID ResetBullet();
	//�f�o�b�O�p�e�L�X�g
	VOID DebugText(TCHAR*,int);
	//debug�{�^��
	VOID DButton(DebugButton*);	
	//�v���C���[��������SE
	VOID CheckSE(Player_SE);
};


