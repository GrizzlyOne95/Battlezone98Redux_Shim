
void __thiscall FUN_004a0710(int param_1,int param_2)

{
  int iVar1;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_8;
  
  local_10 = 0;
  for (local_8 = 0; local_8 < *(int *)(param_1 + 0x188); local_8 = local_8 + 1) {
    if (*(int *)(param_1 + 0x1c + local_8 * 4) == param_2) {
      iVar1 = FUN_004da060(param_2);
      if (iVar1 != 0) {
        FUN_0049f3c0(0);
      }
      *(undefined4 *)(param_1 + 0x117c) = 0xffffffff;
      *(undefined4 *)(param_1 + 0x1188) = 0;
    }
    else {
      *(undefined4 *)(param_1 + 0x1c + local_10 * 4) = *(undefined4 *)(param_1 + 0x1c + local_8 * 4)
      ;
      local_10 = local_10 + 1;
    }
  }
  *(int *)(param_1 + 0x188) = local_10;
  for (local_14 = 0; local_14 < 10; local_14 = local_14 + 1) {
    local_10 = 0;
    for (local_8 = 0; local_8 < *(int *)(param_1 + 0xfc4 + local_14 * 4); local_8 = local_8 + 1) {
      if (*(int *)(param_1 + 0x18c + local_14 * 0x16c + local_8 * 4) != param_2) {
        *(undefined4 *)(param_1 + 0x18c + local_14 * 0x16c + local_10 * 4) =
             *(undefined4 *)(param_1 + 0x18c + local_14 * 0x16c + local_8 * 4);
        local_10 = local_10 + 1;
      }
    }
    *(int *)(param_1 + 0xfc4 + local_14 * 4) = local_10;
  }
  local_10 = 0;
  for (local_8 = 0; local_8 < *(int *)(param_1 + 0x1014); local_8 = local_8 + 1) {
    if (*(int *)(param_1 + 0xfec + local_8 * 4) != param_2) {
      *(undefined4 *)(param_1 + 0xfec + local_10 * 4) =
           *(undefined4 *)(param_1 + 0xfec + local_8 * 4);
      local_10 = local_10 + 1;
    }
  }
  *(int *)(param_1 + 0x1014) = local_10;
  return;
}

