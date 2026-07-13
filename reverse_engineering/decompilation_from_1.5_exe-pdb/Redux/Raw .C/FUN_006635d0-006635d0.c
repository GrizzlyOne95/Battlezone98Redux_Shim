
void __fastcall FUN_006635d0(int param_1)

{
  uint uVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  TextureManager *this;
  undefined4 uVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar4;
  HardwarePixelBufferSharedPtr local_6c [8];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_64 [8];
  SharedPtr<class_Ogre::HardwarePixelBuffer> *local_5c;
  SharedPtr<class_Ogre::HardwarePixelBuffer> *local_58;
  int local_54;
  int *local_50;
  HardwarePixelBuffer *local_4c;
  int local_48;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084dd41;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_48 = param_1;
  local_14 = uVar1;
  if (*(int *)(param_1 + 0x14) == 0) {
    *(undefined4 *)(param_1 + 0x18) = 0;
  }
  else {
    basic_string<>("glowMap");
    local_8 = 0;
    pbVar2 = Ogre::CompositorInstance::getTextureInstanceName
                       (*(CompositorInstance **)(local_48 + 0x14),local_44,0);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar2);
    local_8._0_1_ = 2;
    ~basic_string<>();
    pbVar2 = local_2c;
    pbVar4 = local_64;
    this = Ogre::TextureManager::getSingleton();
    Ogre::TextureManager::getByName(this,pbVar4,pbVar2);
    local_8._0_1_ = 3;
    local_50 = (int *)get();
    local_5c = (SharedPtr<class_Ogre::HardwarePixelBuffer> *)
               (**(code **)(*local_50 + 0x15c))(local_6c,0,0);
    local_8._0_1_ = 4;
    local_58 = local_5c;
    local_4c = Ogre::SharedPtr<class_Ogre::HardwarePixelBuffer>::operator->(local_5c);
    uVar3 = (**(code **)(*(int *)local_4c + 0x40))(0);
    *(undefined4 *)(local_48 + 0x18) = uVar3;
    local_8._0_1_ = 3;
    Ogre::HardwarePixelBufferSharedPtr::~HardwarePixelBufferSharedPtr(local_6c);
    local_8 = CONCAT31(local_8._1_3_,2);
    FUN_004499a0();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  if (*(int *)(local_48 + 0x18) != 0) {
    if (local_48 == 0) {
      local_54 = 0;
    }
    else {
      local_54 = local_48 + 4;
    }
    (**(code **)(**(int **)(local_48 + 0x18) + 0x70))(local_54,uVar1);
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

