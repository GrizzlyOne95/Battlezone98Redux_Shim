
undefined4 * __thiscall FUN_00450be0(undefined4 *param_1,int param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_00417780(param_2);
  *param_1 = *puVar1;
  puVar1 = (undefined4 *)FUN_00417780(param_2 + 4);
  param_1[1] = *puVar1;
  return param_1;
}

