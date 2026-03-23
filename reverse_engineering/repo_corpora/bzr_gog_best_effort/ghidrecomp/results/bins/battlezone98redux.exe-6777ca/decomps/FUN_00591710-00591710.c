
void FUN_00591710(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined4 *puVar7;
  int iVar8;
  int local_2c;
  int local_28;
  int local_24;
  float *local_18;
  int local_14;
  short *local_10;
  int local_c;
  char *local_8;
  
  if ((((-1 < param_1) && (param_1 <= DAT_02a13cb8)) && (-1 < param_2)) &&
     ((param_2 <= DAT_02a13c84 &&
      (local_8 = (char *)((param_1 * DAT_02a13c70 + param_2) * 0x118 + DAT_0091814c),
      *local_8 == '\0')))) {
    iVar2 = param_2 * 0x10 + DAT_02ce99c0;
    iVar8 = param_1 * 0x10 + DAT_02cd9984;
    iVar3 = iVar8 + 0x10;
    DAT_02a13c88 = (iVar3 - iVar8) * 2;
    DAT_02a13c98 = 0;
    DAT_02a13ca8 = (void *)FUN_0083d92c(-(uint)((int)((ulonglong)DAT_02a13c88 * 4 >> 0x20) != 0) |
                                        (uint)((ulonglong)DAT_02a13c88 * 4),(iVar2 + 0x10) - iVar2);
    for (local_14 = iVar2; iVar1 = iVar8, local_14 < iVar2 + 0x10; local_14 = local_14 + 1) {
      while (local_c = iVar1, iVar1 = local_c, local_c < iVar3) {
        iVar4 = FUN_00591690(local_14,local_c);
        do {
          local_c = local_c + 1;
          if (iVar3 <= local_c) break;
          iVar5 = FUN_00591690(local_14,local_c);
        } while (iVar5 == iVar4);
        FUN_00591510(local_14,local_14 + 1,iVar1,local_c,iVar4);
        iVar1 = local_c;
      }
      FUN_00591470(local_14);
    }
    operator_delete__(DAT_02a13ca8);
    piVar6 = (int *)FUN_004200d0(0);
    if (*piVar6 != 0) {
      puVar7 = (undefined4 *)FUN_004200d0(0);
      FUN_0058be60(*puVar7);
      puVar7 = (undefined4 *)FUN_004200d0(0);
      FUN_0058ca30(*puVar7);
      FUN_004cbb80();
    }
    iVar3 = size();
    FUN_004bae50(iVar3 + 4 + DAT_00918194);
    *(int *)(local_8 + 0x10) = iVar2;
    *(int *)(local_8 + 0x14) = iVar8;
    for (local_24 = 0; local_24 < DAT_00918194; local_24 = local_24 + 1) {
      local_10 = (short *)(local_24 * 0xc + DAT_00918138);
      local_18 = (float *)FUN_0058c980(1);
      FUN_0041fe40(&local_18);
      *local_18 = (float)(int)*local_10;
      local_18[2] = (float)(int)local_10[2];
      local_18[1] = (float)(int)local_10[1];
      local_18[3] = (float)(int)local_10[3];
      local_18[4] = (float)(*(uint *)(local_10 + 4) & 0xffff7fff);
      local_18[6] = -NAN;
      *(undefined1 *)(local_18 + 7) = 0;
      for (local_28 = local_10[1] - iVar8; local_28 < local_10[3] - iVar8; local_28 = local_28 + 1)
      {
        for (local_2c = *local_10 - iVar2; local_2c < local_10[2] - iVar2; local_2c = local_2c + 1)
        {
          local_8[local_2c + local_28 * 0x10 + 0x18] = (char)local_24;
        }
      }
    }
    DAT_00918194 = 0;
    *local_8 = '\x01';
  }
  return;
}

