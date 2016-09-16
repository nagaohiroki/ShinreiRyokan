//=====================================================================================================
//最上位ヘッダー
//=====================================================================================================
#pragma once//ヘッダーの重複防止
//=============================================
//ランタイムライブラリについて
//=============================================
//デバッグ中はプロパティ->構成プロパティ->C/C++->コード生成
//ランタイムライブラリをマルチスレッド デバッグ(/MTd)にする。
//リリース時はマルチスレッド(/MT)にする。
//プロジェクト->プロパティ->構成プロパティ->C/C++->詳細設定->必ず使用されるインクルードファイルにstdafx.hを追加
//↑リリース、デバッグともに
#define MY_DEBUG 
//ライブラリ
#pragma comment(lib, "d3d9.lib")//D3D
#pragma comment(lib, "d3dx9.lib")//D3DX
//#pragma comment(lib, "dinput8.lib")//インプット
//#pragma comment(lib, "dxguid.lib")//インプット
//#include <dinput.h>//インプット
#pragma comment(lib, "winmm.lib")//サウンド
#pragma comment(lib, "X3daudio.lib")//サウンド

#pragma warning(disable: 4238)//D3DX演算の警告を消す
//インクルード
#include <windows.h>//window標準
#include <locale.h> //ロケール
#include <time.h> //時間
#include <tchar.h>//TCHAR
#include <vector>//べクタ
#include <map>//マップ
#include <algorithm>//sort
//D3DX
#include <d3dx9.h>//D3DX
//XAudio2
#include <xaudio2.h>
#include <xaudio2fx.h>
#include <X3daudio.h>

//delete系
template <typename T>
inline void SAFE_DELETE(T*& p)
{
	if(p != NULL) 
	{
		delete (p);
		(p) = NULL;
	}
}

template <typename T>
inline void SAFE_DELETE_ARRAY(T*& p)
{
	if(p != NULL) 
	{
		delete[] (p);
		(p) = NULL;
	}
}

template <typename T>
inline void SAFE_RELEASE(T*& p)
{
	if(p != NULL) 
	{
		(p)->Release();
		(p) = NULL;
	}
}
//ライブラリ
#include "arc.h"
#include "CSaveLoad.h"
#include "file.h"
#include "KeyCode.h"

#ifdef USE_GAMEPAD
#include "JoyStick.h"
#endif
#include "GetKey.h"
#include "DirectInput.h"

#include "CollObj.h"
#include "Collision.h"
#include "CollSegmet.h"
#include "CollParfect.h"

#include "CSurTex.h"
#include "CSurface.h"
#include "MultiRend.h"

#include "CFontTex.h"
#include "CString.h"
#include "Font.h"

#include "LightState.h"
#include "LiSPSM.h"
#include "Effect.h"

#include "CLoadTex.h"
#include "FVFSet.h"
#include "CLoadMesh.h"
//オーディオ
#include "SoundFile.h"
#include "CXAudio2.h"
#include "X3DVoiceState.h"
#include "SVoice.h"
#include "CSound.h"
#include "CLoadSound.h"
//ゲーム固有ライブラリ
#include "SystemData.h"
#include "CItem.h"//ゲームのアイテム
#include "MyLibrary.h"//オリジナルライブラリ
//オブジェクト
#include "CObjFVF.h"
#include "CObjSound.h"
#include "CObjMesh.h"
#include "CObjParticl.h"
#include "CObjText.h"
#include "CObjSurf.h"

//パーソナルデータ
#include "FlagManager.h"//ゲームのメニュー
#include "DebugButton.h"//デバッグボタン
#include "MenuMtrl.h"//ゲームのメニューの素材
#include "Menu.h"//ゲームのメニュー

#include "HitPoint.h"//ヒットポイント
#include "Shot.h"//弾
#include "flashlight.h"//懐中電灯
#include "CModel.h"//自作モデル
#include "Personal.h"//プレイヤーオブジェクト
#include "Scene.h"//シーン基底
//敵
#include "fish.h"
#include "Enemy.h"
#include "ActiveEnemy.h"
//イベント本体
#include "Ev_Title.h"//タイトル画面
#include "GameText.h"
#include "EventObj.h"
#include "Event.h"
#include "message.h"
#include "EventCam.h"
#include "Ev_GameOver.h"
//最初のイベント
#include "Ev_FirstStage.h"//最初のイベント
#include "Ev_Guest_Room.h"//客室イベント
#include "Ev_Guest_Room1.h"
#include "Ev_Guest_Bath.h"//客室バスルームイベント
//F2イベント
#include "Ev_201.h"//201
#include "Ev_202.h"//202
#include "Ev_203.h"//203
#include "Ev_Secret_Door.h"//隠されたドア

#include "Ev_F3.h"//F3
#include "Ev_F31.h"//F3
#include "Ev_F32.h"//F3

#include "Ev_Rest_Men.h"//男子トイレ
#include "Ev_Rest_Women.h"//女子トイレ
#include "Ev_Roof_Top.h"//屋上
#include "Ev_SecretRoom.h"//最後のイベント

//F1イベント
#include "Ev_Sandou.h"//山道
#include "Ev_Soto.h"//外
#include "Ev_Soto1.h"//外
#include "Ev_Soto2.h"//外
#include "Ev_Lobby.h"//ロビー
#include "Ev_Lobby1.h"//ロビー
#include "Ev_Bath_Room_Man.h"//男湯
#include "Ev_Bath_Datui_Woman.h"//女湯脱衣所
#include "Ev_Bath_Room_Woman.h"//女湯
#include "Ev_Dining_Room.h"//食堂
#include "Ev_Staff_Room.h"//従業員室

//フィールド本体
//イベント系
#include "Fld_Title.h"
#include "Fld_Intro.h"
#include "Fld_TestRoom.h"
#include "Fld_GameOver.h"

//フィールド
#include "Fld_Sandou.h"
#include "Fld_Soto.h"
#include "Fld_Lobby.h"
#include "Fld_LobbyRestRoom.h"
#include "Fld_Staff_Room.h"
#include "Fld_Dining_Room.h"
#include "Fld_F3.h"
#include "Fld_Roof_Top.h"
#include "Fld_Guest_Room.h"
#include "Fld_Guest_Bath.h"
#include "Fld_Rest_Men.h"
#include "Fld_Rest_Women.h"
#include "Fld_Roof_Kai.h"
#include "Fld_Bath_Pass.h"
#include "Fld_Bath_Datui_Man.h"
#include "Fld_Bath_Datui_Woman.h"
#include "Fld_Bath_Room_Man.h"
#include "Fld_Bath_Room_Woman.h"
#include "Fld_201.h"
#include "Fld_201_Bath.h"
#include "Fld_202.h"
#include "Fld_203.h"
#include "Fld_Secret_Room.h"

//メイン
#include "Main.h"
#include "WindowsAPI.h"
using namespace Ev;
using namespace Fld;