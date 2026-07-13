/*
 * Entry: 004606eb
 * Name: HoppedOutOf
 * Namespace: Global
 * Signature: int HoppedOutOf(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl HoppedOutOf(int param_1)

{
  GameObject *pGVar1;
  _OBJ76 *p_Var2;
  int iVar3;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    return 0;
  }
  p_Var2 = (_OBJ76 *)(**(code **)(pGVar1->_padding_ + 0x30))();
  iVar3 = IsCraft(p_Var2);
  if ((iVar3 == 0) &&
     (iVar3 = (**(code **)(pGVar1->_padding_ + 0x30))(), *(int *)(iVar3 + 0xac) != 4)) {
    return 0;
  }
  pGVar1 = GameObjectHandle::GetObj(pGVar1[1]._padding_);
  if (pGVar1 == (GameObject *)0x0) {
    return 0;
  }
  iVar3 = GameObject::GetHandle(pGVar1);
  return iVar3;
}
