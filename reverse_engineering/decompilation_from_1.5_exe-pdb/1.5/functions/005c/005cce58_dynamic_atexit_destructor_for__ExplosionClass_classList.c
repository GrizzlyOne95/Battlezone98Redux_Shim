/*
 * Entry: 005cce58
 * Name: `dynamic_atexit_destructor_for_'ExplosionClass::classList''
 * Namespace: `dynamic_atexit_destructor_for_'ExplosionClass
 * Signature: void classList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'ExplosionClass::classList__(void)

{
  std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::_Tidy(&ExplosionClass::classList)
  ;
  operator_delete((void *)ExplosionClass::classList._padding_);
  return;
}
