Dining_Key::Dining_Key()
{
	//鍵
	key.Type(x_key);
	key.HitMode(CT_OBB,CB_NONE);
	key.objScal = D3DXVECTOR3(1.0f,1.0f,1.0f) * 0.2f;
	key.MeshCol= D3DXVECTOR4(5.0f,5.0f,5.0f,1.0f);
	Msh.push_back(&key);
	//テキスト
	text.init(this);
	text.s(_T("【食堂の鍵】を手に入れた"));
}
VOID Dining_Key::Update()
{
	if(	P->FM.iGetedFlag(ITEM_DINING_KEY) )
	{
		key.drawSkip = TRUE;
		return;
	}
	if(key.HitObj.Reaction == 1)
	if(P->Check)
	if(P->Mode != Personal::MODE_EVENT)
	{
		text.StartText(P);
		P->CheckSE(Personal::SE_ITEM);
		
	}
	if(text.Update(P,ML) == 1)
	{
		P->FM.iGet(ITEM_DINING_KEY);
	}

}