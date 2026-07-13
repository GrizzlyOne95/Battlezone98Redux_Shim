/*
 * Entry: 0053749c
 * Name: RadarLauncherClass::RadarLauncherClass
 * Namespace: RadarLauncherClass
 * Signature: RadarLauncherClass * RadarLauncherClass(RadarLauncherClass * this, RadarLauncherClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RadarLauncherClass * __thiscall
RadarLauncherClass::RadarLauncherClass
          (RadarLauncherClass *this,RadarLauncherClass *param_1,long64 param_2)

{
  GameObjectClass *pGVar1;
  uint unaff_EBP;
  undefined4 unaff_ESI;
  int in_stack_00000008;
  
  LauncherClass::LauncherClass
            ((LauncherClass *)this,(LauncherClass *)param_1,CONCAT44(unaff_ESI,(int)param_2));
  *(undefined ***)this = &_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,&this->field_0x20);
  ParameterDB::Get((ParameterDB *)&param_1,0x1b103bb5,0xfab4528a,(long64 *)&stack0x00000008,
                   (ulonglong)unaff_EBP << 0x20);
  if (in_stack_00000008 != 0 || (int)param_2 != 0) {
    pGVar1 = GameObjectClass::Find(CONCAT44((int)param_2,in_stack_00000008));
    *(GameObjectClass **)&this->field_0x30 = pGVar1;
    *(long *)&this->field_0x78 = pGVar1->maxAmmo;
  }
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
