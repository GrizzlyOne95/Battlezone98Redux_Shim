
void FUN_0079c970(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  allocator<char> local_125;
  int local_124;
  undefined1 local_120 [268];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085fab4;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if ((DAT_02cc39a4 & 1) == 0) {
    DAT_02cc39a4 = DAT_02cc39a4 | 1;
    local_8 = 0;
    basic_string<>();
    local_8._0_1_ = 1;
    basic_string<>();
    local_8._0_1_ = 2;
    basic_string<>();
    local_8._0_1_ = 3;
    basic_string<>();
    local_8._0_1_ = 4;
    basic_string<>();
    local_8._0_1_ = 5;
    basic_string<>();
    local_8._0_1_ = 6;
    basic_string<>();
    local_8._0_1_ = 7;
    basic_string<>();
    local_8._0_1_ = 8;
    basic_string<>();
    local_8._0_1_ = 9;
    basic_string<>();
    local_8._0_1_ = 10;
    basic_string<>();
    local_8._0_1_ = 0xb;
    std::allocator<char>::allocator<char>(&local_125);
    FUN_00416430();
    FUN_0079ce30();
    local_8 = (uint)local_8._1_3_ << 8;
    _eh_vector_destructor_iterator_(local_120,0x18,0xb,~basic_string<>);
    FUN_0083e979();
  }
  local_8 = 0xffffffff;
  basic_string<>("killLimit");
  local_8 = 0xc;
  uVar3 = *(undefined4 *)(local_124 + 0x1a8);
  uVar2 = 0;
  iVar1 = FUN_0056f900(0,uVar3);
  local_8 = 0xffffffff;
  FUN_0079bdf0(iVar1 + 0x128,uVar2,uVar3);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

