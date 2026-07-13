/*
 * Entry: 005ccc13
 * Name: `dynamic_atexit_destructor_for_'selectionDisplay''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'selectionDisplay''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__selectionDisplay__(void)

{
  DisplayInterface::~DisplayInterface((DisplayInterface *)&selectionDisplay);
  return;
}
