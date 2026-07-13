/*
 * Entry: 005ca83b
 * Name: `dynamic_initializer_for_'Explosion::explosionList''
 * Namespace: `dynamic_initializer_for_'Explosion
 * Signature: void explosionList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'Explosion::explosionList__(void)

{
  std::list<Explosion_*,std::allocator<Explosion_*>_>::
  list<Explosion_*,std::allocator<Explosion_*>_>(&Explosion::explosionList);
  atexit(`dynamic_atexit_destructor_for_'Explosion::explosionList__);
  return;
}
