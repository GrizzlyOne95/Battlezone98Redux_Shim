
void FUN_0067bfc0(undefined4 param_1,undefined4 param_2)

{
  HardwareVertexBufferSharedPtr *this;
  HardwareVertexBufferSharedPtr *pHVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844a01;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  this = (HardwareVertexBufferSharedPtr *)forward<>(8,param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc)
  ;
  local_8 = 0;
  if (this != (HardwareVertexBufferSharedPtr *)0x0) {
    pHVar1 = (HardwareVertexBufferSharedPtr *)FUN_00417780(param_2);
    Ogre::HardwareVertexBufferSharedPtr::HardwareVertexBufferSharedPtr(this,pHVar1);
  }
  ExceptionList = local_10;
  return;
}

