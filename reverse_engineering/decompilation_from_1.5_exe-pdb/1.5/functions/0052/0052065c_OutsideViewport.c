/*
 * Entry: 0052065c
 * Name: OutsideViewport
 * Namespace: Global
 * Signature: int OutsideViewport(CAMERA * param_1, VECTOR_3D * param_2, VECTOR_3D * param_3, VECTOR_3D * param_4, VECTOR_3D * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
OutsideViewport(CAMERA *param_1,VECTOR_3D *param_2,VECTOR_3D *param_3,VECTOR_3D *param_4,
               VECTOR_3D *param_5)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  
  if (TerrainView.Current_View == 0) {
    fVar1 = param_2->y * param_1->View_Volume[0].surf_normal.y +
            param_2->z * param_1->View_Volume[0].surf_normal.z +
            param_1->View_Volume[0].surf_normal.x * param_2->x;
    fVar2 = param_2->x * param_1->View_Volume[1].surf_normal.x +
            param_1->View_Volume[1].surf_normal.z * param_2->z +
            param_1->View_Volume[1].surf_normal.y * param_2->y;
    if ((((uint)fVar1 & 0x80000000) == 0) && (((uint)fVar2 & 0x80000000) == 0)) {
      uVar4 = (uint)(TerrainVisibility2 - (param_2->x * param_2->x + param_2->z * param_2->z)) >>
              0x1f;
    }
    else if (((int)((uint)(param_5->y * param_1->View_Volume[0].surf_normal.y +
                          param_1->View_Volume[0].surf_normal.x * param_5->x +
                          param_1->View_Volume[0].surf_normal.z * param_5->z) &
                    (uint)(param_1->View_Volume[0].surf_normal.x * param_4->x +
                          param_4->y * param_1->View_Volume[0].surf_normal.y +
                          param_1->View_Volume[0].surf_normal.z * param_4->z) &
                    (uint)(param_3->y * param_1->View_Volume[0].surf_normal.y +
                          param_1->View_Volume[0].surf_normal.x * param_3->x +
                          param_3->z * param_1->View_Volume[0].surf_normal.z) & (uint)fVar1) < 0) ||
            ((int)((uint)(param_1->View_Volume[1].surf_normal.z * param_5->z +
                         param_1->View_Volume[1].surf_normal.x * param_5->x +
                         param_1->View_Volume[1].surf_normal.y * param_5->y) &
                   (uint)(param_1->View_Volume[1].surf_normal.z * param_4->z +
                         param_1->View_Volume[1].surf_normal.x * param_4->x +
                         param_1->View_Volume[1].surf_normal.y * param_4->y) &
                   (uint)(param_1->View_Volume[1].surf_normal.y * param_3->y +
                         param_3->z * param_1->View_Volume[1].surf_normal.z +
                         param_3->x * param_1->View_Volume[1].surf_normal.x) & (uint)fVar2) < 0)) {
      uVar4 = 1;
    }
    else {
      uVar4 = (uint)(TerrainVisibility2 - (param_2->x * param_2->x + param_2->z * param_2->z)) >>
              0x1f;
    }
    return uVar4;
  }
  iVar3 = OutsideViewportTB(param_1,param_2,param_3,param_4,param_5);
  return iVar3;
}
