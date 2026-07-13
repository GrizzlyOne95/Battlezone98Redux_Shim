/*
 * Entry: 0047a756
 * Name: Device_Get_Graphic_Buffer
 * Namespace: Global
 * Signature: _GRAPHIC_BUFFER * Device_Get_Graphic_Buffer(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_GRAPHIC_BUFFER * __cdecl Device_Get_Graphic_Buffer(VIDEO_DEVICE *param_1)

{
  return &param_1->Viewport;
}
