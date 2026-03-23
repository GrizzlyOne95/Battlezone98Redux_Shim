
void FUN_007069b0(int param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined1 local_12c [8];
  undefined1 local_124 [24];
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  int local_dc;
  int local_d8;
  int local_d0;
  CAtlBaseModule local_cc [88];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085705c;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_d0 = param_2;
  local_14 = uVar1;
  local_e0 = FUN_00417780(param_2 + 0x80,uVar1);
  local_dc = local_d0;
  local_d8 = local_d0;
  local_8 = 0;
  if ((param_1 == 0) || (param_1 == *(int *)(local_d0 + 0x78))) {
    local_10c = _String_const_iterator<>();
    local_8._0_1_ = 3;
    local_104 = local_10c;
    FUN_00708170(local_d0 + 0x80,local_d0 + 0xc0,local_10c);
    local_8._0_1_ = 5;
    FUN_006cd590();
    local_e0 = FUN_00417780(local_cc,uVar1);
    if (*(int *)(local_d0 + 200) != 0) {
      local_108 = FUN_00707ca0(local_2c);
      local_8._0_1_ = 6;
      local_e4 = local_108;
      local_100 = FUN_00707c60(local_5c);
      local_8._0_1_ = 7;
      local_ec = local_100;
      local_f8 = FUN_00707ce0(local_124,*(undefined4 *)(local_d0 + 200),local_100,local_e4);
      FUN_006d4f10(local_f8);
      FUN_006cd590();
      local_8._0_1_ = 6;
      ~basic_string<>();
      local_8._0_1_ = 5;
      ~basic_string<>();
    }
    FUN_00706cf0();
    if (param_1 != 0) {
      FUN_006acde0(0);
      local_8._0_1_ = 8;
      FUN_0070fa50(local_cc,local_cc);
      local_8._0_1_ = 5;
      FUN_006ace20();
    }
    local_8 = (uint)local_8._1_3_ << 8;
    ATL::CAtlBaseModule::~CAtlBaseModule(local_cc);
  }
  else {
    local_f4 = FUN_00707ca0(local_74);
    local_8._0_1_ = 1;
    local_f0 = local_f4;
    local_fc = FUN_00707c60(local_44);
    local_8._0_1_ = 2;
    iVar3 = local_d0 + 0xc0;
    iVar4 = local_d0 + 200;
    local_e8 = local_fc;
    uVar2 = std::allocator<char>::allocator<char>((allocator<char> *)(local_d0 + 0x28));
    uVar2 = FUN_0041f870(uVar2,iVar4,iVar3);
    uVar2 = FUN_0041f870(uVar2);
    FUN_006aff70(local_12c,local_d0 + 0x20,uVar2);
    local_8._0_1_ = 1;
    ~basic_string<>();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    FUN_006ad660(local_d0);
    local_d8 = 0;
    local_dc = 0;
  }
  local_8 = 0xffffffff;
  FUN_00703ff0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

