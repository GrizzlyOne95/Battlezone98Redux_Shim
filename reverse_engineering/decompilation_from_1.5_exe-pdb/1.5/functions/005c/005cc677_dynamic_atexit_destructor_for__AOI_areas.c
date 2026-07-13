/*
 * Entry: 005cc677
 * Name: `dynamic_atexit_destructor_for_'AOI::areas''
 * Namespace: `dynamic_atexit_destructor_for_'AOI
 * Signature: void areas''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'AOI::areas__(void)

{
  std::list<AOI_*,std::allocator<AOI_*>_>::_Tidy(&AOI::areas);
  operator_delete((void *)AOI::areas._padding_);
  return;
}
