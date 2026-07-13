/*
 * Entry: 00480764
 * Name: RepeatAudioMessage
 * Namespace: Global
 * Signature: void RepeatAudioMessage(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl RepeatAudioMessage(void)

{
  AudioMessageMgr::RepeatLast(&msgMgr);
  return;
}
