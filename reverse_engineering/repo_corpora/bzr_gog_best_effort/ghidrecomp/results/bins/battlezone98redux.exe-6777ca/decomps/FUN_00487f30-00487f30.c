
void FUN_00487f30(void)

{
  char cVar1;
  undefined4 uVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  int iVar4;
  undefined4 uVar5;
  char *pcVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined1 local_7c [4];
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined1 local_60 [4];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00848ea3;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004879f0(local_14);
  FUN_00426b10(0,0,0);
  local_8 = 0;
  FUN_00420260(local_60);
  while( true ) {
    uVar2 = FID_conflict_begin(local_7c);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') break;
    pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_00422150();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar3);
    local_8._0_1_ = 1;
    iVar4 = FUN_00422150();
    local_6c = *(undefined4 *)(iVar4 + 0x18);
    local_68 = *(undefined4 *)(iVar4 + 0x1c);
    local_78 = FUN_00482630(local_5c,local_6c);
    local_8._0_1_ = 2;
    uVar8 = 0;
    uVar7 = 0;
    local_74 = local_78;
    uVar2 = FUN_0041f870(0,0);
    pcVar6 = "current";
    uVar5 = FUN_0041f870("current",uVar2);
    FUN_00421f90(uVar5,pcVar6,uVar2,uVar7,uVar8);
    local_8._0_1_ = 1;
    ~basic_string<>();
    local_70 = FUN_00482630(local_44,local_68);
    local_8._0_1_ = 3;
    uVar8 = 0;
    uVar7 = 0;
    local_64 = local_70;
    uVar2 = FUN_0041f870(0,0);
    pcVar6 = "furthest";
    uVar5 = FUN_0041f870("furthest",uVar2);
    FUN_00421f90(uVar5,pcVar6,uVar2,uVar7,uVar8);
    local_8._0_1_ = 1;
    ~basic_string<>();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    FUN_00428570();
  }
  FUN_004fe800(&DAT_02ceefe0);
  uVar5 = 1;
  uVar2 = FUN_0041f870(1);
  FUN_00426c90(uVar2,uVar5);
  local_8 = 0xffffffff;
  FUN_00426bc0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

