/*
 * Entry: 004786e9
 * Name: Render_Next_Frame
 * Namespace: Global
 * Signature: void Render_Next_Frame(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Render_Next_Frame(CAMERA *param_1)

{
  CAMERA *unaff_ESI;
  
  if (D3D_Video_Memory_Is_Dirty == 0) {
    (*Device.Refresh.Blit)(&Device);
  }
  cameraView = 0;
  if (useD3D != 0) {
    Render_Hardware_Next_Frame(unaff_ESI);
    return;
  }
  Render_Software_Next_Frame(unaff_ESI);
  return;
}
