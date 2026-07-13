/*
 * Entry: 005cc7f1
 * Name: `dynamic_atexit_destructor_for_'Explosion::explosionList''
 * Namespace: `dynamic_atexit_destructor_for_'Explosion
 * Signature: void explosionList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'Explosion::explosionList__(void)

{
  std::list<Explosion_*,std::allocator<Explosion_*>_>::_Tidy(&Explosion::explosionList);
  operator_delete((void *)Explosion::explosionList._padding_);
  return;
}
