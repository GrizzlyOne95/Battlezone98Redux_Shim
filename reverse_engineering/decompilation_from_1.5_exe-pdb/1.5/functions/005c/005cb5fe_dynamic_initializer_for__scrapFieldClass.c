/*
 * Entry: 005cb5fe
 * Name: `dynamic_initializer_for_'scrapFieldClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'scrapFieldClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__scrapFieldClass__(void)

{
  ScrapFieldClass::ScrapFieldClass(&scrapFieldClass);
  atexit(_dynamic_atexit_destructor_for__scrapFieldClass__);
  return;
}
