
void FUN_00685fa0(void)

{
  bool bVar1;
  ManualObject *local_2c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_2c = Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<4>_>::operator_new(0x214);
  bVar1 = local_2c == (ManualObject *)0x0;
  if (bVar1) {
    local_2c = (ManualObject *)0x0;
  }
  else {
    basic_string<>(&DAT_0088b2d8);
    Ogre::ManualObject::ManualObject(local_2c,local_20);
    *(undefined ***)local_2c = Ogre::ManualObject::vftable;
    *(undefined ***)(local_2c + 4) = Ogre::ManualObject::vftable;
  }
  DAT_00920edc = (undefined4 *)local_2c;
  if (!bVar1) {
    ~basic_string<>();
  }
  FUN_0083e885();
  return;
}

