
void FUN_00617800(int param_1)

{
  undefined4 uVar1;
  float local_20;
  float local_1c;
  undefined4 local_18;
  float local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  local_18 = FUN_0081cb40("names","<<< PAUSED >>>");
  FUN_00689ab0(DAT_0091552c,local_18,&local_20,&local_1c);
  local_10 = (DAT_02cecee8 + DAT_02cecef0) / 2;
  local_c = (DAT_02ceceec + DAT_02cecef4) / 2;
  local_8 = FUN_00822e60();
  local_8 = local_8 & 0x7ff;
  local_14 = DAT_00920ef4;
  DAT_00920ef4 = DAT_00920ef4 + 0.01;
  FUN_0068af70(&DAT_02cecee0,local_10 + -100,local_c + -8,local_10 + 100,local_c + 8,0xff000000,0);
  DAT_00920ef4 = local_14;
  if (local_8 < 0x500) {
    if (local_8 < 0x280) {
      std::_Init_atomic_counter(DAT_0091552c,(local_8 * 0xff) / 0x280 << 0x18 | 0xffffff);
    }
    else {
      std::_Init_atomic_counter(DAT_0091552c,((0x500 - local_8) * 0xff) / 0x280 << 0x18 | 0xffffff);
    }
    FUN_00689d10(DAT_0091552c,*(undefined4 *)(param_1 + 0x38),
                 (int)((float)local_10 - local_20 / 2.0),(int)((float)local_c - local_1c / 2.0),
                 local_18);
  }
  uVar1 = FUN_00439e60();
  FUN_006175c0(uVar1);
  FUN_00682540();
  return;
}

