/*
 * Entry: 004608fa
 * Name: GetTug
 * Namespace: Global
 * Signature: int GetTug(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetTug(int param_1)

{
  GameObject *pGVar1;
  int iVar2;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if ((pGVar1 != (GameObject *)0x0) && (pGVar1->tug != (GameObject *)0x0)) {
    iVar2 = GameObject::GetHandle(pGVar1->tug);
    return iVar2;
  }
  return 0;
}
