/*
 * Entry: 00496888
 * Name: GameObject_IsVisibleToUser
 * Namespace: Global
 * Signature: int GameObject_IsVisibleToUser(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GameObject_IsVisibleToUser(_OBJ76 *param_1)

{
  void *pvVar1;
  
  if (param_1 == (_OBJ76 *)0x0) {
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = param_1->gameObj;
  }
  if ((pvVar1 != (void *)0x0) && (0.0 < *(float *)((int)pvVar1 + 0xdc))) {
    return 1;
  }
  return 0;
}
