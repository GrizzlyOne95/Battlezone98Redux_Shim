
undefined4 FUN_0061a080(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if (DAT_008ead14 < 8) {
    puVar3 = (undefined4 *)(&DAT_02cebce0 + DAT_008ead14 * 0x238);
    puVar4 = &DAT_008eaad0;
    for (iVar2 = 0x8e; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    DAT_008ead14 = DAT_008ead14 + 1;
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

