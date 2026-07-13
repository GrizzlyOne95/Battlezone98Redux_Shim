/*
 * Entry: 004c32fe
 * Name: Device_Get_Palette
 * Namespace: Global
 * Signature: RGB * Device_Get_Palette(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RGB * __cdecl Device_Get_Palette(VIDEO_DEVICE *param_1)

{
  return param_1->Palette;
}
