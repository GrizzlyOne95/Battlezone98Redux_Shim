/*
 * Entry: 0052cfd7
 * Name: ChargeGunClass::BuildClass
 * Namespace: ChargeGunClass
 * Signature: WeaponClass * BuildClass(ChargeGunClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall ChargeGunClass::BuildClass(ChargeGunClass *this,long64 param_1)

{
  ChargeGunClass *pCVar1;
  undefined4 unaff_ESI;
  
  pCVar1 = operator_new(0x98);
  if (pCVar1 == (ChargeGunClass *)0x0) {
    pCVar1 = (ChargeGunClass *)0x0;
  }
  else {
    pCVar1 = ChargeGunClass(pCVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (WeaponClass *)pCVar1;
}
