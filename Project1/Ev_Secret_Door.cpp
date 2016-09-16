//=======================================
//隠されたドア
//=======================================
const TCHAR* Secret_Door::name(){return _T("Secret_Door");}
Secret_Door::Secret_Door()
{
	

	black.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f);
	Ui.push_back(&black);

	text.init(this);
	text.s(_T("壁紙がはがれかかっている"));
	text.s(_T("はがす？\nはがす\nはがさない"),4,5);

	frame = 0;
	flag = 0;

	fade.SetKey(0,0.0f);
	fade.SetKey(10,1.0f);
	fade.SetKey(20,0.0f);


	Msh.push_back(&hitbox);
	hitbox.Type(x_cube);
	hitbox.HitMode(CT_OBB,CB_NONE);
	hitbox.drawSkip = TRUE;

	Msh.push_back(&pWaku);
	pWaku.Type(x_wood_door_waku);
	pWaku.objScal=D3DXVECTOR3(0.8f,0.9f,1.0f);
	pWaku.ShadowFlag=FALSE;
	pWaku.SetPare(&hitbox.mWorld);
	pWaku.drawSkip = TRUE;
	pWaku.MeshCol = D3DXVECTOR4(0.4f,0.2f,0.2f,1.0f);


	Msh.push_back(&pDoor);
	pDoor.Type(x_wood_door);
	pDoor.SetPare(&pWaku.mWorld);
	pDoor.objPos.x=-0.47f;
	pDoor.ShadowFlag=FALSE;
	pDoor.drawSkip = TRUE;
	pDoor.MeshCol = D3DXVECTOR4(0.4f,0.2f,0.2f,1.0f);
/*
	Msh.push_back(&pNobu);
	pNobu.Type(x_doornobu);
	pNobu.SetPare(&pDoor.mWorld);
	pNobu.objPos=D3DXVECTOR3(0.82f,0.75f,0);
	pNobu.ShadowFlag=FALSE;	
	pNobu.drawSkip = TRUE;
*/
	Msh.push_back(&pPlate);
	pPlate.Type(x_door_plate);
	pPlate.drawSkip = TRUE;
	pPlate.drawSkip = FALSE;
	pPlate.SetPare(&pDoor.mWorld);
	pPlate.objPos=D3DXVECTOR3(0.47f,1.3f,0);
	pPlate.ShadowFlag=FALSE;
	pPlate.drawSkip = TRUE;

	//壁
	wall.Type(x_kabe);
	wall.SetPare(&hitbox.mWorld);
	wall.YPR = D3DXVECTOR3(0.0f,0.0f,0.0f);
	wall.objScal = D3DXVECTOR3(1.0f,1.5f,1.0f);
	wall.objPos = D3DXVECTOR3(-0.5f,0.0f,0.0f);
	wall.MeshCol = D3DXVECTOR4(0.8f,0.8f,0.8f,1.0f);
	wall.ShadowFlag = FALSE;
	Msh.push_back(&wall);
	

	//破く音
	strip.Set(wav_sa);
	strip.Filter.Frequency = 0.5f;
	strip.Filter.OneOverQ = 0.5f;

	Snd.push_back(&strip);	

	//ルームプレート
	Txt.push_back(&roomPlate);
	roomPlate.objScal=D3DXVECTOR3(0.003f,0.003f,1.0f);
	roomPlate.objPos=D3DXVECTOR3(-0.06f,0.0f,-0.042f);
	roomPlate.drawSkip = FALSE;
	roomPlate.SetText(_T("204"));
	roomPlate.SetPare(&pPlate.mWorld);
	roomPlate.MeshCol=D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
	roomPlate.drawSkip = TRUE;

}
VOID Secret_Door::Set()
{
	black.objScal.x = (float)ML->GV.ClientWidth;
	black.objScal.y = (float)ML->GV.ClientHeight;
	if( P->FM.EventFlag >= TL_READ_TIPS )
	{
		flag =1;
	}
	if( P->FM.EventFlag >= TL_SERCRET_DOOR )
	{
		flag =3;
	}
}

VOID Secret_Door::Update()
{
	black.MeshCol.w = fade.Val1(frame);
	if( flag == 0 )
	{
		//ドア消滅
		wall.drawSkip = TRUE;
		pWaku.drawSkip = TRUE; 
		pDoor.drawSkip = TRUE;
//		pNobu.drawSkip = TRUE;
		pPlate.drawSkip = TRUE;
		roomPlate.drawSkip = TRUE;	
		//暗転消滅
		black.drawSkip = TRUE;
	}
	if( flag == 1 )
	{		
		wall.drawSkip = FALSE;
		//調べる
		if( hitbox.HitObj.Reaction == 1 )
		if( P->Check )
		if( P->Mode != Personal::MODE_EVENT )
		{
			text.StartText(P);
		}
		if(text.Update(P,ML) == 4)
		{
			flag = 2;	
			strip.Start(ML);
		}
		
	}
	if( flag == 2 )
	{
		//暗転消滅
		black.drawSkip = FALSE;
		//フェード
		frame++;
		if( frame >= 10 )
		{
			pWaku.drawSkip = FALSE; 
			pDoor.drawSkip = FALSE;
			pPlate.drawSkip = FALSE;
			roomPlate.drawSkip = FALSE;	
		}
		if(frame > fade.MaxKey())
		{
			P->FM.EventFlag = TL_SERCRET_DOOR;
			flag = 3;
		}
	}
	if( flag == 3 )
	{
		//ドア出現
		pWaku.drawSkip = FALSE; 
		pDoor.drawSkip = FALSE;
		pPlate.drawSkip = FALSE;
		roomPlate.drawSkip = FALSE;	
		//暗転消滅
		black.drawSkip = TRUE;
		//壁紙消滅
		wall.drawSkip = TRUE;
		//移動
		if( hitbox.HitObj.Reaction == 1 )
		if( P->Check )
		if( P->Mode != Personal::MODE_EVENT )
		{
			P->CheckSE(Personal::SE_OPEN);
			m_pPare->FldChange(new SecretRoom,&D3DXVECTOR3(-5.6f,0.35f,-2.2f),90.0f);
		}

	}
}
