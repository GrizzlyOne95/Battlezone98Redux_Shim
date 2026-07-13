/*
 * Entry: 005c88c0
 * Name: ogg_stream_pagein
 * Namespace: Global
 * Signature: undefined ogg_stream_pagein()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_stream_pagein */

undefined4 __cdecl ogg_stream_pagein(int *param_1,int *param_2)

{
  int *piVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  uint *puVar12;
  byte bVar13;
  undefined8 uVar14;
  int local_20;
  int local_1c;
  
  local_1c = param_2[2];
  iVar10 = param_2[3];
  iVar4 = *param_2;
  cVar2 = *(char *)(iVar4 + 4);
  bVar3 = *(byte *)(iVar4 + 5);
  bVar13 = bVar3 & 2;
  local_20 = 0;
  uVar14 = ogg_page_granulepos(param_2);
  uVar11 = (uint)*(byte *)(iVar4 + 0x1a);
  iVar8 = *(int *)(iVar4 + 0xe);
  iVar7 = *(int *)(iVar4 + 0x12);
  if (param_1 == (int *)0x0) {
    return 0xffffffff;
  }
  if (*param_1 == 0) {
    return 0xffffffff;
  }
  iVar5 = param_1[3];
  iVar6 = param_1[9];
  if (iVar5 != 0) {
    piVar1 = param_1 + 2;
    *piVar1 = *piVar1 - iVar5;
    if (*piVar1 != 0) {
      memmove((void *)*param_1,(void *)(*param_1 + iVar5),param_1[2]);
    }
    param_1[3] = 0;
  }
  if (iVar6 != 0) {
    if (param_1[7] - iVar6 != 0) {
      memmove((void *)param_1[4],(void *)(param_1[4] + iVar6 * 4),(param_1[7] - iVar6) * 4);
      memmove((void *)param_1[5],(void *)(param_1[5] + iVar6 * 8),(param_1[7] - iVar6) * 8);
    }
    param_1[7] = param_1[7] - iVar6;
    param_1[8] = param_1[8] - iVar6;
    param_1[9] = 0;
  }
  if (iVar8 != param_1[0x54]) {
    return 0xffffffff;
  }
  if (cVar2 != '\0') {
    return 0xffffffff;
  }
  iVar8 = FUN_005c7ee0();
  if (iVar8 != 0) {
    return 0xffffffff;
  }
  if (iVar7 != param_1[0x55]) {
    iVar8 = param_1[8];
    if (iVar8 < param_1[7]) {
      puVar12 = (uint *)(param_1[4] + iVar8 * 4);
      do {
        param_1[2] = param_1[2] - (*puVar12 & 0xff);
        iVar8 = iVar8 + 1;
        puVar12 = puVar12 + 1;
      } while (iVar8 < param_1[7]);
      iVar8 = param_1[8];
    }
    param_1[7] = iVar8;
    if (param_1[0x55] != -1) {
      *(undefined4 *)(param_1[4] + iVar8 * 4) = 0x400;
      param_1[7] = param_1[7] + 1;
      param_1[8] = param_1[8] + 1;
    }
  }
  param_2 = (int *)iVar10;
  if (((bVar3 & 1) == 0) ||
     (((0 < param_1[7] && (*(int *)(param_1[4] + -4 + param_1[7] * 4) != 0x400)) ||
      (bVar13 = 0, uVar11 == 0)))) {
    local_20 = 0;
  }
  else {
    do {
      uVar9 = (uint)*(byte *)(iVar4 + 0x1b + local_20);
      local_1c = local_1c + uVar9;
      param_2 = (int *)((int)param_2 - uVar9);
      local_20 = local_20 + 1;
      if (uVar9 < 0xff) break;
    } while (local_20 < (int)uVar11);
  }
  if (param_2 != (int *)0x0) {
    iVar10 = FUN_005c7e80();
    if (iVar10 != 0) {
      return 0xffffffff;
    }
    memcpy(param_1[2] + *param_1,local_1c,param_2);
    param_1[2] = param_1[2] + (int)param_2;
  }
  param_2 = (int *)0xffffffff;
  if (local_20 < (int)uVar11) {
    do {
      uVar9 = (uint)*(byte *)(iVar4 + 0x1b + local_20);
      *(uint *)(param_1[4] + param_1[7] * 4) = uVar9;
      iVar10 = param_1[5];
      iVar8 = param_1[7];
      *(undefined4 *)(iVar10 + iVar8 * 8) = 0xffffffff;
      *(undefined4 *)(iVar10 + 4 + iVar8 * 8) = 0xffffffff;
      if (bVar13 != 0) {
        puVar12 = (uint *)(param_1[4] + param_1[7] * 4);
        *puVar12 = *puVar12 | 0x100;
        bVar13 = 0;
      }
      if (uVar9 < 0xff) {
        param_2 = (int *)param_1[7];
      }
      param_1[7] = param_1[7] + 1;
      local_20 = local_20 + 1;
      if (uVar9 < 0xff) {
        param_1[8] = param_1[7];
      }
    } while (local_20 < (int)uVar11);
    if (param_2 != (int *)0xffffffff) {
      iVar10 = param_1[5];
      *(int *)(iVar10 + (int)param_2 * 8) = (int)uVar14;
      *(int *)(iVar10 + 4 + (int)param_2 * 8) = (int)((ulonglong)uVar14 >> 0x20);
    }
  }
  if ((bVar3 & 4) != 0) {
    param_1[0x52] = 1;
    if (0 < param_1[7]) {
      puVar12 = (uint *)(param_1[4] + -4 + param_1[7] * 4);
      *puVar12 = *puVar12 | 0x200;
    }
  }
  param_1[0x55] = iVar7 + 1;
  return 0;
}
