/*
 * Entry: 004743a4
 * Name: HeatSigTest
 * Namespace: Global
 * Signature: _OBJ76 * HeatSigTest(VECTOR_3D param_1, VECTOR_3D param_2, _OBJ76 * param_3, _OBJ76 * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl HeatSigTest(VECTOR_3D param_1,VECTOR_3D param_2,_OBJ76 *param_3,_OBJ76 *param_4)

{
  tagENTITY *ptVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  VECTOR_3D VVar5;
  POINT_VEL *pPVar6;
  SPHERE *pSVar7;
  int iVar8;
  float *pfVar9;
  float fVar10;
  POINT_VEL local_64;
  float local_4c [6];
  SPHERE local_34;
  float local_24;
  float local_20;
  float local_1c;
  float fStack_18;
  double local_14;
  _OBJ76 *local_c;
  wrap_struct *local_8;
  
  local_c = (_OBJ76 *)0x0;
  local_14 = 422500.0;
  for (local_8 = DynamicEnts; local_8 != (wrap_struct *)0x0; local_8 = local_8->next) {
    ptVar1 = local_8->ptr;
    if (ptVar1->obj76 != param_4) {
      pPVar6 = PositionVelocity(&local_64,ptVar1);
      pfVar9 = local_4c;
      for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
        *pfVar9 = (pPVar6->p).x;
        pPVar6 = (POINT_VEL *)&(pPVar6->p).y;
        pfVar9 = pfVar9 + 1;
      }
      VVar5.y = local_4c[1];
      VVar5.x = local_4c[0];
      VVar5.z = local_4c[2];
      fVar10 = Dist3D_Squared(param_1,VVar5);
      if ((fVar10 <= 422500.0) && (iVar8 = valid_heat_target(param_3,ptVar1->obj76), iVar8 != 0)) {
        pSVar7 = Entity_WorldSphere(&local_34,ptVar1);
        local_24 = (pSVar7->origin).x;
        local_20 = (pSVar7->origin).y;
        local_1c = (pSVar7->origin).z;
        fStack_18 = pSVar7->radius;
        fVar10 = local_24 - param_1.x;
        fVar4 = local_20 - param_1.y;
        fVar3 = local_1c - param_1.z;
        fVar2 = param_2.x * fVar10 + param_2.y * fVar4 + param_2.z * fVar3;
        if ((0.0 <= fVar2) &&
           ((fVar10 = fVar3 * fVar3 + fVar10 * fVar10 + fVar4 * fVar4,
            fVar10 * 0.8830222 < fVar2 * fVar2 && (fVar10 < (float)local_14)))) {
          local_c = ptVar1->obj76;
          local_14 = (double)fVar10;
        }
      }
    }
  }
  return local_c;
}
