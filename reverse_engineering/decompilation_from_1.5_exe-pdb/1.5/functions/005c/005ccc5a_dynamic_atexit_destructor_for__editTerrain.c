/*
 * Entry: 005ccc5a
 * Name: `dynamic_atexit_destructor_for_'editTerrain''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'editTerrain''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__editTerrain__(void)

{
  DisplayInterface::~DisplayInterface((DisplayInterface *)&editTerrain);
  return;
}
