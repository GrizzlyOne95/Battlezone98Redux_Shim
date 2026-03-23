
undefined4 FUN_005c7fb0(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00417c70();
  if (iVar1 == 0) {
    DAT_02cc2bdc = 0;
  }
  else {
    iVar2 = FUN_00462630(DAT_02cc2bdc);
    if (iVar2 != iVar1) {
      DAT_02cc2bdc = FUN_00477590(iVar1);
    }
  }
  return DAT_02cc2bdc;
}

