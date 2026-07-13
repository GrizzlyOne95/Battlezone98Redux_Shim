/*
 * Entry: 00579828
 * Name: do_audio_options
 * Namespace: Global
 * Signature: void do_audio_options(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl do_audio_options(void)

{
  Shell_DialogBoxParam(shell_hInstance,(char *)0x7c,shell_hwnd,AudioOptionsDlgProc,0);
  return;
}
