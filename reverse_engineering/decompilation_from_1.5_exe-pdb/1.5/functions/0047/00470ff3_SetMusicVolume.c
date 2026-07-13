/*
 * Entry: 00470ff3
 * Name: SetMusicVolume
 * Namespace: Global
 * Signature: void SetMusicVolume(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetMusicVolume(long param_1)

{
  IDirectSoundBuffer IVar1;
  int iVar2;
  IDirectSoundBuffer *pIVar3;
  int extraout_EAX;
  uint local_8;
  
  if (MusicOggIdx == -1) {
    SetCDVolume(param_1);
    return;
  }
  if (0 < param_1) {
    if (MusicStarted != 0) goto LAB_00471049;
    MusicStarted = 1;
    iVar2 = GetRunning();
    MusicStartedFromShell = (int)(iVar2 == 6);
    OggManager_Play(MusicOggIdx);
  }
  if (MusicStarted == 0) {
    return;
  }
LAB_00471049:
  pIVar3 = OggManager_GetDSBuffer(MusicOggIdx);
  if (pIVar3 != (IDirectSoundBuffer *)0x0) {
    iVar2 = (**(code **)((int)*pIVar3 + 0x24))(pIVar3,&local_8);
    if (param_1 < 1) {
      if ((iVar2 == 0) && ((local_8 & 1) != 0)) {
        MusicPaused = 1;
        OggManager_Pause(MusicOggIdx);
      }
      (**(code **)((int)*pIVar3 + 0x3c))(pIVar3,0xffffd8f0);
    }
    else {
      if ((iVar2 == 0) && ((local_8 & 1) == 0)) {
        MusicPaused = 0;
        OggManager_Resume(MusicOggIdx);
      }
      IVar1 = *pIVar3;
      _ftol2_sse();
      (**(code **)((int)IVar1 + 0x3c))(pIVar3,extraout_EAX << 2);
    }
  }
  return;
}
