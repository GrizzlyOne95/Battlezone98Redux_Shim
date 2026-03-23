
void FUN_0068a2d0(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (DAT_02bf042c <= local_8) {
      return;
    }
    if (param_1 == *(int *)(&DAT_02bf04ac + local_8 * 0x6c)) break;
    local_8 = local_8 + 1;
  }
  DAT_02bf042c = DAT_02bf042c + -1;
  puVar2 = (undefined4 *)(&DAT_02bf04ac + DAT_02bf042c * 0x6c);
  puVar3 = (undefined4 *)(&DAT_02bf04ac + local_8 * 0x6c);
  for (iVar1 = 0x1b; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  return;
}

