CObjSurf::	CObjSurf()
{
	stex = NULL;

	w = 0;
	h = 0;
	z = FALSE;
	fmt = D3DFMT_A8R8G8B8;
	color = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
}
CObjSurf::~CObjSurf()
{
	SAFE_DELETE(stex);
}
VOID CObjSurf::Set(MyLibrary*)
{
	if(stex != NULL){return;}

//	stex = ml->Sr.Set(ml->D,z,w,h,fmt);	
}
VOID CObjSurf::Begin(MyLibrary* ml)
{
	stex->Begin(ml->D,pass,&color);
}
LPDIRECT3DTEXTURE9 CObjSurf::Tex()
{
	if(!stex){return NULL;}
	return stex->m_pSurfTex;
}
