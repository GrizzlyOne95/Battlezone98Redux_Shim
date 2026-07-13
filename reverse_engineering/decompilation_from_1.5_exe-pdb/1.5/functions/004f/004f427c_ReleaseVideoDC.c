/*
 * Entry: 004f427c
 * Name: ReleaseVideoDC
 * Namespace: Global
 * Signature: void ReleaseVideoDC(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ReleaseVideoDC(void)

{
  (*Device.VideoMode.ReleaseVideoDC)(&Device);
  return;
}
