/*
 * Entry: 0053a433
 * Name: SpecialItemClass::BuildClass
 * Namespace: SpecialItemClass
 * Signature: WeaponClass * BuildClass(SpecialItemClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall SpecialItemClass::BuildClass(SpecialItemClass *this,long64 param_1)

{
  SpecialItemClass *pSVar1;
  undefined4 unaff_ESI;
  
  pSVar1 = operator_new(0xa8);
  if (pSVar1 == (SpecialItemClass *)0x0) {
    pSVar1 = (SpecialItemClass *)0x0;
  }
  else {
    pSVar1 = SpecialItemClass(pSVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (WeaponClass *)pSVar1;
}
