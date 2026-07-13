/*
 * Entry: 004607cf
 * Name: AddHealth
 * Namespace: Global
 * Signature: void AddHealth(int param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AddHealth(int param_1,float param_2)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 != (GameObject *)0x0) {
    (**(code **)(pGVar1->_padding_ + 0x28))(param_2);
  }
  return;
}
