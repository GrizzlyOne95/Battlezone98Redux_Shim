
int __thiscall FUN_0072d630(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  
  FUN_00727140(param_2);
  uVar1 = param_3[1];
  *(undefined4 *)(param_1 + 0x50) = *param_3;
  *(undefined4 *)(param_1 + 0x54) = uVar1;
  *(undefined4 *)(param_1 + 0x58) = *param_4;
  return param_1;
}

