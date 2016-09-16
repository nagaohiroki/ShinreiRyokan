#include "main.h"
void main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//メモリリークの検出	
	_tsetlocale(0,_T(""));//全ての言語に対応

	Archive().Save();
	_tprintf_s(_T("Enterキーで終了\n"));

	getchar();
}