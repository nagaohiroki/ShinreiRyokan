
//�T�E���h
//�R���X�g���N�^
CObjSound::CObjSound()
{
	SoundIndex = 0;
	wavType = 0;
	ML = NULL;

}
//�f�X�g���N�^
CObjSound::~CObjSound()
{
	if(ML != NULL)
	{
		ML->Audio.Release(wavType,SoundIndex);
	}
}
//�T�E���h���擾���Ă��Ȃ�������擾
VOID CObjSound::GetSound(MyLibrary* ml)
{	
	if(ML == NULL)
	{
		ML = ml;
		ML->Audio.Load(wavType,&ML->af,ML->fp,&SoundIndex,this);
	}
}
//wav���w��
VOID CObjSound::Set(arc wav)
{
	if(ML == NULL)
	{
		wavType = wav;
	}
}
//�Đ��J�n
VOID CObjSound::Start(MyLibrary* ml)
{
	GetSound(ml);
	ML->Audio.Sv(wavType,SoundIndex)->Start();
}
//�Đ����~���ăV�[�N�̈ʒu���w��
VOID CObjSound::Stop(MyLibrary* ml,float Pos)
{
	GetSound(ml);
	ML->Audio.Sv(wavType,SoundIndex)->Stop(Pos);
}
//�ꎞ��~
VOID CObjSound::Pause(MyLibrary* ml)
{
	GetSound(ml);
	ML->Audio.Sv(wavType,SoundIndex)->Pause();
}
//�f�o�b�O
VOID CObjSound::Debug(MyLibrary *ml,TCHAR* t,int l )
{
	GetSound(ml);

	ML->Audio.Sv(wavType,SoundIndex)->Debug(t,l);

}
//�R�[�����g�p
VOID CObjSound::ConeSet(BOOL b)
{
	if(b){	Emi.pCone = &Cone;	}
	else{	Emi.pCone = NULL;	}
}

//�\�[�X�{�C�X��Ԃ�
SVoice* CObjSound::Sv(MyLibrary* ml)
{
	GetSound(ml);
	return ML->Audio.Sv(wavType,SoundIndex);
}
