
void FUN_0067cb70(float param_1,float param_2,float param_3)

{
  ColourValue local_14 [16];
  
  if (*(int *)(DAT_00920ea0 + 0x24) != 0) {
    Ogre::ColourValue::ColourValue(local_14,param_1,param_2,param_3,1.0);
    Ogre::Viewport::setBackgroundColour(*(Viewport **)(DAT_00920ea0 + 0x24),local_14);
    Ogre::Viewport::setClearEveryFrame(*(Viewport **)(DAT_00920ea0 + 0x24),true,3);
    Ogre::Viewport::setDepthClear(*(Viewport **)(DAT_00920ea0 + 0x24),1.0);
    Ogre::Viewport::setVisibilityMask(*(Viewport **)(DAT_00920ea0 + 0x24),8);
  }
  return;
}

