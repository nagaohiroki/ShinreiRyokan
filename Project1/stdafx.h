//=====================================================================================================
//�ŏ�ʃw�b�_�[
//=====================================================================================================
#pragma once//�w�b�_�[�̏d���h�~
//=============================================
//�����^�C�����C�u�����ɂ���
//=============================================
//�f�o�b�O���̓v���p�e�B->�\���v���p�e�B->C/C++->�R�[�h����
//�����^�C�����C�u�������}���`�X���b�h �f�o�b�O(/MTd)�ɂ���B
//�����[�X���̓}���`�X���b�h(/MT)�ɂ���B
//�v���W�F�N�g->�v���p�e�B->�\���v���p�e�B->C/C++->�ڍאݒ�->�K���g�p�����C���N���[�h�t�@�C����stdafx.h��ǉ�
//�������[�X�A�f�o�b�O�Ƃ���
#define MY_DEBUG 
//���C�u����
#pragma comment(lib, "d3d9.lib")//D3D
#pragma comment(lib, "d3dx9.lib")//D3DX
//#pragma comment(lib, "dinput8.lib")//�C���v�b�g
//#pragma comment(lib, "dxguid.lib")//�C���v�b�g
//#include <dinput.h>//�C���v�b�g
#pragma comment(lib, "winmm.lib")//�T�E���h
#pragma comment(lib, "X3daudio.lib")//�T�E���h

#pragma warning(disable: 4238)//D3DX���Z�̌x��������
//�C���N���[�h
#include <windows.h>//window�W��
#include <locale.h> //���P�[��
#include <time.h> //����
#include <tchar.h>//TCHAR
#include <vector>//�׃N�^
#include <map>//�}�b�v
#include <algorithm>//sort
//D3DX
#include <d3dx9.h>//D3DX
//XAudio2
#include <xaudio2.h>
#include <xaudio2fx.h>
#include <X3daudio.h>

//delete�n
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
//���C�u����
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
//�I�[�f�B�I
#include "SoundFile.h"
#include "CXAudio2.h"
#include "X3DVoiceState.h"
#include "SVoice.h"
#include "CSound.h"
#include "CLoadSound.h"
//�Q�[���ŗL���C�u����
#include "SystemData.h"
#include "CItem.h"//�Q�[���̃A�C�e��
#include "MyLibrary.h"//�I���W�i�����C�u����
//�I�u�W�F�N�g
#include "CObjFVF.h"
#include "CObjSound.h"
#include "CObjMesh.h"
#include "CObjParticl.h"
#include "CObjText.h"
#include "CObjSurf.h"

//�p�[�\�i���f�[�^
#include "FlagManager.h"//�Q�[���̃��j���[
#include "DebugButton.h"//�f�o�b�O�{�^��
#include "MenuMtrl.h"//�Q�[���̃��j���[�̑f��
#include "Menu.h"//�Q�[���̃��j���[

#include "HitPoint.h"//�q�b�g�|�C���g
#include "Shot.h"//�e
#include "flashlight.h"//�����d��
#include "CModel.h"//���샂�f��
#include "Personal.h"//�v���C���[�I�u�W�F�N�g
#include "Scene.h"//�V�[�����
//�G
#include "fish.h"
#include "Enemy.h"
#include "ActiveEnemy.h"
//�C�x���g�{��
#include "Ev_Title.h"//�^�C�g�����
#include "GameText.h"
#include "EventObj.h"
#include "Event.h"
#include "message.h"
#include "EventCam.h"
#include "Ev_GameOver.h"
//�ŏ��̃C�x���g
#include "Ev_FirstStage.h"//�ŏ��̃C�x���g
#include "Ev_Guest_Room.h"//�q���C�x���g
#include "Ev_Guest_Room1.h"
#include "Ev_Guest_Bath.h"//�q���o�X���[���C�x���g
//F2�C�x���g
#include "Ev_201.h"//201
#include "Ev_202.h"//202
#include "Ev_203.h"//203
#include "Ev_Secret_Door.h"//�B���ꂽ�h�A

#include "Ev_F3.h"//F3
#include "Ev_F31.h"//F3
#include "Ev_F32.h"//F3

#include "Ev_Rest_Men.h"//�j�q�g�C��
#include "Ev_Rest_Women.h"//���q�g�C��
#include "Ev_Roof_Top.h"//����
#include "Ev_SecretRoom.h"//�Ō�̃C�x���g

//F1�C�x���g
#include "Ev_Sandou.h"//�R��
#include "Ev_Soto.h"//�O
#include "Ev_Soto1.h"//�O
#include "Ev_Soto2.h"//�O
#include "Ev_Lobby.h"//���r�[
#include "Ev_Lobby1.h"//���r�[
#include "Ev_Bath_Room_Man.h"//�j��
#include "Ev_Bath_Datui_Woman.h"//�����E�ߏ�
#include "Ev_Bath_Room_Woman.h"//����
#include "Ev_Dining_Room.h"//�H��
#include "Ev_Staff_Room.h"//�]�ƈ���

//�t�B�[���h�{��
//�C�x���g�n
#include "Fld_Title.h"
#include "Fld_Intro.h"
#include "Fld_TestRoom.h"
#include "Fld_GameOver.h"

//�t�B�[���h
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

//���C��
#include "Main.h"
#include "WindowsAPI.h"
using namespace Ev;
using namespace Fld;