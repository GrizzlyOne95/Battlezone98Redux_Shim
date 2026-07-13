/*
 * Entry: 00407c68
 * Name: DistToOffBlocked
 * Namespace: Global
 * Signature: float DistToOffBlocked(VECTOR_3D_LONG * param_1, VECTOR_3D * param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl DistToOffBlocked(VECTOR_3D_LONG *param_1,VECTOR_3D *param_2,float param_3)

{
  VECTOR_3D VVar1;
  int iVar2;
  undefined4 *puVar3;
  VECTOR_3D_LONG in_stack_ffffffc8;
  float fVar4;
  float fVar5;
  float fVar6;
  code *pcVar7;
  float *pfVar8;
  
  pfVar8 = &param_3;
  pcVar7 = OffBlockChange;
  fVar4 = param_2->x;
  fVar5 = param_2->y;
  fVar6 = param_2->z;
  puVar3 = (undefined4 *)&stack0xffffffc8;
  for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *(undefined4 *)&param_1->x;
    param_1 = (VECTOR_3D_LONG *)((int)&param_1->x + 4);
    puVar3 = puVar3 + 1;
  }
  VVar1.y = fVar5;
  VVar1.x = fVar4;
  VVar1.z = fVar6;
  Terrain_FindChange(in_stack_ffffffc8,VVar1,pcVar7,pfVar8);
  return param_3;
}
