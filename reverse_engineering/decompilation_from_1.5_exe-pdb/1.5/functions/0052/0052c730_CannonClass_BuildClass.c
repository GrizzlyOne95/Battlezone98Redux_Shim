/*
 * Entry: 0052c730
 * Name: CannonClass::BuildClass
 * Namespace: CannonClass
 * Signature: WeaponClass * BuildClass(CannonClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall CannonClass::BuildClass(CannonClass *this,long64 param_1)

{
  CannonClass *pCVar1;
  undefined4 unaff_ESI;
  
  pCVar1 = operator_new(0x80);
  if (pCVar1 == (CannonClass *)0x0) {
    pCVar1 = (CannonClass *)0x0;
  }
  else {
    pCVar1 = CannonClass(pCVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (WeaponClass *)pCVar1;
}
