/*
 * Entry: 0052038b
 * Name: OutsideViewportTB
 * Namespace: Global
 * Signature: int OutsideViewportTB(CAMERA * param_1, VECTOR_3D * param_2, VECTOR_3D * param_3, VECTOR_3D * param_4, VECTOR_3D * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
OutsideViewportTB(CAMERA *param_1,VECTOR_3D *param_2,VECTOR_3D *param_3,VECTOR_3D *param_4,
                 VECTOR_3D *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar1 = param_2->x * param_1->View_Volume[0].surf_normal.x +
          param_2->y * param_1->View_Volume[0].surf_normal.y +
          param_2->z * param_1->View_Volume[0].surf_normal.z;
  fVar2 = param_1->View_Volume[1].surf_normal.y * param_2->y +
          param_2->x * param_1->View_Volume[1].surf_normal.x +
          param_1->View_Volume[1].surf_normal.z * param_2->z;
  fVar3 = param_2->x * param_1->View_Volume[2].surf_normal.x +
          param_1->View_Volume[2].surf_normal.z * param_2->z +
          param_1->View_Volume[2].surf_normal.y * param_2->y;
  fVar4 = param_2->y * param_1->View_Volume[3].surf_normal.y +
          param_1->View_Volume[3].surf_normal.z * param_2->z +
          param_1->View_Volume[3].surf_normal.x * param_2->x;
  if ((((((uint)fVar1 & 0x80000000) == 0) && (((uint)fVar2 & 0x80000000) == 0)) &&
      (((uint)fVar3 & 0x80000000) == 0)) && (((uint)fVar4 & 0x80000000) == 0)) {
    return (uint)(TerrainVisibility2 - (param_2->x * param_2->x + param_2->z * param_2->z)) >> 0x1f;
  }
  if (((-1 < (int)((uint)(param_1->View_Volume[0].surf_normal.x * param_5->x +
                         param_5->z * param_1->View_Volume[0].surf_normal.z +
                         param_5->y * param_1->View_Volume[0].surf_normal.y) &
                   (uint)(param_4->z * param_1->View_Volume[0].surf_normal.z +
                         param_1->View_Volume[0].surf_normal.x * param_4->x +
                         param_4->y * param_1->View_Volume[0].surf_normal.y) &
                   (uint)(param_1->View_Volume[0].surf_normal.z * param_3->z +
                         param_3->y * param_1->View_Volume[0].surf_normal.y +
                         param_3->x * param_1->View_Volume[0].surf_normal.x) & (uint)fVar1)) &&
      (-1 < (int)((uint)(param_5->z * param_1->View_Volume[1].surf_normal.z +
                        param_5->x * param_1->View_Volume[1].surf_normal.x +
                        param_5->y * param_1->View_Volume[1].surf_normal.y) &
                  (uint)(param_4->z * param_1->View_Volume[1].surf_normal.z +
                        param_4->x * param_1->View_Volume[1].surf_normal.x +
                        param_4->y * param_1->View_Volume[1].surf_normal.y) &
                  (uint)(param_1->View_Volume[1].surf_normal.z * param_3->z +
                        param_3->x * param_1->View_Volume[1].surf_normal.x +
                        param_3->y * param_1->View_Volume[1].surf_normal.y) & (uint)fVar2))) &&
     ((-1 < (int)((uint)(param_1->View_Volume[2].surf_normal.y * param_5->y +
                        param_1->View_Volume[2].surf_normal.x * param_5->x +
                        param_1->View_Volume[2].surf_normal.z * param_5->z) &
                  (uint)(param_1->View_Volume[2].surf_normal.y * param_4->y +
                        param_1->View_Volume[2].surf_normal.z * param_4->z +
                        param_1->View_Volume[2].surf_normal.x * param_4->x) &
                  (uint)(param_1->View_Volume[2].surf_normal.y * param_3->y +
                        param_1->View_Volume[2].surf_normal.z * param_3->z +
                        param_3->x * param_1->View_Volume[2].surf_normal.x) & (uint)fVar3) &&
      (-1 < (int)((uint)(param_1->View_Volume[3].surf_normal.x * param_5->x +
                        param_5->y * param_1->View_Volume[3].surf_normal.y +
                        param_1->View_Volume[3].surf_normal.z * param_5->z) &
                  (uint)(param_1->View_Volume[3].surf_normal.x * param_4->x +
                        param_4->y * param_1->View_Volume[3].surf_normal.y +
                        param_1->View_Volume[3].surf_normal.z * param_4->z) &
                  (uint)(param_1->View_Volume[3].surf_normal.x * param_3->x +
                        param_3->y * param_1->View_Volume[3].surf_normal.y +
                        param_1->View_Volume[3].surf_normal.z * param_3->z) & (uint)fVar4))))) {
    return (uint)(TerrainVisibility2 - (param_2->x * param_2->x + param_2->z * param_2->z)) >> 0x1f;
  }
  return 1;
}
