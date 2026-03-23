
bool __fastcall FUN_007d3d60(int param_1)

{
  bool bVar1;
  VideoClip *this;
  
  if (*(int *)(param_1 + 0x140) == 0) {
    bVar1 = true;
  }
  else {
    this = Ogre::OgreTheoraVideoClip::getClip(*(OgreTheoraVideoClip **)(param_1 + 0x140));
    bVar1 = theoraplayer::VideoClip::isDone(this);
  }
  return bVar1;
}

