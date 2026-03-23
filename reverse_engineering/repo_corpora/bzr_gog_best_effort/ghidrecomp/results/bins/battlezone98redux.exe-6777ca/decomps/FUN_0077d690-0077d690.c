
void FUN_0077d690(void)

{
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_10 = 0x50;
  local_18 = 0;
  local_14 = 0x50;
  local_1c = 0;
  for (local_c = 0; local_c < 0x50; local_c = local_c + 1) {
    for (local_8 = 0; local_8 < 0x50; local_8 = local_8 + 1) {
      if (*(undefined **)(&DAT_02cc5108 + ((local_c + 0x18) * 0x80 + 0x18 + local_8) * 4) !=
          &DAT_02c119d0) {
        if (local_8 < local_10) {
          local_10 = local_8;
        }
        if (local_18 < local_8) {
          local_18 = local_8;
        }
        if (local_c < local_14) {
          local_14 = local_c;
        }
        if (local_1c < local_c) {
          local_1c = local_c;
        }
      }
    }
  }
  DAT_02ce99b0 = (int)DAT_02cc50e0 * local_10 * 0x100;
  DAT_02ce99b4 = (int)DAT_02cc50e0 * local_14 * 0x100;
  DAT_02ce99b8 = (int)DAT_02cc50e0 * (local_18 + 1) * 0x100;
  DAT_02ce99bc = (int)DAT_02cc50e0 * (local_1c + 1) * 0x100;
  return;
}

