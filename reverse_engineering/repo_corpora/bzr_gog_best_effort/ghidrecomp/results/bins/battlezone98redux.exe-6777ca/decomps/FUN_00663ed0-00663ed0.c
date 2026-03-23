
void FUN_00663ed0(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar1;
  LogManager *this;
  Log *pLVar2;
  undefined4 uVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  uint uStack_594;
  ConfigFile local_534 [60];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_4f8;
  undefined4 local_4f0;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_4d8;
  LogManager *local_4b4;
  undefined4 local_494;
  undefined4 local_468;
  undefined4 local_448;
  int local_43c;
  undefined1 local_420 [144];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_390 [480];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_1b0 [264];
  undefined1 local_a8 [72];
  undefined1 local_60 [72];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084e061;
  local_10 = ExceptionList;
  uStack_594 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_594;
  ExceptionList = &local_10;
  local_448 = 0;
  local_8 = 0;
  local_18 = uStack_594;
  FUN_00426a60(&DAT_02cf2000,0);
  local_8._0_1_ = 1;
  FUN_00426af0("Ogre.cfg");
  FUN_00417fd0(local_60);
  local_8._0_1_ = 2;
  FUN_00426a60(&DAT_02cf0000,0);
  local_8._0_1_ = 3;
  FUN_00426af0("bz_resources.cfg");
  FUN_00417fd0(local_a8);
  local_8._0_1_ = 4;
  local_4b4 = Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<0>_>::operator_new(0x24);
  local_8._0_1_ = 5;
  if (local_4b4 == (LogManager *)0x0) {
    local_494 = 0;
  }
  else {
    local_494 = Ogre::LogManager::LogManager(local_4b4);
  }
  local_4f0 = local_494;
  local_8._0_1_ = 4;
  FUN_00662ea0();
  local_8._0_1_ = 6;
  FUN_006668f0(&DAT_02cf1000);
  FUN_00426af0("BZOgreLogfile.log");
  pbVar1 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_00417fd0(local_420);
  local_8._0_1_ = 7;
  bVar6 = false;
  bVar5 = false;
  bVar4 = true;
  local_4f8 = pbVar1;
  local_4d8 = pbVar1;
  this = Ogre::LogManager::getSingleton();
  pLVar2 = Ogre::LogManager::createLog(this,pbVar1,bVar4,bVar5,bVar6);
  *(Log **)(local_43c + 0x28) = pLVar2;
  local_8._0_1_ = 6;
  ~basic_string<>();
  Ogre::Log::setDebugOutputEnabled(*(Log **)(local_43c + 0x28),true);
  local_468 = 2;
  basic_string<>();
  local_8._0_1_ = 8;
  Ogre::ConfigFile::ConfigFile(local_534);
  local_8._0_1_ = 10;
  basic_string<>(&DAT_00892064);
  local_8._0_1_ = 0xb;
  uVar3 = FUN_0041f870();
  basic_string<>(uVar3);
  local_8._0_1_ = 0xc;
  Ogre::ConfigFile::load(local_534,local_390,local_1b0,true);
  local_8._0_1_ = 0xb;
  ~basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,10);
  ~basic_string<>();
  FUN_00664110();
  return;
}

