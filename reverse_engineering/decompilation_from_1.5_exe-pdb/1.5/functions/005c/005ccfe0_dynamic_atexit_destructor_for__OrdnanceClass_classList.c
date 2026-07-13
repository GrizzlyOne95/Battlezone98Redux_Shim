/*
 * Entry: 005ccfe0
 * Name: `dynamic_atexit_destructor_for_'OrdnanceClass::classList''
 * Namespace: `dynamic_atexit_destructor_for_'OrdnanceClass
 * Signature: void classList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'OrdnanceClass::classList__(void)

{
  std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::_Tidy(&OrdnanceClass::classList);
  operator_delete((void *)OrdnanceClass::classList._padding_);
  return;
}
