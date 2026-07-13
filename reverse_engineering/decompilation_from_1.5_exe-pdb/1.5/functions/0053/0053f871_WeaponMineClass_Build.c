/*
 * Entry: 0053f871
 * Name: WeaponMineClass::Build
 * Namespace: WeaponMineClass
 * Signature: GameObject * Build(WeaponMineClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall WeaponMineClass::Build(WeaponMineClass *this,_OBJ76 *param_1)

{
  WeaponMine *pWVar1;
  
  pWVar1 = GameObject::operator_new(0x240);
  if (pWVar1 == (WeaponMine *)0x0) {
    pWVar1 = (WeaponMine *)0x0;
  }
  else {
    pWVar1 = WeaponMine::WeaponMine(pWVar1,param_1,this);
  }
  return (GameObject *)pWVar1;
}
