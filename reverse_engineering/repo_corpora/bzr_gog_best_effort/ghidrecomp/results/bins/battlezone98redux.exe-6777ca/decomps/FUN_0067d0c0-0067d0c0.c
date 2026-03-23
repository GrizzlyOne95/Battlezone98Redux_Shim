
void FUN_0067d0c0(void)

{
  int iVar1;
  
  (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x198))();
  (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x140))();
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
  return;
}

