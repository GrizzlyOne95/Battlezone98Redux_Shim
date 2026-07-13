/*
 * Entry: 00460860
 * Name: AddAmmo
 * Namespace: Global
 * Signature: void AddAmmo(int param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AddAmmo(int param_1,long param_2)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 != (GameObject *)0x0) {
    (**(code **)(pGVar1->_padding_ + 0x18))(param_2);
  }
  return;
}
