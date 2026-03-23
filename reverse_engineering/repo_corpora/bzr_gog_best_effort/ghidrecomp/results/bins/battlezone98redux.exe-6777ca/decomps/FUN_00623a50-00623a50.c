
undefined4 FUN_00623a50(int param_1)

{
  int iVar1;
  
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x60) = 0;
    *(undefined4 *)(param_1 + 100) = 0;
    *(undefined4 *)(param_1 + 0x68) = 0;
    *(undefined4 *)(param_1 + 0x6c) = 0;
    *(undefined4 *)(param_1 + 0x70) = 0;
  }
  FUN_004351e0(0);
  DAT_0092015c = 0;
  do {
    iVar1 = FUN_00435130(1);
  } while (iVar1 == 0);
  return 0;
}

