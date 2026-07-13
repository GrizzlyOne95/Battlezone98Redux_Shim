/*
 * Entry: 0057101d
 * Name: stop_load_voice
 * Namespace: Global
 * Signature: int stop_load_voice(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl stop_load_voice(void)

{
  int iVar1;
  
  if (loadVoice == (void *)0x0) {
    return 0;
  }
  iVar1 = ShellIsGASSoundPlaying(loadVoice);
  if (iVar1 != 0) {
    ShellStopGASEvent(loadVoice);
  }
  loadVoice = (void *)0x0;
  return 1;
}
