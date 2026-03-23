
void FUN_006927b0(int param_1)

{
  undefined4 local_8;
  
  FUN_006928f0(param_1);
  if (*(int *)(param_1 + 0x240) != 0) {
    for (local_8 = 1; local_8 < 0x20; local_8 = local_8 + 1) {
    }
  }
  if (*(int *)(param_1 + 0x58c) != 0) {
    *(int *)(param_1 + 0x58c) = *(int *)(param_1 + 0x58c) + -1;
  }
  if (*(int *)(param_1 + 0x590) != 0) {
    *(int *)(param_1 + 0x590) = *(int *)(param_1 + 0x590) + -1;
  }
  if (*(int *)(param_1 + 0x594) != 0) {
    *(int *)(param_1 + 0x594) = *(int *)(param_1 + 0x594) + -1;
  }
  if (*(int *)(param_1 + 0xb4) != 0) {
    FUN_00690e80(param_1);
    FUN_00692700(param_1);
    FUN_006925e0(param_1);
    FUN_00691a60(param_1);
    if (*(int *)(param_1 + 0x240) != 0) {
      for (local_8 = 1; local_8 < 0x20; local_8 = local_8 + 1) {
      }
    }
  }
  return;
}

