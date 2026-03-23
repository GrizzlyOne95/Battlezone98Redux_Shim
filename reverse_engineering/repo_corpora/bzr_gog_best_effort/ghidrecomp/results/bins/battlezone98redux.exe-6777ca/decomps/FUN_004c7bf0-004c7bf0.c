
void FUN_004c7bf0(undefined4 param_1)

{
  short sVar1;
  int iVar2;
  ushort *puVar3;
  undefined2 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (DAT_009454ac != 0) {
    FUN_004c6ee0(&local_18,&local_14,param_1);
    iVar5 = local_18 - *(int *)(local_8 + 0xec) / 2;
    iVar2 = iVar5 + *(int *)(local_8 + 0xec);
    iVar7 = local_14 - *(int *)(local_8 + 0xf0) / 2;
    iVar6 = iVar7 + *(int *)(local_8 + 0xf0);
    local_c = 0;
    for (local_14 = iVar7; local_14 <= iVar6; local_14 = local_14 + 1) {
      local_10 = 0;
      for (local_18 = iVar5; local_18 <= iVar2; local_18 = local_18 + 1) {
        puVar3 = (ushort *)FUN_00492d60(local_18,local_14);
        *(ushort *)(local_8 + 0x1c468 + local_c * 0x80 + local_10 * 2) = *puVar3 & 0xfff;
        local_10 = local_10 + 1;
      }
      local_c = local_c + 1;
    }
    local_c = 0;
    for (local_14 = iVar7; local_14 <= iVar6; local_14 = local_14 + 1) {
      local_10 = 0;
      for (local_18 = iVar5; local_18 <= iVar2; local_18 = local_18 + 1) {
        puVar4 = (undefined2 *)FUN_004c0fe0(local_18,local_14);
        *(undefined2 *)(local_8 + 0x1e468 + local_c * 0x80 + local_10 * 2) = *puVar4;
        local_10 = local_10 + 1;
      }
      local_c = local_c + 1;
    }
    sVar1 = *(short *)(local_8 + 0x1c468);
    for (local_c = 0; local_c <= *(int *)(local_8 + 0xf0); local_c = local_c + 1) {
      if (*(short *)(local_8 + 0x1c468 + local_c * 0x80) < sVar1) {
        sVar1 = *(short *)(local_8 + 0x1c468 + local_c * 0x80);
      }
      if (*(short *)(local_8 + 0x1c468 + local_c * 0x80 + *(int *)(local_8 + 0xec) * 2) < sVar1) {
        sVar1 = *(short *)(local_8 + 0x1c468 + local_c * 0x80 + *(int *)(local_8 + 0xec) * 2);
      }
    }
    for (local_10 = 0; local_10 <= *(int *)(local_8 + 0xec); local_10 = local_10 + 1) {
      if (*(short *)(local_8 + 0x1c468 + local_10 * 2) < sVar1) {
        sVar1 = *(short *)(local_8 + 0x1c468 + local_10 * 2);
      }
      if (*(short *)(local_8 + 0x1c468 + *(int *)(local_8 + 0xf0) * 0x80 + local_10 * 2) < sVar1) {
        sVar1 = *(short *)(local_8 + 0x1c468 + *(int *)(local_8 + 0xf0) * 0x80 + local_10 * 2);
      }
    }
    for (local_c = 0; local_c <= *(int *)(local_8 + 0xf0); local_c = local_c + 1) {
      for (local_10 = 0; local_10 <= *(int *)(local_8 + 0xec); local_10 = local_10 + 1) {
        *(short *)(local_8 + 0x1c468 + local_c * 0x80 + local_10 * 2) =
             *(short *)(local_8 + 0x1c468 + local_c * 0x80 + local_10 * 2) - sVar1;
      }
    }
    *(undefined4 *)(local_8 + 0x1c460) = *(undefined4 *)(local_8 + 0xec);
    *(undefined4 *)(local_8 + 0x1c464) = *(undefined4 *)(local_8 + 0xf0);
  }
  return;
}

