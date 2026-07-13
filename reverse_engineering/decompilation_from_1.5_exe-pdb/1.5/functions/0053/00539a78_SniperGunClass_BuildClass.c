/*
 * Entry: 00539a78
 * Name: SniperGunClass::BuildClass
 * Namespace: SniperGunClass
 * Signature: WeaponClass * BuildClass(SniperGunClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall SniperGunClass::BuildClass(SniperGunClass *this,long64 param_1)

{
  SniperGunClass *pSVar1;
  undefined4 unaff_ESI;
  
  pSVar1 = operator_new(0x80);
  if (pSVar1 == (SniperGunClass *)0x0) {
    pSVar1 = (SniperGunClass *)0x0;
  }
  else {
    pSVar1 = SniperGunClass(pSVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (WeaponClass *)pSVar1;
}
