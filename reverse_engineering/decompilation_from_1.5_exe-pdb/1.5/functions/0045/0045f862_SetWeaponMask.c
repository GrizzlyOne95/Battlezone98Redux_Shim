/*
 * Entry: 0045f862
 * Name: SetWeaponMask
 * Namespace: Global
 * Signature: void SetWeaponMask(int param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetWeaponMask(int param_1,long param_2)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 != (GameObject *)0x0) {
    pGVar1->weaponMask = param_2;
  }
  return;
}
