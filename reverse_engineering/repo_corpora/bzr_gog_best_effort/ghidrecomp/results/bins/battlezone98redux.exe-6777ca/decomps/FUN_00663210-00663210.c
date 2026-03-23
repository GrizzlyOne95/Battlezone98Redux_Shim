
void __thiscall FUN_00663210(Listener *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  uint uVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  TextureManager *this;
  undefined4 uVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  HardwarePixelBufferSharedPtr local_7c [8];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_74 [8];
  SharedPtr<class_Ogre::HardwarePixelBuffer> *local_6c;
  SharedPtr<class_Ogre::HardwarePixelBuffer> *local_68;
  HardwarePixelBuffer *local_64;
  int *local_60;
  int local_5c;
  Listener *local_58;
  Listener *local_54;
  int *local_50;
  int *local_4c;
  Listener *local_48;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084dc9d;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_48 = param_1;
  local_14 = uVar2;
  Ogre::CompositorInstance::Listener::Listener(param_1);
  local_8 = 0;
  Ogre::RenderTargetListener::RenderTargetListener((RenderTargetListener *)(local_48 + 4));
  local_8._0_1_ = 1;
  Ogre::RenderQueueListener::RenderQueueListener((RenderQueueListener *)(local_48 + 8));
  local_8._0_1_ = 2;
  *(undefined ***)local_48 = RTListener::vftable;
  *(undefined ***)(local_48 + 4) = RTListener::vftable;
  *(undefined ***)(local_48 + 8) = RTListener::vftable;
  FUN_0045e380(uVar2);
  local_8._0_1_ = 3;
  uVar1 = (undefined1)local_8;
  local_8._0_1_ = 3;
  *(undefined4 *)(local_48 + 0x14) = param_2;
  *(undefined4 *)(local_48 + 0x18) = 0;
  if (*(int *)(local_48 + 0x14) != 0) {
    Ogre::CompositorInstance::addListener(*(CompositorInstance **)(local_48 + 0x14),local_48);
    basic_string<>("glowMap");
    local_8._0_1_ = 4;
    pbVar3 = Ogre::CompositorInstance::getTextureInstanceName
                       (*(CompositorInstance **)(local_48 + 0x14),local_44,0);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar3);
    local_8._0_1_ = 6;
    ~basic_string<>();
    pbVar3 = local_2c;
    pbVar5 = local_74;
    this = Ogre::TextureManager::getSingleton();
    Ogre::TextureManager::getByName(this,pbVar5,pbVar3);
    local_8._0_1_ = 7;
    local_60 = (int *)get();
    local_6c = (SharedPtr<class_Ogre::HardwarePixelBuffer> *)
               (**(code **)(*local_60 + 0x15c))(local_7c,0,0);
    local_8._0_1_ = 8;
    local_68 = local_6c;
    local_64 = Ogre::SharedPtr<class_Ogre::HardwarePixelBuffer>::operator->(local_6c);
    uVar4 = (**(code **)(*(int *)local_64 + 0x40))(0);
    *(undefined4 *)(local_48 + 0x18) = uVar4;
    local_8._0_1_ = 7;
    Ogre::HardwarePixelBufferSharedPtr::~HardwarePixelBufferSharedPtr(local_7c);
    local_8._0_1_ = 6;
    FUN_004499a0();
    local_8._0_1_ = 3;
    ~basic_string<>();
    uVar1 = (undefined1)local_8;
  }
  local_8._0_1_ = uVar1;
  if (*(int *)(local_48 + 0x18) != 0) {
    if (local_48 == (Listener *)0x0) {
      local_58 = (Listener *)0x0;
    }
    else {
      local_58 = local_48 + 4;
    }
    (**(code **)(**(int **)(local_48 + 0x18) + 0x70))(local_58);
  }
  local_5c = FUN_0044d2a0();
  if (local_5c == 0) {
    local_50 = (int *)0x0;
  }
  else {
    local_50 = *(int **)(local_5c + 8);
  }
  local_4c = local_50;
  if (local_50 != (int *)0x0) {
    if (local_48 == (Listener *)0x0) {
      local_54 = (Listener *)0x0;
    }
    else {
      local_54 = local_48 + 8;
    }
    (**(code **)(*local_50 + 800))(local_54);
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

