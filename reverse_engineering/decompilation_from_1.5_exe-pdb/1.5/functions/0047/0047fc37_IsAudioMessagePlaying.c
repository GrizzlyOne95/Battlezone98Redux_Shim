/*
 * Entry: 0047fc37
 * Name: IsAudioMessagePlaying
 * Namespace: Global
 * Signature: bool IsAudioMessagePlaying(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsAudioMessagePlaying(void)

{
  return msgMgr.playing;
}
