
void __fastcall FUN_0077c030(int param_1)

{
  uint uVar1;
  HardwareIndexBuffer *this;
  HardwareIndexBufferSharedPtr local_30 [8];
  uint local_28;
  HardwareIndexBufferSharedPtr *local_24;
  HardwareIndexBufferSharedPtr *local_20;
  HardwareIndexBuffer *local_1c;
  HardwareBufferManager *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e5e9;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(undefined1 *)(param_1 + 0x7c) = 0;
  local_14 = param_1;
  local_18 = Ogre::HardwareBufferManager::getSingleton();
  local_24 = (HardwareIndexBufferSharedPtr *)
             (**(code **)(*(int *)local_18 + 0x24))
                       (local_30,0,*(undefined4 *)(local_14 + 0x74),5,0,uVar1);
  local_8 = 0;
  local_20 = local_24;
  Ogre::HardwareIndexBufferSharedPtr::operator=
            ((HardwareIndexBufferSharedPtr *)(local_14 + 0xc),local_24);
  local_8 = 0xffffffff;
  Ogre::HardwareIndexBufferSharedPtr::~HardwareIndexBufferSharedPtr(local_30);
  this = Ogre::SharedPtr<class_Ogre::HardwareIndexBuffer>::operator->
                   ((SharedPtr<class_Ogre::HardwareIndexBuffer> *)(local_14 + 0xc));
  local_28 = Ogre::HardwareBuffer::getSizeInBytes((HardwareBuffer *)this);
  local_1c = Ogre::SharedPtr<class_Ogre::HardwareIndexBuffer>::operator->
                       ((SharedPtr<class_Ogre::HardwareIndexBuffer> *)(local_14 + 0xc));
  (**(code **)(*(int *)local_1c + 0x18))(0,local_28,*(undefined4 *)(local_14 + 0x70),1);
  ExceptionList = local_10;
  return;
}

