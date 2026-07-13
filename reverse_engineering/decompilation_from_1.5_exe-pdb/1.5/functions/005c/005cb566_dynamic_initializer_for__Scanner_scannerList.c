/*
 * Entry: 005cb566
 * Name: `dynamic_initializer_for_'Scanner::scannerList''
 * Namespace: `dynamic_initializer_for_'Scanner
 * Signature: void scannerList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'Scanner::scannerList__(void)

{
  std::vector<Scanner_*,std::allocator<Scanner_*>_>::vector<Scanner_*,std::allocator<Scanner_*>_>
            (&Scanner::scannerList);
  atexit(`dynamic_atexit_destructor_for_'Scanner::scannerList__);
  return;
}
