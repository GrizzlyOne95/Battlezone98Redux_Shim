/*
 * Entry: 005cd29f
 * Name: `dynamic_atexit_destructor_for_'playersInRoom''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'playersInRoom''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__playersInRoom__(void)

{
  PlayerList::~PlayerList(&playersInRoom);
  return;
}
