/*
 * Entry: 0054d318
 * Name: Mono_Init
 * Namespace: Global
 * Signature: void Mono_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mono_Init(void)

{
  int iVar1;
  SCREEN *pSVar2;
  
  pSVar2 = screens;
  for (iVar1 = 0x20; iVar1 != 0; iVar1 = iVar1 + -1) {
    pSVar2->refresh_callbk = (_func___cdecl_void *)0x0;
    pSVar2 = pSVar2 + 1;
  }
  screen_index = 0;
  active_screen = 0;
  next_empty_screen = 0;
  start_line = 0;
  return;
}
