/*
 * Entry: 0053753e
 * Name: RadarLauncherClass::Build
 * Namespace: RadarLauncherClass
 * Signature: Weapon * Build(RadarLauncherClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall RadarLauncherClass::Build(RadarLauncherClass *this,_OBJ76 *param_1)

{
  RadarLauncher *pRVar1;
  
  pRVar1 = operator_new(0xd0);
  if (pRVar1 == (RadarLauncher *)0x0) {
    pRVar1 = (RadarLauncher *)0x0;
  }
  else {
    pRVar1 = RadarLauncher::RadarLauncher(pRVar1,param_1,this);
  }
  return (Weapon *)pRVar1;
}
