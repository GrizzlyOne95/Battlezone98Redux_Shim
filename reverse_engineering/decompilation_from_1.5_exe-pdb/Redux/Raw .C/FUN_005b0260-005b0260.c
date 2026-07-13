
undefined4 * __fastcall FUN_005b0260(undefined4 *param_1)

{
  int local_c;
  
  FUN_004efca0();
  *param_1 = ProducerClass::vftable;
  param_1[5] = 0x50524f44;
  param_1[6] = "producer";
  param_1[7] = 6;
  param_1[0x14] = 0;
  param_1[0xd3] = 0x40400000;
  param_1[0x17c] = 0x40a00000;
  param_1[0x17d] = 0x40a00000;
  param_1[0x17e] = 0x3f800000;
  param_1[0x17f] = 0x42c80000;
  param_1[0x180] = 10;
  param_1[0x181] = 0;
  for (local_c = 0; local_c < 9; local_c = local_c + 1) {
    param_1[local_c + 0x182] = 0;
  }
  *(undefined1 *)(param_1 + 0x18c) = 0;
  *(undefined1 *)(param_1 + 400) = 0;
  *(undefined1 *)(param_1 + 0x194) = 0;
  return param_1;
}

