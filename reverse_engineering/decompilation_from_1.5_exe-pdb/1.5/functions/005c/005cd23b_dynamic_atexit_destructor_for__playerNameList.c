/*
 * Entry: 005cd23b
 * Name: `dynamic_atexit_destructor_for_'playerNameList''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'playerNameList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__playerNameList__(void)

{
  playerNameList.hwnd = (HWND__ *)0x0;
  PlayerNameList::Init(&playerNameList);
  return;
}
