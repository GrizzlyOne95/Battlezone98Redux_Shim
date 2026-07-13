/*
 * Entry: 005b9b90
 * Name: currentpc
 * Namespace: Global
 * Signature: int currentpc(lua_State * param_1, CallInfo * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl currentpc(lua_State *param_1,CallInfo *param_2)

{
  int *piVar1;
  int in_EAX;
  int in_EDX;
  
  piVar1 = *(int **)(in_EAX + 4);
  if ((piVar1[2] == 6) && (*(char *)(*piVar1 + 6) == '\0')) {
    if (in_EAX == *(int *)(in_EDX + 0x14)) {
      *(undefined4 *)(in_EAX + 0xc) = *(undefined4 *)(in_EDX + 0x18);
    }
    return (*(int *)(in_EAX + 0xc) - *(int *)(*(int *)(*piVar1 + 0x10) + 0xc) >> 2) + -1;
  }
  return -1;
}
