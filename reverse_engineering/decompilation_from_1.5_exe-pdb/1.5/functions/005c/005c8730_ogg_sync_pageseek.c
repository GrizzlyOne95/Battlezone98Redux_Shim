/*
 * Entry: 005c8730
 * Name: ogg_sync_pageseek
 * Namespace: Global
 * Signature: undefined ogg_sync_pageseek()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_sync_pageseek */

int __cdecl ogg_sync_pageseek(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  int iVar4;
  int *piVar5;
  int *local_10;
  int local_c;
  int local_8;
  int local_4;
  
  piVar5 = (int *)(*param_1 + param_1[3]);
  iVar4 = param_1[2] - param_1[3];
  if (param_1[1] < 0) {
    return 0;
  }
  if (param_1[5] == 0) {
    if (iVar4 < 0x1b) {
      return 0;
    }
    if (*piVar5 != 0x5367674f) goto LAB_005c881c;
    iVar1 = *(byte *)((int)piVar5 + 0x1a) + 0x1b;
    iVar2 = 0;
    if (iVar4 < iVar1) {
      return 0;
    }
    if (*(byte *)((int)piVar5 + 0x1a) != 0) {
      do {
        param_1[6] = param_1[6] + (uint)*(byte *)((int)piVar5 + iVar2 + 0x1b);
        iVar2 = iVar2 + 1;
      } while (iVar2 < (int)(uint)*(byte *)((int)piVar5 + 0x1a));
    }
    param_1[5] = iVar1;
  }
  if (iVar4 < param_1[5] + param_1[6]) {
    return 0;
  }
  iVar1 = *(int *)((int)piVar5 + 0x16);
  *(undefined4 *)((int)piVar5 + 0x16) = 0;
  local_c = param_1[5];
  local_4 = param_1[6];
  local_8 = local_c + (int)piVar5;
  local_10 = piVar5;
  ogg_page_checksum_set(&local_10);
  if (iVar1 == *(int *)((int)piVar5 + 0x16)) {
    iVar4 = *param_1;
    iVar1 = param_1[3];
    if (param_2 != (int *)0x0) {
      *param_2 = iVar4 + iVar1;
      param_2[1] = param_1[5];
      param_2[2] = param_1[5] + iVar4 + iVar1;
      param_2[3] = param_1[6];
    }
    iVar4 = param_1[5];
    iVar1 = param_1[6];
    param_1[3] = param_1[3] + iVar4 + iVar1;
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    return iVar4 + iVar1;
  }
  *(int *)((int)piVar5 + 0x16) = iVar1;
LAB_005c881c:
  param_1[5] = 0;
  param_1[6] = 0;
  pvVar3 = memchr((void *)((int)piVar5 + 1),0x4f,iVar4 - 1);
  if (pvVar3 == (void *)0x0) {
    pvVar3 = (void *)(param_1[2] + *param_1);
  }
  param_1[3] = (int)pvVar3 - *param_1;
  return (int)piVar5 - (int)pvVar3;
}
