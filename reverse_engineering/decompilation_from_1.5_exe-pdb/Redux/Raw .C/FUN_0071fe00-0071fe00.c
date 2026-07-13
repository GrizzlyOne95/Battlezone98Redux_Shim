
int __thiscall FUN_0071fe00(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  
  FUN_00712920(param_2);
  uVar1 = param_3[1];
  *(undefined4 *)(param_1 + 0x68) = *param_3;
  *(undefined4 *)(param_1 + 0x6c) = uVar1;
  *(undefined4 *)(param_1 + 0x70) = *param_4;
  return param_1;
}

