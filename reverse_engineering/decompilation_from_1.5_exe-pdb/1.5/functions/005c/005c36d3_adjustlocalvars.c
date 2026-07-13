/*
 * Entry: 005c36d3
 * Name: adjustlocalvars
 * Namespace: Global
 * Signature: void adjustlocalvars(LexState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl adjustlocalvars(LexState *param_1,int param_2)

{
  int *piVar1;
  int in_EAX;
  int in_ECX;
  
  piVar1 = *(int **)(in_EAX + 0x30);
  *(char *)((int)piVar1 + 0x32) = *(char *)((int)piVar1 + 0x32) + (char)in_ECX;
  for (; in_ECX != 0; in_ECX = in_ECX + -1) {
    *(int *)((uint)*(ushort *)
                    ((int)piVar1 + ((uint)*(byte *)((int)piVar1 + 0x32) - in_ECX) * 2 + 0xac) * 0xc
             + 4 + *(int *)(*piVar1 + 0x18)) = piVar1[6];
  }
  return;
}
