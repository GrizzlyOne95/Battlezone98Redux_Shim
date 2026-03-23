
undefined4 * FUN_0043af00(char *param_1,int param_2,undefined4 *param_3)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  char *local_14;
  char *local_c;
  
  puVar2 = (undefined4 *)FUN_0043bbc0();
  FUN_0043b640(puVar2);
  if (param_3 != (undefined4 *)0x0) {
    puVar5 = puVar2;
    for (iVar4 = 0xb; puVar5 = puVar5 + 1, iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *param_3;
      param_3 = param_3 + 1;
    }
  }
  if ((param_2 != 0) && ((*(uint *)(param_2 + 0x14) & 0x10) != 0)) {
    puVar2[5] = puVar2[5] | 0x800;
  }
  puVar2[0x16] = param_2;
  if (param_2 == 0) {
    puVar2[0x1e] = 0;
  }
  else {
    uVar3 = FUN_00439cc0(param_2);
    puVar2[0x1e] = uVar3;
  }
  if (param_1 != (char *)0x0) {
    local_14 = param_1;
    local_c = (char *)(puVar2 + 1);
    do {
      cVar1 = *local_14;
      *local_c = cVar1;
      local_14 = local_14 + 1;
      local_c = local_c + 1;
    } while (cVar1 != '\0');
  }
  if ((puVar2[5] & 6) == 0) {
    puVar2[5] = puVar2[5] | 2;
  }
  return puVar2;
}

