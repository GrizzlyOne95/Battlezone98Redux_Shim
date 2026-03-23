
void FUN_006850e0(void)

{
  int local_5c;
  int local_58;
  int local_54;
  undefined1 local_50 [24];
  undefined1 local_38 [24];
  undefined1 local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  basic_string<>("DynamicMain");
  DAT_02b3f014 = FUN_00684f90(local_20,0x11);
  ~basic_string<>();
  if (DAT_02b3f014 == 0) {
    local_58 = 0;
  }
  else {
    local_58 = DAT_02b3f014 + 0xd4;
  }
  (**(code **)(**(int **)(DAT_00920ea0 + 0x10) + 0x20c))(local_58);
  basic_string<>("DynamicTarget");
  DAT_02b79b30 = FUN_00684f90(local_50,2);
  ~basic_string<>();
  if (DAT_02b79b30 == 0) {
    local_5c = 0;
  }
  else {
    local_5c = DAT_02b79b30 + 0xd4;
  }
  (**(code **)(**(int **)(DAT_00920ea0 + 0x14) + 0x20c))(local_5c);
  basic_string<>("DynamicSniper");
  DAT_02b79b28 = FUN_00684f90(local_38,4);
  ~basic_string<>();
  if (DAT_02b79b28 == 0) {
    local_54 = 0;
  }
  else {
    local_54 = DAT_02b79b28 + 0xd4;
  }
  (**(code **)(**(int **)(DAT_00920ea0 + 0x18) + 0x20c))(local_54);
  DAT_02b79b34 = DAT_02b3f014;
  DAT_02b79b2c = FUN_00439e60();
  DAT_02bf0418 = *(undefined4 *)(DAT_00920ea0 + 0x10);
  FUN_0083e885();
  return;
}

