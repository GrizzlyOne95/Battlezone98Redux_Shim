/*
 * Entry: 005c3863
 * Name: markupval
 * Namespace: Global
 * Signature: void markupval(FuncState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl markupval(FuncState *param_1,int param_2)

{
  int in_EAX;
  int *piVar1;
  
  piVar1 = *(int **)(in_EAX + 0x14);
  if (piVar1 != (int *)0x0) {
    do {
      if ((int)(uint)*(byte *)(piVar1 + 2) <= (int)param_1) break;
      piVar1 = (int *)*piVar1;
    } while (piVar1 != (int *)0x0);
    if (piVar1 != (int *)0x0) {
      *(undefined1 *)((int)piVar1 + 9) = 1;
    }
  }
  return;
}
