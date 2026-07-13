/*
 * Entry: 005ca7e3
 * Name: `dynamic_initializer_for_'Craft::craftList''
 * Namespace: `dynamic_initializer_for_'Craft
 * Signature: void craftList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'Craft::craftList__(void)

{
  std::vector<Craft_*,std::allocator<Craft_*>_>::vector<Craft_*,std::allocator<Craft_*>_>
            (&Craft::craftList);
  atexit(`dynamic_atexit_destructor_for_'Craft::craftList__);
  return;
}
