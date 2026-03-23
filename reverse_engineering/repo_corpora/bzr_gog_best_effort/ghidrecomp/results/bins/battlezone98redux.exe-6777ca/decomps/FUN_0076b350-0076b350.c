
void __thiscall FUN_0076b350(int param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  ResourceGroupManager *pRVar4;
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
  int local_c8;
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
  puStack_c = &LAB_0085d7a7;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_c4 = param_1;
  if ((DAT_00915568 == 0) &&
     ((*(int *)(param_1 + 0x8c) != 0 ||
      (cVar1 = FUN_00427310(param_1 + 0x90,param_2 + 0x84,local_14), cVar1 == '\0')))) {
    *(undefined4 *)(local_c4 + 0x8c) = 0;
    FID_conflict_operator_(param_2 + 0x84);
    uVar2 = FUN_0041f870();
    FUN_007d6a70("buildSingleMPResource for %s started\n",uVar2);
    FUN_00434420();
    FUN_00820dd0();
    iVar3 = FUN_0081dee0();
    basic_string<>((&PTR_DAT_008fe178)[iVar3]);
    local_8 = 0;
    FUN_0044d2a0();
    local_cc = FUN_00416410();
    FUN_00667e40();
    local_c8 = 10;
    uVar2 = FUN_0041f870();
    FUN_00820e00(uVar2);
    FUN_006679c0(local_c8,param_2 + 0x84);
    local_c8 = FUN_004170c0();
    local_c8 = local_c8 + 100;
    FUN_0076f230(local_d8);
    local_8._0_1_ = 1;
    while( true ) {
      local_ec = FUN_0076f270(local_104);
      local_8._0_1_ = 2;
      local_e0 = local_ec;
      local_bd = FID_conflict_operator__<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>,class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>
                           (local_d8,local_ec);
      local_8._0_1_ = 1;
      FUN_0076a200();
      if (local_bd == '\0') break;
      iVar3 = FUN_0076fa30();
      if (*(char *)(iVar3 + 0x90) == '\x01') {
        FUN_0076fa30();
        uVar2 = FUN_0041f870();
        FUN_007d6a70("Enabling MP safe mod : %s\n",uVar2);
        FUN_004fbb60();
        uVar2 = 0;
        iVar3 = FUN_0076fa30(0);
        FUN_00666890(iVar3 + 0x18,uVar2);
        local_8._0_1_ = 3;
        FUN_004fed70(local_74);
        cVar1 = FUN_00767a00(local_2c,local_f8);
        if (cVar1 != '\0') {
          local_e8 = FUN_00417fd0(local_bc);
          local_8._0_1_ = 4;
          local_e4 = local_e8;
          uVar2 = FUN_0041f870();
          FUN_00820e00(uVar2);
          local_8._0_1_ = 3;
          ~basic_string<>();
          local_f0 = FUN_00417fd0(local_a4);
          local_8._0_1_ = 5;
          local_dc = local_f0;
          uVar2 = FUN_0041f870();
          basic_string<>(uVar2);
          local_8._0_1_ = 6;
          FUN_006679c0(local_c8,local_44);
          local_8._0_1_ = 5;
          ~basic_string<>();
          local_8._0_1_ = 3;
          ~basic_string<>();
        }
        FUN_0076fa30();
        uVar2 = FUN_0041f870();
        FUN_00820e00(uVar2);
        iVar3 = FUN_0076fa30();
        FUN_006679c0(local_c8,iVar3 + 0x18);
        local_c8 = local_c8 + -1;
        local_8._0_1_ = 1;
        FUN_004180b0();
      }
      FUN_0076fa10();
    }
    local_8._0_1_ = 0;
    FUN_0076a200();
    basic_string<>("Modable");
    local_8._0_1_ = 7;
    pbVar5 = local_5c;
    pRVar4 = Ogre::ResourceGroupManager::getSingleton();
    Ogre::ResourceGroupManager::clearResourceGroup(pRVar4,pbVar5);
    local_8._0_1_ = 0;
    ~basic_string<>();
    basic_string<>("Modable");
    local_8._0_1_ = 8;
    pbVar5 = local_8c;
    pRVar4 = Ogre::ResourceGroupManager::getSingleton();
    Ogre::ResourceGroupManager::initialiseResourceGroup(pRVar4,pbVar5);
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    FUN_00434440();
    uVar2 = FUN_0041f870();
    FUN_007d6a70("buildSingleMPResource for %s complete\n",uVar2);
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

