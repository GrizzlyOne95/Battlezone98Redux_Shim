
void FUN_006839b0(void)

{
  ResourceGroupManager *this;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar1;
  bool bVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  basic_string<>("Modable");
  bVar2 = true;
  pbVar1 = local_20;
  this = Ogre::ResourceGroupManager::getSingleton();
  Ogre::ResourceGroupManager::unloadResourceGroup(this,pbVar1,bVar2);
  ~basic_string<>();
  FUN_0083e885();
  return;
}

