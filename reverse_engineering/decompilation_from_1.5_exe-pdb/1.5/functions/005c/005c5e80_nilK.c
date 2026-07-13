/*
 * Entry: 005c5e80
 * Name: nilK
 * Namespace: Global
 * Signature: int nilK(FuncState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl nilK(FuncState *param_1)

{
  int in_EAX;
  int iVar1;
  undefined4 in_stack_ffffffdc;
  Proto *local_14;
  FuncState *local_c;
  
  local_14 = *(Proto **)(in_EAX + 4);
  local_c = (FuncState *)0x5;
  iVar1 = addk((FuncState *)&local_14,(lua_TValue *)&stack0xffffffdc,(lua_TValue *)in_stack_ffffffdc
              );
  return iVar1;
}
