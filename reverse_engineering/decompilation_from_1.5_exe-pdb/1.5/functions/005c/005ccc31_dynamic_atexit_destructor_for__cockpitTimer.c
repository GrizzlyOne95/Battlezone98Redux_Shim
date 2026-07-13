/*
 * Entry: 005ccc31
 * Name: `dynamic_atexit_destructor_for_'cockpitTimer''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'cockpitTimer''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__cockpitTimer__(void)

{
  DisplayInterface::~DisplayInterface((DisplayInterface *)&cockpitTimer);
  return;
}
