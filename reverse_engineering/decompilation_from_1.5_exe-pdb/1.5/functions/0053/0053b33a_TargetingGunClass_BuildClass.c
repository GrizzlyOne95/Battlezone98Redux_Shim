/*
 * Entry: 0053b33a
 * Name: TargetingGunClass::BuildClass
 * Namespace: TargetingGunClass
 * Signature: WeaponClass * BuildClass(TargetingGunClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall TargetingGunClass::BuildClass(TargetingGunClass *this,long64 param_1)

{
  TargetingGunClass *pTVar1;
  undefined4 unaff_ESI;
  
  pTVar1 = operator_new(0xa8);
  if (pTVar1 == (TargetingGunClass *)0x0) {
    pTVar1 = (TargetingGunClass *)0x0;
  }
  else {
    pTVar1 = TargetingGunClass(pTVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (WeaponClass *)pTVar1;
}
