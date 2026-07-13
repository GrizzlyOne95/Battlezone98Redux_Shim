/*
 * Entry: 005cc7c3
 * Name: `dynamic_atexit_destructor_for_'Craft::craftList''
 * Namespace: `dynamic_atexit_destructor_for_'Craft
 * Signature: void craftList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'Craft::craftList__(void)

{
  std::vector<Craft_*,std::allocator<Craft_*>_>::_Tidy(&Craft::craftList);
  operator_delete((void *)Craft::craftList._padding_);
  return;
}
