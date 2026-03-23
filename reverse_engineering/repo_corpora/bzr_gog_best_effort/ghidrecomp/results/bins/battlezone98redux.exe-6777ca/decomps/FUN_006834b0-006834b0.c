
void FUN_006834b0(void)

{
  Root *pRVar1;
  RenderSystem *pRVar2;
  int iVar3;
  undefined1 *puVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_78;
  undefined1 local_68 [24];
  undefined1 local_50 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_38 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_007d6a70("Updating Window fullscreen mode via toggle\n");
  basic_string<>("Full Screen");
  pRVar1 = Ogre::Root::getSingleton();
  pRVar2 = Ogre::Root::getRenderSystem(pRVar1);
  puVar4 = local_68;
  (**(code **)(*(int *)pRVar2 + 0xc))(puVar4);
  iVar3 = FUN_004b2f10(puVar4);
  ~basic_string<>();
  basic_string<>(&DAT_00873de0);
  basic_string<>(&DAT_00873e10);
  iVar3 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::compare
                    ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
                     )(iVar3 + 0x18),local_20);
  if (iVar3 == 0) {
    local_78 = local_38;
  }
  else {
    local_78 = local_20;
  }
  basic_string<>("Full Screen");
  pRVar1 = Ogre::Root::getSingleton();
  pRVar2 = Ogre::Root::getRenderSystem(pRVar1);
  (**(code **)(*(int *)pRVar2 + 0x10))(local_50,local_78);
  ~basic_string<>();
  FUN_00683620(1,1);
  DAT_00920ed0 = 0;
  ~basic_string<>();
  ~basic_string<>();
  FUN_0083e885();
  return;
}

