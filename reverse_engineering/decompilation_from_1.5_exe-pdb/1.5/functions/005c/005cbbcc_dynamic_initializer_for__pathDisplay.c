/*
 * Entry: 005cbbcc
 * Name: `dynamic_initializer_for_'pathDisplay''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'pathDisplay''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__pathDisplay__(void)

{
  PathDisplay::PathDisplay((PathDisplay *)&pathDisplay);
  atexit(_dynamic_atexit_destructor_for__pathDisplay__);
  return;
}
