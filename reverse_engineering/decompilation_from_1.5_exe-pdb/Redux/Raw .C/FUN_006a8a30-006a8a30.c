
void FUN_006a8a30(int param_1)

{
  int iVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  local_c = 0;
  *(undefined4 *)(param_1 + 4) = 0xffffffff;
  *(undefined4 *)(param_1 + 8) = 0xffffffff;
  if (*(int *)(param_1 + 0x14) != 0) {
    for (local_10 = 0; local_10 < *(int *)(param_1 + 0x14); local_10 = local_10 + 1) {
      iVar1 = FUN_0069d590(param_1 + 0xc,local_10);
      local_8 = local_8 + *(int *)(iVar1 + 0x14);
      local_c = local_c + *(int *)(iVar1 + 0x18);
    }
    *(int *)(param_1 + 4) = local_8 / *(int *)(param_1 + 0x14);
    *(int *)(param_1 + 8) = local_c / *(int *)(param_1 + 0x14);
  }
  return;
}

