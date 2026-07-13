
undefined4 * __thiscall FUN_0042c980(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined1 *puVar2;
  
  puVar1 = (undefined4 *)FUN_00417780(param_2);
  *param_1 = *puVar1;
  puVar2 = (undefined1 *)FUN_00417780(param_3);
  *(undefined1 *)(param_1 + 1) = *puVar2;
  return param_1;
}

