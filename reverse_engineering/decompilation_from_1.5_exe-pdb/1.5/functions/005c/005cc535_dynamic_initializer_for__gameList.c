/*
 * Entry: 005cc535
 * Name: `dynamic_initializer_for_'gameList''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'gameList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__gameList__(void)

{
  SessionList::SessionList((SessionList *)&gameList);
  gameList._0_4_ = &GameSessionList::_vftable_;
  atexit(_dynamic_atexit_destructor_for__gameList__);
  return;
}
