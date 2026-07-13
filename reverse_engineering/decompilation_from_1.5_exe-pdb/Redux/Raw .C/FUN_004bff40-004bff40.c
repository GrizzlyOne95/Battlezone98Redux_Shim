
undefined2 * __thiscall FUN_004bff40(undefined2 *param_1,int param_2)

{
  undefined2 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = (undefined2 *)FUN_00417780(param_2);
  *param_1 = *puVar1;
  puVar2 = (undefined4 *)FUN_00417780(param_2 + 4);
  *(undefined4 *)(param_1 + 2) = *puVar2;
  return param_1;
}

