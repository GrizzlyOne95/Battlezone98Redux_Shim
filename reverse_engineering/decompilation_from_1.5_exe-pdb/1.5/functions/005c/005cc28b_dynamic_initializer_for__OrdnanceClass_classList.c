/*
 * Entry: 005cc28b
 * Name: `dynamic_initializer_for_'OrdnanceClass::classList''
 * Namespace: `dynamic_initializer_for_'OrdnanceClass
 * Signature: void classList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'OrdnanceClass::classList__(void)

{
  std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::
  vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>(&OrdnanceClass::classList);
  atexit(`dynamic_atexit_destructor_for_'OrdnanceClass::classList__);
  return;
}
