
void FUN_00682450(void)

{
  int iVar1;
  undefined8 uVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  basic_string<>("Setting viewports to game menu mode\n");
  Ogre::Log::logMessage(*(Log **)(DAT_00920ea0 + 0x28),local_20,2,false);
  ~basic_string<>();
  uVar2 = 0;
  if (*(int *)(DAT_00920ea0 + 0x20) != 0) {
    iVar1 = Ogre::Viewport::getZOrder(*(Viewport **)(DAT_00920ea0 + 0x20));
    (**(code **)(**(int **)(DAT_00920ea0 + 0xc) + 0x40))(iVar1);
    *(undefined4 *)(DAT_00920ea0 + 0x20) = 0;
  }
  if (*(int *)(DAT_00920ea0 + 0x24) != 0) {
    iVar1 = Ogre::Viewport::getZOrder(*(Viewport **)(DAT_00920ea0 + 0x24));
    (**(code **)(*DAT_00920e80 + 0x40))(iVar1);
    *(undefined4 *)(DAT_00920ea0 + 0x24) = 0;
  }
  (**(code **)(**(int **)(DAT_00920ea0 + 0xc) + 0x68))(uVar2);
  FUN_0083e885();
  return;
}

