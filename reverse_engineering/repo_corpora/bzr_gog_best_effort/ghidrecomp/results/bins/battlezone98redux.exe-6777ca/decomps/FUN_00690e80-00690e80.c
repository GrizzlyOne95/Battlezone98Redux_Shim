
void FUN_00690e80(int param_1)

{
  undefined4 local_c;
  undefined4 local_8;
  
  if (*(int *)(param_1 + 0xb4) != 0) {
    *(undefined4 *)(param_1 + 0x264) = 0;
    FUN_00691860(param_1,0);
    if (*(int *)(param_1 + 0x264) == 0) {
      local_c = 0x1f;
      local_8 = *(int *)(param_1 + 0x260);
      while (local_c != 0) {
        FUN_00691860(param_1,local_8);
        local_c = local_c + -1;
        local_8 = local_8 + 1;
        if (local_8 == 0x20) {
          local_8 = 1;
        }
      }
      *(int *)(param_1 + 0x260) = *(int *)(param_1 + 0x260) + 1;
      if (*(int *)(param_1 + 0x260) == 0x20) {
        *(undefined4 *)(param_1 + 0x260) = 1;
      }
    }
    *(undefined4 *)(param_1 + 0x268) = 0;
  }
  return;
}

