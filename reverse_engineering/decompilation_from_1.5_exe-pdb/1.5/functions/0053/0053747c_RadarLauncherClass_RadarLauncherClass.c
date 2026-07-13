/*
 * Entry: 0053747c
 * Name: RadarLauncherClass::RadarLauncherClass
 * Namespace: RadarLauncherClass
 * Signature: RadarLauncherClass * RadarLauncherClass(RadarLauncherClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RadarLauncherClass * __thiscall RadarLauncherClass::RadarLauncherClass(RadarLauncherClass *this)

{
  LauncherClass::LauncherClass((LauncherClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0x5244524c;
  *(char **)&this->field_0x10 = "radarlauncher";
  return this;
}
