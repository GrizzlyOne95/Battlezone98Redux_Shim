
void FUN_0069adb0(int param_1,int *param_2,undefined4 param_3,int param_4,undefined4 param_5,
                 int param_6)

{
  byte bVar1;
  int iVar2;
  bool bVar3;
  uint local_1c;
  byte *local_14;
  byte *local_10;
  int local_c;
  
  iVar2 = FUN_006995a0(param_5,(*param_2 + 1) * 0x50 + param_4);
  *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + param_6;
  *(int *)(iVar2 + 8) = param_6;
  if (*(int *)(param_1 + 8) == 0) {
    *(int *)(param_1 + 8) = iVar2;
  }
  else {
    for (local_c = *(int *)(param_1 + 8); *(int *)(local_c + 0xc) != 0;
        local_c = *(int *)(local_c + 0xc)) {
    }
    *(int *)(local_c + 0xc) = iVar2;
  }
  do {
    local_10 = (byte *)(*param_2 * 0x50 + param_4);
    *param_2 = *param_2 + 1;
    local_14 = &DAT_008949b8;
    do {
      bVar1 = *local_10;
      bVar3 = bVar1 < *local_14;
      if (bVar1 != *local_14) {
LAB_0069ae89:
        local_1c = -(uint)bVar3 | 1;
        goto LAB_0069ae91;
      }
      if (bVar1 == 0) break;
      bVar1 = local_10[1];
      bVar3 = bVar1 < local_14[1];
      if (bVar1 != local_14[1]) goto LAB_0069ae89;
      local_10 = local_10 + 2;
      local_14 = local_14 + 2;
    } while (bVar1 != 0);
    local_1c = 0;
LAB_0069ae91:
    if (local_1c == 0) {
      return;
    }
  } while( true );
}

