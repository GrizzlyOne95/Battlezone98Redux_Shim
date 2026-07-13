
undefined4 * __thiscall FUN_007c62e0(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(param_1 + 0x20);
  *param_2 = *(undefined4 *)(param_1 + 0x1c);
  param_2[1] = uVar1;
  return param_2;
}

