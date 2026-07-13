/*
 * Entry: 005419be
 * Name: D3D_Clip_3D_Project_Only
 * Namespace: Global
 * Signature: long D3D_Clip_3D_Project_Only(CAMERA * param_1, POINT_3D * param_2, POINT_3D * param_3, long param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
D3D_Clip_3D_Project_Only
          (CAMERA *param_1,POINT_3D *param_2,POINT_3D *param_3,long param_4,long param_5)

{
  float fVar1;
  int iVar2;
  
  for (iVar2 = param_4; 0 < iVar2; iVar2 = iVar2 + -1) {
    fVar1 = 1.0 / (param_3->Vector).z;
    (param_2->Vector).x = (param_3->Vector).x * param_1->Const_x * fVar1 + param_1->Orig_x;
    (param_2->Vector).y = (param_3->Vector).y * fVar1 * param_1->Const_y + param_1->Orig_y;
    (param_2->Vector).z = fVar1;
    (param_2->Texel).u = (param_3->Texel).u;
    (param_2->Texel).v = (param_3->Texel).v;
    (param_2->Texel).field2_0x8 = (param_3->Texel).field2_0x8;
    param_2 = param_2 + 1;
    param_3 = param_3 + 1;
  }
  return param_4;
}
