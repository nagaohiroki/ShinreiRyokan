#pragma once

//============================================
//�J�����̃X�e�[�^�X
//============================================
class Cam
{
private:

public:
	float Near;
	float Far;
	D3DXVECTOR3 Eye;//�J�����̈ʒu
	D3DXVECTOR3 At;//�����_
	D3DXVECTOR3 Up;	//����x�N�g��
	D3DXVECTOR2 wh;	//�A�X��
	float Pars;//�p�[�X
	Cam();
	VOID Init();
	VOID Cast(const Cam*);
	VOID CamSet(D3DXVECTOR3*,D3DXVECTOR3*);
};
//============================================
//�|�C���g�X�|�b�g���C�g�X�e�[�^�X
//============================================
class PointSpotLight
{
private:	
public:
	float dis;//������
	float Lcos;//���C�g�̎ˉe�p
	D3DXVECTOR3 Pos;//�|�W�V����
	D3DXVECTOR3 Vec;//���C�g�̃x�N�g��	
	D3DXVECTOR4 Col;//���C�g�̐Fw�̓A�r�G���g
	PointSpotLight()
	{
		dis=0.0f;
		Lcos=0.0f;
		Pos=D3DXVECTOR3(0,0.5f,0);//�|�W�V����
		Vec=D3DXVECTOR3(0,0.5f,1.0f);//�x�N�g��
		Col=D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);//���C�g�̐Fw�͑S�̂̋���
	}
	VOID Init()
	{
		dis=0.0f;
		Lcos=0.0f;
		Pos=D3DXVECTOR3(0,0.5f,0);//�|�W�V����
		Vec=D3DXVECTOR3(0,0.5f,1.0f);//�x�N�g��
		Col=D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);//���C�g�̐Fw�͑S�̂̋���

	}
	
};

//============================================
//���C�g�X�e�[�^�X
//============================================
class LightState
{
public:
	D3DXVECTOR3 EyePlus;//�J�����̏�悹��
	D3DXVECTOR3 Pos;//���C�g�̌���
	D3DXVECTOR3 At;//���C�g�̑Ώۂ̈ʒu
	D3DXVECTOR4 Col;//w�͑S�I�u�W�F�N�g�̃A�r�G���g
	float Near;//���C�g�̋߉e
	float Far;//���C�g�̉��e
	float Pars;//���C�g�̎ˉe
	float Shadow;//�e�̔Z��
	float Bias;//�o�C�A�X
	LightState()
	{
		Near=60.0f;
		Far=65.0f;
		Col=D3DXVECTOR4(1.0f,1.0f,1.0f,1.0);
		Pos=D3DXVECTOR3(0.0f,63.0f,3.0f);
		At=D3DXVECTOR3(0.0f,0.0f,0.0f);
		Pars=45.0f;//���C�g�̎��p
		Shadow=1.0f;
		Bias=1.0f;
		EyePlus=D3DXVECTOR3(0.0f,0.0f,0.0f);
	}
	VOID Init()
	{
		Near=60.0f;
		Far=65.0f;
		Col=D3DXVECTOR4(1.0f,1.0f,1.0f,1.0);
		Pos=D3DXVECTOR3(0.0f,63.0f,3.0f);
		At=D3DXVECTOR3(0.0f,0.0f,0.0f);
		Pars=45.0f;//���C�g�̎��p
		Shadow=1.0f;
		Bias=1.0f;
		EyePlus=D3DXVECTOR3(0.0f,0.0f,0.0f);

	}
	VOID Cast(const LightState *Ls)
	{
		Near   = Ls->Near;
		Far    = Ls->Far;
		Col    = Ls->Col;
		Pos    = Ls->Pos;
		At     = Ls->At;
		Pars   = Ls->Pars;
		Shadow = Ls->Shadow;
		Bias   = Ls->Bias;
		EyePlus= Ls->EyePlus;

	}

};

//============================================
//�t�H�O
//============================================
class FogState
{
public:
	D3DXVECTOR3 Col;//�J���[
	float Near;//�ŉ�����
	float Far;//�ŋߋ���
	BOOL use;//�I���I�t
	FogState()
	{
		use = TRUE;
		Near= 0.0f;
		Far = 50.0f;
		Col = D3DXVECTOR3(0.84f,0.89f,0.99f);
	}
	VOID Init()
	{
		use = TRUE;
		Near= 0.0f;
		Far = 50.0f;
		Col = D3DXVECTOR3(0.84f,0.89f,0.99f);

	}
	//��r
	BOOL EqualEqual(const FogState* Fs)
	{
		if(Col.x != Fs->Col.x){return FALSE;}
		if(Col.y != Fs->Col.y){return FALSE;}
		if(Col.z != Fs->Col.z){return FALSE;}
		if(Near  != Fs->Near ){return FALSE;}
		if(Far   != Fs->Far  ){return FALSE;}
		if(use   != Fs->use  ){return FALSE;}
		return TRUE;
	}
	//���
	VOID Cast(const FogState* Fs)
	{
		Col.x = Fs->Col.x;
		Col.y = Fs->Col.y;
		Col.z = Fs->Col.z;		
		Near  = Fs->Near;
		Far   = Fs->Far;
		use   = Fs->use;
	}


};
