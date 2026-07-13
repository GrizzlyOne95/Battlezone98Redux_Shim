/*
 * Entry: 005cc56b
 * Name: `dynamic_initializer_for_'playersInGame''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'playersInGame''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__playersInGame__(void)

{
  PlayerList::PlayerList((PlayerList *)&playersInGame);
  playersInGame._0_4_ = &GamePlayerList::_vftable_;
  atexit(_dynamic_atexit_destructor_for__playersInGame__);
  return;
}
