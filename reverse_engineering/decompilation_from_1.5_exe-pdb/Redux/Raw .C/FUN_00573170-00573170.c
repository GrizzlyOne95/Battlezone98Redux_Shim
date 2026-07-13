
undefined4 FUN_00573170(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  float local_c;
  
  iVar1 = FUN_00572a70();
  if (iVar1 == 0) {
    uVar3 = 0;
  }
  else {
    iVar1 = FUN_00822e60();
    local_c = (float)((double)(iVar1 - DAT_009180dc) +
                     (double)(&DAT_008a2fd0)[-(iVar1 - DAT_009180dc >> 0x1f)]) / 1000.0;
    if (local_c == 0.0) {
      local_c = 0.001;
    }
    iVar1 = FUN_004b75b0();
    iVar2 = FUN_00573100();
    iVar1 = (iVar2 - DAT_009180d0) + param_2 * (iVar1 + -1);
    if ((float)((double)iVar1 + (double)(&DAT_008a2fd0)[-(iVar1 >> 0x1f)]) / local_c <=
        (float)((double)DAT_008e8d14 + (double)(&DAT_008a2fd0)[-(DAT_008e8d14 >> 0x1f)])) {
      if (param_2 == 2) {
        DAT_00917f8d = '\0';
      }
      else {
        memcpy(&DAT_00917fc0,(void *)(param_1 + 2),param_2 - 2);
        DAT_00917f8d = (char)param_2 + -2;
      }
      uVar3 = 1;
    }
    else {
      uVar3 = 0;
    }
  }
  return uVar3;
}

