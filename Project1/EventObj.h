#pragma once

namespace Ev{
	//その他=======================================================================================
//=============================================
//当たり判定箱
//=============================================
class HitBox : public Scene
{
	CObjMesh Box;
public:
	HitBox()
	{	

		Msh.push_back(&Box);
		Box.Type(x_cube);
		Box.MeshCol.w=0.5f;
		Box.ShadowFlag=FALSE;
		Box.drawSkip=TRUE;
		Box.HitMode(CT_OBB,CB_PLUS);
	}
	const TCHAR *name(){return _T("HitBox");}
};


//==========================================
//判定用当たり判定
//==========================================
class HitFlag : public Scene
{
	CObjMesh Box;
public:
	HitFlag()
	{
		Msh.push_back(&Box);
		Box.Type(x_cube);
		Box.MeshCol.w=0.5f;
		Box.ShadowFlag=FALSE;
		Box.drawSkip=TRUE;
		Box.HitMode(CT_OBB,CB_NONE);
	}
	const TCHAR *name(){return _T("HitFlag");}
};

//=============================================
//描画するだけのオブジェクト
//=============================================
class drawObj : public Scene
{
	CObjMesh Obj;
public:
	
	drawObj()
	{
		Msh.push_back(&Obj);
		Obj.Type(x_cube);
	}	
	const TCHAR *name(){return _T("drawObj");}
	

};
//=============================================
//描画と単独の当たり判定を持つオブジェクト(OBB)
//=============================================
class drawHitObj : public Scene
{
	CObjMesh Box;
public:
	drawHitObj()
	{
		Msh.push_back(&Box);
		Box.Type(x_cube);
		Box.HitMode(CT_OBB,CB_PLUS);
	}
	const TCHAR *name(){return _T("drawHitObj");}
	
};

//==================================
//扉 
//Flag[0]はプレート:0はなし,1はWC,2スタッフオンリー,3以上フラグの変数
//Flag[1]は施錠確認:0はなし,1は有り,2は緑,3は赤
//Flag[2]はアニメーション
//Flag[3]で非常口化
//==================================
class Door : public Scene
{	
private:
	TCHAR Room[20];
	CObjText roomPlate;	
	CObjMesh pBox;
	CObjMesh pWaku; 
	CObjMesh pDoor;
	CObjMesh pNobu;
	CObjMesh pPlate;
	CObjMesh pKey;
	CObjMesh pKeyC;
	VOID SetPlate(int Plate)
	{
		if(Plate==0)
		{
			pPlate.drawSkip=TRUE;
			return;
		}
		pPlate.drawSkip = FALSE;
		pPlate.SetPare(&pDoor.mWorld);
		pPlate.objPos=D3DXVECTOR3(0.47f,1.3f,0);
		pPlate.ShadowFlag=FALSE;
		_stprintf_s(Room,20,_T(""));
		switch(Plate)
		{	
		case 0:_stprintf_s(Room,20,_T("無効"));break;
		case 1:
			_stprintf_s(Room,20,_T("W.C"));
			roomPlate.objScal=D3DXVECTOR3(0.002f,0.002f,1.0f);
			roomPlate.objPos=D3DXVECTOR3(-0.06f,0.0f,-0.042f);
			break;
		case 2:
			_stprintf_s(Room,20,_T("Staff Only"));
			roomPlate.objScal=D3DXVECTOR3(0.001f,0.001f,1.0f);
			roomPlate.objPos=D3DXVECTOR3(-0.09f,0.0f,-0.042f);
			break;
		default:
			_stprintf_s(Room,20,_T("%d"),Plate);
			roomPlate.objScal=D3DXVECTOR3(0.002f,0.002f,1.0f);
			roomPlate.objPos=D3DXVECTOR3(-0.04f,0.0f,-0.042f);
			break;
		}
		roomPlate.drawSkip = FALSE;
		roomPlate.SetText(Room);
		roomPlate.SetPare(&pPlate.mWorld);
		roomPlate.MeshCol=D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	}
	VOID Setkey(int KeyFlag)
	{
		//鍵
		if(KeyFlag==0)
		{
			pKey.drawSkip=TRUE;
			pKeyC.drawSkip=TRUE;
			return;
		}
		pKey.drawSkip=FALSE;
		pKey.SetPare(&pDoor.mWorld);
		pKey.objPos=D3DXVECTOR3(0.83f,0.8f,0);
		pKey.ShadowFlag=FALSE;

		//施錠確認の色
		if(KeyFlag==1)
		{
			pKeyC.drawSkip=TRUE;
			return;
		}
		pKeyC.drawSkip=FALSE;
		pKeyC.SetPare(&pKey.mWorld);
		pKeyC.objPos=D3DXVECTOR3(0.00f,-0.01f,-0.05f);
		pKeyC.objScal=D3DXVECTOR3(0.01f,0.02f,0.05f);

		switch(KeyFlag)
		{
		case 2:pKeyC.MeshCol=D3DXVECTOR4(0,1.0f,0,1.0f);break;
		case 3:pKeyC.MeshCol=D3DXVECTOR4(1.0f,0,0,1.0f);break;
		default:break;
		}
	}
	VOID Init()
	{
		//あたり判定用ボックス
		Msh.push_back(&pBox);
		pBox.Type(x_cube);
		pBox.drawSkip=TRUE;
		pBox.HitMode(CT_OBB,CB_NONE);

		Msh.push_back(&pWaku);
		pWaku.Type(x_wood_door_waku);
		pWaku.objScal=D3DXVECTOR3(0.8f,0.9f,1.0f);
		pWaku.ShadowFlag=FALSE;
		Msh.push_back(&pDoor);
		pDoor.Type(x_wood_door);
		pDoor.SetPare(&pWaku.mWorld);
		pDoor.objPos.x=-0.47f;
		pDoor.ShadowFlag=FALSE;
		Msh.push_back(&pNobu);
		pNobu.Type(x_doornobu);
		pNobu.SetPare(&pDoor.mWorld);
		pNobu.objPos=D3DXVECTOR3(0.82f,0.75f,0);
		pNobu.ShadowFlag=FALSE;	
		Msh.push_back(&pPlate);
		pPlate.Type(x_door_plate);
		pPlate.drawSkip = TRUE;
		Msh.push_back(&pKey);
		pKey.Type(x_door_key);
		pKey.drawSkip=TRUE;
		pKey.BloomColor.w = 5.0f;
		Msh.push_back(&pKeyC);
		pKeyC.Type(x_cube);
		pKeyC.drawSkip=TRUE;
		roomPlate.drawSkip = TRUE;
		Txt.push_back(&roomPlate);
	}
public:
	const TCHAR *name(){return _T("Door");}
	enum
	{
		F0_NO,
		F0_WC,
		F0_STAFF,
	};
	enum
	{
		F1_NO,
		F1_KEY,
		F1_KEY_GREEN,
		F1_KEY_RED,
	};
	enum
	{
		F2_WOOD,
		F2_EXIT,
		F2_BATH,

	};
	Door()
	{		
		Init();
	}
	//(プレート,鍵,ドアの種類)
	Door(int plate,int key,int DoorType)
	{
		Init();
		SetPlate(plate);
		Setkey(key);
		if(DoorType == F2_EXIT)
		{
			pWaku.Type(x_exit_door_waku);
			pDoor.Type(x_exit_door);
			pNobu.Type(x_exit_door_nobu);
		}

		if(DoorType == F2_BATH)
		{
			pWaku.Type(x_bathdoorwaku);
			pDoor.Type(x_bathdoor);
			pNobu.drawSkip = TRUE;
		}
	}
	VOID Set()
	{
		pWaku.objPos = pBox.objPos;
		pWaku.YPR    = pBox.YPR;
	}
};

//==============================================
//椅子
//==============================================
class Chair : public Scene
{
	CObjMesh pChair;
	CObjMesh pLhand;
	CObjMesh pRhand;

public:
	Chair()
	{
		Msh.push_back(&pChair);
		pChair.Type(x_chair);
		pChair.SpColm=0.0f;
		pChair.Bias=0.5f;
		pChair.HitMode(CT_OBB,CB_PLUS);
		//左の手すり
		Msh.push_back(&pLhand);
		pLhand.Type(x_chair_tesuri);
		pLhand.SetPare(&pChair.mWorld);
		pLhand.SpColm=0.0f;
		pLhand.objPos.x=-0.35f;
		pLhand .Bias=0.5f;

		//右の手すり
		Msh.push_back(&pRhand);
		pRhand.Type(x_chair_tesuri);
		pRhand.SetPare(&pChair.mWorld);
		pRhand.SpColm=0.0f;
		pRhand.objPos.x=0.35f;
		pRhand.Bias=0.5f;
	
	}
	VOID Set()
	{
		pLhand.objScal.x /= pChair.objScal.x;
		pRhand.objScal.x /= pChair.objScal.x;
	}
	const TCHAR *name(){return _T("Chair");}

	
};


//==============================================
//トイレ
//==============================================
class Toile : public Scene
{
	CObjMesh pToile;
	CObjMesh pHuta;
public:	
	const TCHAR *name(){return _T("Toile");}
	Toile()
	{
		Msh.push_back(&pToile);
		pToile.Type(x_toile);
		pToile.HitMode(CT_OBB,CB_PLUS);
		pToile.Bias = 0.1f;
		Msh.push_back(&pHuta);
		pHuta.Type(x_tcover);
		pHuta.SetPare(&pToile.mWorld);
		pHuta.objPos.y=0.35f;
		pHuta.MeshCol=D3DXVECTOR4(2.5f,2.5f,2.5f,1.0f);
		pHuta.SpColm=0.0f;
	}
};
//=============================================
//電気のスイッチ
//=============================================
class LightSwitch : public Scene
{
	CObjMesh pBase;
	CObjMesh pSwitch;
public:
	const TCHAR *name(){return _T("LightSwitch");}
	LightSwitch()
	{
		Msh.push_back(&pBase);
		pBase.Type(x_cube);
		pBase.objScal=D3DXVECTOR3(0.2f,0.4f,0.04f);
		pBase.MeshCol=D3DXVECTOR4(0.6f,0.6f,0.6f,1.0f);
		pBase.ShadowFlag=FALSE;
		pBase.SpColm=0.0f;
		//スイッチ部分
		Msh.push_back(&pSwitch);
		pSwitch.Type(x_cube);
		pSwitch.SetPare(&pBase.mWorld);
		pSwitch.objScal=D3DXVECTOR3(0.5f,0.15f,0.2f);
		pSwitch.objPos=D3DXVECTOR3(0.0f,0.0f,-0.35f);
		pSwitch.MeshCol=D3DXVECTOR4(0.9f,0.9f,0.9f,1.0f);
		pSwitch.YPR.y=-45.0f;
		pSwitch.ShadowFlag=FALSE;
	}

};

//============================================
//窓(小サイズ)
//============================================
class Mado_S : public Scene
{
	CObjMesh pMado;
	CObjMesh pGlass;

public:
	const TCHAR *name(){return _T("Mado_S");}

	Mado_S()
	{	
		Msh.push_back(&pMado);
		pMado.Type(x_mado_s);
		pMado .ShadowFlag=FALSE;
		//窓ガラス
		Msh.push_back(&pGlass);
		pGlass.Type(x_cube);
		pGlass.ShadowFlag=FALSE;
		pGlass.SetPare(&pMado.mWorld);
		pGlass.objPos.z=0.06f;
		pGlass.objScal=D3DXVECTOR3(3.0f,2.2f,0.3f);
		pGlass.MeshCol=D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
		pGlass.SpCol.w=20.0f;
		pGlass.SpColm=0.36f;
	}
};
//==========================================
//照明
//==========================================
class Light :public Scene
{
	CObjMesh pLight; 
public:
	Light()
	{
		Msh.push_back(&pLight);
		pLight.Type(x_sphere);
		pLight.SpCol.w=0.0f;
		pLight.ShadowFlag=FALSE;
		pLight.objScal=D3DXVECTOR3(1.0f,0.7f,1.0f)*0.15f;
		pLight.BloomColor.w=2.0f;
	} 
	const TCHAR *name(){return _T("Light");}
};

//==========================================
//電気
//==========================================
class Denki:public Scene
{
	CObjMesh pCube;
	CObjMesh pCable;
	CObjMesh pDenki;
public:
	const TCHAR *name(){return _T("Denki");}
	Denki()
	{
		//回転原点
		Msh.push_back(&pCube);
		pCube.Type(x_cube);
		pCube.objScal=D3DXVECTOR3(0.1f,0.1f,0.1f);
		pCube.ShadowFlag = FALSE;
		//ケーブル
		Msh.push_back(&pCable);
		pCable.Type(x_cube);
		pCable.ShadowFlag = FALSE;
		pCable.SetPare(&pCube.mWorld);
		pCable.objScal=D3DXVECTOR3(0.05f,0.8f,0.05f);
		pCable.objScal=vec3Ari().D3DXVec3Div(&pCable.objScal,&pCube.objScal);
		pCable.objPos=D3DXVECTOR3(0.0f,-2.0f,0.0f);
		pCable.MeshCol=D3DXVECTOR4(0.2f,0.2f,0.2f,1.0f);
		//電気本体
		Msh.push_back(&pDenki);
		pDenki.Type(x_denki);
		pDenki.SetPare(&pCable.mWorld);
		pDenki.objScal=vec3Ari().D3DXVec3Div(&pDenki.objScal,&pCube.objScal);
		pDenki.objScal=vec3Ari().D3DXVec3Div(&pDenki.objScal,&pCable.objScal);
		pDenki.objPos.y=-0.5f;
		pDenki.ShadowFlag=FALSE;
		pDenki.SpCol.w=0.8f;
		pDenki.BloomColor.w=2.0f;
		pDenki.HitMode(CT_OBB,CB_PLUS);
	}
};
//=========================================
//トイレドア
//=========================================
class Rest_door:public Scene
{
private:
	CObjMesh pDoor;
	CObjMesh pGreen;
	CObjMesh pRed;

	VOID MenSet(size_t lock)
	{
		//ドア
		Msh.push_back(&pDoor);
		pDoor.Type(x_rest_door);
		pDoor.ShadowFlag=FALSE;
		pDoor.HitMode(CT_OBB,CB_PLUS);
		//鍵
		Msh.push_back(&pGreen);
		pGreen.Type(x_cube);
		pGreen.SetPare(&pDoor.mWorld);
		pGreen.objPos=D3DXVECTOR3(0.02f,0.775f,-0.764f);//青
	//	pGreen.objPos=D3DXVECTOR3(0.02f,0.775f,-0.785f);//赤
		pGreen.objScal=D3DXVECTOR3(0.10f,0.05f,0.04f);
		pGreen.MeshCol=D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f);
		pGreen.ShadowFlag=FALSE;
		Msh.push_back(&pRed);
		pRed.Type(x_cube);
		pRed.ShadowFlag=FALSE;
		pRed.SetPare(&pGreen.mWorld);
		pRed.objPos=D3DXVECTOR3(-0.00f,0.00f,0.50f);
		pRed.MeshCol=D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f);
		if(lock==0)
		{
			pGreen.objPos.z=-0.764f;
		}
		else
		{
			pGreen.objPos.z=-0.785f;
		}
	}
public:
	const TCHAR *name(){return _T("Rest_door");}

	//鍵青
	Rest_door()
	{
		MenSet(0);
	}
	//0が鍵青1が鍵赤
	Rest_door(size_t lock)
	{
		MenSet(lock);
	}

};
//=========================================
//トイレ水道のひねり
//=========================================
class Rest_handle:public Scene
{

	CObjMesh pLhandle;
	CObjMesh pRhandle;
	CObjMesh pBlue;
	CObjMesh pRed;
public:
	const TCHAR *name(){return _T("Rest_handle");}
	Rest_handle()
	{
		
		//左のハンドル
		Msh.push_back(&pLhandle);
		pLhandle.Type(x_rest_handle);
		pLhandle.objPos=D3DXVECTOR3(0,0.555f,0);
		pLhandle.ShadowFlag=FALSE;

		//右のハンドル
		Msh.push_back(&pRhandle);
		pRhandle.Type(x_rest_handle);
		pRhandle.SetPare(&pLhandle.mWorld);
		pRhandle.objPos.z=-0.07f;
		pRhandle.ShadowFlag=FALSE;

		//青	
		Msh.push_back(&pBlue);
		pBlue.Type(x_sphere);
		pBlue.SetPare(&pLhandle.mWorld);
		pBlue.objPos=D3DXVECTOR3(0.00f,0.02f,0.00f);
		pBlue.objScal=D3DXVECTOR3(0.01f,0.01f,0.01f);
		pBlue.MeshCol=D3DXVECTOR4(0.00f,1.00f,1.00f,1.00f);
		pBlue.ShadowFlag=FALSE;

		//赤
		Msh.push_back(&pRed);
		pRed.Type(x_sphere);
		pRed.SetPare(&pRhandle.mWorld);
		pRed.objPos=D3DXVECTOR3(0.00f,0.02f,0.00f);
		pRed.objScal=D3DXVECTOR3(0.01f,0.01f,0.01f);
		pRed.MeshCol=D3DXVECTOR4(1.00f,0.00f,0.00f,1.00f);
		pRed.ShadowFlag=FALSE;
	}


};
//============================================
//自販機
//============================================
class Zihanki:public Scene
{
	CObjMesh pZihanki;
public:
	const TCHAR *name(){return _T("Zihanki");}
	Zihanki()
	{
		Msh.push_back(&pZihanki);
		pZihanki.Type(x_zihanki);
		pZihanki.BloomColor.w=2.0f;
		pZihanki.Bias=0.5f;
		pZihanki.HitMode(CT_OBB,CB_PLUS);
	}
};



//==========================================
//扇風機
//==========================================
class Senpu:public Scene
{
	CObjMesh pSenp;
	CObjMesh pCav;
public:
	const TCHAR *name(){return _T("Senpu");}
	Senpu()
	{
		Msh.push_back(&pSenp);
		pSenp.Type(x_senpu);
		pSenp.Bias=0.16f;
		pSenp.HitMode(CT_OBB,CB_PLUS);
		Msh.push_back(&pCav);
		pCav.Type(x_snp_cav);
		pCav.SetPare(&pSenp.mWorld);
		pCav.objPos=D3DXVECTOR3(0.00f,0.70f,0.14f);
	}


};
}