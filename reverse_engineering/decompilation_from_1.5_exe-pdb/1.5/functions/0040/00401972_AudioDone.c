/*
 * Entry: 00401972
 * Name: AudioDone
 * Namespace: Global
 * Signature: bool AudioDone(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl AudioDone(void)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = IsJapanese();
  if (iVar2 == 0) {
    return true;
  }
  bVar1 = IsAudioMessagePlaying();
  return !bVar1;
}
