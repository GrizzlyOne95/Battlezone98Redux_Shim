
void __thiscall FUN_005ed4b0(int param_1,int *param_2)

{
  undefined4 uVar1;
  float local_14;
  undefined1 local_10 [4];
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (*(int *)(param_1 + 0x300) != 0) {
    *(undefined1 *)(*(int *)(param_1 + 0x300) + 0x9c) = 0;
    *(undefined4 *)(*(int *)(param_1 + 0x300) + 0xa0) = 0;
    *(undefined4 *)(param_1 + 0x31c) = 0;
    FUN_004c0af0(&local_14);
    FUN_00785730((double)local_14,(double)local_c,local_10,0);
    FUN_005873a0(&local_14);
  }
  if (param_2 != (int *)0x0) {
    *(undefined1 *)(param_2 + 0x27) = 1;
    param_2[0x28] = param_1;
    uVar1 = (**(code **)(*param_2 + 0x28))();
    *(undefined4 *)(param_1 + 0x31c) = uVar1;
  }
  *(int **)(param_1 + 0x300) = param_2;
  FUN_0083e885();
  return;
}

