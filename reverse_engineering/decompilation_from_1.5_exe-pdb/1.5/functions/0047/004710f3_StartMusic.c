/*
 * Entry: 004710f3
 * Name: StartMusic
 * Namespace: Global
 * Signature: void StartMusic(long param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl StartMusic(long param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  char local_28 [32];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (MusicStarted != 0) {
    return;
  }
  PlayerDone();
  PlayerInit();
  if (param_1 != -1) {
    CDTrackNum = param_1;
  }
  sprintf(local_28,"%02d.ogg",CDTrackNum);
  uVar1 = GetItemSize(local_28);
  iVar2 = CDExists();
  if (((iVar2 == 0) || (iVar2 = PlayerState(), iVar2 == 1)) ||
     (iVar2 = CDTrackExists(CDTrackNum), iVar2 == 0)) {
    if (0 < (int)uVar1) {
      pcVar3 = UseItem(local_28);
      if (pcVar3 == (char *)0x0) {
        return;
      }
      MusicOggIdx = OggManager_Setup(pcVar3,uVar1,0);
      if (MusicOggIdx == -1) {
        return;
      }
      if ((UserProfilePtr->audioControl).music == '\0') {
        return;
      }
      MusicStarted = 1;
      iVar2 = GetRunning();
      MusicStartedFromShell = (int)(iVar2 == 6);
      OggManager_Play(MusicOggIdx);
      SetMusicVolume((uint)(UserProfilePtr->audioControl).music);
      return;
    }
  }
  else {
    if (((UserProfilePtr->audioControl).music == '\0') && (param_2 == 0)) {
      return;
    }
    PlayerTrack(CDTrackNum);
    iVar2 = UpdatePlayerState();
    if (iVar2 == 3) {
      MusicStarted = 1;
      iVar2 = GetRunning();
      MusicStartedFromShell = (uint)(iVar2 == 6);
      return;
    }
  }
  CDTrackNum = -1;
  return;
}
