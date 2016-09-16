#pragma once

//�p�X
namespace fx
{
	enum Pass
	{
		Mesh,
		Mesh_Tex,
		Mesh_AlphaTex,
		Mesh_Bump,
		ShadowMap,
		ShadowAlphaMap,
		FVF,
		FVF_Tex,
		FVF_Tex_Point,
		FVF_Tex_One,
		Tone,
		GaussX,
		GaussY,
	};
};


//�O���[�o���ϐ�
namespace prm
{
	enum
	{
		float4x4_mW ,
		float4x4_mVP ,
		float4x4_mLight ,
		float4_vLightDir ,
		float4_vColor ,
		float3_vEyePos ,
		float4_SP ,
		float4_SBias ,
		float4_vFog ,
		float4_vFogColor ,
		int_vFogUse ,
		float4_PixelUV ,
		float4_BloomColor ,
		float3_CamPos ,
		float4_PLightDif ,
		float4_PLightPos ,
		float4_PLightVec ,
		texture_Tex,
		texture_ShadowTex,
		texture_NormalTex,
		float_w,
		float4_GaussMap ,
		PRM_MAX,
	};
};
//============================================
//HLSL
//============================================
class CEffect
{
private:
	D3DXHANDLE m_hTechnique;
	D3DXHANDLE *Handle;
	D3DXMATRIX matLight;	
	D3DXMATRIX matView;
	D3DXMATRIX matProj;	
	D3DXMATRIX mL;
	BOOL BeginFlag;//�r�M�����Ă΂�Ă��邩�̃t���O
	BOOL PassFlag;//�p�X�����Ă��邩�̃t���O
	int  fxPass;//���݂̃p�X	

	//�J�����p�J�����O
	D3DXVECTOR3 CullPos;

	//���C�g�X�y�[�X�p�[�X�؃N�e�B�u�V���h�E�}�b�v
	LiSPSM Lisp;
	//�G�t�F�N�g
	LPD3DXEFFECT	m_pEffect;
		//�n���h���̃Z�b�g
	HRESULT SetHandle();
	//�n���h����Ԃ�
	D3DXHANDLE Hn(size_t);
	//�I�u�W�F�N�g�X�V
	VOID UpdateLight();
	VOID UpdateFog();	
	VOID UpdatePointLight();
	
public:		
	VOID UpdateCam();		
	BOOL MirrorFlag;
	int MirrorPass;
	Cam Mirrorcam;
	
	D3DXMATRIX matPxV;
	
	//�g�[���}�b�v
	D3DXVECTOR4 Tone;
	//�G�t�F�N�g���
	unsigned int pass;//pass�̐�
	float Fade;
	//�|�C���g���C�g�֘A
	PointSpotLight PSL;
	LightState Ls;
	FogState Fs;
	Cam cam;
	//�V���h�E�}�b�v�p�X1���e0���ʏ�h���[
	int ShadowPassNum;
	BOOL ShadowFlag;	
	CEffect();
	virtual ~CEffect();
	VOID begin();
	HRESULT Create(LPDIRECT3DDEVICE9);//�t�@�C������G�t�F�N�g���쐬 
	HRESULT Create(LPDIRECT3DDEVICE9,char*,UINT);//����������G�t�F�N�g���쐬
	HRESULT Reset();//���Z�b�g�O�ɍs��
	HRESULT Restore();//���Z�b�g��ɍs��
	VOID SetPLCol(D3DXVECTOR4*);//�|�C���g���C�g
	D3DXVECTOR3 LightCol(); 
	VOID LightLamSpc(D3DXMATRIX*,float);//���ʔ��˂ƃ����o�[�g����
	VOID ShadowBias(float,float);
	//�V���h�E�}�b�v
	VOID BeginSh();
	VOID ShadowMapSet(LPDIRECT3DTEXTURE9);
	
	//�e�G�t�F�N�g
	VOID mWVP(D3DXMATRIX*);//���[�J��
	VOID vCol(D3DXVECTOR4*);//���_�J���[
	VOID SpCol(D3DXVECTOR4*);//�X�y�L�����J���[
	VOID Tex(LPDIRECT3DTEXTURE9);//�e�N�X�`��
	//�o���v�}�b�v
	VOID MTex(LPDIRECT3DTEXTURE9);//�o���v�}�b�v�e�N�X�`��
	
	//�G�t�F�N�g�̓���
	VOID BeginPass(int);
	VOID CommitChange();

	//�J�����O
	BOOL Culling(D3DXVECTOR3*,float);

	//�g�[��
	VOID ToneMap();

	//���b�V���̃u���[���̐F
	VOID BloomColor(D3DXVECTOR4*);

	//�K�E�X�t�B���^
	VOID SetGaussMap(float,float);
	VOID SetGaussWeight(float);

	//�X�N���[���s��
	VOID ScreenView(LPDIRECT3DDEVICE9,UINT,UINT);
	//�I�u�W�F�N�g�̍X�V
	VOID UpdateEffect(float,float);
	//�I�u�W�F�N�g�̏�����
	VOID InitEffect();
	VOID UpdateEffect();

};

