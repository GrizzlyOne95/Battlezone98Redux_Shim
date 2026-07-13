/*
 * Entry: 0052d6af
 * Name: DispenserClass::BuildClass
 * Namespace: DispenserClass
 * Signature: WeaponClass * BuildClass(DispenserClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall DispenserClass::BuildClass(DispenserClass *this,long64 param_1)

{
  DispenserClass *pDVar1;
  undefined4 unaff_ESI;
  
  pDVar1 = operator_new(0x80);
  if (pDVar1 == (DispenserClass *)0x0) {
    pDVar1 = (DispenserClass *)0x0;
  }
  else {
    pDVar1 = DispenserClass(pDVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (WeaponClass *)pDVar1;
}
