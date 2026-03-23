
void FUN_005cb2d0(byte *param_1,int param_2)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  bool bVar4;
  uint local_20;
  byte *local_1c;
  byte *local_18;
  byte *local_14;
  byte *local_10;
  int local_c;
  
  if (param_1 == (byte *)0x0) {
    *(undefined4 *)(&DAT_02a13d20 + param_2 * 4) = 0xffffffff;
    FUN_006a3840(param_2,0);
  }
  else {
    for (local_c = 0; local_c < DAT_02a13d84; local_c = local_c + 1) {
      local_14 = (byte *)FUN_005ce740(local_c);
      local_10 = param_1;
      do {
        bVar1 = *local_10;
        bVar4 = bVar1 < *local_14;
        if (bVar1 != *local_14) {
LAB_005cb36f:
          local_20 = -(uint)bVar4 | 1;
          goto LAB_005cb377;
        }
        if (bVar1 == 0) break;
        bVar1 = local_10[1];
        bVar4 = bVar1 < local_14[1];
        if (bVar1 != local_14[1]) goto LAB_005cb36f;
        local_10 = local_10 + 2;
        local_14 = local_14 + 2;
      } while (bVar1 != 0);
      local_20 = 0;
LAB_005cb377:
      if (local_20 == 0) break;
    }
    if (local_c == DAT_02a13d84) {
      local_1c = param_1;
      local_18 = (byte *)FUN_005ce740(local_c);
      do {
        bVar1 = *local_1c;
        *local_18 = bVar1;
        local_1c = local_1c + 1;
        local_18 = local_18 + 1;
      } while (bVar1 != 0);
      uVar2 = FUN_006a37a0(0xffffffff,param_1);
      iVar3 = FUN_005ce740(local_c);
      *(undefined4 *)(iVar3 + 0x10) = uVar2;
      iVar3 = FUN_005ce740(local_c);
      if (*(int *)(iVar3 + 0x10) == 0) {
        FUN_007d6830("Could not load AIP \"%s\"",param_1);
      }
      DAT_02a13d84 = DAT_02a13d84 + 1;
    }
    iVar3 = FUN_005ce740(local_c);
    if (*(int *)(iVar3 + 0x10) != 0) {
      FUN_006a3840(param_2,*(int *)(iVar3 + 0x10));
      *(int *)(&DAT_02a13d20 + param_2 * 4) = local_c;
    }
  }
  return;
}

