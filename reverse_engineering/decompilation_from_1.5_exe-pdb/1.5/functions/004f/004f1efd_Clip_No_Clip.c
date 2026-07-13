/*
 * Entry: 004f1efd
 * Name: __Clip_No_Clip
 * Namespace: Global
 * Signature: long __Clip_No_Clip(CAMERA * param_1, POINT_3D * param_2, POINT_3D * param_3, long param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
__Clip_No_Clip(CAMERA *param_1,POINT_3D *param_2,POINT_3D *param_3,long param_4,long param_5)

{
  memmove(param_2,param_3,param_4 * 0x18);
  return param_4;
}
