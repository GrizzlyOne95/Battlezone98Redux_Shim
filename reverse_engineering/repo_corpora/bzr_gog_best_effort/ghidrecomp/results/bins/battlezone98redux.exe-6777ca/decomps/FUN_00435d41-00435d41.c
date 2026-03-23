
void FUN_00435d41(void)

{
  undefined4 uVar1;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  *(undefined4 *)(unaff_EBP + -4) = 3;
  uVar1 = basic_string<>("RenderSystem_Direct3D11");
  *(undefined4 *)(unaff_EBP + -0xa0) = uVar1;
  *(undefined1 *)(unaff_EBP + -4) = 4;
  Ogre::Root::loadPlugin
            (*(Root **)(*(int *)(unaff_EBP + -0x94) + 4),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (unaff_EBP + -0x5c));
  *(undefined1 *)(unaff_EBP + -4) = 3;
  ~basic_string<>();
  *(int *)(unaff_EBP + -0x90) = *(int *)(unaff_EBP + -0x90) + 1;
  FUN_00435da5();
  return;
}

