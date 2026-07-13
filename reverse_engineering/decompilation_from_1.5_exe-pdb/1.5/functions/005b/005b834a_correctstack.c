/*
 * Entry: 005b834a
 * Name: correctstack
 * Namespace: Global
 * Signature: void correctstack(lua_State * param_1, lua_TValue * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl correctstack(lua_State *param_1,lua_TValue *param_2)

{
  int in_EAX;
  undefined4 *puVar1;
  int *piVar2;
  int in_EDX;
  
  *(int *)(in_EAX + 8) = (*(int *)(in_EAX + 8) - in_EDX >> 4) * 0x10 + *(int *)(in_EAX + 0x20);
  for (puVar1 = *(undefined4 **)(in_EAX + 0x68); puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)*puVar1) {
    puVar1[2] = (puVar1[2] - in_EDX >> 4) * 0x10 + *(int *)(in_EAX + 0x20);
  }
  for (piVar2 = *(int **)(in_EAX + 0x28); piVar2 <= *(int **)(in_EAX + 0x14); piVar2 = piVar2 + 6) {
    piVar2[2] = (piVar2[2] - in_EDX >> 4) * 0x10 + *(int *)(in_EAX + 0x20);
    *piVar2 = (*piVar2 - in_EDX >> 4) * 0x10 + *(int *)(in_EAX + 0x20);
    piVar2[1] = (piVar2[1] - in_EDX >> 4) * 0x10 + *(int *)(in_EAX + 0x20);
  }
  *(int *)(in_EAX + 0xc) = (*(int *)(in_EAX + 0xc) - in_EDX >> 4) * 0x10 + *(int *)(in_EAX + 0x20);
  return;
}
