enum ENUM_KEY
{
	KEY_NONE		= 0x0,
	KEY_LEFT		= 0x1,
	KEY_RIGHT		= 0x2,
	KEY_UP			= 0x4,
	KEY_DOWN		= 0x8,
	KEY_A		    = 0x10,
	KEY_D			= 0x20,
	KEY_W			= 0x40,
	KEY_S			= 0x80,
	KEY_V           = 0x100,
	KEY_E			= 0x200,
	KEY_F			= 0x400,
	KEY_B			= 0x800,
	KEY_SPACE		= 0x1000,
	KEY_Q			= 0x2000,
	KEY_C			= 0x4000,
	KEY_R			= 0x8000,
	KEY_X			= 0x10000,
	KEY_1			= 0x20000,
	KEY_Z			= 0x40000,
	KEY_Ctrl		= 0x80000,
	KEY_Enter       = 0x100000,
	KEY_Back		= 0x200000,
		/*
	KEY_MOUSE_X  	= 0x400000,
	KEY_MOUSE_Z	    = 0x800000,

	KEY_MOUSE_UP	= 0x2000000,
	KEY_MOUSE_DOWN	= 0x4000000,
	
	A5				= 0x8000000,
	A6				= 0x10000000,
	A7				= 0x20000000,
	A8				= 0x40000000,
	A9				= 0x80000000,
	*/
	KEY_ERR			= 0x0f
};
class Key_Set
{
private:
	//トリガ
	BOOL t;
	//ボタンの種類
	int B;
	//インプットキー
	int *Key;
	//押してる時間		
	int Time;	
public:	
	//変数初期化
	Key_Set();	
	//キーの取得
	VOID Get_Key(int b,int* k);
	//普通のオンオフ
	BOOL K();
	//トリガ
	BOOL T();
	//押してる時間
	int time();
};