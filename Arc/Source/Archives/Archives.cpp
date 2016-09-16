#include "main.h" 
Archive::Archive()
{
}
//------------------------------------------------
//�t�@�C���d���̊m�F
//------------------------------------------------
BOOL Archive::NonRepet( TCHAR* Name )
{
	unsigned int i;
	for(i = 0; i < datas.size(); i++)
	{
		//�������O�����݂���ꍇFALSE
		if(_tcscmp(Name,datas[i].name) == 0)
		{
			return FALSE;
		}
	}
	return TRUE;
}
//-------------------------------------------------
//�g���q�ƃt�@�C�������t�ɂ���.��_�ɕϊ�
//-------------------------------------------------
VOID Archive::Dot_to_Under(TCHAR* Name)
{
	TCHAR FlName[MAX_PATH];
	TCHAR ExName[MAX_PATH];
	unsigned int len = _tcslen(Name);
	unsigned int i;
	for(i = len; i > 1; i--)
	{
		if(Name[i] == '.')
		{
			_stprintf_s(ExName,MAX_PATH,_T("%s"),Name + i);
			Name[i] = '\0';
			_stprintf_s(FlName,MAX_PATH,_T("%s"),Name);
			_stprintf_s(Name,MAX_PATH,_T("%s_%s"),ExName + 1,FlName);
			return;
		}
	}
}
//------------------------------------------------
//�t�@�C���̗�
//------------------------------------------------
VOID Archive::EnumFiles(TCHAR* Fold)
{
	//�w�肵���t�H���_�̌���\*.*������
	TCHAR FoldName[MAX_PATH] = _T("");
	_stprintf_s(FoldName,MAX_PATH,_T("%s\\*.*"),Fold);
	//�t�@�C�����
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(FoldName,&fd);		
	//�t�H���_����
	if(hFind != INVALID_HANDLE_VALUE)
	{
		//�t�@�C���̌���
		while(FindNextFile(hFind,&fd))
		{
			if(_tcscmp(_T("."),fd.cFileName) != 0 && _tcscmp(_T(".."),fd.cFileName) != 0)
			{
				//�t�H���_�̏ꍇ
				if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					//�t�H���_��������
					TCHAR NextFold[MAX_PATH] = _T("");
					_stprintf_s(NextFold,MAX_PATH,_T("%s\\%s"),Fold,fd.cFileName);
					//�t�H���_���̃t�H���_����
					EnumFiles(NextFold);
				}
				else
				{	
					//�����̃t�@�C�����o�^����ĂȂ��ꍇ
					if(NonRepet( fd.cFileName ) ==TRUE)
					{					
						//�V�X�e���t�@�C���͏��O
						if(_tcscmp(fd.cFileName,_T("Thumbs.db")) != 0)
						{
							Sleep(2);
							//�A�[�J�C�u�t�@�C���ɏ�������
							Data dat;//�R�s�[�p
							_stprintf_s(dat.path,MAX_PATH,_T("%s\\%s"),Fold,fd.cFileName);//�p�X
							_stprintf_s(dat.name,MAX_PATH,_T("%s"),fd.cFileName);//���O
							dat.size  = fd.nFileSizeLow;//�T�C�Y
							datas.push_back(dat);//�ǉ�
						}
					}
				}
			}
		}
	}
	else
	{
		TCHAR DTxt[MAX_PATH] = _T("");
		_stprintf_s(DTxt,MAX_PATH,_T("\n\n%s\n���J���܂���\n\n"),Fold);
		CDebug().Debug(DTxt);
	}
	//�t�@�C�������
	FindClose(hFind);
}
//------------------------------------------------
//�g���q�̗�
//------------------------------------------------
VOID Archive::EnumExt()
{
	Ext l_Ext;
	unsigned int i;
	unsigned int j;
	unsigned int k;
	unsigned int len = 0;
	BOOL check = FALSE;
	for( i = 0; i < datas.size(); i++ )
	{		
		len = _tcsclen(datas[i].name);
		for( j = len; j > 1; j-- )
		{
			if( datas[i].name[j] == '.' )
			{
				_stprintf_s(l_Ext.name,MAX_PATH,_T("%s"),datas[i].name + j);
				check = TRUE;
				for( k = 0; k < ext.size(); k++ )
				{
					//�g���q�����X�g�ɑ��݂���ꍇ
					if( _tcscmp( ext[k].name,l_Ext.name ) == NULL )
					{
						ext[k].num++;
						check = FALSE;
						break;
					}
				}
				//�g���q���X�g�ɂȂ��ꍇ�o�^
				if( check == TRUE )
				{
					ext.push_back(l_Ext);
					ext[ext.size() - 1].num++;
				}
				//�Ō�̃h�b�g�Ȃ̂Ń��[�v�I��
				break;						
			}
		}
	}
}

//------------------------------------------------
//�g���q���ƂɃ\�[�g
//------------------------------------------------
VOID Archive::ExtSort()
{
	std::vector<Data> datas1;

	unsigned int j;
	unsigned int i;
	for(i = 0; i < ext.size(); i++)
	{
		for(j = 0; j < datas.size(); j++)
		{
			//�w�肵���g���q������ꍇ
			if(_tcsstr(datas[j].name,ext[i].name) != 0)
			{
				Data dt;
				dt.size = datas[j].size;
				_stprintf_s(dt.name,_T("%s"),datas[j].name);
				_stprintf_s(dt.path,_T("%s"),datas[j].path);
				datas1.push_back(dt);
		
			}
		}
	}
	//�f�[�^�����ւ���
	datas.swap(datas1);
}
//--------------------------------------------------
//�w�b�_�[�t�@�C���̍쐬
//--------------------------------------------------
VOID Archive::Header(TCHAR* name)
{
	FILE* fp;
	TCHAR FileName[MAX_PATH] = _T("");
	unsigned int i;
		
	if(_tfopen_s( &fp,name, _T("w") ) == 0)
	{
		//�w�b�_�[����������
		_ftprintf_s(fp,	_T("#pragma once\n"));
		
		//Enum�̍쐬
		_ftprintf_s(fp,	_T("enum arc\n{\n"));	
		for(i = 0; i < datas.size(); i++)
		{
			_stprintf_s( FileName,MAX_PATH,_T("%s"),datas[i].name );
			Dot_to_Under( FileName );
			_ftprintf_s(fp,_T("\t%s,\n"),FileName);
		}
		_ftprintf_s(fp,	_T("\tMAX_arc,\n};\n"));
		//�N���X�ʃf�[�^
		_ftprintf_s(fp,	_T("//�A�[�J�C�u�ʃf�[�^-------------------\n"));
		_ftprintf_s(fp,_T("class arcFile\n")
			_T("{\n")
			_T("public:\n")
			_T("\tunsigned long size;\n")
			_T("\tunsigned long point;\n")
			_T("\tTCHAR name[MAX_PATH];\n")
			_T("\tarcFile()\n")
			_T("\t{\n")
			_T("\t\tsize = 0;\n")
			_T("\t\tpoint = 0;\n")
			_T("\t\t_stprintf_s(name,MAX_PATH,_T(\"\"));\n")
			_T("\t}\n")
			_T("\tVOID Set(TCHAR* Name,unsigned long Size,unsigned long Point)\n")
			_T("\t{\n")
			_T("\t\tsize = Size;\n")
			_T("\t\tpoint = Point;\n")
			_T("\t\t_stprintf_s(name,MAX_PATH,_T(\"%%s\"),Name);\n")
			_T("\t}\n")
			_T("};\n"));	
		//class�{��
		_ftprintf_s(fp,
			_T("//class�f�[�^------------------------------\n")
			_T("class Arc_Files\n")
			_T("{\n")
			_T("public:\n")
			_T("\tarcFile af[MAX_arc];\n")
			_T("\tArc_Files()\n")
			_T("\t{\n"));
		for(i = 0; i < datas.size(); i++)
		{
			_stprintf_s( FileName,MAX_PATH,_T("%s"),datas[i].name );
			Dot_to_Under( FileName );
			_ftprintf_s( fp,_T("\t\taf[%s].Set(_T(\"%s\"),%d,%d);\n"),
				FileName,
				datas[i].name,
				datas[i].size,
				datas[i].point
				);
		}
		_ftprintf_s(fp,
			_T("\t}\n")
			_T("};\n")
			
			);
		//�t�@�C���N���[�Y
		fclose(fp);
	}
	else{CDebug().Debug(_T("�t�@�C���I�[�v�����s\n"));}
}

//--------------------------------------------------
//dat�t�@�C�����쐬
//--------------------------------------------------
VOID Archive::CreateDat(TCHAR* name)
{
	FILE *FpArc;
	FILE *FpData;	
	unsigned int i;
	unsigned int j;
	unsigned int copy_byte = 0;
	unsigned long file_point	= 0;
	//�A�[�J�C�u�t�@�C�����쐬
	if(_tfopen_s( &FpArc,name, _T("w+b") ) == 0)
	{
		//�����Ɋe�t�@�C���̓ǂݍ��݂�����
		for(i = 0; i < datas.size(); i++)
		{
			if(_tfopen_s(&FpData,datas[i].path,_T("r+b")) == 0)
			{
				// �t�@�C���T�C�Y�������J��Ԃ�
				for(j = 0; j < datas[i].size; j++)
				{
					if(fread( &copy_byte, 1, 1,FpData) != 1 ){CDebug().Debug(_T("�t�@�C�����[�h���s\n"));}
					if(fwrite( &copy_byte, 1, 1,FpArc) != 1 ){CDebug().Debug(_T("�t�@�C���������ݎ��s\n"));}
				}
				//�ʒu��ݒ�
				datas[i].point = file_point;//�ʒu
				file_point += datas[i].size;//�t�@�C���ʒu��i�߂�

				_tprintf_s(_T("%s:%d:%d\n"),datas[i].name,datas[i].point,datas[i].size);
			}
			else
			{
				TCHAR Debug[MAX_PATH];
				_stprintf_s(Debug,_T("Fail:Create%s"),datas[i].name);
				CDebug().Debug(Debug);
			}
			fclose(FpData);
		}		
		//�t�@�C�������
		fclose(FpArc);	
	}
	else
	{
		CDebug().Debug(_T("\n�t�@�C���I�[�v�����s\n"));
	}
}
//--------------------------------------------------
//���s
//--------------------------------------------------
VOID Archive::Save()
{
	TCHAR Cur[MAX_PATH];
	TCHAR input[MAX_PATH];
	TCHAR out[MAX_PATH];	
	TCHAR save_name[MAX_PATH];
	TCHAR header_name[MAX_PATH];	
	GetCurrentDirectory(MAX_PATH,Cur);//�J�����g�t�H���_
	_stprintf_s(input,MAX_PATH,_T("%s\\input"),Cur);	//input�t�H���_
	_stprintf_s(out,MAX_PATH,_T("%s\\out"),Cur);//out�t�H���_
	_stprintf_s(save_name,MAX_PATH,_T("%s\\data.dat"),out);//dat�t�@�C��
	_stprintf_s(header_name,MAX_PATH,_T("%s\\arc.h"),out);//�w�b�_�[�t�@�C��
	//�t�@�C���ǂݍ���
	EnumFiles(input);
	//�g���q��
	EnumExt();
	//�g���q���ƂɃ\�[�g
	ExtSort();
	//dat�t�@�C�����쐬
	CreateDat(save_name);
	//�w�b�_�[�t�@�C���̍쐬
	Header(header_name);
	//�f�[�^��\��
	UINT i;
	for(i = 0; i < ext.size(); i++)
	{
		_tprintf_s(_T("%s:%d\n"),ext[i].name,ext[i].num);		 
	}
	
}

