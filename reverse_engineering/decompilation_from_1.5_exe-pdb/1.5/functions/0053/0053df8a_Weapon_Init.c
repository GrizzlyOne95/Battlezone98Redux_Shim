/*
 * Entry: 0053df8a
 * Name: Weapon::Init
 * Namespace: Weapon
 * Signature: void Init(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Weapon::Init(_OBJ76 *param_1)

{
  WeaponClass *pWVar1;
  
  pWVar1 = WeaponClass::Find(param_1->id);
  (**(code **)(pWVar1->_padding_ + 8))(param_1);
  return;
}
