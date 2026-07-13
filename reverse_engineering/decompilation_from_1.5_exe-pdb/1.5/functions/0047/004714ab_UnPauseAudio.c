/*
 * Entry: 004714ab
 * Name: UnPauseAudio
 * Namespace: Global
 * Signature: void UnPauseAudio(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnPauseAudio(void)

{
  UnPauseGAS();
  UnPauseMusic();
  return;
}
