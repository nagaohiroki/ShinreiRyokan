
//�ϐ�������
Key_Set::Key_Set()
{
	B=0;
	Time=0;
	t=FALSE;
	Key=NULL;
}	
//�L�[�̎擾
VOID Key_Set::Get_Key(int b,int* k)
{
	B=b;
	Key=k;
}	
//���ʂ̃I���I�t
BOOL Key_Set::K()
{
	if(*Key & B){return TRUE;}
	return FALSE;
}
//�g���K
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
//�����Ă鎞��
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