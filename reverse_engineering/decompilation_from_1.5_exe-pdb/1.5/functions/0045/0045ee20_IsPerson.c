/*
 * Entry: 0045ee20
 * Name: IsPerson
 * Namespace: Global
 * Signature: bool IsPerson(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsPerson(int param_1)

{
  GameObject *pGVar1;
  int iVar2;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    return false;
  }
  iVar2 = (**(code **)(pGVar1->_padding_ + 0x30))();
  return *(int *)(iVar2 + 0xac) == 4;
}
