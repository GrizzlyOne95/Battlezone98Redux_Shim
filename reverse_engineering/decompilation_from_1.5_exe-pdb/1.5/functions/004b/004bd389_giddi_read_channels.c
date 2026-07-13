/*
 * Entry: 004bd389
 * Name: giddi_read_channels
 * Namespace: Global
 * Signature: int giddi_read_channels(void * param_1, long * param_2, long * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl giddi_read_channels(void *param_1,long *param_2,long *param_3)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  
  if (param_3 != (long *)0x0) {
    iVar3 = 0;
    do {
      puVar1 = (uint *)((int)discreteSetMap + iVar3);
      *(uint *)((int)(param_3 + -0x2c693f) + (int)puVar1) = *puVar1;
      uVar2 = *(uint *)((int)discreteClrMap + iVar3);
      *(uint *)((int)discreteClrMap + iVar3) = 0;
      *puVar1 = *puVar1 & ~uVar2;
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x10);
  }
  return 0;
}
