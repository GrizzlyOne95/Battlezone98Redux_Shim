/*
 * Entry: 00528e87
 * Name: fentry_compare1
 * Namespace: Global
 * Signature: int fentry_compare1(void * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl fentry_compare1(void *param_1,void *param_2)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  bool bVar5;
  
  pbVar2 = param_1;
  pbVar4 = param_2;
  do {
    bVar1 = *pbVar2;
    bVar5 = bVar1 < *pbVar4;
    if (bVar1 != *pbVar4) {
LAB_00528eb3:
      iVar3 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
      goto LAB_00528eb8;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar2[1];
    bVar5 = bVar1 < pbVar4[1];
    if (bVar1 != pbVar4[1]) goto LAB_00528eb3;
    pbVar2 = pbVar2 + 2;
    pbVar4 = pbVar4 + 2;
  } while (bVar1 != 0);
  iVar3 = 0;
LAB_00528eb8:
  if (iVar3 == 0) {
    if (*(uint *)((int)param_2 + 0x10) < *(uint *)((int)param_1 + 0x10)) {
      iVar3 = 1;
    }
    else {
      iVar3 = -(uint)(*(uint *)((int)param_1 + 0x10) < *(uint *)((int)param_2 + 0x10));
    }
  }
  return iVar3;
}
