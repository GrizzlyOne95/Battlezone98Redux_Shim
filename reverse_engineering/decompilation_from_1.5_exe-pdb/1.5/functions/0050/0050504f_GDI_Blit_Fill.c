/*
 * Entry: 0050504f
 * Name: GDI_Blit_Fill
 * Namespace: Global
 * Signature: int GDI_Blit_Fill(VIDEO_DEVICE * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GDI_Blit_Fill(VIDEO_DEVICE *param_1,long param_2)

{
  memset((param_1->Viewport).Buffer,param_2,(param_1->Viewport).Height * (param_1->Viewport).Width);
  return 1;
}
