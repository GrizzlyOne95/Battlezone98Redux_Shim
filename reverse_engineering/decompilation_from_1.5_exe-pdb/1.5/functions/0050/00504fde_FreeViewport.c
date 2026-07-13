/*
 * Entry: 00504fde
 * Name: FreeViewport
 * Namespace: Global
 * Signature: void FreeViewport(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FreeViewport(VIDEO_DEVICE *param_1)

{
  uchar *_Memory;
  
  if ((param_1->Viewport).Status == 1) {
    if (((param_1->Viewport).Allocated != 1) &&
       (_Memory = (param_1->Viewport).OrBuffer, _Memory != (uchar *)0x0)) {
      free(_Memory);
    }
    (param_1->Viewport).Buffer = (uchar *)0x0;
    (param_1->Viewport).OrBuffer = (uchar *)0x0;
    (param_1->Viewport).Allocated = 1;
  }
  return;
}
