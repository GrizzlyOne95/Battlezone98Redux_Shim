
void __fastcall FUN_0066fb90(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084ecd8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = Ogre::SharedPtrInfoDeleteT<class_Ogre::DataStream>::vftable;
  local_8 = 0;
  if (param_1[6] != 0) {
    (**(code **)(*(int *)param_1[6] + 8))(0,uVar1);
    Ogre::StdAllocPolicy::deallocateBytes((void *)param_1[6]);
  }
  local_8 = 0xffffffff;
  FUN_00667260();
  ExceptionList = local_10;
  return;
}

