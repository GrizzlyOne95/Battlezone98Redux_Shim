
undefined4 * __thiscall FUN_004d0d10(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  uVar1 = FUN_00417780(param_2);
  puVar2 = (undefined4 *)FUN_00433f60(uVar1);
  *param_1 = *puVar2;
  param_1[2] = 0;
  param_1[3] = 0;
  return param_1;
}

