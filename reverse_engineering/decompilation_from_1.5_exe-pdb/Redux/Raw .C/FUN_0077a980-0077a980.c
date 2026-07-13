
void FUN_0077a980(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_1)

{
  uint uVar1;
  MaterialManager *this;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_24 [8];
  undefined4 local_1c;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084db68;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FID_conflict_operator_(param_1);
  pbVar2 = local_24;
  this = Ogre::MaterialManager::getSingleton();
  local_1c = Ogre::MaterialManager::getByName(this,pbVar2,param_1);
  local_8 = 0;
  local_18 = local_1c;
  FUN_00449910(local_1c);
  local_8 = 0xffffffff;
  FUN_004499a0(uVar1);
  ExceptionList = local_10;
  return;
}

