
undefined1 * __thiscall FUN_007daa60(undefined1 *param_1,undefined1 *param_2)

{
  undefined4 uVar1;
  
  *param_1 = *param_2;
  uVar1 = *(undefined4 *)(param_2 + 8);
  *(undefined4 *)(param_1 + 4) = *(undefined4 *)(param_2 + 4);
  *(undefined4 *)(param_1 + 8) = uVar1;
  param_1[0xc] = param_2[0xc];
  return param_1;
}

