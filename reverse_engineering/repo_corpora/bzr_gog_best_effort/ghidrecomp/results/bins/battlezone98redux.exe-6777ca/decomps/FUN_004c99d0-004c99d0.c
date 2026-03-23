
undefined4 * FUN_004c99d0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined1 *puVar2;
  undefined1 local_14 [16];
  
  puVar2 = local_14;
  FUN_004c9840(param_2,puVar2);
  puVar1 = (undefined4 *)FUN_004c9850(puVar2);
  *param_1 = *puVar1;
  param_1[1] = puVar1[1];
  param_1[2] = puVar1[2];
  param_1[3] = puVar1[3];
  return param_1;
}

