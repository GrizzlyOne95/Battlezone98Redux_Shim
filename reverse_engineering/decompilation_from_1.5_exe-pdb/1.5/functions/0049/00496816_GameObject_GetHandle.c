/*
 * Entry: 00496816
 * Name: GameObject_GetHandle
 * Namespace: Global
 * Signature: int GameObject_GetHandle(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GameObject_GetHandle(_OBJ76 *param_1)

{
  int iVar1;
  
  if (param_1 == (_OBJ76 *)0x0) {
    return 0;
  }
  iVar1 = GameObject::GetHandle(param_1->gameObj);
  return iVar1;
}
