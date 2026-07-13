/*
 * Entry: 005c5d1c
 * Name: freereg
 * Namespace: Global
 * Signature: void freereg(FuncState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl freereg(FuncState *param_1,int param_2)

{
  int in_EAX;
  
  if ((((uint)param_1 & 0x100) == 0) && ((int)(uint)*(byte *)(in_EAX + 0x32) <= (int)param_1)) {
    *(int *)(in_EAX + 0x24) = *(int *)(in_EAX + 0x24) + -1;
  }
  return;
}
