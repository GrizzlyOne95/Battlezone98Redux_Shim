/*
 * Entry: 0057980a
 * Name: do_graphic_options
 * Namespace: Global
 * Signature: void do_graphic_options(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl do_graphic_options(void)

{
  Shell_DialogBoxParam(shell_hInstance,(char *)0x79,shell_hwnd,GraphicOptionsDlgProc,0);
  return;
}
