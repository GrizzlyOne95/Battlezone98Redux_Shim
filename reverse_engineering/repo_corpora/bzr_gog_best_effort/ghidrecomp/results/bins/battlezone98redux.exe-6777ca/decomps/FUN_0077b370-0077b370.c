
PixelBox * FUN_0077b370(void)

{
  char cVar1;
  Material *this;
  Technique *this_00;
  Pass *this_01;
  TextureUnitState *this_02;
  HardwarePixelBuffer *pHVar2;
  LockOptions LVar3;
  UploadOptions UVar4;
  ushort uVar5;
  ushort uVar6;
  ushort uVar7;
  SharedPtr<class_Ogre::HardwarePixelBuffer> local_28 [8];
  PixelBox *local_20;
  int *local_1c;
  SharedPtr<class_Ogre::Texture> *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e5b9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  cVar1 = FUN_004c85a0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (cVar1 == '\0') {
    uVar7 = 0;
    uVar6 = 0;
    uVar5 = 0;
    this = (Material *)get();
    this_00 = Ogre::Material::getTechnique(this,uVar5);
    this_01 = Ogre::Technique::getPass(this_00,uVar6);
    this_02 = Ogre::Pass::getTextureUnitState(this_01,uVar7);
    local_18 = Ogre::TextureUnitState::_getTexturePtr(this_02);
    cVar1 = FUN_004c85a0();
    if (cVar1 == '\0') {
      local_1c = (int *)get();
      (**(code **)(*local_1c + 0x15c))(local_28,0,0);
      local_8 = 0;
      UVar4 = 0;
      LVar3 = 2;
      pHVar2 = Ogre::SharedPtr<class_Ogre::HardwarePixelBuffer>::operator->(local_28);
      Ogre::HardwareBuffer::lock((HardwareBuffer *)pHVar2,LVar3,UVar4);
      pHVar2 = Ogre::SharedPtr<class_Ogre::HardwarePixelBuffer>::operator->(local_28);
      local_20 = Ogre::HardwarePixelBuffer::getCurrentLock(pHVar2);
      local_8 = 0xffffffff;
      Ogre::HardwarePixelBufferSharedPtr::~HardwarePixelBufferSharedPtr
                ((HardwarePixelBufferSharedPtr *)local_28);
      ExceptionList = local_10;
      return local_20;
    }
  }
  ExceptionList = local_10;
  return (PixelBox *)0x0;
}

