
void __fastcall FUN_0076a240(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  ResourceGroupManager *pRVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  undefined1 local_74 [12];
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined1 local_5c [12];
  undefined4 local_50;
  int local_4c;
  char local_45;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085d5a0;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_4c = param_1;
  if ((DAT_00915568 == 0) && (*(int *)(param_1 + 0x8c) != 2)) {
    *(undefined4 *)(param_1 + 0x8c) = 2;
    FUN_007d6a70("buildMPResources started\n",local_14);
    FUN_00434420();
    FUN_00820dd0();
    FUN_0044d2a0();
    local_50 = FUN_00416410();
    FUN_00667e40();
    local_64 = 10;
    FUN_004bb540(local_5c);
    local_8 = 0;
    while( true ) {
      local_68 = FUN_004bb570(local_74);
      local_8._0_1_ = 1;
      local_60 = local_68;
      local_45 = FID_conflict_operator<(local_68);
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_004bb3b0();
      if (local_45 == '\0') break;
      FUN_00752f10();
      cVar1 = FUN_0041f890();
      if (cVar1 == '\0') {
        FUN_00752f10();
        uVar2 = FUN_0041f870();
        FUN_00820e00(uVar2);
        iVar3 = FUN_00752f10();
        FUN_006679c0(local_64,iVar3 + 0x84);
      }
      FUN_00732df0();
    }
    local_8 = 0xffffffff;
    FUN_004bb3b0();
    basic_string<>("Modable");
    local_8 = 2;
    pbVar5 = local_2c;
    pRVar4 = Ogre::ResourceGroupManager::getSingleton();
    Ogre::ResourceGroupManager::clearResourceGroup(pRVar4,pbVar5);
    local_8 = 0xffffffff;
    ~basic_string<>();
    basic_string<>("Modable");
    local_8 = 3;
    pbVar5 = local_44;
    pRVar4 = Ogre::ResourceGroupManager::getSingleton();
    Ogre::ResourceGroupManager::initialiseResourceGroup(pRVar4,pbVar5);
    local_8 = 0xffffffff;
    ~basic_string<>();
    FUN_00434440();
    FUN_007d6a70("buildMPResources complete\n");
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

