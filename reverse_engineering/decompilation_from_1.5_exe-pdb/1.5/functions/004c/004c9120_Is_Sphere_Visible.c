/*
 * Entry: 004c9120
 * Name: Is_Sphere_Visible
 * Namespace: Global
 * Signature: bool Is_Sphere_Visible(CAMERA * param_1, SPHERE * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl Is_Sphere_Visible(CAMERA *param_1,SPHERE *param_2)

{
  float *pfVar1;
  int iVar2;
  
  if ((-1 < (int)(param_1->View_Volume[5].surf_normal.z * (param_2->origin).z +
                 param_1->View_Volume[5].dist)) &&
     (-1 < (int)(param_1->View_Volume[4].surf_normal.z * (param_2->origin).z +
                param_1->View_Volume[4].dist))) {
    iVar2 = 0;
    pfVar1 = &param_1->View_Volume[0].surf_normal.y;
    do {
      if ((int)(*pfVar1 * (param_2->origin).y +
                ((VECTOR_3D *)(pfVar1 + -1))->x * (param_2->origin).x +
                pfVar1[1] * (param_2->origin).z + param_2->radius) < 0) {
        return false;
      }
      iVar2 = iVar2 + 1;
      pfVar1 = pfVar1 + 4;
    } while (iVar2 < 4);
    return true;
  }
  return false;
}
