/*
 * Entry: 005cbb40
 * Name: `dynamic_initializer_for_'infoDisplay''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'infoDisplay''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__infoDisplay__(void)

{
  InfoDisplay::InfoDisplay(&infoDisplay);
  atexit(_dynamic_atexit_destructor_for__infoDisplay__);
  return;
}
