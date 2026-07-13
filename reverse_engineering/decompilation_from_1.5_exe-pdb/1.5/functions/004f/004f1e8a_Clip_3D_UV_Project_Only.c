/*
 * Entry: 004f1e8a
 * Name: __Clip_3D_UV_Project_Only
 * Namespace: Global
 * Signature: long __Clip_3D_UV_Project_Only(CAMERA * param_1, POINT_3D * param_2, POINT_3D * param_3, long param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
__Clip_3D_UV_Project_Only
          (CAMERA *param_1,POINT_3D *param_2,POINT_3D *param_3,long param_4,long param_5)

{
  float fVar1;
  long lVar2;
  
  if (0 < param_4) {
    lVar2 = param_4;
    do {
      fVar1 = 1.0 / (param_3->Vector).z;
      (param_2->Vector).x = (param_3->Vector).x * param_1->Const_x * fVar1 + param_1->Orig_x;
      (param_2->Vector).y = (param_3->Vector).y * fVar1 * param_1->Const_y + param_1->Orig_y;
      (param_2->Vector).z = fVar1;
      (param_2->Texel).field2_0x8 = (param_3->Texel).field2_0x8;
      if ((param_5 & 0x10U) == 0) {
        (param_2->Texel).u = (param_3->Texel).u;
        fVar1 = (param_3->Texel).v;
      }
      else {
        (param_2->Texel).u = (param_3->Texel).u * fVar1;
        fVar1 = fVar1 * (param_3->Texel).v;
      }
      (param_2->Texel).v = fVar1;
      lVar2 = lVar2 + -1;
      param_3 = param_3 + 1;
      param_2 = param_2 + 1;
    } while (0 < lVar2);
  }
  return param_4;
}
