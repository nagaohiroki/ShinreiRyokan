flashlight::flashlight()
{
	flash.Type(x_flashlight);
	flash.MeshCol = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
//	flash.SpColm = 0.0f;
	flash.SpCol.w = 100.0f;
	light.Type(x_sphere);
	light.ShadowFlag = FALSE;
	light.SetPare(&flash.mWorld);
	light.objPos = D3DXVECTOR3(0.0f,0.2f,0.0f);
	light.objScal = D3DXVECTOR3(0.05f,0.01f,0.05f);
	light.SpCol.w = 0.0f;
	light.SpColm = 1.0f;
	light.BloomColor = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f)* 20.0f;

}
VOID flashlight::Set(MyLibrary* ml)
{
	flash.SetSize(ml);
	light.SetSize(ml);

}	
VOID flashlight::Update(MyLibrary* ML,BOOL Lock)
{	
	if(Lock)
	{
		D3DXVECTOR3 p(flash.mWorld._41,flash.mWorld._42,flash.mWorld._43);
		D3DXVECTOR3 v(light.mWorld._41,light.mWorld._42,light.mWorld._43);
		D3DXVECTOR3 n;
		D3DXVec3Normalize(&n,&(v-p));
		ML->E.PSL.Pos  = p + n * 0.1f;
		ML->E.PSL.Vec = v;
	}
	ML->E.PSL.dis = 1.0f;
	ML->E.PSL.Lcos = 0.7f;
//	ML->E.PSL.Col = D3DXVECTOR4(0.1f,0.1f,0.1f,1.0f);
}


VOID flashlight::draw(MyLibrary* ML)
{
	flash.draw(ML);
	light.draw(ML);
}
