
void FUN_004357d0(int param_1)

{
  if ((*(ushort *)(param_1 + 4) & 1) != 0) {
    DAT_02cebca8 = DAT_02cebca8 & 0xfffffffe;
    DAT_02cebcac = DAT_02cebcac | 1;
  }
  if ((*(ushort *)(param_1 + 4) & 2) != 0) {
    DAT_02cebca8 = DAT_02cebca8 | 1;
  }
  if ((*(ushort *)(param_1 + 4) & 0x10) != 0) {
    DAT_02cebca8 = DAT_02cebca8 & 0xfffffffd;
    DAT_02cebcac = DAT_02cebcac | 2;
  }
  if ((*(ushort *)(param_1 + 4) & 0x20) != 0) {
    DAT_02cebca8 = DAT_02cebca8 | 2;
  }
  if ((*(ushort *)(param_1 + 4) & 4) != 0) {
    DAT_02cebca8 = DAT_02cebca8 & 0xfffffffb;
    DAT_02cebcac = DAT_02cebcac | 4;
  }
  if ((*(ushort *)(param_1 + 4) & 8) != 0) {
    DAT_02cebca8 = DAT_02cebca8 | 4;
  }
  if ((*(ushort *)(param_1 + 4) & 0x40) != 0) {
    DAT_02cebca8 = DAT_02cebca8 & 0xfffffff7;
    DAT_02cebcac = DAT_02cebcac | 8;
  }
  if ((*(ushort *)(param_1 + 4) & 0x80) != 0) {
    DAT_02cebca8 = DAT_02cebca8 | 8;
  }
  if ((*(ushort *)(param_1 + 4) & 0x100) != 0) {
    DAT_02cebca8 = DAT_02cebca8 & 0xffffffef;
    DAT_02cebcac = DAT_02cebcac | 0x10;
  }
  if ((*(ushort *)(param_1 + 4) & 0x200) != 0) {
    DAT_02cebca8 = DAT_02cebca8 | 0x10;
  }
  if ((*(ushort *)(param_1 + 4) & 0x400) != 0) {
    if (*(short *)(param_1 + 6) < 1) {
      if (*(short *)(param_1 + 6) < 0) {
        DAT_02cebcac = DAT_02cebcac | 0x20;
        DAT_02cebca8 = DAT_02cebca8 | 0x20;
      }
    }
    else {
      DAT_02cebcac = DAT_02cebcac | 0x40;
      DAT_02cebca8 = DAT_02cebca8 | 0x40;
    }
  }
  if ((*(ushort *)(param_1 + 4) & 0x800) != 0) {
    if (*(short *)(param_1 + 6) < 1) {
      if (*(short *)(param_1 + 6) < 0) {
        DAT_02cebcac = DAT_02cebcac | 0x80;
        DAT_02cebca8 = DAT_02cebca8 | 0x80;
      }
    }
    else {
      DAT_02cebcac = DAT_02cebcac | 0x100;
      DAT_02cebca8 = DAT_02cebca8 | 0x100;
    }
  }
  if ((*(int *)(param_1 + 0xc) != 0) || (*(int *)(param_1 + 0x10) != 0)) {
    DAT_02cebca0 = DAT_02cebca0 + *(int *)(param_1 + 0xc);
    DAT_02cebca4 = DAT_02cebca4 + *(int *)(param_1 + 0x10);
  }
  return;
}

