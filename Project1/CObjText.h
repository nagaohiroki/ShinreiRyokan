#pragma once

//����
class CObjText
{
private:
	int MaxLen;//�����̍ő吔
	const D3DXMATRIX* Pare;//�e�I�u�W�F�N�g	
	VOID Sdraw(MyLibrary*);//������
	VOID Ldraw(MyLibrary*);//�c����	
	VOID UpdateMat();

public:
	D3DXVECTOR2 vol;
	TCHAR *txt;
	D3DXVECTOR3	objPos;// �r���{�[�h�̍��W
	D3DXVECTOR3 objScal;//�X�P�[���̔{��
	D3DXVECTOR3 YPR;//���[�s�b�`���[��
	D3DXVECTOR4 MeshCol;
	D3DXMATRIX  mWorld;//�s�񌋉�
	BOOL drawSkip;//�h���[���X�L�b�v����
	BOOL Length;//�c�����ɂ��邩
	int StrLen;//�����̕`�搔
	D3DXVECTOR2 intrval;//�s��
	CObjText(); 
	VOID SetPare(const D3DXMATRIX* );
	VOID SetText(TCHAR*);
	VOID draw(MyLibrary*);
	int Max();

	//���̕�����
	int wN(MyLibrary*);
	//�i����
	int hN(MyLibrary*);

};
