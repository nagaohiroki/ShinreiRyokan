
//サウンド
//コンストラクタ
CObjSound::CObjSound()
{
	SoundIndex = 0;
	wavType = 0;
	ML = NULL;

}
//デストラクタ
CObjSound::~CObjSound()
{
	if(ML != NULL)
	{
		ML->Audio.Release(wavType,SoundIndex);
	}
}
//サウンドを取得していなかったら取得
VOID CObjSound::GetSound(MyLibrary* ml)
{	
	if(ML == NULL)
	{
		ML = ml;
		ML->Audio.Load(wavType,&ML->af,ML->fp,&SoundIndex,this);
	}
}
//wavを指定
VOID CObjSound::Set(arc wav)
{
	if(ML == NULL)
	{
		wavType = wav;
	}
}
//再生開始
VOID CObjSound::Start(MyLibrary* ml)
{
	GetSound(ml);
	ML->Audio.Sv(wavType,SoundIndex)->Start();
}
//再生を停止してシークの位置を指定
VOID CObjSound::Stop(MyLibrary* ml,float Pos)
{
	GetSound(ml);
	ML->Audio.Sv(wavType,SoundIndex)->Stop(Pos);
}
//一時停止
VOID CObjSound::Pause(MyLibrary* ml)
{
	GetSound(ml);
	ML->Audio.Sv(wavType,SoundIndex)->Pause();
}
//デバッグ
VOID CObjSound::Debug(MyLibrary *ml,TCHAR* t,int l )
{
	GetSound(ml);

	ML->Audio.Sv(wavType,SoundIndex)->Debug(t,l);

}
//コーンを使用
VOID CObjSound::ConeSet(BOOL b)
{
	if(b){	Emi.pCone = &Cone;	}
	else{	Emi.pCone = NULL;	}
}

//ソースボイスを返す
SVoice* CObjSound::Sv(MyLibrary* ml)
{
	GetSound(ml);
	return ML->Audio.Sv(wavType,SoundIndex);
}
