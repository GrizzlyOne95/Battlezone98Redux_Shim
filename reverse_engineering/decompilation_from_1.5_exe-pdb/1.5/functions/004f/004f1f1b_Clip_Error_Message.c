/*
 * Entry: 004f1f1b
 * Name: __Clip_Error_Message
 * Namespace: Global
 * Signature: long __Clip_Error_Message(CAMERA * param_1, POINT_3D * param_2, POINT_3D * param_3, long param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
__Clip_Error_Message(CAMERA *param_1,POINT_3D *param_2,POINT_3D *param_3,long param_4,long param_5)

{
  DEBUG_systemError("Error in clipping function\n");
  return 0;
}
