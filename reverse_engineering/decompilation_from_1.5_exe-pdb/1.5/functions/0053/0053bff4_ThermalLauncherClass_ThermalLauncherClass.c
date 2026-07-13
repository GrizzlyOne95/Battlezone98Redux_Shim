/*
 * Entry: 0053bff4
 * Name: ThermalLauncherClass::ThermalLauncherClass
 * Namespace: ThermalLauncherClass
 * Signature: ThermalLauncherClass * ThermalLauncherClass(ThermalLauncherClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ThermalLauncherClass * __thiscall
ThermalLauncherClass::ThermalLauncherClass(ThermalLauncherClass *this)

{
  LauncherClass::LauncherClass((LauncherClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0x54484d4c;
  *(char **)&this->field_0x10 = "thermallauncher";
  return this;
}
