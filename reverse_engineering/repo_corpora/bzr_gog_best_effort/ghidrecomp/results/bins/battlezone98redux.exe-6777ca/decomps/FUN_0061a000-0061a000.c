
undefined4 FUN_0061a000(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if (DAT_008ead14 < 1) {
    uVar1 = 0;
  }
  else {
    DAT_008ead14 = DAT_008ead14 + -1;
    puVar3 = &DAT_008eaad0;
    puVar4 = (undefined4 *)(&DAT_02cebce0 + DAT_008ead14 * 0x238);
    for (iVar2 = 0x8e; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    uVar1 = 1;
  }
  return uVar1;
}

