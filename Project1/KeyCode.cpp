
//変数初期化
Key_Set::Key_Set()
{
	B=0;
	Time=0;
	t=FALSE;
	Key=NULL;
}	
//キーの取得
VOID Key_Set::Get_Key(int b,int* k)
{
	B=b;
	Key=k;
}	
//普通のオンオフ
BOOL Key_Set::K()
{
	if(*Key & B){return TRUE;}
	return FALSE;
}
//トリガ
BOOL Key_Set::T()
{
	if(!t)
	if(*Key & B)
	{
		t=TRUE;
		return TRUE;
	}
	if((*Key & B) == NULL)
	{
		t=FALSE;	
	}
	return FALSE;
}	
//押してる時間
int Key_Set::time()
{
	if(*Key & B)
	{
		Time++;
		return Time;
	}
	Time=0;
	return 0;
}