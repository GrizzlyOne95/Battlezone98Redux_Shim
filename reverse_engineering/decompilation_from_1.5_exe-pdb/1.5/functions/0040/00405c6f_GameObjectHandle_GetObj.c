/*
 * Entry: 00405c6f
 * Name: GameObjectHandle::GetObj
 * Namespace: GameObjectHandle
 * Signature: GameObject * GetObj(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl GameObjectHandle::GetObj(int param_1)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObject::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    return (GameObject *)0x0;
  }
  return (GameObject *)(~-(uint)((pGVar1->obj->flags & 0x200) != 0) & (uint)pGVar1);
}
