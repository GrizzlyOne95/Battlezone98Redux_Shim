/*
 * Entry: 0052ac47
 * Name: BeamGunClass::BuildClass
 * Namespace: BeamGunClass
 * Signature: WeaponClass * BuildClass(BeamGunClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall BeamGunClass::BuildClass(BeamGunClass *this,long64 param_1)

{
  BeamGunClass *pBVar1;
  undefined4 unaff_ESI;
  
  pBVar1 = operator_new(0x80);
  if (pBVar1 == (BeamGunClass *)0x0) {
    pBVar1 = (BeamGunClass *)0x0;
  }
  else {
    pBVar1 = BeamGunClass(pBVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (WeaponClass *)pBVar1;
}
