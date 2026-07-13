
void FUN_0067cb10(float param_1,float param_2,float param_3)

{
  ColourValue local_14 [16];
  
  if (*(int *)(DAT_00920ea0 + 0x1c) != 0) {
    Ogre::ColourValue::ColourValue(local_14,param_1,param_2,param_3,1.0);
    Ogre::Viewport::setBackgroundColour(*(Viewport **)(DAT_00920ea0 + 0x1c),local_14);
  }
  return;
}

