#pragma once

//FVF
class CObjFVF
{
private:

	int TexType;//�e�N�X�`���̎��
	int Pass;//�`��p�X
	const D3DXMATRIX* Pare;//�e�I�u�W�F�N�g
	MyLibrary* ML;
	VOID UpdateMat();
	std::map<int,CTexture*>::iterator it;
public:
	D3DXVECTOR3	objPos;// �r���{�[�h�̍��W
	D3DXVECTOR3 objScal;//�X�P�[���̔{��
	D3DXVECTOR3 YPR;//���[�s�b�`���[��
	D3DXVECTOR4 MeshCol;//�F	
	D3DXMATRIX  mWorld;//�s�񌋉�
	BOOL drawSkip;//�h���[���X�L�b�v����
	CObjFVF();
	virtual ~CObjFVF();
	//�e�N�X�`���̃Z�b�g
	VOID SetTex(arc);
	VOID SetTex(arc,fx::Pass);
	VOID SetPare(const D3DXMATRIX* );
	//�`��	
	VOID draw(MyLibrary*);
	//�C���X�^���g�`��
	VOID draw(MyLibrary*,LPDIRECT3DTEXTURE9,int);	

	//�~���[�`��
	VOID drawMirror(MyLibrary*);	
}; 
