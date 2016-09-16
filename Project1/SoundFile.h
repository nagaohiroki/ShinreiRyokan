#pragma once//�w�b�_�[�̏d���h�~
//=======================================================
//wave�t�@�C��
//=======================================================
class LoadWave
{
private:
	enum{NOISE = 100};
	//�����������݂Ƃ�
	char* m_ptr;
	//wave�t�@�C��
	HMMIO m_hMmio;
	//���f�B�A����X�e�[�^�X���擾
	HRESULT Create(WAVEFORMATEX&);
public:
	//�t�@�C���S�̂̃T�C�Y
	DWORD m_dwSize;
	//wav�t�H�[�}�b�g
	WAVEFORMATEX m_wfx;
	LoadWave();
	virtual ~LoadWave();
	//�t�@�C�����J��
	HRESULT Open(TCHAR*);
	HRESULT Open(char*,UINT);
	//�o�b�t�@��ǂݍ���(�o�b�t�@,�ǂݍ��ރT�C�Y)
	LONG Read(BYTE*,LONG);
	//�V�[�N(�o�C�g�P��)���s�Ȃ�-1��Ԃ�
	LONG SeekByte(LONG);
	//���v�T���v��
	DWORD AllSamp();
	//���v�Đ�����
	float AllTime();
};
