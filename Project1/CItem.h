#pragma once
//================================
//アイテム
//================================
class CItem
{
private:
	enum ITEM_DATA
	{
		MAX_NAME = 20,
		MAX_INFO = 100
	};
public:
	TCHAR name[MAX_NAME];//名前
	TCHAR info[MAX_INFO];//情報	
	CItem();
	VOID Set(TCHAR*,TCHAR*);	
};
//================================
//アイテム総合
//================================
enum ITEM
{
	ITEM_DARTS,
	ITEM_LIGHT,
	ITEM_MASUI,
	ITEM_MASUI_DARTS,
	ITEM_GUEST_KEY,
	ITEM_202_KEY,
	ITEM_ROOF_KEY,
	ITEM_SYOUKAKI,
	ITEM_DINING_KEY,
	ITEM_STAFF_KEY,
	ITEM_DESK_KEY,
	ITEM_203_KEY,
	ITEM_GENKAN_KEY,
	ITEM_TENYEN,


	ITEM_MAX,
};
class CItemList
{
public:
	CItem item[ITEM_MAX];
	CItemList();
};
