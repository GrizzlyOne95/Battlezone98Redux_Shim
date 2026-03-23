
int __thiscall FUN_007081b0(int param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  FUN_006f6240(param_2);
  uVar1 = param_3[1];
  *(undefined4 *)(param_1 + 0x40) = *param_3;
  *(undefined4 *)(param_1 + 0x44) = uVar1;
  return param_1;
}

