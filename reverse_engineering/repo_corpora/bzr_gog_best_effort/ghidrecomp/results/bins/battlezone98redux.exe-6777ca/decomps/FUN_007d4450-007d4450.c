
ulong __fastcall FUN_007d4450(int param_1)

{
  ulong uVar1;
  
  if (*(int *)(param_1 + 0x140) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = Ogre::OgreTheoraVideoClip::getSkippedFrames(*(OgreTheoraVideoClip **)(param_1 + 0x140));
  }
  return uVar1;
}

