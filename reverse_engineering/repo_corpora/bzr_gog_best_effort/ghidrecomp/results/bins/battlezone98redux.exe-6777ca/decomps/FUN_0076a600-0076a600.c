
void __thiscall FUN_0076a600(int param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  ResourceGroupManager *pRVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  undefined1 local_17c [12];
  undefined1 local_170 [8];
  undefined1 local_168 [8];
  undefined4 local_160;
  undefined4 local_15c;
  undefined4 local_158;
  undefined4 local_154;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined1 local_138 [12];
  undefined4 local_12c;
  int local_128;
  char local_121;
  int local_120;
  undefined1 local_11c [24];
  undefined1 local_104 [24];
  undefined1 local_ec [24];
  undefined1 local_d4 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_bc [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085d6a3;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_120 = param_1;
  if ((DAT_00915568 == 0) &&
     ((*(int *)(param_1 + 0x8c) != 0 ||
      (cVar1 = FUN_00427310(param_1 + 0x90,param_2 + 0x30,local_14), cVar1 == '\0')))) {
    *(undefined4 *)(local_120 + 0x8c) = 0;
    FID_conflict_operator_(param_2 + 0x30);
    uVar2 = FUN_0041f870();
    FUN_007d6a70("buildSingleIAResource for %s started\n",uVar2);
    FUN_00434420();
    FUN_00820dd0();
    FUN_0044d2a0();
    local_12c = FUN_00416410();
    FUN_00667e40();
    iVar3 = FUN_0081dee0();
    basic_string<>((&PTR_DAT_008fe178)[iVar3]);
    local_8 = 0;
    local_128 = FUN_004170c0();
    local_128 = local_128 + 100;
    FUN_0076f230(local_138);
    local_8._0_1_ = 1;
    while( true ) {
      local_150 = FUN_0076f270(local_17c);
      local_8._0_1_ = 2;
      local_140 = local_150;
      local_121 = FID_conflict_operator__<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>,class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>
                            (local_138,local_150);
      local_8._0_1_ = 1;
      FUN_0076a200();
      if (local_121 == '\0') break;
      FUN_004fbb60();
      uVar2 = 0;
      iVar3 = FUN_0076fa30(0);
      FUN_00666890(iVar3 + 0x18,uVar2);
      local_8._0_1_ = 3;
      FUN_004fed70(local_5c);
      cVar1 = FUN_00767a00(local_2c,local_168);
      if (cVar1 != '\0') {
        local_160 = FUN_00417fd0(local_11c);
        local_8._0_1_ = 4;
        local_158 = local_160;
        uVar2 = FUN_0041f870();
        FUN_00820e00(uVar2);
        local_8._0_1_ = 3;
        ~basic_string<>();
        local_154 = FUN_00417fd0(local_104);
        local_8._0_1_ = 5;
        local_144 = local_154;
        uVar2 = FUN_0041f870();
        basic_string<>(uVar2);
        local_8._0_1_ = 6;
        FUN_006679c0(local_128,local_74);
        local_8._0_1_ = 5;
        ~basic_string<>();
        local_8._0_1_ = 3;
        ~basic_string<>();
      }
      FUN_0076fa30();
      uVar2 = FUN_0041f870();
      FUN_00820e00(uVar2);
      iVar3 = FUN_0076fa30();
      FUN_006679c0(local_128,iVar3 + 0x18);
      local_128 = local_128 + -1;
      local_8._0_1_ = 1;
      FUN_004180b0();
      FUN_0076fa10();
    }
    local_8._0_1_ = 0;
    FUN_0076a200();
    local_128 = 10;
    FUN_004fbb60();
    FUN_00666890(param_2 + 0x18,0);
    local_8._0_1_ = 7;
    FUN_004fed70(local_5c);
    cVar1 = FUN_00767a00(local_44,local_170);
    if (cVar1 != '\0') {
      local_15c = FUN_00417fd0(local_d4);
      local_8._0_1_ = 8;
      local_14c = local_15c;
      uVar2 = FUN_0041f870();
      FUN_00820e00(uVar2);
      local_8._0_1_ = 7;
      ~basic_string<>();
      local_148 = FUN_00417fd0(local_ec);
      local_8._0_1_ = 9;
      local_13c = local_148;
      uVar2 = FUN_0041f870();
      basic_string<>(uVar2);
      local_8._0_1_ = 10;
      FUN_006679c0(local_128,local_8c);
      local_8._0_1_ = 9;
      ~basic_string<>();
      local_8._0_1_ = 7;
      ~basic_string<>();
    }
    uVar2 = FUN_0041f870();
    FUN_00820e00(uVar2);
    FUN_006679c0(local_128,param_2 + 0x18);
    basic_string<>("Modable");
    local_8._0_1_ = 0xb;
    pbVar5 = local_bc;
    pRVar4 = Ogre::ResourceGroupManager::getSingleton();
    Ogre::ResourceGroupManager::clearResourceGroup(pRVar4,pbVar5);
    local_8._0_1_ = 7;
    ~basic_string<>();
    basic_string<>("Modable");
    local_8._0_1_ = 0xc;
    pbVar5 = local_a4;
    pRVar4 = Ogre::ResourceGroupManager::getSingleton();
    Ogre::ResourceGroupManager::initialiseResourceGroup(pRVar4,pbVar5);
    local_8._0_1_ = 7;
    ~basic_string<>();
    FUN_00434440();
    uVar2 = FUN_0041f870();
    FUN_007d6a70("buildSingleIAResource for %s complete\n",uVar2);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_004180b0();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

