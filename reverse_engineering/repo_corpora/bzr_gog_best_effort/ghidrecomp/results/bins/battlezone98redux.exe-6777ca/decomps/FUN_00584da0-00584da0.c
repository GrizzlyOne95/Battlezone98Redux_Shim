
undefined4 * FUN_00584da0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  FUN_00583d90(param_2);
  puVar1 = (undefined4 *)FUN_00583e50();
  *param_1 = *puVar1;
  param_1[1] = puVar1[1];
  param_1[2] = puVar1[2];
  param_1[3] = puVar1[3];
  return param_1;
}

