/*
 * Entry: 0054d423
 * Name: Mono_Cleanup
 * Namespace: Global
 * Signature: void Mono_Cleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mono_Cleanup(void)

{
  int iVar1;
  SCREEN *pSVar2;
  bool bVar3;
  
  bVar3 = console_out != (void *)0xffffffff;
  pSVar2 = screens;
  for (iVar1 = 0x20; iVar1 != 0; iVar1 = iVar1 + -1) {
    pSVar2->refresh_callbk = (_func___cdecl_void *)0x0;
    pSVar2 = pSVar2 + 1;
  }
  screen_index = 0;
  active_screen = 0;
  next_empty_screen = 0;
  start_line = 0;
  if (bVar3) {
    FreeConsole();
    console_out = (void *)0xffffffff;
  }
  return;
}
