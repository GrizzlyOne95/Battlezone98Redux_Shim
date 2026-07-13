/*
 * Entry: 005cd2b3
 * Name: `dynamic_atexit_destructor_for_'playersInSyncGame''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'playersInSyncGame''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__playersInSyncGame__(void)

{
  PlayerList::~PlayerList((PlayerList *)&playersInSyncGame);
  return;
}
