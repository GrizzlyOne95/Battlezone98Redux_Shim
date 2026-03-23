
void FUN_00693430(int param_1,int param_2,undefined4 param_3,int param_4,undefined4 param_5)

{
  void *pvVar1;
  undefined4 local_8;
  
  *(int *)(*(int *)(param_1 + 4) + 8 + param_2 * 0x10) = param_4;
  *(undefined4 *)(*(int *)(param_1 + 4) + 4 + param_2 * 0x10) = param_5;
  *(undefined4 *)(*(int *)(param_1 + 4) + param_2 * 0x10) = param_3;
  pvVar1 = malloc(param_4 * 0xc);
  *(void **)(*(int *)(param_1 + 4) + 0xc + param_2 * 0x10) = pvVar1;
  for (local_8 = 0; local_8 < param_4; local_8 = local_8 + 1) {
    *(undefined2 *)(*(int *)(*(int *)(param_1 + 4) + 0xc + param_2 * 0x10) + local_8 * 0xc) = 0;
    *(undefined4 *)(*(int *)(*(int *)(param_1 + 4) + 0xc + param_2 * 0x10) + 4 + local_8 * 0xc) = 0;
  }
  return;
}

