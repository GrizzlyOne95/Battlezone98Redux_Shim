
undefined4 * __thiscall FUN_0069d330(undefined4 param_1,undefined4 *param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_0069d1d0(param_1);
  *puVar1 = param_3;
  puVar1[2] = 0;
  puVar1[1] = param_2[3];
  param_2[3] = puVar1;
  if (param_2[4] == 0) {
    param_2[4] = puVar1;
  }
  *param_2 = 0xfffffc19;
  if (*(int *)(param_2[3] + 4) != 0) {
    *(undefined4 *)(*(int *)(param_2[3] + 4) + 8) = param_2[3];
  }
  param_2[2] = param_2[2] + 1;
  return puVar1;
}

