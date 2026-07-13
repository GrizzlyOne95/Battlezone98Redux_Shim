/*
 * Entry: 005cca96
 * Name: `dynamic_atexit_destructor_for_'Scanner::scannerList''
 * Namespace: `dynamic_atexit_destructor_for_'Scanner
 * Signature: void scannerList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'Scanner::scannerList__(void)

{
  std::vector<Scanner_*,std::allocator<Scanner_*>_>::_Tidy(&Scanner::scannerList);
  operator_delete((void *)Scanner::scannerList._padding_);
  return;
}
