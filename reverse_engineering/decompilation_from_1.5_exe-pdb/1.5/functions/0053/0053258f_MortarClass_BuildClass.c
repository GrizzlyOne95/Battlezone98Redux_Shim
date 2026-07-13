/*
 * Entry: 0053258f
 * Name: MortarClass::BuildClass
 * Namespace: MortarClass
 * Signature: WeaponClass * BuildClass(MortarClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall MortarClass::BuildClass(MortarClass *this,long64 param_1)

{
  MortarClass *pMVar1;
  undefined4 unaff_ESI;
  
  pMVar1 = operator_new(0x80);
  if (pMVar1 == (MortarClass *)0x0) {
    pMVar1 = (MortarClass *)0x0;
  }
  else {
    pMVar1 = MortarClass(pMVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (WeaponClass *)pMVar1;
}
