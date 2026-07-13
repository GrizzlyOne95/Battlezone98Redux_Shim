/*
 * Entry: 005cbcc2
 * Name: `dynamic_initializer_for_'targetCam''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'targetCam''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__targetCam__(void)

{
  TargetCam::TargetCam(&targetCam);
  atexit(_dynamic_atexit_destructor_for__targetCam__);
  return;
}
