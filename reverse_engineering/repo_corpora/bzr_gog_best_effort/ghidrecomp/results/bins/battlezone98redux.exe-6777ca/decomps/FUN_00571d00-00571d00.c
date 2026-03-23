
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00571d00(int *param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_2 < 8) {
    DAT_008e8c04 = DAT_008e8c00;
  }
  else {
    DAT_008e8d14 = *param_1;
    DAT_00917f98 = FUN_00573100();
    _DAT_009180c4 = FUN_00822e60();
    DAT_008e8c04 = (uint)*(byte *)(param_1 + 1) << 2;
    if (DAT_008e8ce8 < DAT_008e8c04) {
      DAT_008e8c04 = DAT_008e8ce8;
    }
    if (DAT_008e8c04 < DAT_008e8c00) {
      DAT_008e8c04 = DAT_008e8c00;
    }
    if ((DAT_009180c0 != DAT_008e8d14) || (DAT_00917f74 != DAT_008e8c04)) {
      DAT_009180c0 = DAT_008e8d14;
      DAT_00917f74 = DAT_008e8c04;
      uVar1 = FUN_0081e820("Net: Bandwidth usage now set to %d, Interval %d ms\n",DAT_008e8d14,
                           DAT_008e8c04);
      FUN_0081e710(uVar1);
    }
  }
  iVar2 = DAT_00917fa8 / DAT_008e8c08;
  if ((DAT_008e8c04 < iVar2) && (DAT_008e8c04 = iVar2, DAT_008e8ce8 < iVar2)) {
    DAT_008e8c04 = DAT_008e8ce8;
  }
  return;
}

