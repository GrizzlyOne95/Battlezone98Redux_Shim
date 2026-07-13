/*
 * Entry: 004b94e7
 * Name: WeaponPowerupClass::Build
 * Namespace: WeaponPowerupClass
 * Signature: GameObject * Build(WeaponPowerupClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall WeaponPowerupClass::Build(WeaponPowerupClass *this,_OBJ76 *param_1)

{
  WeaponPowerup *pWVar1;
  
  pWVar1 = GameObject::operator_new(0x228);
  if (pWVar1 == (WeaponPowerup *)0x0) {
    pWVar1 = (WeaponPowerup *)0x0;
  }
  else {
    pWVar1 = WeaponPowerup::WeaponPowerup(pWVar1,param_1,this);
  }
  return (GameObject *)pWVar1;
}
