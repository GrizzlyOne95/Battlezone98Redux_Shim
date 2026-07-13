/*
 * Entry: 0053116b
 * Name: LauncherClass::BuildClass
 * Namespace: LauncherClass
 * Signature: WeaponClass * BuildClass(LauncherClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall LauncherClass::BuildClass(LauncherClass *this,long64 param_1)

{
  LauncherClass *pLVar1;
  undefined4 unaff_ESI;
  
  pLVar1 = operator_new(0xc0);
  if (pLVar1 == (LauncherClass *)0x0) {
    pLVar1 = (LauncherClass *)0x0;
  }
  else {
    pLVar1 = LauncherClass(pLVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (WeaponClass *)pLVar1;
}
