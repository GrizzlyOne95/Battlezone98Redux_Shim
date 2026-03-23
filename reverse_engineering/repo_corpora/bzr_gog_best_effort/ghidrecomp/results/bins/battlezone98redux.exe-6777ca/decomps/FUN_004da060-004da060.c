
undefined * FUN_004da060(uint param_1)

{
  undefined *puVar1;
  int iVar2;
  
  if (param_1 == 0) {
    puVar1 = (undefined *)0x0;
  }
  else {
    iVar2 = (param_1 >> 0x14) * 0x400;
    puVar1 = &DAT_0260db20 + iVar2;
    if (*(uint *)(&DAT_0260dc7c + iVar2) != (param_1 & 0xfffff)) {
      puVar1 = (undefined *)0x0;
    }
  }
  return puVar1;
}

