
void FUN_0067cc20(void)

{
  TextureManager *this;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_58 [8];
  undefined1 local_50 [24];
  undefined1 local_38 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  (**(code **)(*DAT_00920e80 + 0x44))();
  basic_string<>("SniperTex");
  pbVar2 = local_20;
  pbVar1 = local_58;
  this = Ogre::TextureManager::getSingleton();
  Ogre::TextureManager::getByName(this,pbVar1,pbVar2);
  ~basic_string<>();
  FUN_004c85d0();
  FUN_004c85d0();
  basic_string<>("scope");
  FUN_00665f20(local_38);
  ~basic_string<>();
  basic_string<>("SniperTex");
  FUN_00665f40(local_50);
  ~basic_string<>();
  FUN_004499a0();
  FUN_0083e885();
  return;
}

