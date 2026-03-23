
void __fastcall FUN_0066fe20(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084ecd8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = Ogre::
             SharedPtrInfoFree<class_std::vector<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_Ogre::STLAllocator<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_Ogre::CategorisedAllocPolicy<0>_>_>_>
             ::vftable;
  local_8 = 0;
  Ogre::StdAllocPolicy::deallocateBytes((void *)param_1[6]);
  local_8 = 0xffffffff;
  FUN_00667260(uVar1);
  ExceptionList = local_10;
  return;
}

