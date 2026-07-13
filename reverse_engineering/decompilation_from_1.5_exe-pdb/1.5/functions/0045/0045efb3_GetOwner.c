/*
 * Entry: 0045efb3
 * Name: GetOwner
 * Namespace: Global
 * Signature: int GetOwner(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetOwner(int param_1)

{
  GameObject *pGVar1;
  int iVar2;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 != (GameObject *)0x0) {
    pGVar1 = GameObject::GetObj(pGVar1->ownerHandle);
    if (pGVar1 != (GameObject *)0x0) {
      iVar2 = GameObject::GetHandle(pGVar1);
      return iVar2;
    }
  }
  return 0;
}
