
undefined4 * FUN_007da220(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 local_14 [4];
  undefined4 local_10;
  undefined1 local_5;
  
  FUN_007da5b0(local_14,param_2);
  local_10 = FUN_00422f60(param_3);
  local_5 = 0;
  puVar2 = (undefined4 *)FUN_00422f60(local_14);
  uVar1 = puVar2[1];
  *param_1 = *puVar2;
  param_1[1] = uVar1;
  return param_1;
}

