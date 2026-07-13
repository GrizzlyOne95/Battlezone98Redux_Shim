/*
 * Entry: 004b950d
 * Name: WeaponPowerupClass::BuildClass
 * Namespace: WeaponPowerupClass
 * Signature: GameObjectClass * BuildClass(WeaponPowerupClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall WeaponPowerupClass::BuildClass(WeaponPowerupClass *this,long64 param_1)

{
  WeaponPowerupClass *pWVar1;
  undefined4 unaff_ESI;
  
  pWVar1 = operator_new(0x178);
  if (pWVar1 == (WeaponPowerupClass *)0x0) {
    pWVar1 = (WeaponPowerupClass *)0x0;
  }
  else {
    pWVar1 = WeaponPowerupClass(pWVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pWVar1;
}
