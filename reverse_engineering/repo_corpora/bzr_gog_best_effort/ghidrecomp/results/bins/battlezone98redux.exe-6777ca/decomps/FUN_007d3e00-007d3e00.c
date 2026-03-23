
void __thiscall FUN_007d3e00(int param_1,int param_2,char param_3)

{
  VideoClip *pVVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x140) != 0) {
    pVVar1 = Ogre::OgreTheoraVideoClip::getClip(*(OgreTheoraVideoClip **)(param_1 + 0x140));
    theoraplayer::VideoClip::setPlaybackSpeed(pVVar1,1.0);
    if (param_3 != '\0') {
      iVar2 = param_2;
      pVVar1 = Ogre::OgreTheoraVideoClip::getClip(*(OgreTheoraVideoClip **)(param_1 + 0x140));
      theoraplayer::VideoClip::seekToFrame(pVVar1,iVar2);
    }
    Ogre::OgreTheoraVideoClip::playAndReplayFromFrame
              (*(OgreTheoraVideoClip **)(param_1 + 0x140),param_2);
  }
  return;
}

