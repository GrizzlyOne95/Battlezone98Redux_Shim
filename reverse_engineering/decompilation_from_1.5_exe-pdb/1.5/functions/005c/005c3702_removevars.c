/*
 * Entry: 005c3702
 * Name: removevars
 * Namespace: Global
 * Signature: void removevars(LexState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl removevars(LexState *param_1,int param_2)

{
  byte bVar1;
  int *piVar2;
  int in_EAX;
  
  piVar2 = *(int **)(in_EAX + 0x30);
  bVar1 = *(byte *)((int)piVar2 + 0x32);
  while ((int)param_1 < (int)(uint)bVar1) {
    *(char *)((int)piVar2 + 0x32) = *(char *)((int)piVar2 + 0x32) + -1;
    *(int *)((uint)*(ushort *)((int)piVar2 + (uint)*(byte *)((int)piVar2 + 0x32) * 2 + 0xac) * 0xc +
             8 + *(int *)(*piVar2 + 0x18)) = piVar2[6];
    bVar1 = *(byte *)((int)piVar2 + 0x32);
  }
  return;
}
