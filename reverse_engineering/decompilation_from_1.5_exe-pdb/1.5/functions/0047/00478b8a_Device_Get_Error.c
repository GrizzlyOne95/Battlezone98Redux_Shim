/*
 * Entry: 00478b8a
 * Name: Device_Get_Error
 * Namespace: Global
 * Signature: DEVICE_ERROR Device_Get_Error(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DEVICE_ERROR __cdecl Device_Get_Error(VIDEO_DEVICE *param_1)

{
  return param_1->Error;
}
