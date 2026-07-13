/*
 * Entry: 00570ffb
 * Name: check_load_voice
 * Namespace: Global
 * Signature: int check_load_voice(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl check_load_voice(void)

{
  int iVar1;
  
  if (loadVoice != (void *)0x0) {
    iVar1 = ShellIsGASSoundPlaying(loadVoice);
    if (iVar1 != 0) {
      return 1;
    }
    loadVoice = (void *)0x0;
  }
  return 0;
}
