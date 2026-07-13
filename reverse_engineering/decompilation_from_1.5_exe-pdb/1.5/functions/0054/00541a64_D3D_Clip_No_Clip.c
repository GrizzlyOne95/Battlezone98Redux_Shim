/*
 * Entry: 00541a64
 * Name: D3D_Clip_No_Clip
 * Namespace: Global
 * Signature: long D3D_Clip_No_Clip(CAMERA * param_1, POINT_3D * param_2, POINT_3D * param_3, long param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
D3D_Clip_No_Clip(CAMERA *param_1,POINT_3D *param_2,POINT_3D *param_3,long param_4,long param_5)

{
  memmove(param_2,param_3,param_4 * 0x18);
  return param_4;
}
