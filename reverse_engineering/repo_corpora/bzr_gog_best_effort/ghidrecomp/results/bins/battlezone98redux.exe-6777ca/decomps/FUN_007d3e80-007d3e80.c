
void __thiscall FUN_007d3e80(int param_1,int param_2,int param_3,bool param_4)

{
  if (*(int *)(param_1 + 0x140) != 0) {
    Ogre::OgreTheoraVideoClip::playFrames
              (*(OgreTheoraVideoClip **)(param_1 + 0x140),param_2,param_3,param_4);
  }
  return;
}

