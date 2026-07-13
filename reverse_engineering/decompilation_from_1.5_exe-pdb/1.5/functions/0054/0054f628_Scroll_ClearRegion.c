/*
 * Entry: 0054f628
 * Name: Scroll_ClearRegion
 * Namespace: Global
 * Signature: void Scroll_ClearRegion(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scroll_ClearRegion(void *param_1)

{
  int iVar1;
  
  iVar1 = *(int *)((int)param_1 + 8);
  memset(*(undefined4 *)(iVar1 + 0x28),0,(*(int *)(iVar1 + 0x10) + 5) * 0x58);
  *(undefined4 *)(iVar1 + 0x1c) = 0;
  if ((*(uint *)(iVar1 + 0x60) & 8) == 0) {
    *(undefined4 *)(iVar1 + 0x20) = *(undefined4 *)(iVar1 + 0x10);
  }
  else {
    *(undefined4 *)(iVar1 + 0x20) = 0;
  }
  *(uint *)(iVar1 + 0x60) = *(uint *)(iVar1 + 0x60) | 0x80000000;
  return;
}
