/*
 * Entry: 004ebaa2
 * Name: RDBlit
 * Namespace: Global
 * Signature: int RDBlit(_GRAPHIC_BUFFER * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl RDBlit(_GRAPHIC_BUFFER *param_1)

{
  int iVar1;
  
  iVar1 = (*Device.VideoMode.LockBuffer)(&Device);
  if (iVar1 == 0) {
    return 0;
  }
  if ((Device.Viewport.Width == param_1->Width) && (Device.Viewport.Height == param_1->Height)) {
    Graphic_Copy_Bitmap(&Device.Viewport,param_1,0,0,SOLID_PIXELS);
  }
  else {
    Graphic_Stretch_Bitmap
              (&Device.Viewport,param_1,0,0,Device.Viewport.Width,Device.Viewport.Height,
               SOLID_PIXELS,0);
  }
  (*Device.VideoMode.UnlockBuffer)(&Device);
  (*Device.Refresh.Blit)(&Device);
  return 1;
}
