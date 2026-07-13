
undefined4 * FUN_0058dbb0(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *local_8;
  
  local_8 = (undefined4 *)FUN_0058c980(0);
  puVar2 = local_8;
  for (iVar1 = 0xe; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_3;
    param_3 = param_3 + 1;
    puVar2 = puVar2 + 1;
  }
  local_8[9] = param_1;
  local_8[10] = param_2;
  *(undefined1 *)(local_8 + 8) = 1;
  local_8[5] = 0xffffffff;
  FUN_0041fe40(&local_8);
  return local_8;
}

