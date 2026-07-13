
void FUN_00706610(int param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined1 local_134 [8];
  undefined1 local_12c [24];
  undefined4 local_114;
  undefined4 local_110;
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
  int local_e4;
  int local_e0;
  int local_d8;
  CDataPathProperty local_d4 [96];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856fdc;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_d8 = param_2;
  local_14 = uVar1;
  local_e8 = FUN_00417780(param_2 + 0x80,uVar1);
  local_e4 = local_d8;
  local_e0 = local_d8;
  local_8 = 0;
  if ((param_1 == 0) || (param_1 == *(int *)(local_d8 + 0x78))) {
    local_114 = _String_const_iterator<>();
    local_8._0_1_ = 3;
    local_10c = local_114;
    FUN_00708130(local_d8 + 0x80,local_d8 + 200,local_114);
    local_8._0_1_ = 5;
    FUN_006cd590();
    local_e8 = FUN_00417780(local_d4,uVar1);
    if (*(int *)(local_d8 + 0xd0) != 0) {
      local_110 = FUN_00707ca0(local_2c);
      local_8._0_1_ = 6;
      local_ec = local_110;
      local_108 = FUN_00707c60(local_5c);
      local_8._0_1_ = 7;
      local_f4 = local_108;
      local_100 = FUN_00707ce0(local_12c,*(undefined4 *)(local_d8 + 0xd0),local_108,local_ec);
      FUN_006d4f10(local_100);
      FUN_006cd590();
      local_8._0_1_ = 6;
      ~basic_string<>();
      local_8._0_1_ = 5;
      ~basic_string<>();
    }
    FUN_00706950();
    if (param_1 != 0) {
      FUN_006acde0(0);
      local_8._0_1_ = 8;
      FUN_0070fa00(local_d4,local_d4);
      local_8._0_1_ = 5;
      FUN_006ace20();
    }
    local_8 = (uint)local_8._1_3_ << 8;
    CDataPathProperty::~CDataPathProperty(local_d4);
  }
  else {
    local_fc = FUN_00707ca0(local_74);
    local_8._0_1_ = 1;
    local_f8 = local_fc;
    local_104 = FUN_00707c60(local_44);
    local_8._0_1_ = 2;
    iVar3 = local_d8 + 200;
    iVar4 = local_d8 + 0xd0;
    local_f0 = local_104;
    uVar2 = std::allocator<char>::allocator<char>((allocator<char> *)(local_d8 + 0x28));
    uVar2 = FUN_0041f870(uVar2,iVar4,iVar3);
    uVar2 = FUN_0041f870(uVar2);
    FUN_006aff70(local_134,local_d8 + 0x20,uVar2);
    local_8._0_1_ = 1;
    ~basic_string<>();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    FUN_006ad660(local_d8);
    local_e0 = 0;
    local_e4 = 0;
  }
  local_8 = 0xffffffff;
  FUN_00703f00();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

