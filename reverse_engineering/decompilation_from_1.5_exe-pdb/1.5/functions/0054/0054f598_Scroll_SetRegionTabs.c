/*
 * Entry: 0054f598
 * Name: Scroll_SetRegionTabs
 * Namespace: Global
 * Signature: void Scroll_SetRegionTabs(void * param_1, int param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scroll_SetRegionTabs(void *param_1,int param_2,int *param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = *(int *)((int)param_1 + 8);
  iVar3 = 0;
  *(int *)(iVar1 + 0x34) = param_2;
  if (0 < param_2) {
    piVar2 = (int *)(iVar1 + 0x38);
    do {
      *piVar2 = param_3[iVar3];
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar3 < param_2);
  }
  return;
}
