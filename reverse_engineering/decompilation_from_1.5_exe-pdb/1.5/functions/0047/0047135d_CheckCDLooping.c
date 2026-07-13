/*
 * Entry: 0047135d
 * Name: CheckCDLooping
 * Namespace: Global
 * Signature: void CheckCDLooping(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CheckCDLooping(void)

{
  IDirectSoundBuffer *pIVar1;
  int iVar2;
  DWORD DVar3;
  uint local_8;
  
  if (MusicOggIdx == -1) {
    if ((MusicStarted != 0) && (DVar3 = Get_TimeNow(), RedbookAudio_TimeStamp < (int)DVar3)) {
      if (MusicStartedFromShell == 0) {
        RedbookAudio_TimeStamp = DVar3 + 60000;
      }
      else {
        RedbookAudio_TimeStamp = DVar3 + 5000;
      }
      iVar2 = PlayerState();
      if ((iVar2 == 1) || (iVar2 == 5)) {
        MusicPaused = 0;
        MusicStarted = 0;
      }
      else if ((((MusicPaused == 0) && (1 < (UserProfilePtr->audioControl).music)) &&
               (iVar2 = PlayerUpdate(), iVar2 != 0)) && (CDTrackNum != -1)) {
        iVar2 = CDTrackNum;
        if (MusicStartedFromShell == 0) {
          iVar2 = 2;
        }
        PlayerTrack(iVar2);
        UpdatePlayerState();
      }
    }
  }
  else if ((MusicStarted != 0) && (MusicPaused == 0)) {
    pIVar1 = OggManager_GetDSBuffer(MusicOggIdx);
    iVar2 = (**(code **)((int)*pIVar1 + 0x24))(pIVar1,&local_8);
    if ((iVar2 == 0) && ((local_8 & 1) == 0)) {
      if (MusicStartedFromShell == 0) {
        StopMusic();
        CDTrackNum = CDTrackNum + 1;
        if (CDTrackNum == 0xc) {
          CDTrackNum = 0xd;
        }
        if (0x10 < CDTrackNum) {
          CDTrackNum = 2;
        }
        StartMusic(CDTrackNum,0);
      }
      else {
        OggManager_Stop(MusicOggIdx);
        OggManager_Play(MusicOggIdx);
      }
    }
  }
  return;
}
