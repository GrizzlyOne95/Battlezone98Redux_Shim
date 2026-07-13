/*
 * Entry: 005cb5a8
 * Name: `dynamic_initializer_for_'scrapClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'scrapClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__scrapClass__(void)

{
  ScrapClass::ScrapClass(&scrapClass);
  atexit(_dynamic_atexit_destructor_for__scrapClass__);
  return;
}
