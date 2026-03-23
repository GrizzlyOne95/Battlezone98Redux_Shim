
void FUN_007d2a00(void)

{
  MaterialManager *this;
  TextureManager *this_00;
  SharedPtr<class_Ogre::Texture> *pSVar1;
  Material *this_01;
  Technique *this_02;
  Pass *this_03;
  TextureUnitState *this_04;
  ushort uVar2;
  ushort uVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar4;
  ushort uVar5;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar6;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [8];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_68 [8];
  undefined4 local_60;
  undefined1 *local_5c;
  undefined4 local_58;
  SharedPtr<class_Ogre::Texture> *local_54;
  undefined4 local_50;
  SharedPtr<class_Ogre::Texture> *local_4c;
  int local_48;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00862b70;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  basic_string<>();
  local_8 = 0;
  pbVar6 = local_44;
  pbVar4 = local_70;
  this = Ogre::MaterialManager::getSingleton();
  local_58 = Ogre::MaterialManager::getByName(this,pbVar4,pbVar6);
  local_8._0_1_ = 1;
  local_50 = local_58;
  FUN_00449910();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004499a0();
  local_8 = 0xffffffff;
  ~basic_string<>();
  basic_string<>();
  local_8 = 2;
  pbVar6 = local_2c;
  pbVar4 = local_68;
  this_00 = Ogre::TextureManager::getSingleton();
  pSVar1 = (SharedPtr<class_Ogre::Texture> *)Ogre::TextureManager::getByName(this_00,pbVar4,pbVar6);
  local_8._0_1_ = 3;
  uVar5 = 0;
  uVar3 = 0;
  uVar2 = 0;
  local_54 = pSVar1;
  local_4c = pSVar1;
  this_01 = (Material *)get();
  this_02 = Ogre::Material::getTechnique(this_01,uVar2);
  this_03 = Ogre::Technique::getPass(this_02,uVar3);
  this_04 = Ogre::Pass::getTextureUnitState(this_03,uVar5);
  Ogre::TextureUnitState::setTexture(this_04,pSVar1);
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_004499a0();
  local_8 = 0xffffffff;
  ~basic_string<>();
  local_5c = &stack0xffffff84;
  local_60 = FUN_004498d0(local_48 + 0x114);
  FUN_007d2b70();
  *(uint *)(local_48 + 0x14) = *(uint *)(local_48 + 0x14) | 0x10;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

