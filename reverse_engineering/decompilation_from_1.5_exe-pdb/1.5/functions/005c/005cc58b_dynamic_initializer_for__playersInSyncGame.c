/*
 * Entry: 005cc58b
 * Name: `dynamic_initializer_for_'playersInSyncGame''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'playersInSyncGame''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__playersInSyncGame__(void)

{
  PlayerList::PlayerList((PlayerList *)&playersInSyncGame);
  playersInSyncGame._padding_ = (int)&SyncGamePlayerList::_vftable_;
  atexit(_dynamic_atexit_destructor_for__playersInSyncGame__);
  return;
}
