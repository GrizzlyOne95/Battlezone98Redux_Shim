
void FUN_00434b00(int param_1)

{
  ushort uVar1;
  int iVar2;
  
  uVar1 = *(ushort *)(&DAT_008e7268 + param_1 * 2);
  if (uVar1 != 0) {
    iVar2 = FUN_00619f60();
    if (iVar2 != 0) {
      uVar1 = uVar1 | 0x100;
    }
    iVar2 = FUN_00619f80();
    if (iVar2 != 0) {
      uVar1 = uVar1 | 0x400;
    }
    iVar2 = FUN_00619fa0();
    if (iVar2 != 0) {
      uVar1 = uVar1 | 0x200;
    }
    *(ushort *)(&DAT_02cf4420 + DAT_0260c230 * 2) = uVar1;
    DAT_0260c230 = DAT_0260c230 + 1;
    if (DAT_0260c230 == 0x40) {
      DAT_0260c230 = 0;
    }
    else if ((DAT_0260c230 == DAT_0260c22c) &&
            (DAT_0260c22c = DAT_0260c22c + 1, DAT_0260c22c == 0x40)) {
      DAT_0260c22c = 0;
    }
  }
  return;
}

