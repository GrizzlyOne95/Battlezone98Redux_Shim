/*
 * Entry: 00542fae
 * Name: D3D_Unlock_Buffer
 * Namespace: Global
 * Signature: int D3D_Unlock_Buffer(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl D3D_Unlock_Buffer(VIDEO_DEVICE *param_1)

{
  if (Is_Buffer_Lock != 0) {
    Is_Buffer_Lock = 0;
    (param_1->Viewport).Buffer = (uchar *)0xfff00000;
  }
  return 1;
}
