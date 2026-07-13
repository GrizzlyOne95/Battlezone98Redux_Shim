/*
 * Entry: 005cc985
 * Name: `dynamic_atexit_destructor_for_'geizerClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'geizerClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__geizerClass__(void)

{
  geizerClass._0_4_ = &GeizerClass::_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)&geizerClass);
  return;
}
