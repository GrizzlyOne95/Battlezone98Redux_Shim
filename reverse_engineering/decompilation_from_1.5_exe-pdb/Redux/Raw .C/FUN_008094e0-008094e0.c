
undefined4 * __thiscall FUN_008094e0(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = *(undefined4 *)(param_1 + 8);
  uVar2 = *(undefined4 *)(param_1 + 0xc);
  *param_2 = *(undefined4 *)(param_1 + 4);
  param_2[1] = uVar1;
  param_2[2] = uVar2;
  return param_2;
}

