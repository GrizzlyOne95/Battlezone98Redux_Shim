
void FUN_00682390(void)

{
  int iVar1;
  undefined4 uVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_0067f240();
  DAT_00920c6f = 0;
  uVar2 = 1;
  (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x4f8))(1);
  basic_string<>("Start main loop...");
  Ogre::Log::logMessage(*(Log **)(DAT_00920ea0 + 0x28),local_20,2,false);
  ~basic_string<>();
  (**(code **)(**(int **)(DAT_00920ea0 + 0xc) + 0x68))(uVar2,0,0);
  iVar1 = FUN_00685520();
  if (iVar1 == 0) {
    FUN_006854b0();
    FUN_006854d0();
  }
  FUN_0083e885();
  return;
}

