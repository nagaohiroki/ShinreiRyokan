#pragma once
namespace Ev{


class EvTitle : public Scene
{
	
	int PreMS;
	AKey<float> alpha;
	int Key;
	FlagManager Fm[3];
	BOOL LFlag[3];
	enum{IL = 500};
	TCHAR LoadInfo[IL];
	//���[�h�t���O
	int LoadNum;
	//����
	int ModeSelect;
	//�y�[�W
	int NextPage;
	//�e�L�X�g
	CObjText tLoad;
	//���[�h���
	CObjText tInfo;
	//������@
	CObjText tCtrl;
	//�v���C����
	enum{TMAX = 50};
	TCHAR tmax[TMAX];
	CObjText tTime;
	//����
	CObjFVF Choice;
	//�^�C�g���̃��j���[
	VOID TitleMenu();
	//���[�h���
	VOID Load();
	//�t�B�[���h�����ւ���
	Scene* FLoad(int);
	//�^�C�g��
	CObjText Title;
	//��
	Fish fish;
	D3DXVECTOR3 fAt;
	int mode;
	int frame;
	float AngleNeck;
	float Rot;
	float neck;
	float body;
	AKey<float> rAnim;
	VOID NeckAngle(D3DXVECTOR3*,float);
	VOID FishUpdate();
public:
	EvTitle();
	const TCHAR* name();//�N���X�̖��O	
	VOID Set();
	VOID Update();
	VOID draw();

	VOID DebugText(TCHAR*,int);
	VOID DebugBtn(DebugButton*);
};
};