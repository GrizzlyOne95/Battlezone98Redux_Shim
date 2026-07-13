/*
 * Entry: 005cc96e
 * Name: `dynamic_atexit_destructor_for_'Geizer::geizerList''
 * Namespace: `dynamic_atexit_destructor_for_'Geizer
 * Signature: void geizerList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'Geizer::geizerList__(void)

{
  std::vector<Geizer_*,std::allocator<Geizer_*>_>::_Tidy(&Geizer::geizerList);
  operator_delete((void *)Geizer::geizerList._padding_);
  return;
}
