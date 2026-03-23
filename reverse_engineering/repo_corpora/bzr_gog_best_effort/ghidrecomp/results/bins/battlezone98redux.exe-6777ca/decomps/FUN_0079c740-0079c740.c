
void FUN_0079c740(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  allocator<char> local_13d;
  int local_13c;
  undefined1 local_138 [292];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085f9ef;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if ((DAT_02cc39b4 & 1) == 0) {
    DAT_02cc39b4 = DAT_02cc39b4 | 1;
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
    basic_string<>();
    local_8._0_1_ = 0xc;
    std::allocator<char>::allocator<char>(&local_13d);
    FUN_00416430();
    FUN_0079ce30();
    local_8 = (uint)local_8._1_3_ << 8;
    _eh_vector_destructor_iterator_(local_138,0x18,0xc,~basic_string<>);
    FUN_0083e979();
  }
  local_8 = 0xffffffff;
  basic_string<>("timeLimit");
  local_8 = 0xd;
  uVar3 = *(undefined4 *)(local_13c + 0x194);
  uVar2 = 1;
  iVar1 = FUN_0056f900(1,uVar3);
  local_8 = 0xffffffff;
  FUN_0079bdf0(iVar1 + 0x118,uVar2,uVar3);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

