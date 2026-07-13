/*
 * Entry: 005cccf2
 * Name: `dynamic_atexit_destructor_for_'targetCam''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'targetCam''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__targetCam__(void)

{
  DisplayInterface::~DisplayInterface((DisplayInterface *)&targetCam);
  return;
}
