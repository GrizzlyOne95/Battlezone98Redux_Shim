
void __fastcall FUN_006623e0(int param_1)

{
  uint uVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  MaterialManager *this;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_24 [8];
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084db68;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = param_1;
  pbVar2 = Ogre::SubEntity::getMaterialName(*(SubEntity **)(param_1 + 0x1c));
  pbVar3 = local_24;
  this = Ogre::MaterialManager::getSingleton();
  local_1c = Ogre::MaterialManager::getByName(this,pbVar3,pbVar2);
  local_8 = 0;
  local_18 = local_1c;
  FUN_00449910(local_1c);
  local_8 = 0xffffffff;
  FUN_004499a0(uVar1);
  ExceptionList = local_10;
  return;
}

