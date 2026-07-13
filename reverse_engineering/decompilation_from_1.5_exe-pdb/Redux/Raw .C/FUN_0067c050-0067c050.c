
void FUN_0067c050(undefined4 param_1,undefined4 param_2)

{
  HardwareIndexBufferSharedPtr *this;
  HardwareIndexBufferSharedPtr *pHVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844a01;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  this = (HardwareIndexBufferSharedPtr *)forward<>(8,param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  if (this != (HardwareIndexBufferSharedPtr *)0x0) {
    pHVar1 = (HardwareIndexBufferSharedPtr *)FUN_00417780(param_2);
    Ogre::HardwareIndexBufferSharedPtr::HardwareIndexBufferSharedPtr(this,pHVar1);
  }
  ExceptionList = local_10;
  return;
}

