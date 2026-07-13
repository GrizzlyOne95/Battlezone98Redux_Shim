/*
 * Entry: 004d33ea
 * Name: ScreenToWorld
 * Namespace: Global
 * Signature: VECTOR_3D * ScreenToWorld(VECTOR_3D * __return_storage_ptr__, tagPOINT param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
ScreenToWorld(VECTOR_3D *__return_storage_ptr__,tagPOINT param_1,CAMERA *param_2)

{
  double dVar1;
  double dVar2;
  double dVar3;
  float fVar4;
  VECTOR_3D VVar5;
  float *in_EAX;
  VECTOR_3D *pVVar6;
  int iVar7;
  double *pdVar8;
  float *pfVar9;
  VECTOR_3D_LONG in_stack_ffffff90;
  float fVar10;
  float fVar11;
  float fVar12;
  float *pfVar13;
  VECTOR_3D local_20;
  VECTOR_3D local_14;
  float local_8;
  
  dVar1 = *(double *)(in_EAX + 0x58);
  dVar2 = *(double *)(in_EAX + 0x5a);
  dVar3 = *(double *)(in_EAX + 0x5c);
  local_14.x = ((float)param_1.x - *in_EAX) / in_EAX[2];
  local_14.y = ((float)param_1.y - in_EAX[1]) / in_EAX[3];
  local_14.z = 1.0;
  pVVar6 = Vector_Unrotate(&local_20,&local_14,(MAT_3D *)(in_EAX + 0x10));
  fVar10 = pVVar6->x;
  fVar11 = pVVar6->y;
  fVar12 = pVVar6->z;
  fVar4 = -1.0 / fVar11;
  pVVar6 = (VECTOR_3D *)0x0;
  pfVar13 = &local_8;
  pdVar8 = (double *)(in_EAX + 0x58);
  pfVar9 = (float *)&stack0xffffff90;
  local_14.x = fVar10;
  local_14.y = fVar11;
  local_14.z = fVar12;
  for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
    *pfVar9 = *(float *)pdVar8;
    pdVar8 = (double *)((int)pdVar8 + 4);
    pfVar9 = pfVar9 + 1;
  }
  local_8 = fVar4 * (float)dVar2;
  VVar5.y = fVar11;
  VVar5.x = fVar10;
  VVar5.z = fVar12;
  Terrain_GetIntersection(in_stack_ffffff90,VVar5,pfVar13,pVVar6);
  __return_storage_ptr__->x = local_8 * local_14.x + (float)dVar1;
  __return_storage_ptr__->y = local_8 * local_14.y + (float)dVar2;
  __return_storage_ptr__->z = local_8 * local_14.z + (float)dVar3;
  return __return_storage_ptr__;
}
