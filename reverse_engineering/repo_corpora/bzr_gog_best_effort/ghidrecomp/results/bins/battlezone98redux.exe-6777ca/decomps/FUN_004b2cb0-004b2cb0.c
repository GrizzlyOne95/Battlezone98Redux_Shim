
void FUN_004b2cb0(void)

{
  undefined4 *puVar1;
  undefined1 local_120 [264];
  undefined1 local_18 [4];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00849809;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if ((DAT_02cc2f38 & 1) == 0) {
    DAT_02cc2f38 = DAT_02cc2f38 | 1;
    local_8 = 0;
    basic_string<>("avartl");
    local_8._0_1_ = 1;
    basic_string<>("avdemo");
    local_8._0_1_ = 2;
    basic_string<>("avhraz");
    local_8._0_1_ = 3;
    basic_string<>("sbspow");
    local_8._0_1_ = 4;
    basic_string<>("sbhang");
    local_8._0_1_ = 5;
    basic_string<>("sbhqcp");
    local_8._0_1_ = 6;
    basic_string<>("sbwpwo");
    local_8._0_1_ = 7;
    basic_string<>("sblpow");
    local_8._0_1_ = 8;
    basic_string<>("svhraz");
    local_8._0_1_ = 9;
    basic_string<>("svltnk");
    local_8._0_1_ = 10;
    basic_string<>("svrckt");
    local_8._0_1_ = 0xb;
    puVar1 = (undefined4 *)FUN_00416430(local_120,local_18);
    FUN_004b2fd0(*puVar1,puVar1[1]);
    local_8 = (uint)local_8._1_3_ << 8;
    _eh_vector_destructor_iterator_(local_120,0x18,0xb,~basic_string<>);
    FUN_0083e979(FUN_008669b0);
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

