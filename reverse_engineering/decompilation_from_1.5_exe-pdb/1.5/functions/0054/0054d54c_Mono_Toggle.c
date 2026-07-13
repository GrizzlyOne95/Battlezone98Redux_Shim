/*
 * Entry: 0054d54c
 * Name: Mono_Toggle
 * Namespace: Global
 * Signature: void Mono_Toggle(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mono_Toggle(void)

{
  SCREEN *pSVar1;
  
  if (active_screen == 0) {
    pSVar1 = screens + screen_index;
  }
  else {
    pSVar1 = (SCREEN *)0x0;
  }
  Mono_SetActive((long)pSVar1);
  return;
}
