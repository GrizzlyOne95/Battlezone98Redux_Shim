
void __thiscall FUN_004faaf0(int param_1,undefined4 param_2)

{
  int *local_8;
  
  if (DAT_008eaad8 != 3) {
    for (local_8 = (int *)(param_1 + 0x28);
        local_8 != (int *)(param_1 + 0x28 + *(int *)(param_1 + 0x68) * 4); local_8 = local_8 + 1) {
      if (*(int *)(*local_8 + 0x20) != 0) {
        FUN_004fb690(*local_8,param_2);
      }
    }
  }
  return;
}

