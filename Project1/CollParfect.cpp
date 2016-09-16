
//ƒRƒŠƒWƒ‡ƒ“
CollSell::CollSell()
{
	int i;
	for(i = 0; i < CT_MAX; i++)
	{
		coll[i] = NULL;
	}
}

CollParfect::CollParfect()
{
	int i;
	int j;
	for(i = 0; i < CT_MAX;i++)
	{
		for(j = 0; j < CT_MAX;j++)
		{
			coll[i].coll[j] = &base; 
		}
	}
	coll[CT_SPHERE].coll[CT_SPHERE]= &svss;
	coll[CT_SPHERE].coll[CT_PLANE] = &svsp;
	coll[CT_SPHERE].coll[CT_OBB]   = &svso;
	coll[CT_SPHERE].coll[CT_SEGMET]= &svsg;

	coll[CT_OBB].coll[CT_SPHERE]   = &ovss;
	coll[CT_OBB].coll[CT_PLANE]    = &ovsp;
	coll[CT_OBB].coll[CT_OBB]      = &ovso;
	coll[CT_OBB].coll[CT_SEGMET]   = &ovsg;

	coll[CT_PLANE].coll[CT_SPHERE] = &pvss;
	coll[CT_PLANE].coll[CT_OBB]    = &pvso;

	coll[CT_SEGMET].coll[CT_SPHERE]= &gvss;
	coll[CT_SEGMET].coll[CT_OBB]   = &gvso;

	
}
BOOL CollParfect::Hit(CollObj* c1,CollObj* c2)
{
	return coll[c1->cType].coll[c2->cType]->Hit(c1,c2);
}

