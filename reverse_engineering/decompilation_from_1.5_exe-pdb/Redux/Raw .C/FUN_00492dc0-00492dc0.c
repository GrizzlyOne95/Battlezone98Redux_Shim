
void FUN_00492dc0(int param_1)

{
  if (param_1 != 2) {
    DAT_008e7754 = 0x43750000;
    DAT_008e7918 = 0x43898000;
    DAT_008e77b4 = 0x432a0000;
    DAT_008e77b0 = 0x3f800000;
    DAT_009782a0 = 0x41200000;
  }
  else {
    DAT_008e7754 = 0x43235555;
    DAT_008e7918 = 0;
    DAT_008e77b4 = 0x42e2aaab;
    DAT_008e77b0 = 0x3f2aaaab;
    DAT_009782a0 = 0xc330aaaa;
  }
  DAT_009173c4 = (uint)(param_1 == 2);
  return;
}

