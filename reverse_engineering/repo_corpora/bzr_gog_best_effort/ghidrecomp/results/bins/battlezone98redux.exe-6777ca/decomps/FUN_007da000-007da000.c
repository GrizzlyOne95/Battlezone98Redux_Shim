
undefined4 * FUN_007da000(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 local_14;
  undefined4 local_10;
  undefined1 local_5;
  
  local_14 = FUN_00422f60(param_2);
  local_10 = FUN_00422f60(param_3);
  local_5 = 0;
  puVar2 = (undefined4 *)FUN_00422f60(&local_14);
  uVar1 = puVar2[1];
  *param_1 = *puVar2;
  param_1[1] = uVar1;
  return param_1;
}

