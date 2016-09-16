#pragma once
//=======================================================
//�v���C���[�L�����ݒ�
//=======================================================
//�t�B�[���hIndex
enum FIELD
{
	FD_TestRoom,
	FD_Soto,
	FD_Lobby,
	FD_LobbyRestRoom,
	FD_Staff_Room,
	FD_Dining_Room,
	FD_Bath_Pass,
	FD_Bath_Datui_Man,
	FD_Bath_Datui_Woman,
	FD_Bath_Room_Man,
	FD_Bath_Room_Woman,
	FD_Guest_Room,
	FD_Guest_Bath,
	FD_Rest_Men,
	FD_Rest_Women,
	FD_F3,
	FD_Roof_Kai,
	FD_Roof_Top,
	FD_201,
	FD_201_Bath,
	FD_202,
	FD_203,
	FD_Sandou,
	FD_Secret,
};
//�^�C�����C��
enum TIMELINE
{
	TL_INTRO_START,
	TL_INTRO_1,
	TL_INTRO_2,
	TL_INTRO_END,
	TL_DRUG_START,
	TL_DRUG_LIGHT,
	TL_DRUG_GUNGUN,
	TL_GUEST_ENEMY_START,
	TL_GUEST_ENEMY_END,
	TL_ROOF_ENEMY,
	TL_ROOF_DUCT,
	TL_201_OPEN,
	TL_BOUKA_OPEN,
	TL_ENEMY_WALK,	
	TL_TIME5,
	TL_DATUI_ENEMY_END,
	TL_WHITEBORD,
	TL_203_OPEN,
	TL_203_EXIT,
	TL_GOOD_BYE,
	TL_READ_TIPS,
	TL_FISH_WALK1,
	TL_FISH_WALK2,
	TL_SERCRET_DOOR,
	TL_ENDING,
};
//�d�|���t���O
class TrickFlag
{
public:
	int chairMove;
	int dinigDoor;
	int darts;
	int dartsbord;
	TrickFlag();
	VOID Init();

};
//�G�̃t���O
class EnemyFlag
{
public:
	int Level;
	int HP;
	int mode;
	float rot;
	D3DXVECTOR3 pos;
	EnemyFlag();
	VOID Init();
};
//�t���O�}�l�[�W��
class FlagManager
{
private:	
	
public:
	//�v���C���Ԃ̈ꎞ�ۑ�
	DWORD NTime;
	//�G�t���O
	EnemyFlag enemy;
	//�d�|���̃t���O
	TrickFlag trick;
	//�A�C�e��
	BOOL ItemGet[ITEM_MAX];
	BOOL ItemGeted[ITEM_MAX];
	//�v���C����
	DWORD PlayTime;
	//�Z�[�u��������
	tm Local;
	//�L�����̌���
	float RotY;
	//�t�B�[���h�^�C�v
	FIELD FldType;
	//�L�����̈ʒu
	D3DXVECTOR3 Pos;
	//�ǂ��̃h�A�����������
	size_t Door;
	//�C�x���g�̐i�s�t���O
	TIMELINE EventFlag;
	

	FlagManager();
	VOID Init();
	VOID StaticPos(D3DXVECTOR3*,float);
	VOID SaveTime();
	VOID LoadTime();
	VOID ShowData(TCHAR*,int);
	//�A�C�e��
	//�A�C�e�����擾
	VOID iGet(ITEM);
	//�̂Ă�
	VOID iRelease(ITEM);
	//���O(�ߋ��Ɏ����Ă����t���O���j������)
	VOID iRemove(ITEM);
	//���ݎ����Ă��邩�̃t���O
	BOOL iGetFlag(ITEM);
	//�ߋ��Ɏ����Ă������̃t���O
	BOOL iGetedFlag(ITEM);



};
//�t���O�Z�[�u
class GameSave
{
private:	
	
public:
	enum{MAX_SAVE = 3};
	GameSave();
	BOOL Save(FlagManager*,int);
	BOOL Load(FlagManager*,int);
};