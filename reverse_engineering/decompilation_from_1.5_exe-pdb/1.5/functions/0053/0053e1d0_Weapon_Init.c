/*
 * Entry: 0053e1d0
 * Name: Weapon_Init
 * Namespace: Global
 * Signature: void Weapon_Init(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Weapon_Init(_OBJ76 *param_1)

{
  WeaponClass *pWVar1;
  
  pWVar1 = WeaponClass::Find(param_1->id);
  (**(code **)(pWVar1->_padding_ + 8))(param_1);
  return;
}
