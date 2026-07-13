
void __fastcall FUN_0066f980(undefined4 *param_1)

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
             SharedPtrInfoDeleteT<class_std::vector<struct_Ogre::FileInfo,class_Ogre::STLAllocator<struct_Ogre::FileInfo,class_Ogre::CategorisedAllocPolicy<0>_>_>_>
             ::vftable;
  local_8 = 0;
  if (param_1[6] != 0) {
    FUN_0066fec0(0);
    Ogre::StdAllocPolicy::deallocateBytes((void *)param_1[6]);
  }
  local_8 = 0xffffffff;
  FUN_00667260(uVar1);
  ExceptionList = local_10;
  return;
}

