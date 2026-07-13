/*
 * Entry: 005369e9
 * Name: PopperGunClass::BuildClass
 * Namespace: PopperGunClass
 * Signature: WeaponClass * BuildClass(PopperGunClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall PopperGunClass::BuildClass(PopperGunClass *this,long64 param_1)

{
  PopperGunClass *pPVar1;
  undefined4 unaff_ESI;
  
  pPVar1 = operator_new(0x80);
  if (pPVar1 == (PopperGunClass *)0x0) {
    pPVar1 = (PopperGunClass *)0x0;
  }
  else {
    pPVar1 = PopperGunClass(pPVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (WeaponClass *)pPVar1;
}
