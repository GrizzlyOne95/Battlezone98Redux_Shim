/*
 * Entry: 005ccc1d
 * Name: `dynamic_atexit_destructor_for_'hardPoints''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'hardPoints''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__hardPoints__(void)

{
  DisplayInterface::~DisplayInterface((DisplayInterface *)&hardPoints);
  return;
}
