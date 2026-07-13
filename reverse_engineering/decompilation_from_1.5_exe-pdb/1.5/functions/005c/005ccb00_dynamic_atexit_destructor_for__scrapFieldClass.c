/*
 * Entry: 005ccb00
 * Name: `dynamic_atexit_destructor_for_'scrapFieldClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'scrapFieldClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__scrapFieldClass__(void)

{
  scrapFieldClass._0_4_ = &ScrapFieldClass::_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)&scrapFieldClass);
  return;
}
