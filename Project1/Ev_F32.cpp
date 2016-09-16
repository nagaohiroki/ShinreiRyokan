const TCHAR* FishGhost::name(){return _T("FishGhost");}
FishGhost::FishGhost()
{
	flag = 0;
	frame = 0;

	pos.SetKey(0,D3DXVECTOR3(1.0f,2.56f,31.1f));
	pos.SetKey(200,D3DXVECTOR3(-1.0f,2.56f,31.1f));

	alpha.SetKey(0,1.0f);
	alpha.SetKey(100,0.0f);
}
VOID FishGhost::Set()
{

	if(P->FM.EventFlag == TL_FISH_WALK1)
	{
		flag = 2;
	}
	if(P->FM.EventFlag == TL_FISH_WALK2)
	{
		flag = 4;
	}
}

VOID FishGhost::Update()
{
	//ŠK’i‚ð‚ ‚ª‚Á‚½‚ç
	if( flag == 0 )
	{
		if(P->obj.objPos.x < 2.8f)
		{
			P->FM.EventFlag = TL_FISH_WALK1;
			flag = 1;
		}
	}
	//•à‚­
	if( flag == 1 )
	{
		fish.MotType = fish_anim::FM_WALK;
		fish.Null.objPos = pos.Val1(frame);
		fish.Null.YPR.y = -90.0f;

		frame++;
		if(frame > pos.MaxKey())
		{
			flag = 2; 
			frame = 0;
		}
	}
	//‰œ‚És‚Á‚½‚ç
	if( flag == 2 )
	{
		if(P->obj.objPos.z >= 29.5f)
		{
			
			P->FM.EventFlag = TL_FISH_WALK2;
			flag = 3; 
		}
	}
	//Á‚¦‚é
	if( flag == 3 )
	{
		fish.MotType = fish_anim::FM_WAIT;
		fish.Null.objPos = D3DXVECTOR3(-7.9f,2.56f,32.0f);
		fish.Null.YPR.y = 0.0f;
		fish.MeshCol(&D3DXVECTOR4(1.0f,1.0f,1.0f,alpha.Val1(frame)));
		frame++;
		if(frame > alpha.MaxKey())
		{
			fish.drawSkip = TRUE;
			flag = 4; 
		}
	}

	fish.Update(ML);
}
VOID FishGhost::draw()
{
	fish.draw(ML);
}