
int __thiscall FUN_00710810(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  
  FUN_006f64c0(param_2);
  uVar1 = param_3[1];
  *(undefined4 *)(param_1 + 0x30) = *param_3;
  *(undefined4 *)(param_1 + 0x34) = uVar1;
  *(undefined4 *)(param_1 + 0x38) = *param_4;
  return param_1;
}

