/*
 * Entry: 005cb3b3
 * Name: `dynamic_initializer_for_'Geizer::geizerList''
 * Namespace: `dynamic_initializer_for_'Geizer
 * Signature: void geizerList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'Geizer::geizerList__(void)

{
  std::vector<Geizer_*,std::allocator<Geizer_*>_>::vector<Geizer_*,std::allocator<Geizer_*>_>
            (&Geizer::geizerList);
  atexit(`dynamic_atexit_destructor_for_'Geizer::geizerList__);
  return;
}
