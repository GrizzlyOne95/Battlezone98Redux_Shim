
void FUN_006a1bc0(undefined4 *param_1,char param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_14;
  int local_10;
  int local_c;
  
  iVar3 = FUN_0046f5c0(*param_1,param_2);
  if (iVar3 != 0) {
    if (param_2 == '\0') {
      local_14 = 0;
    }
    else {
      local_14 = FUN_0046f600(*param_1);
    }
    for (local_c = 0; local_c < DAT_02c00a94; local_c = local_c + 1) {
      for (local_10 = 0; local_10 < DAT_02c00ed8; local_10 = local_10 + 1) {
        iVar1 = *(int *)(*(int *)(param_1[0x20] + local_c * 4) + local_10 * 4);
        iVar2 = *(int *)(iVar3 + (local_c * DAT_02c00ed8 + local_10) * 4);
        if (param_2 == '\0') {
          if (iVar2 != 0) {
            *(undefined4 *)(iVar1 + 0x68) = 0xc4653600;
            *(undefined4 *)(iVar1 + 0x6c) = 0;
            *(undefined4 *)(iVar1 + 0x70) = 0;
            *(undefined4 *)(iVar1 + 0x50) = 0;
            *(undefined4 *)(iVar1 + 0x54) = 0;
            *(undefined4 *)(iVar1 + 100) = 0;
            *(undefined4 *)(iVar1 + 0x60) = 0;
            *(undefined4 *)(iVar1 + 0x48) = 0;
          }
        }
        else {
          *(int *)(iVar1 + 0x68) = *(int *)(iVar1 + 0x68) + iVar2;
          *(undefined4 *)(iVar1 + 0x6c) =
               *(undefined4 *)(local_14 + (local_c * DAT_02c00ed8 + local_10) * 4);
          *(undefined4 *)(iVar1 + 0x70) =
               *(undefined4 *)(local_14 + (local_c * DAT_02c00ed8 + local_10) * 4);
        }
      }
    }
  }
  return;
}

