/*
 * Entry: 0047123b
 * Name: PauseMusic
 * Namespace: Global
 * Signature: void PauseMusic(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PauseMusic(void)

{
  if ((MusicStarted != 0) && (MusicPaused == 0)) {
    if ((CDTrackNum != -1) && ((UserProfilePtr->audioControl).music != '\0')) {
      if (MusicOggIdx == -1) {
        PlayerPlayOrPause(0);
      }
      else {
        OggManager_Pause(MusicOggIdx);
      }
    }
    MusicPaused = 1;
  }
  return;
}
