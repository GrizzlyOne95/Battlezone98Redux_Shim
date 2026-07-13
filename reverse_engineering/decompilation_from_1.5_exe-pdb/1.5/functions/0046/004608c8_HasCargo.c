/*
 * Entry: 004608c8
 * Name: HasCargo
 * Namespace: Global
 * Signature: bool HasCargo(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl HasCargo(int param_1)

{
  GameObject *pGVar1;
  int iVar2;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 != (GameObject *)0x0) {
    iVar2 = (**(code **)pGVar1->_padding_)();
    if (*(int *)(iVar2 + 0x20) == 0x54554700) {
      return pGVar1[1].hitOrdClass != (OrdnanceClass *)0x0;
    }
  }
  return false;
}
