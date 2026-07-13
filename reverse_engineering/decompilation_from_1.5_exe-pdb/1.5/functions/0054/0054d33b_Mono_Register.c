/*
 * Entry: 0054d33b
 * Name: Mono_Register
 * Namespace: Global
 * Signature: long Mono_Register(_func___cdecl_void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Mono_Register(_func___cdecl_void *param_1)

{
  SCREEN *pSVar1;
  
  if (next_empty_screen == 0x20) {
    return 0;
  }
  pSVar1 = screens + next_empty_screen;
  pSVar1->refresh_callbk = param_1;
  next_empty_screen = next_empty_screen + 1;
  return (long)pSVar1;
}
