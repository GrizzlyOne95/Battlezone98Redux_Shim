/*
 * Entry: 0048099b
 * Name: StopAudioMessage
 * Namespace: Global
 * Signature: void StopAudioMessage(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl StopAudioMessage(int param_1)

{
  AudioMessageMgr::Stop(&msgMgr,param_1);
  return;
}
