/*
 * Entry: 0053c069
 * Name: ThermalLauncherClass::Build
 * Namespace: ThermalLauncherClass
 * Signature: Weapon * Build(ThermalLauncherClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall ThermalLauncherClass::Build(ThermalLauncherClass *this,_OBJ76 *param_1)

{
  ThermalLauncher *pTVar1;
  
  pTVar1 = operator_new(0xd0);
  if (pTVar1 == (ThermalLauncher *)0x0) {
    pTVar1 = (ThermalLauncher *)0x0;
  }
  else {
    pTVar1 = ThermalLauncher::ThermalLauncher(pTVar1,param_1,this);
  }
  return (Weapon *)pTVar1;
}
