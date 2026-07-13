/*
 * Entry: 005c9ad6
 * Name: `dynamic_initializer_for_'AOI::areas''
 * Namespace: `dynamic_initializer_for_'AOI
 * Signature: void areas''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'AOI::areas__(void)

{
  std::list<AOI_*,std::allocator<AOI_*>_>::list<AOI_*,std::allocator<AOI_*>_>(&AOI::areas);
  atexit(`dynamic_atexit_destructor_for_'AOI::areas__);
  return;
}
