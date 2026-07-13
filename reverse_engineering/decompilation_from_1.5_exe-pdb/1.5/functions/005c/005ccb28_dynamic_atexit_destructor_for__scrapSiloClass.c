/*
 * Entry: 005ccb28
 * Name: `dynamic_atexit_destructor_for_'scrapSiloClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'scrapSiloClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__scrapSiloClass__(void)

{
  scrapSiloClass._padding_ = (int)&ScrapSiloClass::_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)&scrapSiloClass);
  return;
}
