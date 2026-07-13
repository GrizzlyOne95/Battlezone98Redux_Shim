/*
 * Entry: 005cb7d8
 * Name: `dynamic_initializer_for_'selectionDisplay''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'selectionDisplay''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__selectionDisplay__(void)

{
  SelectionDisplay::SelectionDisplay(&selectionDisplay);
  atexit(_dynamic_atexit_destructor_for__selectionDisplay__);
  return;
}
