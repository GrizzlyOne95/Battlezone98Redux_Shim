/*
 * Entry: 0053c014
 * Name: ThermalLauncherClass::ThermalLauncherClass
 * Namespace: ThermalLauncherClass
 * Signature: ThermalLauncherClass * ThermalLauncherClass(ThermalLauncherClass * this, ThermalLauncherClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ThermalLauncherClass * __thiscall
ThermalLauncherClass::ThermalLauncherClass
          (ThermalLauncherClass *this,ThermalLauncherClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  LauncherClass::LauncherClass
            ((LauncherClass *)this,(LauncherClass *)param_1,CONCAT44(unaff_ESI,(undefined4)param_2))
  ;
  *(undefined ***)this = &_vftable_;
  return this;
}
