/*
 * Entry: 005cd2a9
 * Name: `dynamic_atexit_destructor_for_'playersInGame''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'playersInGame''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__playersInGame__(void)

{
  PlayerList::~PlayerList((PlayerList *)&playersInGame);
  return;
}
