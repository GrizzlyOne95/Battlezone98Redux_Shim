
void __fastcall FUN_007c6a30(FrameListener *param_1)

{
  int iVar1;
  Root *this;
  WindowEventListener *local_c;
  
  if (param_1 == (FrameListener *)0x0) {
    local_c = (WindowEventListener *)0x0;
  }
  else {
    local_c = (WindowEventListener *)(param_1 + 4);
  }
  iVar1 = FUN_0044d2a0();
  Ogre::WindowEventUtilities::removeWindowEventListener(*(RenderWindow **)(iVar1 + 0xc),local_c);
  this = Ogre::Root::getSingletonPtr();
  Ogre::Root::removeFrameListener(this,param_1);
  return;
}

