/*
 * Entry: 00478b95
 * Name: Device_Get_ShutDown
 * Namespace: Global
 * Signature: int Device_Get_ShutDown(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Device_Get_ShutDown(VIDEO_DEVICE *param_1)

{
  return param_1->ShutDownReq;
}
