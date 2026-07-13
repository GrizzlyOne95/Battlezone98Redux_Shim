/*
 * Entry: 0045ef66
 * Name: GetTarget
 * Namespace: Global
 * Signature: int GetTarget(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetTarget(int param_1)

{
  GameObject *pGVar1;
  int iVar2;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 != (GameObject *)0x0) {
    pGVar1 = GameObject::GetObj(pGVar1->targetHandle);
    if (pGVar1 != (GameObject *)0x0) {
      iVar2 = GameObject::GetHandle(pGVar1);
      return iVar2;
    }
  }
  return 0;
}
