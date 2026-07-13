/*
 * Entry: 005cbed8
 * Name: `dynamic_initializer_for_'ExplosionClass::classList''
 * Namespace: `dynamic_initializer_for_'ExplosionClass
 * Signature: void classList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'ExplosionClass::classList__(void)

{
  std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::
  vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>(&ExplosionClass::classList);
  atexit(`dynamic_atexit_destructor_for_'ExplosionClass::classList__);
  return;
}
