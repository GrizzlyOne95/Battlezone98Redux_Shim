
void __fastcall FUN_004f9430(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  MaterialManager *pMVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar6;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_74 [8];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_6c [8];
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  int *local_54;
  int local_50;
  uint local_4c;
  int local_48;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a940;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_48 = param_1;
  local_14 = uVar1;
  for (local_4c = 0; local_4c < 6; local_4c = local_4c + 1) {
    uVar2 = FUN_0068bed0((&PTR_s_ring_0_008e8690)[local_4c * 3]);
    *(undefined4 *)(&DAT_008e8698 + local_4c * 0xc) = uVar2;
  }
  if (local_48 == 0) {
    local_50 = 0;
  }
  else {
    local_50 = local_48 + 0x28;
  }
  iVar3 = FUN_0044d2a0(uVar1);
  local_54 = *(int **)(iVar3 + 8);
  (**(code **)(*local_54 + 800))(local_50);
  basic_string<>("QueryArea");
  local_8 = 0;
  pbVar6 = local_2c;
  pbVar5 = local_74;
  pMVar4 = Ogre::MaterialManager::getSingleton();
  local_64 = Ogre::MaterialManager::getByName(pMVar4,pbVar5,pbVar6);
  local_8._0_1_ = 1;
  local_58 = local_64;
  FUN_00449910(local_64);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004499a0();
  local_8 = 0xffffffff;
  ~basic_string<>();
  basic_string<>("QueryVisible");
  local_8 = 2;
  pbVar6 = local_44;
  pbVar5 = local_6c;
  pMVar4 = Ogre::MaterialManager::getSingleton();
  local_60 = Ogre::MaterialManager::getByName(pMVar4,pbVar5,pbVar6);
  local_8._0_1_ = 3;
  local_5c = local_60;
  FUN_00449910(local_60);
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_004499a0();
  local_8 = 0xffffffff;
  ~basic_string<>();
  *(undefined4 *)(local_48 + 0x48) = 0;
  *(undefined4 *)(local_48 + 0x4c) = 0;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

