/*
 * Entry: 0040def9
 * Name: GameObjectHandle::Find
 * Namespace: GameObjectHandle
 * Signature: int Find(GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GameObjectHandle::Find(GameObject *param_1)

{
  int iVar1;
  
  if (param_1 == (GameObject *)0x0) {
    return 0;
  }
  iVar1 = GameObject::GetHandle(param_1);
  return iVar1;
}
