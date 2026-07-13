/*
 * Entry: 004714a1
 * Name: PauseAudio
 * Namespace: Global
 * Signature: void PauseAudio(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PauseAudio(void)

{
  PauseGAS();
  PauseMusic();
  return;
}
