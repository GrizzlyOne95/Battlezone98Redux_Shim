
undefined4 * __thiscall FUN_007f8c30(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(param_1 + 8);
  *param_2 = *(undefined4 *)(param_1 + 4);
  param_2[1] = uVar1;
  return param_2;
}

