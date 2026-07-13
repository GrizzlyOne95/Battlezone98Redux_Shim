
undefined1 * __thiscall
FUN_007dc170(undefined1 *param_1,undefined1 *param_2,undefined4 *param_3,undefined1 *param_4)

{
  undefined4 uVar1;
  
  *param_1 = *param_2;
  uVar1 = param_3[1];
  *(undefined4 *)(param_1 + 4) = *param_3;
  *(undefined4 *)(param_1 + 8) = uVar1;
  param_1[0xc] = *param_4;
  return param_1;
}

