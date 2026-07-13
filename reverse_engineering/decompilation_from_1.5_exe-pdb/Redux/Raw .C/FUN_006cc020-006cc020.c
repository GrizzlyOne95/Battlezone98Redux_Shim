
undefined4 * __thiscall FUN_006cc020(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(param_1 + 0x4c2c);
  *param_2 = *(undefined4 *)(param_1 + 0x4c28);
  param_2[1] = uVar1;
  return param_2;
}

