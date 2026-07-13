/*
 * Entry: 005cc9f3
 * Name: `dynamic_atexit_destructor_for_'personClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'personClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__personClass__(void)

{
  personClass._padding_ = (int)&PersonClass::_vftable_;
  CraftClass::~CraftClass((CraftClass *)&personClass);
  return;
}
