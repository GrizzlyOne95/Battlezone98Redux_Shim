/*
 * Entry: 005ccad8
 * Name: `dynamic_atexit_destructor_for_'scrapClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'scrapClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__scrapClass__(void)

{
  scrapClass._0_4_ = &ScrapClass::_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)&scrapClass);
  return;
}
