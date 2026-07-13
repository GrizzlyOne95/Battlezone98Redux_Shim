/*
 * Entry: 005cb592
 * Name: `dynamic_initializer_for_'Scrap::scrapList''
 * Namespace: `dynamic_initializer_for_'Scrap
 * Signature: void scrapList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'Scrap::scrapList__(void)

{
  std::vector<Scrap_*,std::allocator<Scrap_*>_>::vector<Scrap_*,std::allocator<Scrap_*>_>
            (&Scrap::scrapList);
  atexit(`dynamic_atexit_destructor_for_'Scrap::scrapList__);
  return;
}
