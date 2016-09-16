//--------------------------------
//�{�^���ЂƂ�
//--------------------------------
MyButton::MyButton()
{
	Mode = 0;
	TextX = 0;
	TextY = 0;
	Size = 100.0f;
	Pos = D3DXVECTOR2(0.0f,0.0f);
	Pos2= D3DXVECTOR2(0.0f,0.0f);
	_stprintf_s(txt,TMAX,_T(""));
	slide = 0.0f;
	PreMPos = D3DXVECTOR2(0.0f,0.0f);
}	
//2D�����蔻��
BOOL MyButton::Hit2D(CObjFVF *fvf,float X,float Y)
{		
	if( X < fvf->objPos.x + fvf->objScal.x / 2.0f )
	if( X > fvf->objPos.x - fvf->objScal.x / 2.0f )
	if( Y < fvf->objPos.y + fvf->objScal.y / 2.0f )
	if( Y > fvf->objPos.y - fvf->objScal.y / 2.0f )
	{
		return TRUE;
	}
	return FALSE;	
}
//�ʒu���w��
VOID MyButton::SetPos(float x,float y)
{
	Pos.x = x;
	Pos.y = y;
}	
//�`��
VOID MyButton::draw(MyLibrary* ml)
{		
	Move.draw(ml);
	mater.draw(ml);	
	toggle.draw(ml);
	ml->Tx.draw(txt,TextX,TextY);
}
//--------------------------------
//�{�^���܂Ƃ�
//--------------------------------
//�R���X�g���N�^
DebugButton::DebugButton()
{
	ml = NULL;
	Position = D3DXVECTOR2(-500.0f,350.0f);
	Num = 0;
}
//���C�u�����ƈʒu�̃Z�b�g
VOID DebugButton::Set(MyLibrary* ML,float x,float y)
{
	Position.x = x;
	Position.y = y;
	ml = ML;
}
//�`��
VOID DebugButton::draw()
{		
	if(ml == NULL){return;}
	if(Num == 0){return;}
 	size_t i;
	//�`��
	for( i = 0; i < Num; i++ )
	{
		Button[i].draw(ml);
	}	
	//�g��Ȃ��I�u�W�F�N�g���폜
	size_t Size = Button.size();
	for(i = Num; i < Size; i++)
	{
		Button.pop_back();
	}

	//Ctrl + S�Œl��ۑ�
	if(ml->C.Ctrl.K())
	{
		if(ml->C.S.T())
		{
			CFile().txt(_T("Memo.txt"),_T("test\n"));
			for( i = 0; i < Num; i++ )
			{
				TCHAR tmp[100] = _T("");
				_stprintf_s(tmp,100,_T("%s\n"),Button[i].txt);
				CFile().atxt(_T("Memo.txt"),tmp);
			}
		}
	}
	Num = 0;

}