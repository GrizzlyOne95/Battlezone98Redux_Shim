
undefined4 * __thiscall FUN_00719aa0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar1 = (undefined4 *)FUN_00417780(param_2);
  puVar4 = param_1;
  for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = (undefined1 *)FUN_00417780(param_3);
  *(undefined1 *)(param_1 + 7) = *puVar2;
  return param_1;
}

