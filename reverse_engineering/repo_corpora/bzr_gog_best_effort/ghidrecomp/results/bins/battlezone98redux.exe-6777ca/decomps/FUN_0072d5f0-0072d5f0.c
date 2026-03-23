
int __thiscall FUN_0072d5f0(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  
  FUN_007270d0(param_2);
  uVar1 = param_3[1];
  *(undefined4 *)(param_1 + 0x58) = *param_3;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x60) = *param_4;
  return param_1;
}

