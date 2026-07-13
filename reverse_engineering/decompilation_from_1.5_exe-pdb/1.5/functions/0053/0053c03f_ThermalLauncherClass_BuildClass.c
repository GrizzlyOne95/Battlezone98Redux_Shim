/*
 * Entry: 0053c03f
 * Name: ThermalLauncherClass::BuildClass
 * Namespace: ThermalLauncherClass
 * Signature: WeaponClass * BuildClass(ThermalLauncherClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall ThermalLauncherClass::BuildClass(ThermalLauncherClass *this,long64 param_1)

{
  ThermalLauncherClass *pTVar1;
  undefined4 unaff_ESI;
  
  pTVar1 = operator_new(0xc0);
  if (pTVar1 == (ThermalLauncherClass *)0x0) {
    pTVar1 = (ThermalLauncherClass *)0x0;
  }
  else {
    pTVar1 = ThermalLauncherClass(pTVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (WeaponClass *)pTVar1;
}
