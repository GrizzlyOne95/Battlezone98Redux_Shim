
int __thiscall FUN_006f44e0(int param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  FUN_006f4320(param_2);
  uVar1 = param_3[1];
  *(undefined4 *)(param_1 + 0x68) = *param_3;
  *(undefined4 *)(param_1 + 0x6c) = uVar1;
  return param_1;
}

