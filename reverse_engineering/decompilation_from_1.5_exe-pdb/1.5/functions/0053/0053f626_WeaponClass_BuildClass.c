/*
 * Entry: 0053f626
 * Name: WeaponClass::BuildClass
 * Namespace: WeaponClass
 * Signature: WeaponClass * BuildClass(WeaponClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall WeaponClass::BuildClass(WeaponClass *this,long64 param_1)

{
  WeaponClass *pWVar1;
  undefined4 unaff_ESI;
  
  pWVar1 = operator_new(0x78);
  if (pWVar1 == (WeaponClass *)0x0) {
    pWVar1 = (WeaponClass *)0x0;
  }
  else {
    pWVar1 = WeaponClass(pWVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return pWVar1;
}
