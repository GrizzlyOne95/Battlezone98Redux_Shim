/*
 * Entry: 00530f05
 * Name: LauncherClass::Build
 * Namespace: LauncherClass
 * Signature: Weapon * Build(LauncherClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall LauncherClass::Build(LauncherClass *this,_OBJ76 *param_1)

{
  Launcher *pLVar1;
  
  pLVar1 = operator_new(0xd0);
  if (pLVar1 == (Launcher *)0x0) {
    pLVar1 = (Launcher *)0x0;
  }
  else {
    pLVar1 = Launcher::Launcher(pLVar1,param_1,this);
  }
  return (Weapon *)pLVar1;
}
