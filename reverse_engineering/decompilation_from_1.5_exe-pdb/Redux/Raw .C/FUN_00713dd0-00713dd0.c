
undefined4 * __thiscall FUN_00713dd0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  uVar1 = FUN_00417780(param_2);
  *param_1 = uVar1;
  puVar2 = (undefined4 *)FUN_00417780(param_3);
  param_1[1] = *puVar2;
  return param_1;
}

