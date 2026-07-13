
void FUN_0067ca70(float param_1,float param_2,float param_3)

{
  ColourValue local_14 [16];
  
  Ogre::ColourValue::ColourValue(local_14,param_1,param_2,param_3,1.0);
  if (*(int *)(DAT_00920ea0 + 0x1c) != 0) {
    Ogre::Viewport::setBackgroundColour(*(Viewport **)(DAT_00920ea0 + 0x1c),local_14);
  }
  if (*(int *)(DAT_00920ea0 + 0x20) != 0) {
    Ogre::Viewport::setBackgroundColour(*(Viewport **)(DAT_00920ea0 + 0x20),local_14);
  }
  if (*(int *)(DAT_00920ea0 + 0x24) != 0) {
    Ogre::Viewport::setBackgroundColour(*(Viewport **)(DAT_00920ea0 + 0x24),local_14);
  }
  return;
}

