/*
 * Entry: 00471284
 * Name: UnPauseMusic
 * Namespace: Global
 * Signature: void UnPauseMusic(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnPauseMusic(void)

{
  if ((MusicStarted != 0) && (MusicPaused != 0)) {
    if ((CDTrackNum != -1) && ((UserProfilePtr->audioControl).music != '\0')) {
      if (MusicOggIdx == -1) {
        PlayerPlayOrPause(CDTrackNum);
      }
      else {
        OggManager_Resume(MusicOggIdx);
      }
    }
    MusicPaused = 0;
  }
  return;
}
