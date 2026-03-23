
char FUN_0056f960(void)

{
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_00917f4f = DAT_00917f8c;
  DAT_00917f8c = '\0';
  iVar1 = FUN_00822e60();
  if (DAT_009175b4 == 0) {
    if (-1 < iVar1 - DAT_009180c8) {
      DAT_00917f8c = '\x01';
    }
  }
  else {
    DAT_00917f8c = '\x01';
  }
  if (DAT_00917f8c != '\0') {
    local_8 = FUN_004b75b0();
    if (local_8 < 2) {
      local_8 = 1;
    }
    else if (0xf < local_8) {
      local_8 = 0xf;
    }
    local_c = (uint)(((longlong)DAT_008e8d14 * (longlong)DAT_008e8c04 & 0xffffffffU) / 2000);
    if (1 < (int)(local_8 - 1U)) {
      local_c = local_c / (local_8 - 1U);
    }
    DAT_00917fa0 = local_c;
    if (local_c < 0xc9) {
      if (local_c < 0x28) {
        DAT_00917fa0 = 0x28;
      }
    }
    else {
      DAT_00917fa0 = 200;
    }
  }
  return DAT_00917f8c;
}

