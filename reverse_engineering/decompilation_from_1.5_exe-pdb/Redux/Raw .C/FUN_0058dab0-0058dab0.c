
/* WARNING: Removing unreachable block (ram,0x0058db2a) */

undefined4 *
FUN_0058dab0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *local_8;
  
  local_8 = (undefined4 *)FUN_0058c980(0);
  puVar2 = param_4;
  puVar3 = local_8;
  for (iVar1 = 0xe; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  *(undefined1 *)((int)local_8 + 0x21) = 0;
  local_8[9] = param_1;
  local_8[10] = param_2;
  *(undefined1 *)((int)local_8 + 0x1d) = 1;
  local_8[5] = 0xffffffff;
  local_8[0xd] = param_4;
  *(undefined1 *)((int)local_8 + 0x1f) = *(undefined1 *)((int)param_4 + 0x1f);
  FUN_0041fe40(&local_8);
  return local_8;
}

