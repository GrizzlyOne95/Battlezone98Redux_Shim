
void FUN_00435e45(void)

{
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  basic_string<>("Plugin_ParticleFX");
  *(undefined4 *)(unaff_EBP + -4) = 9;
  Ogre::Root::loadPlugin
            (*(Root **)(*(int *)(unaff_EBP + -0x94) + 4),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (unaff_EBP + -0x44));
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  ~basic_string<>();
  basic_string<>("Plugin_CgProgramManager");
  *(undefined4 *)(unaff_EBP + -4) = 10;
  Ogre::Root::loadPlugin
            (*(Root **)(*(int *)(unaff_EBP + -0x94) + 4),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (unaff_EBP + -0x74));
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  ~basic_string<>();
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  FUN_0083e885();
  return;
}

