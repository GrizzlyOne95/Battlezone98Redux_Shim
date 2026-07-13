/*
 * Entry: 004712cd
 * Name: StopMusic
 * Namespace: Global
 * Signature: void StopMusic(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl StopMusic(void)

{
  char local_28 [32];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (CDTrackNum != -1) {
    if (MusicOggIdx == -1) {
      if (MusicStarted != 0) {
        PlayerStop();
      }
    }
    else {
      if (MusicStarted != 0) {
        OggManager_Pause(MusicOggIdx);
      }
      OggManager_Release(MusicOggIdx);
      sprintf(local_28,"%02d.ogg",CDTrackNum);
      UnlockItem(local_28);
      MusicOggIdx = -1;
    }
    MusicStarted = 0;
    MusicPaused = 0;
  }
  return;
}
