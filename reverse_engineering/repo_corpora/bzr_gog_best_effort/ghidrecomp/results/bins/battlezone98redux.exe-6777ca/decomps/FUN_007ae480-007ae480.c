
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_007ae480(int param_1)

{
  undefined4 uVar1;
  
  _DAT_009455b0 = 0;
  if ((DAT_0260baa8 == *(byte *)(DAT_0094672c + 0x27)) &&
     (DAT_0260baac == *(char *)(DAT_0094672c + 0x25))) {
    if ((*(char *)(DAT_0094672c + 0x27) == '\0') && (*(char *)(DAT_0094672c + 0x25) < '\0')) {
      uVar1 = 0;
    }
    else {
      DAT_008f0684 = -1;
      DAT_009455a8 = 2;
      *(undefined1 *)(DAT_0094672c + 0x25) = 0xff;
      *(undefined1 *)(DAT_0094672c + 0x27) = 2;
      FUN_00680fe0();
      if (DAT_009455a4 != 0) {
        FUN_007ae5b0();
      }
      uVar1 = 1;
    }
  }
  else {
    if (param_1 != 0) {
      if (DAT_0260baac < *(char *)(DAT_0094672c + 0x25)) {
        DAT_008f0684 = *(char *)(DAT_0094672c + 0x25) + -1;
      }
      if ((int)(uint)*(byte *)(DAT_0094672c + 0x27) < (int)DAT_0260baa8) {
        DAT_009455a8 = *(byte *)(DAT_0094672c + 0x27) + 1;
      }
    }
    *(undefined1 *)(DAT_0094672c + 0x25) = (undefined1)DAT_0260baac;
    *(undefined1 *)(DAT_0094672c + 0x27) = (undefined1)DAT_0260baa8;
    FUN_00680fe0();
    if (DAT_009455a4 != 0) {
      FUN_007ae5b0();
    }
    uVar1 = 1;
  }
  return uVar1;
}

