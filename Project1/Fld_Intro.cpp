//オープニング
Intro::Intro()
{
}
VOID Intro::Set()
{
	if(P->FM.EventFlag == TL_INTRO_START)
	{
		pIntro = NewObj(new IntroFirst);
	}
	if(P->FM.EventFlag == TL_INTRO_1)
	{
		pIntro = NewObj(new IntroSoto);
	}
	if(P->FM.EventFlag == TL_INTRO_2)
	{
		pIntro = NewObj(new IntroTitleCall);
	}
	pIntroCut = NewObj(new IntroCut);
}


VOID Intro::Update()
{
	
}
VOID Intro::UI()
{}	
