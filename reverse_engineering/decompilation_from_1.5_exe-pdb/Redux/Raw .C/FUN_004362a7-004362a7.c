
void FUN_004362a7(void)

{
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  *(undefined4 *)(unaff_EBP + -4) = 3;
  if (*(int *)(*(int *)(unaff_EBP + -0x68) + 0x1c) != 0) {
    Ogre::Viewport::_updateDimensions(*(Viewport **)(*(int *)(unaff_EBP + -0x68) + 0x1c));
  }
  FUN_004362fc();
  return;
}

