/*
 * Entry: 005cd295
 * Name: `dynamic_atexit_destructor_for_'gameList''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'gameList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__gameList__(void)

{
  SessionList::~SessionList((SessionList *)&gameList);
  return;
}
