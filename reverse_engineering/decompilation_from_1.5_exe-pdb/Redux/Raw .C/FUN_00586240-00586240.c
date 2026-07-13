
undefined2 * __thiscall FUN_00586240(undefined2 *param_1,int param_2)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)FUN_00417780(param_2);
  *param_1 = *puVar1;
  puVar1 = (undefined2 *)FUN_00417780(param_2 + 2);
  param_1[1] = *puVar1;
  return param_1;
}

