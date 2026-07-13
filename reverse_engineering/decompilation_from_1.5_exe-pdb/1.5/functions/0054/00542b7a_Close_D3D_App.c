/*
 * Entry: 00542b7a
 * Name: Close_D3D_App
 * Namespace: Global
 * Signature: void Close_D3D_App(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Close_D3D_App(VIDEO_DEVICE *param_1)

{
  D3D_Flush_Texture_Cache();
  D3DAppDestroy((tagD3DAppInfo *)param_1);
  return;
}
