
void FUN_0077c130(void)

{
  char cVar1;
  HardwareVertexBuffer *this;
  HardwareVertexBufferSharedPtr local_30 [8];
  uint local_28;
  HardwareVertexBufferSharedPtr *local_24;
  HardwareVertexBufferSharedPtr *local_20;
  HardwareVertexBuffer *local_1c;
  HardwareBufferManager *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e619;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0077c670(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  cVar1 = FUN_00777710();
  if (cVar1 != '\0') {
    *(undefined1 *)(local_14 + 0x84) = 0;
    local_18 = Ogre::HardwareBufferManager::getSingleton();
    local_24 = (HardwareVertexBufferSharedPtr *)
               (**(code **)(*(int *)local_18 + 0x20))(local_30,0x10,0x24c1,5,0);
    local_8 = 0;
    local_20 = local_24;
    Ogre::HardwareVertexBufferSharedPtr::operator=
              ((HardwareVertexBufferSharedPtr *)(local_14 + 4),local_24);
    local_8 = 0xffffffff;
    Ogre::HardwareVertexBufferSharedPtr::~HardwareVertexBufferSharedPtr(local_30);
    this = Ogre::SharedPtr<class_Ogre::HardwareVertexBuffer>::operator->
                     ((SharedPtr<class_Ogre::HardwareVertexBuffer> *)(local_14 + 4));
    local_28 = Ogre::HardwareBuffer::getSizeInBytes((HardwareBuffer *)this);
    local_1c = Ogre::SharedPtr<class_Ogre::HardwareVertexBuffer>::operator->
                         ((SharedPtr<class_Ogre::HardwareVertexBuffer> *)(local_14 + 4));
    (**(code **)(*(int *)local_1c + 0x18))(0,local_28,*(undefined4 *)(local_14 + 0x80),1);
  }
  ExceptionList = local_10;
  return;
}

