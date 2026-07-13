
void FUN_006679c0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  undefined1 *puVar5;
  undefined1 local_114 [4];
  undefined1 local_110 [4];
  undefined1 local_10c [12];
  uint local_100;
  undefined4 local_fc;
  void *local_f8;
  undefined4 local_ec;
  int local_e8;
  uint local_e4;
  int local_e0;
  undefined1 local_dc [52];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_a8 [32];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_88 [24];
  undefined1 local_70 [24];
  undefined1 local_58 [16];
  undefined1 local_48 [28];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e3db;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0066e7d0(&param_1,param_2);
  local_8 = 0;
  uVar2 = FID_conflict_begin(local_114);
  FUN_0066acd0(local_110,local_48);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 != '\0') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_88,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)(local_e0 + 4));
    local_8._0_1_ = 1;
    FID_conflict_operator_(param_2);
    *(undefined4 *)(local_e0 + 0x5c) = param_1;
    local_f8 = Ogre::StdAllocPolicy::allocateBytes(0x10,(char *)0x0,0,(char *)0x0);
    local_e8 = forward<>(0x10,local_f8);
    local_8._0_1_ = 2;
    if (local_e8 == 0) {
      local_ec = 0;
    }
    else {
      local_ec = FUN_00669f20();
    }
    local_fc = local_ec;
    local_8._0_1_ = 1;
    FUN_0066e810(local_ec,1);
    local_8._0_1_ = 3;
    basic_string<>(&DAT_008922f0);
    local_8._0_1_ = 4;
    iVar3 = local_e0 + 4;
    uVar2 = get(iVar3);
    FUN_00667ed0(local_70,0,uVar2,iVar3);
    local_8._0_1_ = 3;
    ~basic_string<>();
    get();
    local_100 = FUN_00669fa0();
    FUN_0066a100();
    local_8._0_1_ = 5;
    for (local_e4 = 0; local_e4 < local_100; local_e4 = local_e4 + 1) {
      uVar4 = local_e4;
      get(local_e4);
      uVar2 = FUN_00669fc0(uVar4);
      FUN_00667cf0(uVar2);
      local_8._0_1_ = 6;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (local_2c,local_a8);
      local_8._0_1_ = 7;
      Ogre::StringUtil::toLowerCase(local_2c);
      uVar2 = FUN_004170c0(0x3a8efa67,local_58);
      uVar2 = FUN_0041f870(uVar2);
      FUN_00662830(uVar2);
      puVar5 = local_dc;
      FUN_0066a240(local_58);
      FUN_00667dd0(puVar5);
      local_8._0_1_ = 6;
      ~basic_string<>();
      local_8._0_1_ = 5;
      FUN_00667da0();
    }
    puVar5 = local_10c;
    FUN_0066a490(local_48);
    FUN_0066a220(puVar5);
    FID_conflict_operator_(local_88);
    local_8._0_1_ = 3;
    FUN_00667cd0();
    local_8._0_1_ = 1;
    FUN_004499a0();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
  }
  local_8 = 0xffffffff;
  FUN_00430250();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

