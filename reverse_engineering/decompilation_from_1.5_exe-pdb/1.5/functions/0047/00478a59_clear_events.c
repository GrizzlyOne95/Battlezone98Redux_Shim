/*
 * Entry: 00478a59
 * Name: clear_events
 * Namespace: Global
 * Signature: void clear_events(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl clear_events(void)

{
  BOOL BVar1;
  MSG local_20;
  
  while( true ) {
    BVar1 = PeekMessageA(&local_20,(HWND)0x0,0,0,1);
    if (BVar1 == 0) break;
    TranslateMessage(&local_20);
    DispatchMessageA(&local_20);
  }
  return;
}
