/*
 * Entry: 004f04ab
 * Name: Camera_Bounding_Sphere_Test
 * Namespace: Global
 * Signature: long Camera_Bounding_Sphere_Test(CAMERA * param_1, VECTOR_3D * param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Camera_Bounding_Sphere_Test(CAMERA *param_1,VECTOR_3D *param_2,float param_3)

{
  float fVar1;
  long lVar2;
  float *pfVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  fVar1 = param_1->View_Volume[5].surf_normal.z * param_2->z + param_1->View_Volume[5].dist;
  uVar5 = (uint)(fVar1 - param_3) >> 0x1f | (uint)(fVar1 + param_3) >> 0x1e & 2;
  if (uVar5 == 3) {
    lVar2 = 1;
  }
  else {
    fVar1 = param_1->View_Volume[4].surf_normal.z * param_2->z + param_1->View_Volume[4].dist;
    uVar6 = (uint)(fVar1 - param_3) >> 0x1f | (uint)(fVar1 + param_3) >> 0x1e & 2;
    if (uVar6 == 3) {
      lVar2 = 1;
    }
    else {
      uVar5 = uVar5 | uVar6;
      iVar4 = 0;
      pfVar3 = &param_1->View_Volume[0].surf_normal.y;
      do {
        fVar1 = *pfVar3 * param_2->y +
                pfVar3[1] * param_2->z + ((VECTOR_3D *)(pfVar3 + -1))->x * param_2->x;
        uVar6 = (uint)(fVar1 - param_3 * 1.1) >> 0x1f | (uint)(fVar1 + param_3 * 1.1) >> 0x1e & 2;
        if (uVar6 == 3) {
          return 1;
        }
        uVar5 = uVar5 | uVar6;
        iVar4 = iVar4 + 1;
        pfVar3 = pfVar3 + 4;
      } while (iVar4 < 4);
      lVar2 = -uVar5;
    }
  }
  return lVar2;
}
