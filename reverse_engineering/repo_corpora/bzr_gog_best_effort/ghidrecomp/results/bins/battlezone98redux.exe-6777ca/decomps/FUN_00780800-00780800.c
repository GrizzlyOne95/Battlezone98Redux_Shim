
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00780800(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if (1 < param_1) {
    if (param_1 < 4) {
      puVar2 = &DAT_008f05f0;
      puVar3 = &DAT_02c06748;
      for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      _DAT_02c0676c = 1.0 / (float)(DAT_008f05fc - _DAT_008f05f8);
      goto LAB_007808d6;
    }
    if (param_1 == 10) {
      puVar2 = &DAT_008f05f0;
      puVar3 = &DAT_02c06748;
      for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      DAT_02c06748 = 1000.0;
      _DAT_02c0676c = 1.0 / (float)(DAT_008f05fc - _DAT_008f05f8);
      goto LAB_007808d6;
    }
  }
  puVar2 = &DAT_008f0598;
  puVar3 = &DAT_02c06748;
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  _DAT_02c0676c = 1.0 / (float)(DAT_008f05a4 - _DAT_008f05a0);
LAB_007808d6:
  DAT_02ce99c8 = DAT_02c06748;
  DAT_02cd9134 = DAT_02c06748 * DAT_02c06748;
  DAT_02cc50c0 = DAT_02c06760;
  DAT_02c06770 = param_1;
  DAT_02c06774 = DAT_009454bc;
  _DAT_02c06764 = DAT_02c06760 / 256.0;
  _DAT_008ead08 = DAT_02c06748;
  FUN_00683370((float)DAT_02cd9120 / 255.0,(float)DAT_02cd9121 / 255.0,(float)DAT_02cd9122 / 255.0,
               (float)_DAT_02c06750,(float)_DAT_02c06754 * 1.5);
  return;
}

