
void __fastcall FUN_0076ab20(int param_1)

{
  char cVar1;
  int iVar2;
  ResourceGroupManager *pRVar3;
  undefined4 uVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  undefined1 local_104 [12];
  undefined1 local_f8 [8];
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined1 local_d8 [12];
  undefined4 local_cc;
  undefined4 local_c8;
  int local_c4;
  char local_bd;
  undefined1 local_bc [24];
  undefined1 local_a4 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_8c [24];
  undefined1 local_74 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085d727;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_c4 = param_1;
  if ((DAT_00915568 == 0) && (*(int *)(param_1 + 0x8c) != 3)) {
    *(undefined4 *)(param_1 + 0x8c) = 3;
    FUN_00434420(local_14);
    FUN_00820dd0();
    iVar2 = FUN_0081dee0();
    basic_string<>((&PTR_DAT_008fe178)[iVar2]);
    local_8 = 0;
    FUN_0044d2a0();
    local_c8 = FUN_00416410();
    FUN_00667e40();
    local_cc = 10;
    FUN_004bb540(local_d8);
    local_8._0_1_ = 1;
    while( true ) {
      local_ec = FUN_004bb570(local_104);
      local_8._0_1_ = 2;
      local_e0 = local_ec;
      local_bd = FID_conflict_operator<(local_ec);
      local_8._0_1_ = 1;
      FUN_004bb3b0();
      if (local_bd == '\0') break;
      FUN_004fbb60();
      uVar4 = 0;
      iVar2 = FUN_0076f910(0);
      FUN_00666890(iVar2 + 0x7c,uVar4);
      local_8._0_1_ = 3;
      FUN_004fed70(local_74);
      cVar1 = FUN_00767a00(local_2c,local_f8);
      if (cVar1 != '\0') {
        local_e8 = FUN_00417fd0(local_bc);
        local_8._0_1_ = 4;
        local_e4 = local_e8;
        uVar4 = FUN_0041f870();
        FUN_00820e00(uVar4);
        local_8._0_1_ = 3;
        ~basic_string<>();
        local_f0 = FUN_00417fd0(local_a4);
        local_8._0_1_ = 5;
        local_dc = local_f0;
        uVar4 = FUN_0041f870();
        basic_string<>(uVar4);
        local_8._0_1_ = 6;
        FUN_006679c0(local_cc,local_44);
        local_8._0_1_ = 5;
        ~basic_string<>();
        local_8._0_1_ = 3;
        ~basic_string<>();
      }
      FUN_0076f910();
      uVar4 = FUN_0041f870();
      FUN_00820e00(uVar4);
      iVar2 = FUN_0076f910();
      FUN_006679c0(local_cc,iVar2 + 0x7c);
      local_8._0_1_ = 1;
      FUN_004180b0();
      FUN_00732df0();
    }
    local_8._0_1_ = 0;
    FUN_004bb3b0();
    basic_string<>("Modable");
    local_8._0_1_ = 7;
    pbVar5 = local_5c;
    pRVar3 = Ogre::ResourceGroupManager::getSingleton();
    Ogre::ResourceGroupManager::clearResourceGroup(pRVar3,pbVar5);
    local_8._0_1_ = 0;
    ~basic_string<>();
    basic_string<>("Modable");
    local_8._0_1_ = 8;
    pbVar5 = local_8c;
    pRVar3 = Ogre::ResourceGroupManager::getSingleton();
    Ogre::ResourceGroupManager::initialiseResourceGroup(pRVar3,pbVar5);
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    FUN_00434440();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

