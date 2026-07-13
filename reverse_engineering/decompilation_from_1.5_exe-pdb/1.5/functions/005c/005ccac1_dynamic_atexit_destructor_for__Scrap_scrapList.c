/*
 * Entry: 005ccac1
 * Name: `dynamic_atexit_destructor_for_'Scrap::scrapList''
 * Namespace: `dynamic_atexit_destructor_for_'Scrap
 * Signature: void scrapList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'Scrap::scrapList__(void)

{
  std::vector<Scrap_*,std::allocator<Scrap_*>_>::_Tidy(&Scrap::scrapList);
  operator_delete((void *)Scrap::scrapList._padding_);
  return;
}
