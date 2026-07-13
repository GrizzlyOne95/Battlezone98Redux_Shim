
void FUN_00662f60(void)

{
  MaterialManager *this;
  Material *this_00;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar1;
  float fVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  float fVar4;
  float fVar5;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_5c [8];
  undefined4 local_54;
  undefined4 local_50;
  MaterialManager *local_4c;
  undefined4 *local_48;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084dbeb;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_006631f0(local_14);
  local_8 = 0;
  *local_48 = MatListener::vftable;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(local_48 + 1));
  local_8._0_1_ = 1;
  basic_string<>("Glow/Null");
  local_8._0_1_ = 2;
  pbVar3 = local_44;
  pbVar1 = local_5c;
  this = Ogre::MaterialManager::getSingleton();
  local_54 = Ogre::MaterialManager::getByName(this,pbVar1,pbVar3);
  local_8._0_1_ = 3;
  local_50 = local_54;
  FUN_00449910(local_54);
  local_8._0_1_ = 2;
  FUN_004499a0();
  local_8._0_1_ = 1;
  ~basic_string<>();
  fVar5 = 0.0;
  fVar4 = 0.0;
  fVar2 = 0.0;
  this_00 = (Material *)get();
  Ogre::Material::setSelfIllumination(this_00,fVar2,fVar4,fVar5);
  basic_string<>(&DAT_00892124);
  local_8._0_1_ = 4;
  local_4c = Ogre::MaterialManager::getSingleton();
  (**(code **)(*(int *)local_4c + 0xac))(local_48,local_2c);
  local_8 = CONCAT31(local_8._1_3_,1);
  ~basic_string<>();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

