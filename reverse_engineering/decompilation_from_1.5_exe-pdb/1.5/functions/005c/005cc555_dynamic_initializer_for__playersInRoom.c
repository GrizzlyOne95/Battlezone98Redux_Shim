/*
 * Entry: 005cc555
 * Name: `dynamic_initializer_for_'playersInRoom''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'playersInRoom''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__playersInRoom__(void)

{
  PlayerList::PlayerList(&playersInRoom);
  atexit(_dynamic_atexit_destructor_for__playersInRoom__);
  return;
}
