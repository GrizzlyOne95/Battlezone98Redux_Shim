
void __fastcall FUN_0076a030(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  ResourceGroupManager *pRVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar4;
  undefined1 local_74 [12];
  undefined1 local_68 [12];
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  int local_50;
  int local_4c;
  char local_45;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085d550;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_4c = param_1;
  if ((DAT_00915568 == 0) && (*(int *)(param_1 + 0x8c) != 4)) {
    *(undefined4 *)(param_1 + 0x8c) = 4;
    FUN_00434420(local_14);
    FUN_00820dd0();
    FUN_0044d2a0();
    local_54 = FUN_00416410();
    FUN_00667e40();
    local_50 = FUN_004170c0();
    local_50 = local_50 + 100;
    FUN_0076f230(local_68);
    local_8 = 0;
    while( true ) {
      local_5c = FUN_0076f270(local_74);
      local_8._0_1_ = 1;
      local_58 = local_5c;
      local_45 = FID_conflict_operator__<class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>,class_std::_Vector_iterator<class_std::_Vector_val<struct_std::_Simple_types<class_std::shared_ptr<struct_Concurrency::details::_Task_impl<struct_std::pair<unsigned_char,class_Concurrency::details::_CancellationTokenState*>_>_>_>_>_>_>
                           (local_68,local_5c);
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_0076a200();
      if (local_45 == '\0') break;
      FUN_0076fa30();
      uVar1 = FUN_0041f870();
      FUN_00820e00(uVar1);
      iVar2 = FUN_0076fa30();
      FUN_006679c0(local_50,iVar2 + 0x18);
      local_50 = local_50 + -1;
      FUN_0076fa10();
    }
    local_8 = 0xffffffff;
    FUN_0076a200();
    basic_string<>("Modable");
    local_8 = 2;
    pbVar4 = local_2c;
    pRVar3 = Ogre::ResourceGroupManager::getSingleton();
    Ogre::ResourceGroupManager::clearResourceGroup(pRVar3,pbVar4);
    local_8 = 0xffffffff;
    ~basic_string<>();
    basic_string<>("Modable");
    local_8 = 3;
    pbVar4 = local_44;
    pRVar3 = Ogre::ResourceGroupManager::getSingleton();
    Ogre::ResourceGroupManager::initialiseResourceGroup(pRVar3,pbVar4);
    local_8 = 0xffffffff;
    ~basic_string<>();
    FUN_00434440();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

