/*
 * Entry: 00579866
 * Name: do_input_config
 * Namespace: Global
 * Signature: void do_input_config(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl do_input_config(void)

{
  Shell_DialogBoxParam(shell_hInstance,(char *)0x83,shell_hwnd,InputConfigDlgProc,0);
  return;
}
