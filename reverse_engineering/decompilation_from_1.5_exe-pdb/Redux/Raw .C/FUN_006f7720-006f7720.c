
void FUN_006f7720(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)FUN_006d7d50();
  uVar1 = puVar2[1];
  *param_1 = *puVar2;
  param_1[1] = uVar1;
  *(undefined1 *)(param_1 + 2) = 0;
  return;
}

