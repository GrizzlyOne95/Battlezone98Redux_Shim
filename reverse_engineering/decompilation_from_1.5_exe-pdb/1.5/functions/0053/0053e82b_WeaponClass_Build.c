/*
 * Entry: 0053e82b
 * Name: WeaponClass::Build
 * Namespace: WeaponClass
 * Signature: Weapon * Build(WeaponClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall WeaponClass::Build(WeaponClass *this,_OBJ76 *param_1)

{
  Weapon *pWVar1;
  
  pWVar1 = operator_new(0xa8);
  if (pWVar1 == (Weapon *)0x0) {
    pWVar1 = (Weapon *)0x0;
  }
  else {
    pWVar1 = Weapon::Weapon(pWVar1,param_1,this);
  }
  return pWVar1;
}
