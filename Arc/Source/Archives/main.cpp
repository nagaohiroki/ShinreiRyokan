#include "main.h"
void main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//���������[�N�̌��o	
	_tsetlocale(0,_T(""));//�S�Ă̌���ɑΉ�

	Archive().Save();
	_tprintf_s(_T("Enter�L�[�ŏI��\n"));

	getchar();
}