/*
 * Entry: 005ccde7
 * Name: `dynamic_atexit_destructor_for_'bulletClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'bulletClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__bulletClass__(void)

{
  bulletClass._0_4_ = &BulletClass::_vftable_;
  OrdnanceClass::~OrdnanceClass((OrdnanceClass *)&bulletClass);
  return;
}
