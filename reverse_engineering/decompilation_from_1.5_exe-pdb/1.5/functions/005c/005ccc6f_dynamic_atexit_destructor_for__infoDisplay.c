/*
 * Entry: 005ccc6f
 * Name: `dynamic_atexit_destructor_for_'infoDisplay''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'infoDisplay''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__infoDisplay__(void)

{
  DisplayInterface::~DisplayInterface((DisplayInterface *)&infoDisplay);
  return;
}
