
void FUN_0077b470(void)

{
  char cVar1;
  Material *this;
  Technique *this_00;
  Pass *this_01;
  TextureUnitState *this_02;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  SharedPtr<class_Ogre::HardwarePixelBuffer> local_28 [8];
  HardwarePixelBuffer *local_20;
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
    uVar4 = 0;
    uVar3 = 0;
    uVar2 = 0;
    this = (Material *)get();
    this_00 = Ogre::Material::getTechnique(this,uVar2);
    this_01 = Ogre::Technique::getPass(this_00,uVar3);
    this_02 = Ogre::Pass::getTextureUnitState(this_01,uVar4);
    local_18 = Ogre::TextureUnitState::_getTexturePtr(this_02);
    cVar1 = FUN_004c85a0();
    if (cVar1 == '\0') {
      local_1c = (int *)get();
      (**(code **)(*local_1c + 0x15c))(local_28,0,0);
      local_8 = 0;
      local_20 = Ogre::SharedPtr<class_Ogre::HardwarePixelBuffer>::operator->(local_28);
      (**(code **)(*(int *)local_20 + 0x10))();
      local_8 = 0xffffffff;
      Ogre::HardwarePixelBufferSharedPtr::~HardwarePixelBufferSharedPtr
                ((HardwarePixelBufferSharedPtr *)local_28);
    }
  }
  ExceptionList = local_10;
  return;
}

